#include "minunit.h"
#include "tree.h"
#include "dist.h"

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


MU_TEST(test_copy_tree){
    int n_tips = 3;
    int edges[] = {5, 5, 4, 4, 1, 3, 2, 5};
    int ranks[] = {0, 0, 0, 2, 1};
    Tree* source = new_tree(n_tips, edges, ranks);

    Tree* target = copy_tree(source);

    // same trees
    mu_check(!compare_tree(source, target));

    // different pointers
    mu_check(source != target);

    // the tree array is also a different pointer
    mu_check(&(source->tree) != &(target->tree) );

    // underlying node pointers also differ
    mu_check(&(source->tree[0]) != &(target->tree[0]));

    // node children pointer also differ
    mu_check(&(source->tree[0].children) != &(target->tree[0].children));

    free_tree(source);
    free_tree(target);
}


MU_TEST(test_swap_nodes){
    Node noriginal[] = {
        {4, {-1, -1}, 0},
        {3, {-1, -1}, 0},
        {4, {-1, -1}, 0},
        {-1, {1, 4}, 2},
        {3, {0, 2}, 1}
    };
    Tree original = {noriginal, 3, 2};
    swap_nodes(&original, 3,4);

    Node nswapped[] = {
        {3, {-1, -1}, 0},
        {4, {-1, -1}, 0},
        {3, {-1, -1}, 0},
        {4, {0, 2}, 1},
        {-1, {1, 3}, 2}
    };
    Tree swapped = {nswapped, 3, 2};

    mu_check(!compare_tree(&original, &swapped));

}

MU_TEST(test_sort_tree_1){
    Node nodes[] = {
        {3, {-1, -1}, 0},
        {4, {-1, -1}, 0},
        {3, {-1, -1}, 0},
        {4, {0, 2}, 1},
        {-1, {1, 3}, 2}
    };
    Tree tree = {nodes, 3, 2};

    int n_tips = 3;
    int edges[] = {5, 5, 4, 4, 1, 3, 2, 5};
    int ranks[] = {0, 0, 0, 2, 1};
    Tree* ptree = new_tree(n_tips, edges, ranks);
    sort_tree(ptree);

    mu_check(!compare_tree(&tree, ptree));

    free_tree(ptree);
}

MU_TEST(test_sort_tree_2){
    Node xnodes[] = {
        {7, {-1, -1}, 0},
        {7, {-1, -1}, 0},
        {8, {-1, -1}, 0},
        {8, {-1, -1}, 0},
        {6, {-1, -1}, 0},
        {-1, {6, 7}, 4},
        {5, {8, 4}, 3},
        {5, {0, 1}, 2},
        {6, {2, 3}, 1}
    };
    Tree xtree = {xnodes, 5, 4};
    sort_tree(&xtree);
    
    Node ynodes[] = {
        {6, {-1, -1}, 0},
        {6, {-1, -1}, 0},
        {5, {-1, -1}, 0},
        {5, {-1, -1}, 0},
        {7, {-1, -1}, 0},
        {7, {2, 3}, 1},
        {8, {0, 1}, 2},
        {8, {5, 4}, 3},
        {-1, {7, 6}, 4}
    };
    Tree ytree = {ynodes, 5, 4};

    mu_check(!compare_tree(&xtree, &ytree));
}


MU_TEST(test_mrca){
    Node nodes[] = {
        {3, {-1, -1}, 0},
        {4, {-1, -1}, 0},
        {3, {-1, -1}, 0},
        {4, {0, 2}, 1},
        {-1, {1, 3}, 2}
    };
    Tree tree = {nodes, 3, 2};

    mu_check(mrca(&tree, 0, 2) == 3);
    mu_check(mrca(&tree, 0, 1) == 4);
    mu_check(mrca(&tree, 1, 4) == 4);
    mu_check(mrca(&tree, 2, 3) == 3);
}


MU_TEST(test_distance){
    int n_tips = 3;
    int edges[] = {5, 5, 4, 4, 1, 3, 2, 5};
    int ranks[] = {0, 0, 0, 2, 1};
    Tree* tree = new_tree(n_tips, edges, ranks);
    sort_tree(tree);

    mu_check(distance(tree, tree) == 0);
    free_tree(tree);


    Node xnodes[] = {
        {5, {-1, -1}, 0},
        {5, {-1, -1}, 0},
        {6, {-1, -1}, 0},
        {7, {-1, -1}, 0},
        {8, {-1, -1}, 0},
        {6, {0, 1}, 1},
        {7, {2, 5}, 2},
        {8, {3, 6}, 3},
        {-1, {4, 7}, 4}
    };
    Tree xtree = {xnodes, 5, 4};

    Node ynodes[] = {
        {5, {-1, -1}, 0},
        {8, {-1, -1}, 0},
        {6, {-1, -1}, 0},
        {5, {-1, -1}, 0},
        {6, {-1, -1}, 0},
        {7, {0, 3}, 1},
        {7, {2, 4}, 2},
        {8, {5, 6}, 3},
        {-1, {1, 7}, 4},
    };
    Tree ytree = {ynodes, 5, 4};

    mu_check(distance(&xtree, &ytree) == 5);
}


MU_TEST_SUITE(test_suite){
    MU_RUN_TEST(test_set_parent);
    MU_RUN_TEST(test_set_children);
    MU_RUN_TEST(test_compare_node);
    MU_RUN_TEST(test_compare_tree);
    MU_RUN_TEST(test_new_tree);
    MU_RUN_TEST(test_copy_tree);
    MU_RUN_TEST(test_swap_nodes);
    MU_RUN_TEST(test_sort_tree_1);
    MU_RUN_TEST(test_sort_tree_2);
    MU_RUN_TEST(test_mrca);
    MU_RUN_TEST(test_distance);
}


int main(int argc, char* argv[argc+1]){
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
