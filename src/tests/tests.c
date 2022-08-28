#include "minunit.h"
#include "tree.h"


MU_TEST(test_set_parent){
    Node node;

    int n_edges = 4;
    int edges[] = {5, 5, 4, 4, 1, 3, 2, 5}; // in 1-index

    set_parent(&node, 0, n_edges, edges);
    mu_check(node.parent == 4);

    set_parent(&node, 1, n_edges, edges);
    mu_check(node.parent == 3);

    set_parent(&node, 2, n_edges, edges);
    mu_check(node.parent == 4);

    set_parent(&node, 3, n_edges, edges);
    mu_check(node.parent == -1);

    set_parent(&node, 4, n_edges, edges);
    mu_check(node.parent == 3);

}


MU_TEST(test_set_children){
    Node node;
    
    int n_edges = 4;
    int edges[] = {5, 5, 4, 4, 1, 3, 2, 5}; // in 1-index

    set_children(&node, 0, n_edges, edges);
    mu_check(node.children[0] == -1);
    mu_check(node.children[1] == -1);

    set_children(&node, 3, n_edges, edges);
    mu_check(node.children[0] == 1);
    mu_check(node.children[1] == 4);
}


MU_TEST(test_compare_node){
    Node x = {3, {0, 2}, 1};
    Node y = {3, {0, 2}, 1};

    // x and y are identical
    mu_check(!compare_node(&x, &x));
    mu_check(!compare_node(&x, &y));

    // identical, but children have different order
    y.children[0] = 2;
    y.children[1] = 0;
    mu_check(!compare_node(&x, &y));

    // x and y differ
    memcpy(&y, &x, sizeof(y));
    y.parent = 4;
    mu_check(compare_node(&x, &y));

    memcpy(&y, &x, sizeof(y));
    y.time = 3;
    mu_check(compare_node(&x, &y));

    memcpy(&y, &x, sizeof(y));
    y.children[1] = 1;
    mu_check(compare_node(&x, &y));
}


MU_TEST(test_compare_tree){
    Node x_nodes[] = {
        {4, {-1, -1}, 0},
        {3, {-1, -1}, 0},
        {4, {-1, -1}, 0},
        {-1, {1, 4}, 2},
        {3, {0, 2}, 1}
    };

    Tree x = {x_nodes, 3, 2};


    Node y_nodes[5];
    memcpy(&y_nodes, &x_nodes, sizeof(x_nodes));
    Tree y = {y_nodes, 3, 2};

    // x and y are identical
    mu_check(!compare_tree(&x, &x));
    mu_check(!compare_tree(&x, &y));

    // x and y differ:
    y.num_leaves = 4;
    mu_check(compare_tree(&x, &y));
    
    y.num_leaves = 3;
    y.root_time = 3;
    mu_check(compare_tree(&x, &y));
}


MU_TEST(test_new_tree){
    Node nodes[] = {
        {4, {-1, -1}, 0},
        {3, {-1, -1}, 0},
        {4, {-1, -1}, 0},
        {-1, {1, 4}, 2},
        {3, {0, 2}, 1}
    };
    Tree tree = {nodes, 3, 2};

    int n_tips = 3;
    int edges[] = {5, 5, 4, 4, 1, 3, 2, 5};
    int ranks[] = {0, 0, 0, 2, 1};
    Tree* ptree = new_tree(n_tips, edges, ranks);

    mu_check(!compare_tree(&tree, ptree));

    free_tree(ptree);
}

MU_TEST_SUITE(test_suite){
    MU_RUN_TEST(test_set_parent);
    MU_RUN_TEST(test_set_children);
    MU_RUN_TEST(test_compare_node);
    MU_RUN_TEST(test_compare_tree);
    MU_RUN_TEST(test_new_tree);
}


int main(int argc, char* argv[argc+1]){
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
