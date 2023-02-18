#include "hierclust.h"
#include "hierclust_utils.h"


void test_pairing() {
    printf("INFO: testing pairing()...\n");
    size_t n_nodes = 5;
    size_t n_new_nodes = 2;
    size_t start_new_node = 0;
    size_t start_new_nodes_ind = n_nodes;
    size_t idx_orphan_nodes[n_nodes];
    for (size_t i = 0; i < n_nodes; i++) idx_orphan_nodes[i] = i+1;

    double distance_matrix[n_nodes][n_nodes];
    for (size_t i = 0; i < n_nodes; i++) {
        for (size_t j = 0; j < n_nodes; j++) {
            distance_matrix[i][j] = (j > i) ? (i+1)*(j+1): 0;
        }
    }

    size_t flatten_size = n_nodes * (n_nodes - 1) / 2;
    struct dist distance_flatten[flatten_size];
    flatten_distance_matrix(n_nodes, distance_matrix, distance_flatten);

    struct Node nodes[n_nodes+n_new_nodes];
    for (size_t i = 0; i < n_nodes; i++) {
        struct Node node = {.index = i+1, .level = 0, .parent = NULL, .children = {NULL, NULL}};
        nodes[i] = node;
    }
    printf("INFO: nodes (before pairing()):\n");
    for (size_t i = 0; i < n_nodes; i++) print_node(&nodes[i]);

    printf("INFO: distance_matrix:\n");
    print_array(n_nodes, n_nodes, distance_matrix);
    printf("INFO: distance_flatten:\n");
    print_distance_flatten(flatten_size, distance_flatten);

    pairing(idx_orphan_nodes, start_new_node, n_new_nodes, flatten_size, &start_new_nodes_ind, distance_flatten, nodes);

    printf("INFO: nodes (after pairing()):\n");
    for (size_t i = 0; i < n_nodes; i++) print_node(&nodes[i]);
}


void test_find_leaves() {
    printf("INFO: testing find_leaves()...\n");
    // Preparing data
    struct Node nodes[7];
    for (size_t i = 0; i < 4; i++) {
        nodes[i].index = i+1;
        nodes[i].level = 0;
        size_t parent_id = (i < 2)? 4: 5;
        nodes[i].parent = &nodes[parent_id];
        nodes[i].children[0] = NULL; 
        nodes[i].children[1] = NULL; 
    }
    for (size_t i = 4; i < 6; i++) {
        nodes[i].index = i+1;
        nodes[i].level = 1;
        nodes[i].parent = &nodes[6];
        size_t child0id = (i == 4)? 0: 2;
        nodes[i].children[0] = &nodes[child0id];
        nodes[i].children[1] = &nodes[child0id+1];
    }
    nodes[6].index = 7;
    nodes[6].level = 2;
    nodes[6].parent = NULL;
    nodes[6].children[0] = &nodes[4];
    nodes[6].children[1] = &nodes[5];

    printf("INFO: nodes:\n");
    for (size_t i = 0; i < 7; i++) print_node(&nodes[i]);

    // Testing proper
    struct Node node0 = nodes[6];
    size_t li_size = max_n_leaves(node0.level);
    size_t leaves_idx[li_size];
    size_t min_idx = 0, max_idx = li_size;
    find_leaves(&node0, leaves_idx, min_idx, max_idx);
    printf("leaves indices:\n");
    for(size_t i = min_idx; i < max_idx; i++) printf("%zu ", leaves_idx[i]);
    printf("\n");
}


void test_build_tree() {
    printf("INFO: testing build_tree()...\n");
    size_t n_nodes = 7;
    size_t n_total_nodes = get_n_total_nodes(n_nodes);
    struct Node all_nodes[n_total_nodes];
    double distance_matrix[n_nodes][n_nodes];
    for (size_t i = 0; i < n_nodes; i++) {
        for (size_t j = 0; j < n_nodes; j++) {
            distance_matrix[i][j] = (j > i) ? (i+1)*(j+1): 0;
        }
    }
    unsigned int method = MIN_DIST;
    bool balanced = false;

    build_tree(n_nodes, n_total_nodes, all_nodes, distance_matrix,  method, balanced); 

    printf("distance_matrix:\n");
    print_array(n_nodes, n_nodes, distance_matrix);    
    printf("\nResulting tree:\n");
    for (size_t i = 0; i < n_total_nodes; i++) print_node(&all_nodes[i]);
}

int main(int argc, char* argv[argc+1]){
    // test_pairing();
    // test_find_leaves();
    test_build_tree();

    return EXIT_SUCCESS;
}
