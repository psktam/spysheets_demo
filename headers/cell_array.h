#ifndef CELL_ARRAY_H
#define CELL_ARRAY_H
#include <string>
#include <vector>
#include "cell_value.h"
#include "table_types.h"

template <class T>
class CellArray {
    private:
        ord rows;
        ord cols;
        std::vector<T> contents;

    public:
        CellArray(ord _rows, ord _cols) {
            rows = _rows;
            cols = _cols;
            contents = std::vector<T>(rows * cols);
        };

        void insert_at(ord row, ord col, const T value) {
            ord index = (cols * row) + col;
            contents[index] = value;
        };

        void insert_at(coord coordinate, const T value) {
            ord row, col;
            std::tie(row, col) = coordinate;

            insert_at(row, col, value);
        };

        const T get(ord row, ord col) const {
            ord index = (row * cols) + col;
            return contents[index];
        };

        const T get(coord coordinate) const {
            ord row, col;
            std::tie(row, col) = coordinate;
            return get(row, col);
        };

        ord get_rows() const {
            return rows;
        };
        ord get_cols() const {
            return cols;
        };
};

#endif  // CELL_ARRAY_H