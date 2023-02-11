#include "hierclust.h"
#include "hierclust_utils.h"


void test_pairing() {
    printf("INFO: testing pairing()...\n");
    size_t n_nodes = 3;
    size_t n_new_nodes = 1;
    size_t start_new_nodes_ind = n_nodes + 1;

    double distance_matrix[n_nodes][n_nodes];
    for (size_t i = 0; i < n_nodes; i++) {
        for (size_t j = 0; j < n_nodes; j++) {
            distance_matrix[i][j] = (j > i) ? (i+1)*(j+1): 0;
        }
    }

    struct Node nodes[n_nodes];
    for (size_t i = 0; i < n_nodes; i++) {
        nodes[i].index = i + 1;
        nodes[i].parent = NULL;
        nodes[i].children[0] = NULL;
        nodes[i].children[1] = NULL;
    }

    struct Node new_nodes[n_new_nodes];
    
    printf("INFO: nodes (before pairing()):\n");
    for (size_t i = 0; i < n_nodes; i++) print_node(&nodes[i]);

    printf("INFO: distance_matrix:\n");
    print_array(n_nodes, n_nodes, distance_matrix);

    pairing(n_nodes, n_new_nodes, start_new_nodes_ind, distance_matrix, nodes, new_nodes);

    printf("INFO: new_nodes (after pairing()):\n");
    for (size_t i = 0; i < n_new_nodes; i++) print_node(&new_nodes[i]);
    printf("INFO: nodes (after pairing()):\n");
    for (size_t i = 0; i < n_nodes; i++) print_node(&nodes[i]);
}


int main(int argc, char* argv[argc+1]){
    test_pairing();
    return EXIT_SUCCESS;
}
