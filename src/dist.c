#include <stdio.h>
#include <stdlib.h>
#include "dist.h"


// translate error code to error string
const char* dist_error_str(dist_error_e code){
    if( code < 0 || code >= DIST_ERROR_COUNT)
        return(DIST_ERROR_STRS[DIST_ERROR_WRONG]);

    return(DIST_ERROR_STRS[code]);
}


// find mrca of nodes with positions node1 and node2 in tree
// returns the rank of the mrca
long mrca(Tree* input_tree, long node1, long node2){
    long rank1 = node1;
    long rank2 = node2;
    while (rank1 != rank2){
        if (rank1 < rank2){
            rank1 = input_tree->tree[rank1].parent;
        } else{
            rank2 = input_tree->tree[rank2].parent;
        }
    }
    return(rank1);
}


// NNI move on edge bounded by rank rank_in_list and rank_in_list + 1, moving child_stays (index) of the lower node up
int nni_move(Tree* input_tree, long rank_in_list, int child_moves_up){
    if (input_tree->tree == NULL){
        return(-DIST_ERROR_NOTREE);
    }

    if(input_tree->tree[rank_in_list].parent != rank_in_list + 1){
        return(-DIST_ERROR_NOMOVE);
    }

    int child_moved_up;
    for (int i = 0; i < 2; i++){
        //skip the child of the node of rank_in_list k+1 that is the node of rank_in_list k
        if (input_tree->tree[rank_in_list+1].children[i] == rank_in_list){
            continue;
        }

        // update parent/children relations to get nni neighbour
        input_tree->tree[input_tree->tree[rank_in_list+1].children[i]].parent = rank_in_list; //update parents
        input_tree->tree[input_tree->tree[rank_in_list].children[child_moves_up]].parent = rank_in_list+1;
        child_moved_up = input_tree->tree[rank_in_list].children[child_moves_up];
        input_tree->tree[rank_in_list].children[child_moves_up] = input_tree->tree[rank_in_list+1].children[i]; //update children
        input_tree->tree[rank_in_list+1].children[i] = child_moved_up;
    }
    return 0;
}


// Make a rank move on tree between nodes of rank rank and rank + 1 (if possible)
int rank_move(Tree * input_tree, long rank_in_list){
    if (input_tree->tree == NULL){
        return(-DIST_ERROR_NOTREE);
    }

    if (input_tree->tree[rank_in_list].parent == rank_in_list + 1){
        return(-DIST_ERROR_NOMOVE);
    }

    // update parents of nodes that swap ranks
    long upper_parent;
    upper_parent = input_tree->tree[rank_in_list + 1].parent;
    input_tree->tree[rank_in_list + 1].parent = input_tree->tree[rank_in_list].parent;
    input_tree->tree[rank_in_list].parent = upper_parent;

    for (int i = 0; i < 2; i++){
        // update children of nodes that swap ranks
        long upper_child = input_tree->tree[rank_in_list + 1].children[i];
        input_tree->tree[rank_in_list + 1].children[i] = input_tree->tree[rank_in_list].children[i];
        input_tree->tree[rank_in_list].children[i] = upper_child;
    }
    for (int i = 0; i < 2; i++){
        // update parents of children of nodes that swap ranks
        input_tree->tree[input_tree->tree[rank_in_list + 1].children[i]].parent = rank_in_list + 1; 
        input_tree->tree[input_tree->tree[rank_in_list].children[i]].parent = rank_in_list;
    }
    for (int i = 0; i < 2; i++){
        // update children of parents of nodes that swap rank
        //first case: nodes that swap ranks share a parent. In this case nothing needs to be changed
        if (input_tree->tree[rank_in_list + 1].parent == input_tree->tree[rank_in_list].parent){
            break;
        }
        
        if (input_tree->tree[input_tree->tree[rank_in_list + 1].parent].children[i] == rank_in_list){ //parent pointer of input_tree->tree[rank_in_list + 1] is already set correctly!
            input_tree->tree[input_tree->tree[rank_in_list + 1].parent].children[i] = rank_in_list + 1;
        }
        if (input_tree->tree[input_tree->tree[rank_in_list].parent].children[i] == rank_in_list + 1){
            input_tree->tree[input_tree->tree[rank_in_list].parent].children[i] = rank_in_list;
        }
    }
    return 0;
}


