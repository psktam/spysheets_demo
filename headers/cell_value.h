#ifndef CELL_VALUE_H
#define CELL_VALUE_H
#include <cstdint>
#include <memory>
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
        CellValue(const CellValue&);
        CellValue(int64_t);
        CellValue(double);
        CellValue(std::string);
        ~CellValue();

        CellValue& operator=(const CellValue&);

        bool is_empty() const;
        CellType get_type() const;
        int64_t get_int() const;
        double get_float() const;
        std::string get_string() const;

        void print_self() const;
};

#endif  // CELL_VALUE_H