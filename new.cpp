#include "node.h"


void initialise_list(linked_list &list)
{
    list.first = nullptr;
    list.last = nullptr;
}

bool list_is_empty(const linked_list &list)
{
    return list.first == nullptr; 
}

node new_node(node_data &data, linked_list &list, node next, node prev)
{
    node add = new node_data();
    add ->f = data.f;
    add ->g = data.g;
    add ->h = data.h;
    add ->in_cell = data.in_cell;
    add ->in_list = &list;
    add ->parent=data.parent;
    add ->next=next;
    add ->prev=prev;
    return add;

}

void add_to_end(linked_list &list, node_data &value)
{
    node added_node;

    added_node = new_node(value, list, nullptr,list.last);

    if (not list_is_empty(list))
    {
        list.last->next = added_node; // point last node to new node
        list.last = added_node;
    }
    else
    {
        list.first = added_node;
        list.last = added_node;
    }
}

void add_into (linked_list &update, linked_list &data)
{
    node current =data.first;
    while (current != nullptr)
    { 
        add_to_end(update,*current);
        current = current -> next;
    }
    
}

void add_to_start(linked_list &list, node_data &value)
{
    node added_node;

    added_node = new_node(value, list, list.first,nullptr);

    if (not list_is_empty(list))
    {
        list.first->prev = added_node;
        list.first = added_node;
    }
    else
    {
        list.first = added_node;
        list.last = added_node;
    }
}

void add_into_start(linked_list &update, linked_list &data)
{
    node current =data.first;
    while (current != nullptr)
    { 
        add_to_start(update,*current);
        current = current -> next;
    }
    
}

void delete_node(node current) 
{
    linked_list *list;
    node before, after;

    list = current->in_list;
    before = current->prev;
    after = current->next;

    if (before != nullptr)
    {
        before->next = current->next;
    }
    else
    {
        list->first = after;
    }

    if (after != nullptr)
    {
        after->prev = current->prev;
    }
    else
    {
        list->last = before;
    }

    current->prev = nullptr;
    current->next = nullptr;

    delete current;
}

void set_node(node &parent,cell &start)
{
    parent -> in_cell=start;
    parent ->f=0;
    parent ->g=0;
    parent ->h=0;
    parent ->parent = nullptr;
    parent ->prev = nullptr;
    parent ->next = nullptr;
}
