#ifndef _HIERCLUST_H
#define _HIERCLUST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define MIN_DIST 0
#define AVG_DIST 1

struct Node {
    size_t index;
    size_t level;
    struct Node* parent;
    struct Node* children[2];
};

struct dist {
    double value;
    size_t rowind;
    size_t colind;
};

size_t max_level(size_t l0, size_t l1); 

size_t max_n_leaves(size_t level);

int dist_cmp(const void *a, const void *);

size_t get_n_total_nodes(size_t n_nodes); 

void flatten_distance_matrix(size_t n_cols, double distance_matrix[n_cols][n_cols], struct dist distance_flatten[]); 

void pairing(size_t n_nodes, size_t n_new_nodes, size_t flatten_size, size_t start_new_nodes_ind, struct dist distance_flatten[flatten_size], struct Node nodes[n_nodes], struct Node new_nodes[n_new_nodes]); 

void find_leaves(struct Node *node, size_t leaves_idx[], size_t min_idx, size_t max_idx);

#endif
