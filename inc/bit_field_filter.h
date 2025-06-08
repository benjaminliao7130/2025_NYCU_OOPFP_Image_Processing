#ifndef BIT_FIELD_FILTER_H
#define BIT_FIELD_FILTER_H

enum BitFieldFilter {
    FILTER_FLIP = 1,
    FILTER_MOSAIC = 2,
    FILTER_GAUSSIAN = 4,
    FILTER_LAPLACIAN = 8,
    FILTER_RESTORE = 16 
};

bool isFilterEnabled(int bitfield, BitFieldFilter filter);
void printEnabledFilters(int bitfield);

#endif
