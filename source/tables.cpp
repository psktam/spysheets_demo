#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>
#include "tables.h"


Table::Table() {
    data = cellmap({});
    op_regions = std::unordered_map<op_id_t, region>({});
    cursor = 0;
    op_sequence = std::vector<op_id_t>();
}


/** 
 * Generates strings that look and smell like UUIDs but probably aren't. This 
 * was ripped from this very helpful SO post: 
 * https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
*/
std::string Table::get_op_id() {
    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    std::string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}


CellValue* Table::get(ord row, ord col) {
    coord coordinate = coord(row, col);
    return get(coordinate);
}


CellValue* Table::get(coord coordinate) {
    return data[coordinate];
}


region Table::get_region(op_id_t op_id) {
    return op_regions[op_id];
}


void Table::insert(coord coordinate, CellValue* value) {
    data.insert({coordinate, value});
}


void Table::insert(ord row, ord col, CellValue* value) {
    data.insert({coord(row, col), value});
}


void Table::pop(ord row, ord col) {
    data.erase(coord(row, col));
}


void Table::print_contents() {
    std::unordered_map<ord, std::vector<ord>*> row_major;
    std::vector<ord> sorted_rows;

    for (auto [key, val] : data) {
        ord row, col;
        std::tie(row, col) = key;

        if (row_major.find(row) == row_major.end()) {
            row_major[row] = new std::vector<ord>({col});
            sorted_rows.push_back(row);
        }
        else {
            row_major[row]->push_back(col);
        }
    }

    std::sort(sorted_rows.begin(), sorted_rows.end());

    // Do another pass now and sort all of the columns.
    for (auto row : sorted_rows) {
        auto columns = row_major[row];
        std::sort(columns->begin(), columns->end());

        // Now we can actually print stuff.
        for (auto col : *columns) {
            std::cout << "(" << row << ", " << col << "): ";
            get(row, col)->print_self();
        }

        // Now that we've printed the row, no need to keep it in memory anymore.
        std::cout << std::endl;
        free(row_major[row]);
    }
}

/**
 * Inserts the provided operation at the current cursor location.
*/
void Table::insert_operation_at_current_locatiton(Operation& op) {
    op_sequence.insert(op_sequence.begin() + cursor, op.op_id);
    op_map[op.op_id] = &op;

    advance_cursor_to_position(cursor + 1);
}

/**
 * This function is ONLY for moving the cursor forward to the given position. 
 * Along the way, it applies every operation it passes.
*/
void Table::advance_cursor_to_position(uint64_t new_position) {
    for (auto index = cursor; index < new_position; index++) {
        auto op_id = op_sequence[index];
        Operation* op = op_map[op_id];
        ord row_offset, col_offset;
        CellArray* outputs = apply_operation(*this, *op, row_offset, col_offset);

        for (ord row = 0; row < outputs->get_rows(); row++) {
            for (ord col = 0; col < outputs->get_cols(); col++) {
                auto output_val = outputs->get(row, col);
                if (!output_val->is_empty()) {
                    insert(row + row_offset, col + col_offset, output_val);
                }
            }
        }

        op_regions[op_id] = region(
            coord(row_offset, col_offset),
            coord(row_offset + outputs->get_rows(), col_offset + outputs->get_cols())
        );
    }

    cursor = new_position;
}

/**
 * This function is ONLY for moving the cursor to a previous position. Doing
 * this will almost always remove data from the table.
*/
void Table::rewind_cursor(uint64_t new_position) {
    for (auto index = cursor - 1; index >= new_position; index--) {
        auto op_id = op_sequence[index];
        region area = op_regions[op_id];

        coord upper_left, lower_right;
        std::tie(upper_left, lower_right) = area;
        ord first_row, first_col, last_row, last_col;
        std::tie(first_row, first_col) = upper_left;
        std::tie(last_row, last_col) = lower_right;

        for (auto row = first_row; row <= last_row; row++) {
            for (auto col = first_col; col <= last_col; col++) {
                CellValue* current_value = get(row, col);
                pop(row, col);
            }
        }

        op_regions.erase(op_id);
        
        if (index == 0) {
            break;  // Underflow issues  otherwise.
        }
    }
    cursor = new_position;
}


/** 
 * Wrapper function for applying an operation in its entirety. It's essentially
 * the pipeline function.
*/
CellArray* apply_operation(Table& table, Operation& op, ord& final_row_offset, ord& final_col_offset) {
    arg_list_t realized_args = arg_list_t({});

    for (auto [arg_name, arg_selection] : *op.input_selections) {
        // Resolve the upper left and lower right corners.
        coord upper_left = std::get<0>(arg_selection)->resolve(table);
        coord lower_right = std::get<1>(arg_selection)->resolve(table);

        // Some stuff to just unpack the coordinate tuples.
        ord first_row, first_col, last_row, last_col;
        std::tie(first_row, first_col) = upper_left;
        std::tie(last_row, last_col) = lower_right;

        // Create the CellArray for this input value.
        CellArray* realized_inputs = new CellArray(
            last_row - first_row + 1,
            last_col - first_col + 1
        );

        // Now populate.
        for (ord row = first_row; row <= last_row; row++) {
            for (ord col = first_col; col <= last_col; col++) {
                realized_inputs->insert_at(
                    row - first_row,
                    col - first_col,
                    table.get(row, col)
                );
            }
        }
        realized_args.push_back({arg_name, realized_inputs});
    }

    CellArray* results = op.action.run(&realized_args);

    // Finally, apply the offset as defined by the output anchor. The whole 
    // point is that if the user specified they want the output to be anchored
    // on its lower left corner, that means the lower left corner of the output
    // will be positioned at the coordinate specified in output_anchor.
    // This is so fucking ugly. I suck at C++.
    coord base_anchor = std::get<0>(op.output_anchor)->resolve(table);
    Corner anchor_corner = std::get<1>(op.output_anchor);
    ord row_offset, col_offset;

    if (anchor_corner == Corner::upper_left) {
        row_offset = 0;
        col_offset = 0;
    }
    else if (anchor_corner == Corner::upper_right) {
        row_offset = 0;
        col_offset = results->get_cols() - 1;
    }
    else if (anchor_corner == Corner::lower_left) {
        row_offset = results->get_rows() - 1;
        col_offset = 0;
    }
    else /* lower_right */ {
        row_offset = results->get_rows() - 1;
        col_offset = results->get_cols() - 1;
    }

    final_row_offset = std::get<0>(base_anchor) - row_offset;
    final_col_offset = std::get<1>(base_anchor) - col_offset;

    return results;
}
