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


void flatten_distance_matrix(size_t n_cols, double distance_matrix[n_cols][n_cols], struct dist distance_flatten[]) {
    size_t ind = 0;
    for (size_t i = 0; i < n_cols - 1; i++) {
        for (size_t j = i + 1; j  < n_cols; j++) {
            distance_flatten[ind].value = distance_matrix[i][j];
            distance_flatten[ind].rowind = i;
            distance_flatten[ind].colind = j;
            ind++;
        }
    }
}


void pairing(size_t n_nodes, size_t n_new_nodes, size_t flatten_size, size_t start_new_nodes_ind, struct dist distance_flatten[flatten_size], struct Node nodes[n_nodes], struct Node new_nodes[n_new_nodes]) {

    qsort(distance_flatten, flatten_size, sizeof(distance_flatten[0]), dist_cmp);

    size_t n_found_nodes = 0, current_dist_idx = 0;
    size_t max_used_nodes = 2 * n_new_nodes;
    size_t used_nodes[max_used_nodes];
    while ((n_found_nodes < n_new_nodes) && (current_dist_idx < flatten_size)) {
        bool not_already_there = true;
        size_t current_rowind = distance_flatten[current_dist_idx].rowind;
        size_t current_colind = distance_flatten[current_dist_idx].colind;
        for (size_t i = 0; i < 2 * n_found_nodes; i++) {
            if (current_rowind == used_nodes[i] || current_colind == used_nodes[i]) {
                not_already_there = false;
                break;
            }
        }
        if (not_already_there) {  // new pair found: update 
            new_nodes[n_found_nodes].index = start_new_nodes_ind + n_found_nodes;
            new_nodes[n_found_nodes].parent = NULL;
            new_nodes[n_found_nodes].children[0] = &nodes[current_rowind];
            new_nodes[n_found_nodes].children[1] = &nodes[current_colind];
            nodes[current_rowind].parent = &new_nodes[n_found_nodes];
            nodes[current_colind].parent = &new_nodes[n_found_nodes];

            // Update the list of used_nodes
            size_t new_found_node_0_idx = n_found_nodes * 2;
            size_t new_found_node_1_idx = n_found_nodes * 2 + 1;
            used_nodes[new_found_node_0_idx] = current_rowind; 
            used_nodes[new_found_node_1_idx] = current_colind;

            n_found_nodes++;
        }
        current_dist_idx++;
    }
}
