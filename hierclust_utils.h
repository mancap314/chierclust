#ifndef _HIERCLUST_UTILS_H
#define _HIERCLUST_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include "hierclust.h"

void print_array(size_t nrows, size_t ncols, double arr[nrows][ncols]); 
void print_node(struct Node* node);
void print_distance_flatten(size_t flatten_size, struct dist distance_flatten[flatten_size]); 

#endif
