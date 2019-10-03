#ifndef PATHFIND
#define PATHFIND
#include "cell.h"
#include "node.h"
#include "draw.h"
#include <iostream>
#include <fstream>

/**
 * diffrent types of pathfinding algorithms 
 */
enum pathfinding_algorithm
{
    A_STAR,
    ALL,
    DEPTH_F
};

/**
 * creates a new child node to from the parent node and adds to the list of children for that generation
 * 
 * @param data      the list of cells
 * @param list      the list of children nodes
 * @param end       the end cell used to calculate h and hence f
 * @param parent    the parent node of the created child node
 */
void add_child_to_link_list(cell &data, linked_list &list,cell end,node parent);
/**
 * creates all children posible from the give parent node
 * 
 * @param parent    the parent node
 * @param end       the end cell
 * @param list      the list of children nodes
 */
void add_children(node &parent,cell &end,linked_list &list);
/**
 * generates children from the given parent node and returns a list of child nodes
 * 
 * @param parent    the given paarent node
 * @param end       the end cell in maze
 * return list      the list of child nodes.
 */
linked_list generate_children(node &parent,cell &end);
/**
 * searches the list of nodes to check if it is the given type
 * 
 * @param list      list of nodes to be searched
 * @param type      the place type that is searched for
 * @param ending    the node with the searched type
 * @param n_cell_saerched   the number of cells searched to find the node. 
 */
bool check_list_for(linked_list &list, place_type type, node &ending,int &n_cell_searched, int num);
/**
 * find the path from the end to the start which was tracked
 * 
 * @param destination       end node in the map
 * @param list              the map of cells
 */
int back_track(node &destination,cell &start,cell_list &list,int num);
/**
 * a-star path finding algorithm 
 * 
 * @param parents   list of parent cells to create the next generation of cells
 * @param open      list of cells first to be searched
 * @param close     list of cells searched after open list is empty
 * @param end       the end cell
 * @param full      boolean check to find if no more searches can be done
 * 
 */
void a_star_next_gen(linked_list &parents, linked_list &open, linked_list &close,cell &end, bool &full);
/**
 * path finding algorithm that will search below from the parent cell first
 * 
 * @param parents   list of parent cells to create the next generation of cells
 * @param down     list of cells first to be searched
 * @param close     list of cells searched after open list is empty
 * @param end       the end cell
 * @param full      boolean check to find if no more searches can be done
 * 
 */
void d_f_s_next_gen(linked_list &parents, linked_list &down, linked_list &close, cell &end, bool &full);
/**
 * path finding algorithm that will search in all directions from the parent cell
 * 
 * @param parents   list of parent cells to create the next generation of cells
 * @param open      list of cells first to be searched
 * @param close     list of cells searched after open list is empty
 * @param end       the end cell
 * @param full      boolean check to find if no more searches can be done
 * 
 */
void all_search_next_gen(linked_list &parents, linked_list &open,cell &end, bool &full);
/**
 * writes the data of the path finding on to a file
 * 
 * @param file      the file to write the data on to
 * @param gen       data of number of generations
 * @param tot_s     data of number of searches
 * @param lenght    data of the path found
 */
void write_to_file(ofstream &file,int gen,int tot_s, int lenght);
/**
 * resets the parent node list to the start cell
 * 
 * @param parents       node list to be reset
 * @param parent        the parent node
 * @param start         the cell which is going to be the parent
 */
void reset_parents(linked_list &parents,node &parent,cell &start);
/**
 * carries out the algorithm passed to it
 * to find the path from start to end and show the path to the user
 * 
 * @param list      map of cells
 * @param start     the start cell in the map
 * @param end       the end cell in the map
 * @param parents   the list of parent cells
 * @param end_parents   the list of parent cells from end point
 * @param  option   the algorithm the use 
 * @param file      to record the path finding algorithm
 */
bool execute_algorithm(cell_list &list,cell start,cell end,linked_list parents,pathfinding_algorithm const &option,ofstream &file,int stop_no);
/**
 * find the path from the start to the end in the map of cells
 * using all pathfinding algorithms
 * 
 * @param list      the map of cells
 * @param file      to record the data of path finding algorithm
 */
void path_finding(cell_list &list,ofstream &file);

#endif