// decrease the mrca of node1 and node2 in tree by a (unique) RNNI move
// this function ignores times, only considers ranks
// output: 0 if rank move, 1 if nni move where children[0] stays, 2 if nni move where children[1] stays
int decrease_mrca(Tree* tree, long node1, long node2){
    long num_leaves = tree->num_leaves;
    long current_mrca = mrca(tree, node1, node2); // position of current mrca in tree_list

    Tree* neighbour = copy_tree(tree);

    int err = -DIST_ERROR_WRONG;
    int move_type;
    if (neighbour->tree[current_mrca-1].parent == current_mrca){ // edge -> NNI move
        // we try both possible NNI moves and see which one decreases the rank of the mrca
        err = nni_move(neighbour, current_mrca-1, 0);
        if(err < 0)
            goto error;
        
        move_type = 1;
        if(mrca(neighbour,node1,node2)>=current_mrca){
            // we did not decrease the rank of the mrca by this nni move,
            // so we need to do the other one
            // but first we need to reset neighbour to tree:
            for (long i = 0; i < 2 * num_leaves - 1; i++){
                neighbour->tree[i] = tree->tree[i];
            }

            err = nni_move(neighbour, current_mrca-1, 1);
            if(err > 0)
                goto error;

            move_type = 2;
        }
    } else{ // otherwise, we make a rank move
        err = rank_move(neighbour, current_mrca - 1);
        if(err < 0)
            goto error;

        move_type = 0;
    }
    // now update tree to become neighbour
    for (long i = 0; i < 2 * num_leaves - 1; i++){
        tree->tree[i] = neighbour->tree[i];
    }
    free_tree(neighbour);

    return(move_type);
    
error:
    free_tree(neighbour);
    return(err);
}


// Move up internal nodes that are at position >i in node list so that there are no nodes with rank less than k in the tree at the end (i.e. length moves that move nodes up -- see pseudocode FindPath_matrix^+)
int move_up(Tree * itree, long i, long k){
    if (itree->tree == NULL){
        return(-DIST_ERROR_NOTREE);
    }

    long num_moves = 0; // counter for the number of moves that are necessary
    long j = i;
    // Find the highest j that needs to be moved up -- maximum is reached at root!
    while (itree->tree[j+1].time <= k && j+1 <=2*itree->num_leaves-2){
        j++;
    }

    long num_moving_nodes = j - i; // number of nodes that will need to be moved
    // it might happen that we need to move nodes with times above k up, if there is not enough space for the other nodes that are supposed to move up.
    // Find the uppermost node that needs to move up
    while (itree->tree[j+1].time <= k+num_moving_nodes && j+1 <=2*itree->num_leaves-2){
        j++;
        num_moving_nodes++;
    }

    for (long index = i; index <= j; index++){ // Do all required length moves
        num_moves += k+index-i - itree->tree[index].time;
        itree->tree[index].time = k+index-i;
    }

    return num_moves;
}


// Distance between two trees using the FINDPATH algorithm
long distance(Tree* start_tree, Tree* dest_tree){
    if (start_tree->tree == NULL || dest_tree->tree == NULL){
        return(-DIST_ERROR_NOTREE);
    }

    if(start_tree->num_leaves != dest_tree->num_leaves){
        return(-DIST_ERROR_DIFFSIZE);
    }

    Tree* current_tree = copy_tree(start_tree);
    long path_index = 0; // next position on path that we want to fill with a tree pointer
    long current_mrca; //rank of the mrca that needs to be moved down
    int n_tips = current_tree->num_leaves;
    int n_nodes = 2 * n_tips - 1;
    int err = -DIST_ERROR_WRONG;
    for (int i = n_tips; i < n_nodes; i++){
        // we might need to move nodes below the time of node i in dest_tree up in the current tree
        if (current_tree->tree[i].time < dest_tree->tree[i].time){
            int move = move_up(current_tree, i, dest_tree->tree[i].time);
            if(move < 0)
                goto error;

            path_index += move;
        }

        // we now need to find the current MRCA and decrease its time in the tree
        current_mrca = mrca(
            current_tree,
            dest_tree->tree[i].children[0],
            dest_tree->tree[i].children[1]
        ); //rank of the current mrca (i.e. index in the list of nodes representing the tree)

        // move current_mrca down
        // -- one rank or NNI move per iteration of this loop,
        // but multiple length moves (which are summarised to one 'jump')
        while(current_tree->tree[current_mrca].time != dest_tree->tree[i].time){
            // We first see if we need to do length moves:
            // We need to move the current node down by length moves
            // if its time is greater than the time  of the next lower node + 1
            // After this, we do an NNI or rank move and then repeat the while loop
            if (current_tree->tree[current_mrca-1].time < current_tree->tree[current_mrca].time - 1){
                // We either need to move the node to be right above the time of the next lower node...
                if( current_tree->tree[current_mrca-1].time + 1 > dest_tree->tree[i].time){
                    // Update the time to be one greater than the time of the next lower node.
                    // This is equivalent to doing length moves,
                    // so we add the time difference to the distance
                    path_index +=
                        current_tree->tree[current_mrca].time -
                        (current_tree->tree[current_mrca-1].time + 1);
                    current_tree->tree[current_mrca].time = current_tree->tree[current_mrca-1].time + 1;
                // Or we move the current node to be at the same position
                // as the corresponding node in dest_tree
                } else{ // in this case we move the node to its final position
                    path_index += current_tree->tree[current_mrca].time - dest_tree->tree[i].time;
                    current_tree->tree[current_mrca].time = dest_tree->tree[i].time;
                    break; // the current iteration i is finished
                }
            }
            // Now do RNNI moves
            err = decrease_mrca(
                current_tree,
                dest_tree->tree[i].children[0],
                dest_tree->tree[i].children[1]
            );
            if(err < 0)
                goto error;

            current_mrca--;
            path_index++;
        }
    }
    free_tree(current_tree);
    return(path_index);

error:
    free_tree(current_tree);
    return(err);
}


