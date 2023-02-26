"""
Contains core functionality for processing messages.
"""
import textwrap

from . import operations_pb2 as opb2


EMPTY_CELL = object()


def is_empty(value):
    return value is EMPTY_CELL


def parse_value(value_struct):
    if value_struct.type == opb2.CellValue.CellType.Integer:
        return value_struct.int_val
    elif value_struct.type == opb2.CellValue.CellType.Real:
        return value_struct.real_val
    elif value_struct.type == opb2.CellValue.CellType.String:
        return value_struct.string_val
    return EMPTY_CELL


# Fun to think about making a betterer slicing object that doesn't restrict 
# people to a row-major format. Maybe like numpy arrays, but native in python.
def parse_argument_struct(raw_string):
    action = opb2.ActionSpecification()
    action.ParseFromString(raw_string)

    to_exec = action.script_contents
    arg_dict = {}

    for raw_data in action.input_data:
        arg_dict[raw_data.name] = []

        index = 0
        for _ in range(raw_data.value_array.rows):
            new_row = []
            arg_dict[raw_data.name].append(new_row)

            for _ in range(raw_data.value_array.cols):
                cell_value = parse_value(raw_data.value_array.values[index])
                new_row.append(cell_value)
                index += 1
    
    return {"script": to_exec, "inputs": arg_dict}


def run_action(arg_struct):
    """
    Runs the specified action and returns the data that the action generated.
    """
    temp_globals = {}
    temp_locals = {}

    contents = textwrap.indent(arg_struct["script"], '    ')
    full_script = "def __throwaway__():\n" + contents + "\n" + "return_value = __throwaway__()"

    print("Executing \n")
    print(full_script)
    print("\nWith:\n")
    print(arg_struct["inputs"])

    exec(full_script, dict(arg_struct["inputs"]), temp_locals)

    return temp_locals["return_value"]
