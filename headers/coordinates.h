#ifndef COORDINATES_H
#define COORDINATES_H
#include "table_types.h"
#include "tables.h"


class DirectCoordinate : public Coordinate {
    private:
        ord row;
        ord col;

    public:
        DirectCoordinate(ord _row, ord _col);
        coord resolve(Table& table);
};


class OpCorner : public Coordinate {
    private:
        op_id_t op_id;
        Corner corner;

    public:
        OpCorner(op_id_t, Corner);
        coord resolve(Table& table);
};


class OffsetCoordinate : public Coordinate {
    private:
        Coordinate& internal_coordinate;
        coord offset;

    public:
        OffsetCoordinate(Coordinate&, coord);
        coord resolve(Table& table);
};
#endif  // COORDINATES_H