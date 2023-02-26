#include <iostream>
#include <stdexcept>
#include "cell_value.h"


CellValue::CellValue() {
    type = CellType::Empty;
}


CellValue::CellValue(const CellValue& to_copy) {
    type = to_copy.get_type();

    if (type == CellType::Integer) {
        value = (void*)(new int64_t(to_copy.get_int()));
    }
    else if (type == CellType::Real) {
        value = (void*)(new double(to_copy.get_float()));
    }
    else if (type == CellType::String) {
        value = (void*)(new std::string(to_copy.get_string()));
    }
}


CellValue::CellValue(int64_t input) {
    value = (void*)(new int64_t(input));
    type = CellType::Integer;
}

CellValue::CellValue(double input) {
    value = (void*)(new double(input));
    type = CellType::Real;
}

CellValue::CellValue(std::string input) {
    value = static_cast<void*>(new std::string(input));
    type = CellType::String;
}

CellValue& CellValue::operator=(const CellValue &other) {
    if (this == &other) {
        return *this;
    }

    // Erase whatever data I'm currently holding.
    if (type == CellType::Integer) {
        delete ((int64_t*)value);
    }
    else if (type == CellType::Real) {
        delete ((double*)value);
    }
    else if (type == CellType::String) {
        delete ((std::string*)value);
    }

    // Now bring in the data from the other person.
    type = other.get_type();
    if (type == CellType::Integer) {
        value = new int64_t(other.get_int());
    }
    else if (type == CellType::Real) {
        value = new double(other.get_float());
    }
    else if (type == CellType::String) {
        value = new std::string(other.get_string());
    }

    return *this;
}

CellValue::~CellValue() {
    if (type == CellType::Integer) {
        delete ((int64_t*)value);
    }
    else if (type == CellType::Real) {
        delete ((double*)value);
    }
    else if (type == CellType::String) {
        delete ((std::string*)value);
    }
}

CellType CellValue::get_type() const {
    return type;
}

bool CellValue::is_empty() const {
    return type == CellType::Empty;
}

int64_t CellValue::get_int() const {
    if (type == CellType::Integer) {
        return *(int64_t*)value;
    }

    throw std::domain_error("Trying to resolve integer value for non-integer type");
}

double CellValue::get_float() const {
    if (type == CellType::Real) {
        return *(double*)value;
    }

    throw std::domain_error("Trying to resolve floating-point value for non floating-point type");
}

std::string CellValue::get_string() const {
    if (type == CellType::String) {
        std::string recovered = *(static_cast<std::string*>(value));
        return recovered;
    }

    throw std::domain_error("Trying to resolve string value for non-string data.");
}

void CellValue::print_self() const {
    if (type == CellType::Integer) {
        std::cout << get_int();
    }
    else if (type == CellType::Real) {
        std::cout << get_float();
    }
    else if (type == CellType::String){
        std::cout << get_string();
    }
}