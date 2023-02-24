#include "cell_array.h"

CellArray::CellArray(ord _rows, ord _cols) {
    rows = _rows;
    cols = _cols;
    contents = std::vector<CellValue*>(rows * cols);
}

void CellArray::insert_at(ord row, ord col, CellValue* value) {
    ord index = (cols * row) + col;
    contents[index] = value;
}

void CellArray::insert_at(coord coordinate, CellValue* value) {
    ord row, col;
    std::tie(row, col) = coordinate;

    insert_at(row, col, value);
}

CellValue* CellArray::get(ord row, ord col) {
    ord index = (row * cols) + col;
    return contents[index];
}

CellValue* CellArray::get(coord coordinate) {
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