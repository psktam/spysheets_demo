#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include "actions.h"
#include "cell_value.h"
#include "cell_array.h"
#include "coordinates.h"
#include "table_types.h"
#include "tables.h"


int main(int argc, char* argv[]) {
    // Okay, now we're starting to make and populate the table.
    Table demo_table = Table();
    CellArray direct_input_array = CellArray(5, 3);
    direct_input_array.insert_at(0, 0, new CellValue(new std::string("Item")));
    direct_input_array.insert_at(1, 0, new CellValue(new std::string("toothbrush")));
    direct_input_array.insert_at(2, 0, new CellValue(new std::string("comb")));
    direct_input_array.insert_at(3, 0, new CellValue(new std::string("mirror")));
    direct_input_array.insert_at(4, 0, new CellValue(new std::string("toilet paper")));
    direct_input_array.insert_at(0, 1, new CellValue(new std::string("Unit Price")));

    direct_input_array.insert_at(0, 1, new CellValue(new std::string("Unit Price")));
    direct_input_array.insert_at(1, 1, new CellValue(new double(1.00)));
    direct_input_array.insert_at(2, 1, new CellValue(new double(5.04)));
    direct_input_array.insert_at(3, 1, new CellValue(new double(100000.30)));
    direct_input_array.insert_at(4, 1, new CellValue(new double(1241241242134.0)));

    direct_input_array.insert_at(0, 2, new CellValue(new std::string("Quantity")));
    direct_input_array.insert_at(1, 2, new CellValue(new int64_t(1)));
    direct_input_array.insert_at(2, 2, new CellValue(new int64_t(5)));
    direct_input_array.insert_at(3, 2, new CellValue(new int64_t(10)));
    direct_input_array.insert_at(4, 2, new CellValue(new int64_t(12)));
    
    auto action1 = DirectInputs(direct_input_array);
    auto output_anchor_coordinate = DirectCoordinate(0, 0);
    auto throwaway_inputs = new std::unordered_map<std::string, Selection>();
    Operation op1 = Operation(
        demo_table.get_op_id(),
        throwaway_inputs,
        action1,
        std::tuple<Coordinate*, Corner>(&output_anchor_coordinate, Corner::upper_left)
    );

    std::cout << "Inserting direct input" << std::endl;
    demo_table.insert_operation_at_current_locatiton(op1);
    demo_table.print_contents();

    std::cout << "Now rewinding to the beginning" << std::endl;
    demo_table.rewind_cursor(0);
    demo_table.print_contents();

    std::cout << "Rolling back forward" << std::endl;
    demo_table.advance_cursor_to_position(1);
    demo_table.print_contents();
    return 0;
}
