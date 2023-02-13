#include "hierclust.h"


size_t max_level(size_t l0, size_t l1) {
    size_t ml = (l0 >= l1)? l0: l1;
    return ml;
}

size_t max_n_leaves(size_t level) {
    size_t mnl = 1;
    while (level > 0) {
        mnl *= 2;
        level--;
    }
    return mnl;
}


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
            new_nodes[n_found_nodes].level = max_level(nodes[current_rowind].level, nodes[current_colind].level) + 1;
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


void find_leaves(struct Node *node, size_t leaves_idx[], size_t min_idx, size_t max_idx) {
    if (node->level > 0) {
        size_t mm_diff = max_idx - min_idx;
        find_leaves(node->children[0], leaves_idx, min_idx, min_idx + mm_diff / 2);
        find_leaves(node->children[1], leaves_idx, min_idx + mm_diff / 2, max_idx);
    } else {
        leaves_idx[min_idx] = node->index;
        if (max_idx > min_idx + 1) {
            for (size_t i = min_idx + 1; i < max_idx; i++) leaves_idx[i] = 0;
        }
    }
}


double nodes_distance(struct Node *node_0, struct Node *node_1, size_t n_leaves, double distance_matrix[n_leaves][n_leaves], unsigned short int method) {
    size_t n_leaves_0 = max_n_leaves(node_0->level);
    size_t leaves_idx_0[n_leaves_0];
    find_leaves(node_0, leaves_idx_0, 0, n_leaves_0);

    size_t n_leaves_1 = max_n_leaves(node_1->level);
    size_t leaves_idx_1[n_leaves_1];
    find_leaves(node_1, leaves_idx_1, 0, n_leaves_1);

    double distances[n_leaves_0][n_leaves_1];
    for (size_t i = 0; i < n_leaves_0; i++) {
        for(size_t j = 0; j < n_leaves_1; j++) {
            size_t ind_0 = leaves_idx_0[i], ind_1 = leaves_idx_1[j];
            if ((ind_0 == 0) || (ind_1 == 0)) {
                distances[ind_0 - 1][ind_1 - 1] = -1.0;
                continue;
            }
            distances[ind_0 - 1][ind_1 - 1] = distance_matrix[ind_0 - 1][ind_1 - 1];
        }
    }
    double dist = 0;
    if (method == MIN_DIST) {
        for (size_t i = 0; i < n_leaves_0; i++) {
            for(size_t j = 0; j < n_leaves_1; j++) {
                if (distances[i][j] < 0) continue;
                else if (dist == 0) dist = distances[i][j];
                else if (dist > distances[i][j]) dist = distances[i][j];
                else continue;
            }
        }
    }

    return dist;
}

