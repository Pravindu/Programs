#include "pathfinding.h"


void add_child_to_link_list(cell &data, linked_list &list,cell end,node parent)
{
    if ((data != nullptr) and (data->object.type != WALL) and (not (data -> tracked)))
    {
        data ->tracked = true; 
        node child = new node_data();
        child ->in_cell = data;
        child ->g=parent->g+1;
        child ->h=((child->in_cell->x  - end->x)*(child->in_cell->x - end->x) +(child->in_cell->y - end->y)*(child->in_cell->y - end->y));
        child ->f=child->g+child->h;
        child ->parent = parent;
        child ->in_list = &list;
        child ->next=nullptr;
        if (not list_is_empty(list))
        {
            list.last -> next = child;
            child->prev=list.last;
            list.last=child;
        }
        else
        {
            child->prev=nullptr;
            list.first = child;
            list.last = child;
        }
    }
}

void add_children(node &parent,cell &end,linked_list &list)
{
    add_child_to_link_list(parent ->in_cell->up,list,end,parent);
    add_child_to_link_list(parent ->in_cell->down,list,end,parent);
    add_child_to_link_list(parent ->in_cell->left,list,end,parent);
    add_child_to_link_list(parent ->in_cell->right,list,end,parent);

}

linked_list generate_children(node &parent,cell &end)
{
    linked_list list;
    initialise_list(list);
    add_children(parent,end,list);
    return list;
}

place_type select_back_track(int i)
{
    
    i = div(i,10).rem;
    place_type checks;
    switch (i)
    {
        case 0:
            checks = BACKTRACK;
            break;
        case 1:
            checks = BACKTRACK1;
            break;
        case 2:
            checks = BACKTRACK2;
            break;
        case 3:
            checks = BACKTRACK3;
            break;
        case 4:
            checks = BACKTRACK4;
            break;
        case 5:
            checks = BACKTRACK5;
            break;
        case 6:
            checks = BACKTRACK6;
            break;
        case 7:
            checks = BACKTRACK7;
            break;
        case 8:
            checks = BACKTRACK8;
            break;
        case 9:
            checks = BACKTRACK9;
            break;
        default:
            checks = BACKTRACK;
            break;
    }
    return checks;
}

place_type select_track(int i)
{
    
    i = div(i,10).rem;
    place_type checks;
    switch (i)
    {
        case 0:
            checks = TRACK;
            break;
        case 1:
            checks = TRACK1;
            break;
        case 2:
            checks = TRACK2;
            break;
        case 3:
            checks = TRACK3;
            break;
        case 4:
            checks = TRACK4;
            break;
        case 5:
            checks = TRACK5;
            break;
        case 6:
            checks = TRACK6;
            break;
        case 7:
            checks = TRACK7;
            break;
        case 8:
            checks = TRACK8;
            break;
        case 9:
            checks = TRACK9;
            break;
        default:
            checks = TRACK;
            break;
    }
    return checks;
}  

bool check_list_for(linked_list &list, cell &tracking, node &ending,int &n_cell_searched,int num)
{
    bool found = false;
    node current = list.first;
    place_type checks;
    point_2d point;
    checks = select_track(num);
    while ((current != nullptr) and  (not found) )
    {
        
        if (current->in_cell == tracking)
        {
            found = true;
            ending = current;
        }
        else
        {
            if ((current->in_cell->object.type != STOPS) and (current->in_cell->object.type != END) and (current->in_cell->object.type != START))
            {                
                if (not current->in_cell->backtrack)
                {
                    current->in_cell->object.place_sprite = set_sprite(checks);
                    point.x=(current->in_cell->x-1)*10+1;
                    point.y=(current->in_cell->y-1)*10+1;
                    sprite_set_position(current->in_cell->object.place_sprite,point);
                }
            }
        }
        draw_map(*current->in_cell->in_list);
        refresh_screen(60);
        current = current ->next;
        n_cell_searched += 1;
    }
    return found;
        

}

int back_track(node &destination,cell &start,cell_list &list,int num)
{
    place_type checks = BACKTRACK;
    checks = select_back_track(num);
    point_2d point;
    int result = 0;
    while ((destination->parent->in_cell!=start))
    {
        if (destination->parent->in_cell->object.type != STOPS)
        {
            destination->parent->in_cell->object.place_sprite = set_sprite(checks);
            point.x=(destination->parent->in_cell->x-1)*10+1;
            point.y=(destination->parent->in_cell->y-1)*10+1;
            sprite_set_position(destination->parent->in_cell->object.place_sprite,point);
        }
        destination->parent->in_cell->backtrack=true;
        destination = destination ->parent;
        draw_map(list);
        result +=1;
        refresh_screen(60);
    }
    return result;
}

