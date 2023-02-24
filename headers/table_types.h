#ifndef TABLE_TYPES_H
#define TABLE_TYPES_H

#include <string>
#include <tuple>
#include <unordered_map>
#include "cell_value.h"

typedef std::string op_id_t;
typedef unsigned long long int ord;
typedef std::tuple<ord, ord> coord;

enum Corner {
    upper_left,
    upper_right,
    lower_left,
    lower_right
};

// Shorthand for table mapping declarations.

/** 
 * Function for hashing the coord tuples.
*/
struct coord_hasher{  // Wonder why we have to put this in a struct first.
    size_t operator()(const coord &x)
        const
    {
        return std::get<0>(x) ^ std::get<1>(x);
    }
};

typedef std::unordered_map<coord, CellValue*, coord_hasher> cellmap;


class Table;
class Coordinate {
    public:
        virtual coord resolve(Table& table) = 0;
};

// Ordered as upper_left, lower_right
typedef std::tuple<Coordinate*, Coordinate*> Selection;

#endif  // TABLE_TYPES_H