#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include "actions.h"
#include "cell_value.h"
#include "cell_array.h"
#include "table_types.h"
#include "tables.h"


int main(int argc, char* argv[]) {
    Table table = Table();
    std::cout << "Getting Op ID: " << table.get_op_id() << std::endl;
    std::cout << "Getting Op ID: " << table.get_op_id() << std::endl;

    table.insert(coord(1, 1), new CellValue(new std::string("This is at 1, 1")));
    table.insert(coord(2, 1), new CellValue(new std::string("What is going on with your life?")));
    table.insert(coord(2, 2), new CellValue(new std::string("I don't know man.")));

    table.print_contents();

    CellArray arr = CellArray(10, 10);
    arr.insert_at(0, 0, new CellValue(new std::string("Hi there!")));
    arr.insert_at(9, 0, new CellValue(new std::string("Welcome to the last row!")));
    arr.insert_at(9, 9, new CellValue(new std::string("Farewell from the last row!")));

    CellArray arr2 = CellArray(arr);

    std::cout << arr2.get(0, 0) << std::endl;
    std::cout << arr2.get(9, 0) << std::endl;
    std::cout << arr2.get(9, 9) << std::endl;

    // Let's make an action now and see if it will.. uh, work.
    EngineAction action = EngineAction("return np.array(arg1).dot(arg2)");
    arg_list_t* args = new arg_list_t({});

    CellArray* arg1_val = new CellArray(5, 1);
    arg1_val->insert_at(0, 0, new CellValue(new int64_t(1)));
    arg1_val->insert_at(1, 0, new CellValue(new int64_t(2)));
    arg1_val->insert_at(2, 0, new CellValue(new int64_t(3)));
    arg1_val->insert_at(3, 0, new CellValue(new int64_t(4)));
    arg1_val->insert_at(4, 0, new CellValue(new int64_t(5)));

    std::cout << "Arg1 populated" << std::endl;

    args->push_back(std::tuple<std::string, CellArray*>({"arg1", arg1_val}));

    CellArray* arg2_val = new CellArray(5, 1);
    arg2_val->insert_at(0, 0, new CellValue(new int64_t(10)));
    arg2_val->insert_at(1, 0, new CellValue(new int64_t(20)));
    arg2_val->insert_at(2, 0, new CellValue(new int64_t(50)));
    arg2_val->insert_at(3, 0, new CellValue(new int64_t(30)));
    arg2_val->insert_at(4, 0, new CellValue(new int64_t(50)));

    args->push_back(std::tuple<std::string, CellArray*>({"arg2", arg2_val}));

    std::cout << "Arg2 populated" << std::endl;

    action.run(args);
    return 0;
}
