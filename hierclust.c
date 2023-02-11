#include "hierclust.h"


int dist_cmp(const void *a, const void *b) {
    struct dist *a1 = (struct dist *)a;
    struct dist *a2 = (struct dist *)b;
    if ((*a1).value < (*a2).value) return -1;
    else if ((*a1).value > (*a2).value) return 1;
    else return 0;
}


size_t get_n_total_nodes(size_t n_nodes) {
    size_t n_total_nodes = n_nodes;
    while (n_nodes >= 1) {
        n_nodes /= 2;
        n_total_nodes += n_nodes;
    }
    return n_total_nodes;
}


void pairing(size_t n_nodes, size_t n_new_nodes, size_t start_new_nodes_ind, double distance_matrix[n_nodes][n_nodes], struct Node nodes[n_nodes], struct Node new_nodes[n_new_nodes]) {
    size_t flatten_size = n_nodes * (n_nodes - 1) / 2;
    struct dist distance_flatten[flatten_size];
    size_t index = 0;
    for (size_t i = 0; i < n_nodes - 1; i++) {
        for (size_t j = i+1; j < n_nodes; j++) {
            struct dist d = { .value = distance_matrix[i][j], .index = index };
            distance_flatten[index] = d;
            index++;
        }
    }

    qsort(distance_flatten, flatten_size, sizeof(distance_flatten[0]), dist_cmp);
    for (size_t i = 0; i < n_new_nodes; i++) {
        bool index_found = false;
        size_t index = 0;
        // Find distance_matrix index corresponding to distance_flatten index
        for (size_t row_index = 0; row_index < n_nodes -1 && !index_found; row_index++) {
            size_t last_index_row = index + (n_nodes - row_index) - 1;
            // continue if flatten_distance index for sure not in row j
            if (last_index_row < distance_flatten[i].index) {
                index = last_index_row;
                continue;
            }
            size_t col_index = row_index + 1;
            while (!index_found) {
                if (index == distance_flatten[i].index) {
                    new_nodes[i].index = start_new_nodes_ind + i;
                    new_nodes[i].parent = NULL;
                    new_nodes[i].children[0] = &nodes[row_index];
                    new_nodes[i].children[1] = &nodes[col_index];
                    nodes[row_index].parent = &new_nodes[i];
                    nodes[col_index].parent = &new_nodes[i];
                    index_found = true;
                }
                index++;
                col_index++;
            }
        }
    }
}
