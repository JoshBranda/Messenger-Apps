#include"Vertex.h"
#include"Globals.h"
#include<iostream>
#include<cstring>

using namespace std;

vertex::vertex()
{
    archived = new message * [MAX_DATA];

    for (int x = 0; x < MAX_DATA; x++)
    {
        archived[x] = NULL;
    }

    children = new vertex * [MAX_NODES];
    
    for (int x = 0; x < MAX_NODES; x++)
        children[x] = NULL; 
}



vertex::vertex(vertex & to_copy)
{
    archived = new message * [MAX_DATA];

    for (int x = 0; x < MAX_DATA; x++)
    {
        archived[x] = to_copy.copy_type(x);
    }

    children = new vertex * [MAX_NODES];
    
    for (int x = 0; x < MAX_NODES; x++)
        children[x] = NULL; 
}



vertex::~vertex()
{
    for (int x = 0; x < MAX_DATA; x++)
    {
        if (archived[x])
        {
            delete archived[x];
            archived[x] = NULL;
        }
    }

    delete [] archived;

    delete [] children;
}



message * vertex::copy_type(int to_copy)
{
    char *      array;
    message *   temp = NULL;

    temp = archived[to_copy];
    
    if (!temp)
        return NULL;

    array = temp->return_author();

    if (strchr(array, '@') != NULL)
    {
        Email * e_temp = (Email*)(temp);
        Email * e_new = new Email;
        e_new->copy_email(e_temp);
        return e_new;
    }

    else
    {
        for (unsigned int x = 0; x < strlen(array); x++)
        {
            if (isdigit(array[x]))
            {
                Text * t_temp = (Text*)(temp);
                Text * t_new = new Text;
                t_new->copy_text(t_temp);
                return t_new;   
            }
        }               
    }

    Facebook * f_temp = (Facebook*)(temp);
    Facebook * f_new = new Facebook;
    f_new->copy_facebook(f_temp);
    return f_new;   
}



int vertex::copy_vertex(vertex * to_copy)
{
    if (archived)
    {
        for (int x = 0; x < MAX_DATA; x++)
        {
            if (archived[x])
            {
                delete archived[x];
                archived[x] = NULL;
            }
        }

        delete [] archived;
    }

    if (children)
        delete [] children;

    archived = new message * [MAX_DATA];

    for (int x = 0; x < MAX_DATA; x++)
    {
        archived[x] = to_copy->copy_type(x);
    }

    children = new vertex * [MAX_NODES];
    
    for (int x = 0; x < MAX_NODES; x++)
        children[x] = NULL; 

    return 1;
}



vertex & vertex::operator=(vertex & to_copy)
{
    archived = new message * [MAX_DATA];

    for (int x = 0; x < MAX_DATA; x++)
    {
        archived[x] = to_copy.copy_type(x);
    }

    children = new vertex * [MAX_NODES];
    
    for (int x = 0; x < MAX_NODES; x++)
        children[x] = NULL; 

    return *this;
}
