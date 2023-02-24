#ifndef CELL_ARRAY_H
#define CELL_ARRAY_H
#include <string>
#include <vector>
#include "cell_value.h"
#include "table_types.h"


class CellArray {
    private:
        ord rows;
        ord cols;
        std::vector<CellValue*> contents;

    public:
        CellArray(ord _rows, ord _cols);
        void insert_at(ord, ord, CellValue*);
        void insert_at(coord, CellValue*);

        CellValue* get(ord, ord);
        CellValue* get(coord);

        ord get_rows();
        ord get_cols();
};

#endif  // CELL_ARRAY_H