#include "cell.h"

void initialise_list(cell_list &list)
{
    list.first = nullptr;
    list.last = nullptr;
}

bool list_is_empty(const cell_list &list)
{
    return list.first == nullptr; // last will also be null
}

cell new_cell(int x, int y, places data, cell_list &list, cell down, cell up, cell left, cell right, vector<cell> *stop_points)
{
    cell result;

    result = new cell_data();
    point_2d point;
    point.x = x*10 +1;
    point.y = y*10 +1;
    result->x = x;
    result->y = y;
    result->object = data;
    sprite_set_position(result->object.place_sprite, point);
    result->down = down;
    result->up = up;
    result->left = left;
    result->right = right;
    result->in_list = &list;
    result -> tracked = false;
    result -> backtrack = false;
    result ->stop_points = stop_points;

    return result;
}

void create_map(cell_list &list)
{
    cell added_node;
    vector<cell> *stop_points;
    stop_points = new vector<cell>();
    places data;
    data = get_place(BLANK);
    cell b,c;
    int i;
    
    for (int y = 1; y<= 60; y++)
    {
        for (int x = 1;x <= 80; x++)
        {
            if(y==1)
            {
                b=nullptr;
            }
            else
            {
                b=list.first;
                if (x>1)
                {
                    for (i = x; i > 1; i--)
                    {
                        b= b ->right;
                    }
                }
                if (y>2)
                {
                    for (i= y; i>2; i--)
                    {
                        b = b ->down;
                    }  
                }
                                
            }
            if (x==1)
            {
                c=nullptr;
            }
            else
            {
                c=list.first;
                if (x>2)
                {
                    for (i = x; i > 2; i--)
                    {
                        c= c ->right;
                    }
                }
                if (y>1)
                {
                    for (i= y; i>1; i--)
                    {
                        c = c ->down;
                    }  
                }
            }
                        
            added_node = new_cell (x,y,data,list, nullptr, b, c, nullptr,stop_points);
            if (b != nullptr) b->down=added_node;
            if (c != nullptr) c->right=added_node;

            if (not list_is_empty(list))
            {
                list.last->right = added_node; // point last node to new node
                
                if (x==1)
                {
                    list.last->right = nullptr; // point last node to new node
                    
                }
                list.last = added_node;
            }
            else
            {
                list.first = added_node;
                list.last = added_node;
            }
        }  
    }
}

place_type set_type(place_type &current)
{
    if (key_typed(B_KEY))
    {
        return BLANK;
    }
    if (key_typed(S_KEY))
    {
        return START;
    }
    if (key_typed(E_KEY))
    {
        return END;
    }
    if (key_typed(W_KEY))
    {
        return WALL;
    }
    if (key_typed(P_KEY))
    {
        return STOPS;
    }
    return current;
}

sprite set_sprite(place_type &current)
{
    sprite data;
    data=create_sprite("blank");
    switch (current)
    {
        case START:
            data=create_sprite("start");
            break;
        case END:
            data=create_sprite("end");
            break;
        case WALL:
            data=create_sprite("wall");
            break;
        case TRACK:
            data=create_sprite("track");
            break;
        case TRACK1:
            data=create_sprite("track1");
            break;
        case TRACK2:
            data=create_sprite("track2");
            break;
        case TRACK3:
            data=create_sprite("track3");
            break;
        case TRACK4:
            data=create_sprite("track4");
            break;
        case TRACK5:
            data=create_sprite("track5");
            break;
        case TRACK6:
            data=create_sprite("track6");
            break;
        case TRACK7:
            data=create_sprite("track7");
            break;
        case TRACK8:
            data=create_sprite("track8");
            break;
        case TRACK9:
            data=create_sprite("track9");
            break;
        case BACKTRACK:
            data=create_sprite("backtrack");
            break;
        case BACKTRACK1:
            data=create_sprite("backtrack1");
            break;
        case BACKTRACK2:
            data=create_sprite("backtrack2");
            break;
        case BACKTRACK3:
            data=create_sprite("backtrack3");
            break;
        case BACKTRACK4:
            data=create_sprite("backtrack4");
            break;
        case BACKTRACK5:
            data=create_sprite("backtrack5");
            break;
        case BACKTRACK6:
            data=create_sprite("backtrack6");
            break;
        case BACKTRACK7:
            data=create_sprite("backtrack7");
            break;
        case BACKTRACK8:
            data=create_sprite("backtrack8");
            break;
        case BACKTRACK9:
            data=create_sprite("backtrack9");
            break;
        case STOPS:
            data=create_sprite("stop");
            break;
        default:
            break;
        
    }
    return data;
}

places get_place(place_type current)
{
    places result;
    result.type = current;
    result.place_sprite = set_sprite(current);
    return result;
}

cell select_cell(cell_list &data,int x, int y)
{
    cell selected = data.first;
    for (int i= 1; i < y; i++)
    {   
        if (selected->down != nullptr)  selected = selected ->down;
    }   
    for (int i= 1; i < x; i++)
    {
        if (selected->right != nullptr) selected = selected ->right;
    }
    return selected;
}
void set_place(cell_list &data, place_type &current,int x, int y)
{
    point_2d point;    
    cell selected;
    selected = select_cell(data,x,y);
    
    if (current == STOPS)
    {
        selected->stop_points->push_back(selected);
    }
    if (selected->object.type == STOPS)
    {
        for (int i=0; i<int(selected->stop_points->size()); i++)
        {
            if (selected->stop_points->at(i) == selected)
            {
                for (int j=i; j<int(selected->stop_points->size()-1); j++)
                {
                    selected->stop_points->at(j)=selected->stop_points->at(j+1);
                }
                selected->stop_points->pop_back();
            }
        }
    }
    selected->object = get_place(current);
    point.x=(selected->x-1)*10+1;
    point.y=(selected->y-1)*10+1;
    sprite_set_position(selected->object.place_sprite,point);

    
}

