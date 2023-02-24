#ifndef TABLES_H
#define TABLES_H

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "actions.h"
#include "table_types.h"


typedef std::tuple<coord, coord> region;


class Coordinate;


struct Operation {
    op_id_t op_id;
    Action& action;
    Coordinate& output_anchor;
};


class Table {
    private:
        cellmap data;
        std::unordered_map<op_id_t, region> op_regions;
        unsigned long long int cursor;
        std::vector<op_id_t> op_sequence;

    public:
        Table();

        std::string get_op_id();

        std::string* get(ord, ord);
        std::string* get(coord);

        region get_region(op_id_t);

        void insert(coord, std::string*);
        void insert(ord, ord, std::string*);

        /** 
         * Print the contents of the table, going from left to right and then
         * top to bottom.
        */
        void print_contents();
};

#endif  // TABLES_H