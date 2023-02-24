#ifndef COORDINATES_H
#define COORDINATES_H
#include "table_types.h"
#include "tables.h"


class Coordinate {
    public:
        virtual coord resolve(Table& table) = 0;
};


class DirectCoordinate : Coordinate {
    private:
        ord row;
        ord col;

    public:
        DirectCoordinate(ord _row, ord _col);
        coord resolve(Table& table);
};


class OpCorner : Coordinate {
    private:
        op_id_t op_id;
        Corner corner;

    public:
        OpCorner(op_id_t, Corner);
        coord resolve(Table& table);
};

#endif  // COORDINATES_H