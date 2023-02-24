#include "cell_array.h"

CellArray::CellArray(ord _rows, ord _cols) {
    rows = _rows;
    cols = _cols;
    contents = std::vector<std::string>(rows * cols);
}

void CellArray::insert_at(ord row, ord col, std::string value) {
    ord index = (cols * row) + col;
    contents[index] = value;
}

void CellArray::insert_at(coord coordinate, std::string value) {
    ord row, col;
    std::tie(row, col) = coordinate;

    insert_at(row, col, value);
}

std::string CellArray::get(ord row, ord col) {
    ord index = (row * cols) + col;
    return contents[index];
}

std::string CellArray::get(coord coordinate) {
    ord row, col;
    std::tie(row, col) = coordinate;
    return get(row, col);
}

ord CellArray::get_rows() {
    return rows;
}

ord CellArray::get_cols() {
    return cols;
}