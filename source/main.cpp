#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include "actions.h"
#include "cell_value.h"
#include "cell_array.h"
#include "coordinates.h"
#include "engine_client.h"
#include "table_types.h"
#include "tables.h"


int main(int argc, char* argv[]) {
    engine_client::EngineClient client_connection = engine_client::EngineClient(
        argv[1],
        atoi(argv[2])
    );

    // Okay, now we're starting to make and populate the table.
    Table demo_table = Table();
    CellArray<CellValue> direct_input_array = CellArray<CellValue>(5, 3);
    direct_input_array.insert_at(0, 0, CellValue("Item"));
    direct_input_array.insert_at(1, 0, CellValue("toothbrush"));
    direct_input_array.insert_at(2, 0, CellValue("comb"));
    direct_input_array.insert_at(3, 0, CellValue("mirror"));
    direct_input_array.insert_at(4, 0, CellValue("toilet paper"));
    direct_input_array.insert_at(0, 1, CellValue("Unit Price"));

    direct_input_array.insert_at(0, 1, CellValue("Unit Price"));
    direct_input_array.insert_at(1, 1, CellValue(1.00));
    direct_input_array.insert_at(2, 1, CellValue(5.04));
    direct_input_array.insert_at(3, 1, CellValue(100000.30));
    direct_input_array.insert_at(4, 1, CellValue(1241241242134.0));

    direct_input_array.insert_at(0, 2, CellValue(std::string("Quantity")));
    direct_input_array.insert_at(1, 2, CellValue(int64_t(1)));
    direct_input_array.insert_at(2, 2, CellValue(int64_t(5)));
    direct_input_array.insert_at(3, 2, CellValue(int64_t(10)));
    direct_input_array.insert_at(4, 2, CellValue(int64_t(12)));

    auto throwaway_inputs = std::vector<Argument>({});

    Operation* op1 = new Operation(
        demo_table.get_op_id(),
        throwaway_inputs,
        new DirectInputs(direct_input_array),
        new DirectCoordinate(0, 0),
        Corner::upper_left
    );

    Coordinate* sel00 = new OffsetCoordinate(
        new OpCorner(
            op1->op_id,
            Corner::upper_left
        ),
        coord(1, 1)
    );
    Coordinate* sel11 = new OpCorner(
        op1->op_id,
        Corner::lower_right
    );

    std::vector<Argument> op2_inputs({
        Argument("raw_values", sel00, sel11)
    });
    Operation* op2 = new Operation(
        demo_table.get_op_id(),
        op2_inputs,
        new EngineAction(client_connection, "import numpy as np\nvalues = np.array(raw_values)\nreturn np.dot(values[:, 0], values[:, 1])"),
        new DirectCoordinate(5, 0),
        Corner::upper_left
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

    std::cout << "Now inserting engine action" << std::endl;
    demo_table.insert_operation_at_current_locatiton(op2);

    std::cout << "Made it to the end" << std::endl;

    client_connection.close_connection();
    return 0;
}
