#include "splashkit.h"
#include <vector>
#include "cell.h"
#include "node.h"
#include "draw.h"
#include "pathfinding.h"



/**
 * Sets up a window for user to interact and create mazes.
 * Then finds pathfinds from the start to the end.
 */
int main()
{
    bool track = false;
    bool hud =false;
    ofstream myfile;
    cell_list my_list;
    place_type type_in_use = BLANK;

    load_resources();
    open_window("Path Finder", 800, 600);

    initialise_list(my_list);
    create_map(my_list);
    set_map_to_default(my_list,BLANK);

    draw_map(my_list);
    refresh_screen(60);

    myfile.open("path finding data.txt");

    while ( not quit_requested())
    {
        process_events();
        draw_map(my_list);
        draw_hud(hud);
        update_map(my_list);

        if (not track)
        {
            setup_positions(my_list,type_in_use);

            if (key_typed(Q_KEY))
            {
               track=true;
            }
        }
        else
        {
            path_finding(my_list,myfile);
            track = false;
        }

        if (key_typed(C_KEY))
        {
            set_map_to_default(my_list,BLANK);
        }
        if (key_typed(R_KEY))
        {
            set_map_to_random(my_list);
        }
        refresh_screen(60);  
    }

    myfile.close();
    return 0;
}