void a_star_next_gen(linked_list &parents, linked_list &open, linked_list &close,cell &end, bool &full)
{
    initialise_list(open);
    node parent;
    linked_list new_gen;
    parent = parents.first;  
    int f;
    bool active = false;  
    full=true;
    if (not list_is_empty(parents))
    {
        f=parent->f;
        while (parent->next != nullptr)
        {
            parent=parent->next;   
            if (parent->f<f)    
            {
                f=parent->f;
            } 
        }
        parent = parents.first; 
        while (parent != nullptr)
        {
            full=false;

            if (parent->f<=f)
            {
                new_gen=generate_children(parent,end);
                add_into(open,new_gen);
                active = true;
            }
            else
            {
                new_gen=generate_children(parent,end);
                add_into_start(close,new_gen);
            }

            parent = parent->next;
        }
    }
    if ((not active) and (not list_is_empty(close)))
    {
        add_into_start(open,close);
        initialise_list(close);
    }
    parents = open;
    if (not list_is_empty(parents))
    {
        full = false;
    }
    
    
    
} 

void d_f_s_next_gen(linked_list &parents, linked_list &down, linked_list &close, cell &end, bool &full)
{
    initialise_list(down);
    node parent;
    linked_list new_gen;
    parent = parents.first;
    full=true;
    while (parent != nullptr)
    {
        full=false;
        if (parent->parent != nullptr)
        {
            if (parent->in_cell->y>parent->parent->in_cell->y)
            {
                new_gen=generate_children(parent,end);
                add_into(down,new_gen);
            }
            else
            {
                new_gen=generate_children(parent,end);
                add_into(close,new_gen);
            }
        }
        else
        {
            new_gen=generate_children(parent,end);
            add_into(down,new_gen);
        }
        parent = parent->next;
    }
    if (list_is_empty(down) and not list_is_empty(close))
    {
        add_to_start(down,*close.first);
        delete_node(close.first);
           
    }
    parents = down;
    if (not list_is_empty(parents))
    {
        full = false;
    }
    else 
    {
        full = true;
    }
    
    
}

void all_search_next_gen(linked_list &parents, linked_list &open,cell &end, bool &full)
{
    initialise_list(open);
    node parent;
    linked_list new_gen;
    full=true;
    if (not list_is_empty(parents))
    {
        parent = parents.first; 
        while (parent != nullptr)
        {
            full=false;
            new_gen=generate_children(parent,end);
            add_into(open,new_gen);

            parent = parent->next;
        }
    }
    parents = open;
    if (not list_is_empty(parents))
    {
        full = false;
    }
    
    
}

void write_to_file(ofstream &file,int gen,int tot_s, int lenght)
{
    double waste;
    waste = (1-double(lenght)/double(tot_s))*100;
    file << "Number of Generations: ";
    file << gen;
    file << "\n";
    file << "Number of cells searched: ";
    file << tot_s;
    file << "\n";
    file << "distance of the path found to the end: ";
    file << lenght;
    file << "\n";
    file << "Percentage of wasted search: ";
    file << waste;
    file << "%";
    file << "\n";
}

bool execute_algorithm(cell_list &list,cell start,cell end,linked_list parents,pathfinding_algorithm const &option,ofstream &file,int stop_no)
{
    bool found=false;
    bool full_check = false;
    int gen,n_search,path;
    gen= 1;
    n_search = 0;
    path = 0;
    linked_list open_list,close_list;
    linked_list end_open,end_close;
    node destination = new node_data();

    initialise_list(open_list); 
    initialise_list(close_list); 
    initialise_list(end_close); 
    initialise_list(end_open); 
    
    
    while ((not found) and (not full_check))
    {
        switch (option)
        {
        case A_STAR:
            a_star_next_gen(parents,open_list,close_list,end,full_check);
            break;
        case ALL:
            all_search_next_gen(parents,open_list,end,full_check);
            break;
        case DEPTH_F:
            d_f_s_next_gen(parents,open_list,close_list,end,full_check);
            break;
        default:
            break;
        }
        gen=gen+1;
        found = check_list_for(open_list,end,destination,n_search,stop_no);
    }

    if (found)
    {
        path=back_track(destination,start,list,stop_no); 
    }

    write_to_file(file,gen,n_search,path);

    delay(1000);
    return found;
}

void reset_parents(linked_list &parents,node &parent,cell &start)
{
    initialise_list(parents); 
    set_node(parent,start);
    add_to_end(parents,*parent);
}

void path_finding(cell_list &list,ofstream &file)
{
    bool check;
    cell start;
    cell end;
    linked_list parents;
    node parent = new node_data();
    pathfinding_algorithm algorithm;

    start = search_for(list,START);
    end = search_for(list,END);
    list.first->stop_points->push_back(end);
    if ((start != nullptr) and (end != nullptr))
    {
        for (int i = 0; i < 3; i++)
        {
            reset_parents(parents,parent,start);
            algorithm = static_cast<pathfinding_algorithm> (i);
            file << "Algorithm " + to_string(i+1) + ". \n";
            for(int j=0; j<int(list.first->stop_points->size()); j++)
            {
                end = list.first->stop_points->at(j);
                check=execute_algorithm(list,start,end,parents,algorithm,file,j);
                detrack(list);
                if (check)
                    start = end;
                reset_parents(parents,parent,start);
            }
            file << "\n";
            delay(2000);
            set_map_to_maze(list);
            draw_map(list);
            refresh_screen(60);
            delay(500);

            start = search_for(list,START);

        }
    }
    list.first->stop_points->pop_back();
}