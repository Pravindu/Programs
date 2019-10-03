#include "draw.h"

void load_resources()
{
    load_bitmap ("start", "start.png");
    load_bitmap ("end", "end.png");
    load_bitmap ("stop", "stop.png");
    load_bitmap ("wall", "wall.png");
    load_bitmap ("blank", "blank.png");
    load_bitmap ("track",   "track.png");
    load_bitmap ("track1",  "track1.png");
    load_bitmap ("track2",  "track2.png");
    load_bitmap ("track3",  "track3.png");
    load_bitmap ("track4",  "track4.png");
    load_bitmap ("track5",  "track5.png");
    load_bitmap ("track6",  "track6.png");
    load_bitmap ("track7",  "track7.png");
    load_bitmap ("track8",  "track8.png");
    load_bitmap ("track9",  "track9.png");
    load_bitmap ("backtrack", "backtrack.png");
    load_bitmap ("backtrack1",  "backtrack1.png");
    load_bitmap ("backtrack2",  "backtrack2.png");
    load_bitmap ("backtrack3",  "backtrack3.png");
    load_bitmap ("backtrack4",  "backtrack4.png");
    load_bitmap ("backtrack5",  "backtrack5.png");
    load_bitmap ("backtrack6",  "backtrack6.png");
    load_bitmap ("backtrack7",  "backtrack7.png");
    load_bitmap ("backtrack8",  "backtrack8.png");
    load_bitmap ("backtrack9",  "backtrack9.png");
}

void draw_map(cell_list &data)
{
    clear_screen(COLOR_WHITE);
    
    cell result;
    int y=0;
    result = data.first;
    draw_sprite(result ->object.place_sprite);
    while ((result != data.last) )
    {
        y=y+1;
        result = data.first;
        for (int i = 1; i < y; i++)
        {
            result = result ->down;
        }
        while ((result != nullptr) and (result != data.last))
        {
            draw_sprite(result ->object.place_sprite);
            result = result -> right;
        }  
    }
    draw_sprite(result ->object.place_sprite);
    for (int i=0; i<100; i++)
    {
        draw_line(COLOR_BLACK,i*10,0,i*10,screen_height());
        draw_line(COLOR_BLACK,0,i*10,screen_width(),i*10);
    }
}

void update_map(cell_list &data)
{
    cell result;
    int y=0;
    result = data.first;
    update_sprite(result ->object.place_sprite);
    while ((result != data.last) )
    {
        y=y+1;
        result = data.first;
        for (int i = 1; i < y; i++)
        {
            result = result ->down;
        }
        while ((result->right != nullptr) and (result != data.last))
        {
            result = result -> right;
            update_sprite(result ->object.place_sprite);
        }  
    }
}

void draw_hud(bool &flag)
{
    draw_text("Controls: /", COLOR_BLUE, 2,2,option_to_screen());
    if (key_typed(SLASH_KEY))
    {
        flag = not flag;
    }
    if (flag)
    {
        fill_rectangle(COLOR_WHITE,0,0,600,30);
        draw_text("Controls: /"     ,       COLOR_BLUE,   2, 2,option_to_screen());
        draw_text("Clear Screen: C" , COLOR_DARK_GREEN,   0,22,option_to_screen());
        draw_text("Randomize: R"    , COLOR_DARK_GREEN, 200,22,option_to_screen());
        draw_text("Start: S"        , COLOR_DARK_GREEN,   0,12,option_to_screen());
        draw_text("End: E"          , COLOR_DARK_GREEN, 100,12,option_to_screen());
        draw_text("Wall: W"         , COLOR_DARK_GREEN, 200,12,option_to_screen());
        draw_text("Blank: B"        , COLOR_DARK_GREEN, 300,12,option_to_screen());
        draw_text("A Stop: P"       , COLOR_DARK_GREEN, 400,12,option_to_screen());
        draw_text("Path Find: Q"    , COLOR_DARK_GREEN, 500,12,option_to_screen());
    }
}

