#include "hierclust_utils.h"
#include "hierclust.h"


void print_array(size_t nrows, size_t ncols, double arr[nrows][ncols]) {
    printf("[");
    for (size_t i = 0; i < nrows; i++) {
        printf("[");
        for(size_t j = 0; j < ncols; j++) {
            printf("%f", arr[i][j]);
            if (j < ncols - 1) printf(", ");
        }
        printf("]");
        if (i < ncols - 1) printf("\n");
    }
    printf("]\n");
}


void print_node(struct Node* node) {
    size_t parent_id = (NULL != node->parent)? node->parent->index: 0;
    size_t child0_id = (NULL != node->children[0])? node->children[0]->index: 0;
    size_t child1_id = (NULL != node->children[1])? node->children[1]->index: 0;


    printf("[Node id: %zu, parent.id: %zu, children[0].id: %zu, children[1].id: %zu]\n", node->index, parent_id, child0_id, child1_id);
}