void set_map_to_default(cell_list &data,place_type current)
{
    vector<cell> *stops = new vector<cell> ();
    cell selected;
    for (int y= 1; y <= 60; y++)
    {
        for (int x = 1; x <= 80; x++)
        {
            selected=select_cell(data,x,y);
            selected->object=get_place(current);
            
            sprite_set_x(selected->object.place_sprite,(selected->x-1)*10+1);
            sprite_set_y(selected->object.place_sprite,(selected->y-1)*10+1);
            selected->tracked=false;
            selected->backtrack=false;
            selected->stop_points=stops;
        }
    }
}

void set_map_to_random(cell_list &data)
{
    vector<cell> *stops = new vector<cell> ();
    place_type current;
    cell selected;
    for (int y= 1; y <= 60; y++)
    {
        for (int x = 1; x <= 80; x++)
        {
            selected=select_cell(data,x,y);
            if (rnd()<0.5)
            {
                current = BLANK;
            }
            else
            {
                current = WALL;
            }
            selected->object=get_place(current);
            
            sprite_set_x(selected->object.place_sprite,(selected->x-1)*10+1);
            sprite_set_y(selected->object.place_sprite,(selected->y-1)*10+1);
            selected->tracked=false;
            selected->backtrack=false;
            selected->stop_points=stops;
        }
    }
}

void detrack(cell_list &data)
{
    cell current;

    for (int y= 1; y <= 60; y++)
    {
        for (int x = 1; x <= 80; x++)
        {
            current = select_cell(data,x,y);
            current ->tracked=false;
        }
    }
}

void set_map_to_maze(cell_list &data)
{
    cell current;
    place_type current_type;

    for (int y= 1; y <= 60; y++)
    {
        for (int x = 1; x <= 80; x++)
        {
            current = select_cell(data,x,y);
            current_type=current->object.type;
            current->object=get_place(current_type);
            sprite_set_x(current->object.place_sprite,(current->x-1)*10+1);
            sprite_set_y(current->object.place_sprite,(current->y-1)*10+1);
            current ->tracked=false;
            current ->backtrack=false;
        }
    }
}

void create_places(cell_list &data, place_type &current)
{
    point_2d point;
    int x,y;
    point = mouse_position();
    x=div(point.x,10).quot+1;
    y=div(point.y,10).quot+1;

    set_place(data,current,x,y);

}

cell search_list(cell_list &data, place_type &current)
{
    cell result;
    int y=0;
    result = data.first;
    while ( (result->object.type != current) and (result != data.last) )
    {
        y=y+1;
        result = data.first;
        for (int i = 1; i < y; i++)
        {
            result = result ->down;
        }
        while ((result->right != nullptr) and (result->object.type != current) and (result != data.last))
        {
            result = result -> right;
        }
    }
    if (result->object.type != current)     result = nullptr;
    return result;
    
}

cell search_list_for_node(cell_list &data, int num)
{
    cell result;
    int count;
    int y=0;
    result = data.first;
    count = 1;
    while ( (count!=num) and (result != data.last) )
    {
        y=y+1;
        result = data.first;
        for (int i = 1; i < y; i++)
        {
            result = result ->down;
        }
        while ((result->right != nullptr) or (count!=num) or (result != data.last))
        {
            result = result -> right;
            count = count + 1;
        }  
    }
    if (count!=num)     result = nullptr;
    return result;
    
}

cell search_for(cell_list &list, place_type type)
{
    cell current = new cell_data();
    current = list.first;
    int y=0;
    while ( (current->object.type != type) and (current != list.last) )
    {
        current = list.first;
        for (int i = 0; i < y; i++)
        {
            current = current ->down;
        }
        while ((current->right != nullptr) and (current->object.type != type) and (current != list.last))
        {
            current = current -> right;
        }
        y=y+1;
    }
    if (current->object.type != type)
    {
        current = nullptr;
    }
    return current;
}

void move_place(cell_list &data, place_type &current)
{
    cell searched;
    place_type def_type=BLANK;
    point_2d point;

    searched=search_list(data,current);
    if (searched != nullptr)
    {
        searched ->object = get_place(def_type);
        point.x=(searched->x-1)*10+1;
        point.y=(searched->y-1)*10+1;
        sprite_set_position(searched ->object.place_sprite,point);
    }
    
    point = mouse_position();
    point.x=div(point.x,10).quot + 1;
    point.y=div(point.y,10).quot + 1;

    set_place(data,current,point.x,point.y);

}

void setup_positions(cell_list &place, place_type &current) 
{

    current = set_type(current);
    if (mouse_down(LEFT_BUTTON))
    {
        switch (current)
        {
            case START:
                move_place(place,current);
                break;
            case END:
                move_place(place,current);
                break;
            case WALL:
                create_places(place,current);
                break;
            case BLANK:
                create_places(place,current);
                break;
            case STOPS:
                create_places(place,current);
            default:
                break;
        }   
    }
}
