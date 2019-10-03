#ifndef NODE
#define NODE

#include "cell.h"

/**
 * Forward declare that a node is a pointer to
 * a struct node_data value.
 */
typedef struct node_data *node;

/**
 * The linked list has a first and
 * a last node.
 * 
 * @field first The first node in the list (or nullptr when it is empty)
 * @field last  The last node in the list (or nullptr when it is empty)
 */
struct linked_list
{
    node first;
    node last;
};

/**
 * Each node records its data, the next and previous
 * nodes, and the list. This allows both forward and
 * reverse iteration through the list, and makes it
 * easier to add and remove elements.
 * 
 * @field h      The h(distance from this node to end node) value in this node
 * @field g      The g(distance from this node to start node) value in this node
 * @field f      The f(h+g of this node) value in this node
 * @field parent   A pointer to the parent node of this node
 * @field in_cell   A pointer to the cell_data that contains this node
 * @field in_list   A pointer to the linked list that contains this node
 * @field next      A pointer to the next node in the list
 * @field prev      A pointer to the previous node in the list
 */
struct node_data
{
    int h;
    int g;
    int f;
    place_type type;
    node_data *parent;
    cell_data *in_cell;
    linked_list *in_list;
    node next;
    node prev;
};

/**
 * Setup an empty list.
 * 
 * @param list  The list to initialise, passed by reference
 */
void initialise_list(linked_list &list);
/**
 * Checks if a list is empty.
 * 
 * @param list  The list to check
 * @returns     True when the list is empty
 */
bool list_is_empty(const linked_list &list);
/**
 * creates a node in memory and returns a pointer to it
 * 
 * @param data      the node data of the node
 * @param list      a pointer to the list in which the node is
 * @param next      A pointer to the next node in the list
 * @param prev      A pointer to the previous node in the list
 */
node new_node(node_data &data, linked_list &list, node next, node prev);
/**
 * Add a new node to the end of the list.
 * 
 * @param list      The list to add the node to. Passed by reference.
 * @param value     The value to store in the node.
 */
void add_to_end(linked_list &list, node_data &value);
/**
 * Add all nodes of the second to the end of the list first.
 * 
 * @param update      The list to add the nodes to. Passed by reference.
 * @param data        The list of nodes to store in the update list.
 */
void add_into (linked_list &update, linked_list &data);
/**
 * Add a new node to the start of the list.
 * 
 * @param list      The list to add the node to. Passed by reference.
 * @param value     The value to store in the node.
 */
void add_to_start(linked_list &list, node_data &value);
/**
 * Add all nodes of the second to the first of the list first.
 * 
 * @param update      The list to add the nodes to. Passed by reference.
 * @param data        The list of nodes to store in the update list.
 */
void add_into_start(linked_list &update, linked_list &data);
/**
 * Delete the passed in node from its list.
 * 
 * @param current   The node to delete
 */
void delete_node(node current);
/**
 * set node to default values of startr position
 * 
 * @param parent    the parent node
 * @param start     the start cell in map
 */
void set_node(node &parent,cell &start);

#endif