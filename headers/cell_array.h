#ifndef CELL_ARRAY_H
#define CELL_ARRAY_H
#include <string>
#include <vector>
#include "table_types.h"


class CellArray {
    private:
        ord rows;
        ord cols;
        std::vector<std::string> contents;

    public:
        CellArray(ord _rows, ord _cols);
        void insert_at(ord, ord, std::string);
        void insert_at(coord, std::string);

        std::string get(ord, ord);
        std::string get(coord);

        ord get_rows();
        ord get_cols();
};

#endif  // CELL_ARRAY_H