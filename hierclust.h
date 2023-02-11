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
    size_t index;
};


int dist_cmp(const void *a, const void *);

size_t get_n_total_nodes(size_t n_nodes); 

void pairing(size_t n_nodes, size_t n_new_nodes, size_t start_new_nodes_ind, double distance_matrix[n_nodes][n_nodes], struct Node nodes[n_nodes], struct Node new_nodes[n_new_nodes]); 

#endif
