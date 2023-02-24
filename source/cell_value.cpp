#include <iostream>
#include <stdexcept>
#include "cell_value.h"

CellValue::CellValue(int64_t* input) {
    value = (void*) input;
    type = CellType::Integer;
}

CellValue::CellValue(double* input) {
    value = (void*) input;
    type = CellType::Real;
}

CellValue::CellValue(std::string* input) {
    value = (void*) input;
    type = CellType::String;
}

CellType CellValue::get_type() {
    return type;
}

int64_t CellValue::get_int() {
    if (type == CellType::Integer) {
        return *(int64_t*)value;
    }

    throw std::domain_error("Trying to resolve integer value for non-integer type");
}

double CellValue::get_float() {
    if (type == CellType::Real) {
        return *(double*)value;
    }

    throw std::domain_error("Trying to resolve floating-point value for non floating-point type");
}

std::string CellValue::get_string() {
    if (type == CellType::String) {
        return *(std::string*)value;
    }

    throw std::domain_error("Trying to resolve string value for non-string data.");
}

void CellValue::print_self() {
    if (type == CellType::Integer) {
        std::cout << get_int();
    }
    else if (type == CellType::Real) {
        std::cout << get_float();
    }
    else {
        std::cout << get_string();
    }
}