#include <fstream>
#include <iostream>
#include <tuple>
#include "actions.h"
#include "protocols/operations.pb.h"
#include "table_types.h"


/** 
 * Definitions for DirectInputs
*/
DirectInputs::DirectInputs(CellArray& _values):values(_values) {
}


CellArray* DirectInputs::run(arg_list_t* realized_inputs) {
    return new CellArray(values);
}


/** 
 * Definitions for Engine-based actions.
*/
EngineAction::EngineAction(std::string _script_contents) {
    script_contents = _script_contents;
}

CellArray* EngineAction::run(arg_list_t* realized_inputs) {
    operations::ActionSpecification action;
    action.set_script_contents(script_contents);

    for (auto entry : *realized_inputs) {
        std::string arg_name;
        CellArray* arg_value;
        std::tie(arg_name, arg_value) = entry;

        auto proto_entry = action.add_input_data();
        proto_entry->set_name(arg_name);
        
        // Now fill out the CellArray object. First set number of rows and 
        // columns.
        auto proto_arg_value = proto_entry->mutable_value_array();
        proto_arg_value->set_rows(arg_value->get_rows());
        proto_arg_value->set_cols(arg_value->get_cols());
        
        // Now fill in the internal vector by iterating through each array 
        // element one-by-one. Admittedly, this is rather inelegant. I'm 
        // thinking that these elements should own their own serialization 
        // methods, or they otherwise need to be extracted out of here.

        for (auto r = 0; r < arg_value->get_rows(); r++) {
            for (auto c = 0; c < arg_value->get_cols(); c++) {
                auto proto_arg_value_pointer = proto_arg_value->add_values();
                CellValue* code_value = arg_value->get(r, c);

                if (code_value->get_type() == CellType::Integer) {
                    proto_arg_value_pointer->set_type(operations::CellValue_CellType_Integer);
                    proto_arg_value_pointer->set_int_val(code_value->get_int());
                }
                else if (code_value->get_type() == CellType::Real) {
                    proto_arg_value_pointer->set_type(operations::CellValue_CellType_Real);
                    proto_arg_value_pointer->set_real_val(code_value->get_float());
                }
                else {
                    proto_arg_value_pointer->set_type(operations::CellValue_CellType_String);
                    proto_arg_value_pointer->set_string_val(code_value->get_string());
                }
            }
        }
    }

    // At this point, the message should be fully filled out. Let's stream it to
    // a file and to standard output as well for now and see if we can recover
    // the contents in python.
    std::fstream output("samply_dude.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    if (!action.SerializeToOstream(&output)) {
      std::cerr << "Failed to write to disk." << std::endl;
    }
    action.SerializeToOstream(&std::cout);

    return new CellArray(0, 0);
}