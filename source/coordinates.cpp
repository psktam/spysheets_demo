#include <tuple>
#include "coordinates.h"

/**
 * Definitions for DirectCoordinate.
*/
DirectCoordinate::DirectCoordinate(ord _row, ord _col) {
    row = _row;
    col = _col;
}

coord DirectCoordinate::resolve(Table& table) {
    return coord(row, col);
}


/** 
 * Definitions for OpCorner
*/
OpCorner::OpCorner(op_id_t _op_id, Corner _corner) {
    op_id = _op_id;
    corner = _corner;
}


coord OpCorner::resolve(Table& table) {
    coord upper_left, lower_right;
    std::tie(upper_left, lower_right) = table.get_region(op_id);
    ord first_row, first_col, last_row, last_col;
    std::tie(first_row, first_col) = upper_left;
    std::tie(last_row, last_col) = lower_right;

    if (corner == Corner::upper_left) {
        return coord(first_row, first_col);
    }
    else if (corner == Corner::upper_right) {
        return coord(first_row, last_col);
    }
    else if (corner == Corner::lower_left) {
        return coord(last_row, first_col);
    }
    else {
        return coord(last_row, last_col);
    }
}


/** 
 * Definitions for offset coordinate.
*/
OffsetCoordinate::OffsetCoordinate(Coordinate* _internal_coordinate, coord _offset) {
    internal_coordinate = std::unique_ptr<Coordinate>(_internal_coordinate);
    offset = _offset;
}

coord OffsetCoordinate::resolve(Table& table) {
    coord base_coord = internal_coordinate->resolve(table);
    return coord(
        std::get<0>(base_coord) + std::get<0>(offset),
        std::get<1>(base_coord) + std::get<1>(offset)
    );
}