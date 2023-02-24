#include <algorithm>
#include <iostream>
#include <random>
#include <string>
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
            std::cout << std::endl;
        }

        // Now that we've printed the row, no need to keep it in memory anymore.
        free(row_major[row]);
    }
}