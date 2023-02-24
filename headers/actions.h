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
typedef std::vector<std::tuple<std::string, CellArray*>> arg_list_t;


class Action {
    public:
        virtual CellArray* run(arg_list_t*) = 0;
};


class DirectInputs : public Action {
    private:
        CellArray& values;

    public:
        DirectInputs(CellArray&);
        CellArray* run(arg_list_t*);
};

// Other types of actions basically involve passing the data to the 
// python kernel and bringing the data back here. 
// In python, this would be just serializing stuff as JSON, passing to python,
// and getting the stuff back here. Pretty inefficient for large arrays, 
// however.
class EngineAction : public Action {
    private:
        std::string script_contents;
    public:
        EngineAction(std::string);
        CellArray* run(arg_list_t*);
};


#endif  // ACTIONS_H