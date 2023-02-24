#ifndef TABLE_TYPES_H
#define TABLE_TYPES_H

#include <string>
#include <tuple>
#include <unordered_map>

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

typedef std::unordered_map<coord, std::string*, coord_hasher> cellmap;


#endif  // TABLE_TYPES_H