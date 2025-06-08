#include "bit_field_filter.h"
#include <iostream>

bool isFilterEnabled(int bitfield, BitFieldFilter filter) {
    return (bitfield & filter) != 0;
}

void printEnabledFilters(int bitfield) {
    std::cout << "Enabled filters: ";
    if (isFilterEnabled(bitfield, FILTER_FLIP)) std::cout << "[FLIP] ";
    if (isFilterEnabled(bitfield, FILTER_MOSAIC)) std::cout << "[MOSAIC] ";
    if (isFilterEnabled(bitfield, FILTER_GAUSSIAN)) std::cout << "[GAUSSIAN] ";
    if (isFilterEnabled(bitfield, FILTER_LAPLACIAN)) std::cout << "[LAPLACIAN] ";
    if (isFilterEnabled(bitfield, FILTER_RESTORE)) std::cout << "[RESTORE] ";
    std::cout << std::endl;
}
