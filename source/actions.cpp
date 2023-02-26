#include <fstream>
#include <iostream>
#include <tuple>
#include "actions.h"
#include "protocols/operations.pb.h"
#include "table_types.h"


/** 
 * Definitions for DirectInputs
*/
DirectInputs::DirectInputs(CellArray<CellValue> _values): 
    values(_values) {
}

CellArray<CellValue> DirectInputs::run(const arg_list_t& realized_inputs) {
    return values;
}


/** 
 * Definitions for Engine-based actions.
*/
EngineAction::EngineAction(
    engine_client::EngineClient& _client, 
    std::string _script_contents) : client(_client) {
    script_contents = _script_contents;
}

CellArray<CellValue> EngineAction::run(const arg_list_t& realized_inputs) {
    operations::ActionSpecification action;
    action.set_script_contents(script_contents);

    for (auto entry : realized_inputs) {
        std::string arg_name = std::get<0>(entry);
        CellArray<CellValue> arg_value = std::get<1>(entry);

        auto proto_entry = action.add_input_data();
        proto_entry->set_name(arg_name);
        
        // Now fill out the CellArray object. First set number of rows and 
        // columns.
        auto proto_arg_value = proto_entry->mutable_value_array();
        proto_arg_value->set_rows(arg_value.get_rows());
        proto_arg_value->set_cols(arg_value.get_cols());
        
        // Now fill in the internal vector by iterating through each array 
        // element one-by-one. Admittedly, this is rather inelegant. I'm 
        // thinking that these elements should own their own serialization 
        // methods, or they otherwise need to be extracted out of here.

        for (auto r = 0; r < arg_value.get_rows(); r++) {
            for (auto c = 0; c < arg_value.get_cols(); c++) {
                auto proto_arg_value_pointer = proto_arg_value->add_values();
                const CellValue& code_value = arg_value.get(r, c);

                if (code_value.get_type() == CellType::Integer) {
                    proto_arg_value_pointer->set_type(operations::CellValue_CellType_Integer);
                    proto_arg_value_pointer->set_int_val(code_value.get_int());
                }
                else if (code_value.get_type() == CellType::Real) {
                    proto_arg_value_pointer->set_type(operations::CellValue_CellType_Real);
                    proto_arg_value_pointer->set_real_val(code_value.get_float());
                }
                else if (code_value.get_type() == CellType::String){
                    proto_arg_value_pointer->set_type(operations::CellValue_CellType_String);
                    proto_arg_value_pointer->set_string_val(code_value.get_string());
                }
                else if (code_value.is_empty()){
                    proto_arg_value_pointer->set_type(operations::CellValue_CellType_Empty);
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

    client.send_data(action.SerializeAsString());

    return CellArray<CellValue>(0, 0);
}