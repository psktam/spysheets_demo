#ifndef TABLES_H
#define TABLES_H

#include <cstdint>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "actions.h"
#include "cell_value.h"
#include "table_types.h"


typedef std::tuple<coord, coord> region;


class Coordinate;


class Argument{
    public:
        std::string name;
        std::shared_ptr<Coordinate> upper_left;
        std::shared_ptr<Coordinate> lower_right;

        Argument(std::string _name, Coordinate* _upper_left, Coordinate* _lower_right) {
            name = _name;
            upper_left = std::shared_ptr<Coordinate>(_upper_left);
            lower_right = std::shared_ptr<Coordinate>(_lower_right);
        };
};

typedef std::unordered_map<coord, CellValue, coord_hasher> cellmap;


struct Operation {
    op_id_t op_id;
    std::vector<Argument> input_selections;
    std::unique_ptr<Action> action;
    std::unique_ptr<Coordinate> output_anchor_coordinate;
    Corner output_anchor_corner;

    Operation( 
        op_id_t _op_id,
        std::vector<Argument> _input_selections,
        Action* _action,
        Coordinate* _output_anchor_coordinate,
        Corner _output_anchor_corner
    ) {
        op_id = _op_id;
        input_selections = _input_selections;
        action = std::unique_ptr<Action>(_action);
        output_anchor_coordinate = std::unique_ptr<Coordinate>(_output_anchor_coordinate);
        output_anchor_corner = _output_anchor_corner;
    }
};


// Last hurdle here is to get rid of the raw Operation* pointer, but that can
// probably be done with unique_ptr. I think it makes sense for table to own
// operation.
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

        CellValue get(ord, ord);
        CellValue get(coord);

        region get_region(op_id_t);

        void insert(coord, CellValue);
        void insert(ord, ord, CellValue);
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


CellArray<CellValue> run_operation(Table&, Operation&, ord&, ord&);


#endif  // TABLES_H