#ifndef TABLES_H
#define TABLES_H

#include <cstdint>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "actions.h"
#include "cell_value.h"
#include "table_types.h"


typedef std::tuple<coord, coord> region;


class Coordinate;


struct Operation {
    op_id_t op_id;
    std::unordered_map<std::string, Selection>* input_selections;
    Action& action;
    std::tuple<Coordinate*, Corner> output_anchor;

    Operation(
        op_id_t _op_id, 
        std::unordered_map<std::string, Selection>* _input_selections,
        Action& _action,
        std::tuple<Coordinate*, Corner> _output_anchor
        ): action(_action) {

        op_id = _op_id;
        input_selections = _input_selections;
        output_anchor = _output_anchor;
    }
};


class Table {
    private:
        cellmap data;
        std::unordered_map<op_id_t, region> op_regions;
        std::unordered_map<op_id_t, Operation*> op_map;
        uint64_t cursor;
        std::vector<op_id_t> op_sequence;

    public:
        Table();

        std::string get_op_id();

        CellValue* get(ord, ord);
        CellValue* get(coord);

        region get_region(op_id_t);

        void insert(coord, CellValue*);
        void insert(ord, ord, CellValue*);
        void pop(ord, ord);

        /** 
         * Print the contents of the table, going from left to right and then
         * top to bottom.
        */
        void print_contents();

        /**
         * Operational functions that are used when we start modifying the 
         * table's contents.
        */
        void insert_operation_at_current_locatiton(Operation&);
        void advance_cursor_to_position(uint64_t);
        void rewind_cursor(uint64_t);
};


CellArray* apply_operation(Table&, Operation&, ord&, ord&);


#endif  // TABLES_H