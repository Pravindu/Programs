#ifndef DRAW
#define DRAW

#include "cell.h"

/**
 * load all resources to the program
 */
void load_resources();
/**
 * draws the map and the cells on it
 * 
 * @param data  the list of cells
 */
void draw_map(cell_list &data);
/**
 * updates all sprites in the cell list
 * 
 * @param data      the list of cells
 */
void update_map(cell_list &data);
/**
 * draw the hud of the program
 * 
 * @param flag      check to see if more hud is needed
 */
void draw_hud(bool &flag);

#endif