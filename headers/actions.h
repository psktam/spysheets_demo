#ifndef ACTIONS_H
#define ACTIONS_H
#include <string>
#include <tuple>
#include <vector>
#include "cell_array.h"
#include "table_types.h"

// The arguments into an action are internally represented as a list of 
// 2-element tuples, where the first element is the name of the argument, and 
// the second element is the array-like object that represents the actual values
// being provided as the argument.
typedef std::vector<std::tuple<std::string, CellArray<CellValue>>> arg_list_t;


class Action {
    public:
        /**
         * Since we only expect the Table class to use the results of actions,
         * I'm going to roll the dice and just return raw stuff. The Table 
         * should wrap all of these usages in unique_ptr.
        */
        virtual CellArray<CellValue> run(const arg_list_t&) = 0;
};


class DirectInputs : public Action {
    private:
        CellArray<CellValue> values;

    public:
        DirectInputs(CellArray<CellValue>);
        CellArray<CellValue> run(const arg_list_t&);
};

// Other types of actions basically involve passing the data to the 
// python kernel and bringing the data back here. We're going to try doing this 
// with protobuf and opening up a TCP/IP connection.
class EngineAction : public Action {
    private:
        std::string script_contents;
    public:
        EngineAction(std::string);
        CellArray<CellValue> run(const arg_list_t&);
};


#endif  // ACTIONS_H