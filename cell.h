#ifndef CELL
#define CELL

#include "splashkit.h"
#include <vector>

using std::vector;
using namespace std;

/**
 * Forward declare that a cell is a pointer to
 * a struct cell_data value.
 */
typedef struct cell_data *cell;

/**
 * The cell list has a first and
 * a last cell.
 * 
 * @field first The first cell in the list (or nullptr when it is empty)
 * @field last  The last cell in the list (or nullptr when it is empty)
 */
struct cell_list
{
    cell first;
    cell last;
};

/**
 * different types of places in the map
 */
enum place_type
{
    BLANK,
    START,
    END,
    WALL,
    TRACK,
    TRACK1,
    TRACK2,
    TRACK3,
    TRACK4,
    TRACK5,
    TRACK6,
    TRACK7,
    TRACK8,
    TRACK9,
    BACKTRACK,
    BACKTRACK1,
    BACKTRACK2,
    BACKTRACK3,
    BACKTRACK4,
    BACKTRACK5,
    BACKTRACK6,
    BACKTRACK7,
    BACKTRACK8,
    BACKTRACK9,
    STOPS
};

/**
 * places is the data about the type of place of a cell
 * 
 * @field   place_sprite    the sprite of the place
 * @field   type            the place type of the cell
 */
struct places
{
    sprite place_sprite;
    place_type  type;
};

/**
 * Each cell records its data, the up, down, left and right
 * cell, and the list. 
 * 
 * @field x         The x value in this cell
 * @field y         The y value in this cell
 * @field up        A pointer to the up cell in the list
 * @field down      A pointer to the down cell in the list
 * @field left      A pointer to the left cell in the list
 * @field right     A pointer to the right cell in the list
 * @field tracked   A boolean to check if the pathfinding algorithm has tracked this cell
 * @field backtrack A boolean to check if the pathfinding algorithm has back tracked this cell
 * @field in_list   A pointer to the cell list that contains this node
 */
struct cell_data
{
    int x;
    int y;
    places object;
    cell up;
    cell down;
    cell left;
    cell right;
    vector<cell> *stop_points;
    bool tracked;
    bool backtrack;
    cell_list *in_list;
};

/**
 * Setup an empty list.
 * 
 * @param list  The cell list to initialise, passed by reference
 */
void initialise_list(cell_list &list);
/**
 * Checks if a list is empty.
 * 
 * @param list  The list to check
 * @returns     True when the list is empty
 */
bool list_is_empty(const cell_list &list);  
/**
 * Creates a new node in memory, and returns a pointer to it.
 * 
 * @param value     The value for the node
 * @param list      The list the node will be in
 * @param prev      The node before this in the list
 * @param next      The node after this in the list
 */
cell new_cell(int x, int y, places data, cell_list &list, cell down, cell up, cell left, cell right);
/**
 * creates a map of cells interconnected 
 * 
 * @param list      The list to add the cells to create the map. Passed by reference.
 */
void create_map(cell_list &list);
/**
 * returns the place type from the corresponding key typed
 * 
 * @param current       the current place type that is in use
 */
place_type set_type(place_type &current);
/**
 * returns the sprite of the given place_type
 * 
 * @param current   the given place type
 * return data      the sprite of the place 
 */
sprite set_sprite(place_type &current);
/**
 * retruns the place data for a give place type
 * 
 * @param current   the given place type
 * return result    the place data of the place type
 */
places get_place(place_type current);
/**
 * selects the cell with the x and y values given
 * 
 * @param data      the list of cells
 * @param x         the x value of cell searched for
 * @param y         the y value of cell searched for
 */
cell select_cell(cell_list &data,int x, int y);
/**
 * sets place of the cell of value x and y to the given place type
 * 
 * @param data      the list of cells
 * @param current   the give place type to change to
 * @param x         the x value of the cell
 * @param y         the y value of the cell
 */
void set_place(cell_list &data, place_type &current,int x, int y);
/**
 * set tracked to false of the map
 * 
 * @param data  the list of cells
 */
void detrack(cell_list &data);
/**
 * set the map to its maze state before pathfinding occured 
 * 
 * @param data  the list of cells
 */
void set_map_to_maze(cell_list &data);
/**
 * set the map to its default state of passed place type
 * 
 * @param data  the list of cells
 * @param current   place type to be set
 */
void set_map_to_default(cell_list &data,place_type curent);
/**
 * set the map to random state of blanks and walls
 * 
 * @param data  the list of cells
 */
void set_map_to_random(cell_list &data);
/**
 * creates a new place of the selected place type to the position of the mouse
 * 
 * @param data  map of the maze
 * @param current   the current place type user has selected
 */
void create_places(cell_list &data, place_type &current);
/**
 * searches the list of cells to find the first cell with the given palce type
 * 
 * @param data      the map of the maze
 * @param current   the place type searched for
 */
cell search_list(cell_list &data, place_type &current);
/**
 * searches the list of cells for the given numbered cell
 * 
 * @param data      the map of the maze of cells
 * @num             the number of the cell
 */
cell search_list_for_node(cell_list &data, int num);
/**
 * searches the list of cells to find the cell with the give place type and creates a new cell of similar values to return
 * 
 * @param list      the list of cells
 * @param type      the give place type 
 */
cell search_for(cell_list &list, place_type type);
/**
 * Moves the selected place type to the position of the mouse
 * 
 * @param data  map of the maze
 * @param current   the current place type user has selected
 */
void move_place(cell_list &data, place_type &current);
/**
 * Creates the diffrent types of positions in the maze
 * 
 * @param place     the map of the maze
 * @param current   the current place type that the user is creating
 */
void setup_positions(cell_list &place, place_type &current);

#endif
