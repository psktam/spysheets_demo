#ifndef CELL_VALUE_H
#define CELL_VALUE_H
#include <cstdint>
#include <string>

enum CellType {
    Integer,
    Real,
    String,
    Empty
};


class CellValue {
    private:
        CellType type;
        void* value;

    public:
        // Because of the way we expect these to be used, everything this thing 
        // wraps needs to be created on the heap, so we expect pointers for 
        // all the constructors defined here. There is probably a smarter way to 
        // do this with templates. But I stupid.
        CellValue();
        CellValue(int64_t*);
        CellValue(double*);
        CellValue(std::string*);

        bool is_empty();
        CellType get_type();
        int64_t get_int();
        double get_float();
        std::string get_string();

        void print_self();
};

#endif  // CELL_VALUE_H