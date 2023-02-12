#ifndef _HIERCLUST_H
#define _HIERCLUST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct Node {
    size_t index;
    struct Node* parent;
    struct Node* children[2];
};

struct dist {
    double value;
    size_t rowind;
    size_t colind;
};


int dist_cmp(const void *a, const void *);

size_t get_n_total_nodes(size_t n_nodes); 

void flatten_distance_matrix(size_t n_cols, double distance_matrix[n_cols][n_cols], struct dist distance_flatten[]); 

void pairing(size_t n_nodes, size_t n_new_nodes, size_t flatten_size, size_t start_new_nodes_ind, struct dist distance_flatten[flatten_size], struct Node nodes[n_nodes], struct Node new_nodes[n_new_nodes]); 

#endif
