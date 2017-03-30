#include"Storage.h"
#include<iostream>

using namespace std;


Storage::Storage()
{
    root = NULL;
}



Storage::Storage(const Storage & to_copy)
{
    copy_storage(to_copy.root, root);
}



Storage::~Storage()
{
    if (root)
        destroy_archive(root);
}



int Storage::display_in_order()
{
    if (!root)
        return 0;

    return display_in_order(root);
}



int Storage::display_inbox()
{
    if (!root)
        return 0;

    return display_inbox(root);
}



message * Storage::return_message(int retrieve)
{
    if (!root)
        return NULL;

    return return_message(retrieve, root);
}



int Storage::destroy_archive(vertex *& current)
{
    if (!current->children[0])
    {
        delete current;
        return 1;
    }

    destroy_archive(current->children[0]);
    destroy_archive(current->children[1]);
    
    if (current->children[2])
    {
        destroy_archive(current->children[2]);
        if (current->children[3])
        {
            destroy_archive(current->children[3]);
        }
    }

    delete current;
    
    return 0;
}



message * Storage::insert_email(const Email & to_add)
{
    vertex * previous = NULL;

    if (!root)
    {
        root = new vertex;
        root->archived[0] = new Email(to_add);
        return root->archived[0];
    }

    return insert_email(to_add, root, previous);
}



message * Storage::insert_facebook(const Facebook & to_add)
{
    vertex * previous = NULL;

    if (!root)
    {
        root = new vertex;
        root->archived[0] = new Facebook(to_add);
        return root->archived[0];
    }

    return insert_facebook(to_add, root, previous);
}



message * Storage::insert_text(const Text & to_add)
{
    vertex * previous = NULL;

    if (!root)
    {
        root = new vertex;
        root->archived[0] = new Text(to_add);
        return root->archived[0];
    }

    return insert_text(to_add, root, previous);
}



int Storage::display_in_order(vertex * current)
{
    if (!current)
        return 0;

    if (!current->children[0])
    {
        for (int x = 0; x < 3; x++)
        {
            if (current->archived[x])
                cout << current->archived[x];
        }   
        return 1;
    }

    display_in_order(current->children[0]);
    cout << current->archived[0];
    display_in_order(current->children[1]);
    
    if (current->archived[1])
    {
        cout << current->archived[1];
        display_in_order(current->children[2]);
        if (current->archived[2])
        {
            cout << current->archived[2];
            display_in_order(current->children[3]);
        }
    }
    
    return 1;
}



int Storage::display_inbox(vertex * current)
{
    if (!current)
        return 0;

    if (!current->children[0])
    {
        for (int x = 0; x < 3; x++)
        {
            if (current->archived[x])
                current->archived[x]->print_inbox();
        }   
        return 1;
    }

    display_inbox(current->children[0]);
    current->archived[0]->print_inbox();
    display_inbox(current->children[1]);
    
    if (current->archived[1])
    {
        current->archived[1]->print_inbox();
        display_inbox(current->children[2]);
        if (current->archived[2])
        {
            current->archived[2]->print_inbox();
            display_inbox(current->children[3]);
        }
    }
    
    return 1;
}



message * Storage::return_message(int retrieve, vertex * current)
{
    if (!current)
        return NULL;

    int x = 0;

    while (current->archived[x])
    {
        if (retrieve == current->archived[x]->return_number() )
            return current->archived[x];

        else if (retrieve < current->archived[x]->return_number() )
            return return_message(retrieve, current->children[x]);

        x++;
    }

    return return_message(retrieve, current->children[x]);
}



message * Storage::insert_email(const Email & to_add, vertex *& current, vertex *& previous)
{
    if (current->archived[2] && previous == NULL)
    {
        vertex * parent = new vertex;
        vertex * child2 = new vertex;

        parent->archived[0] = current->archived[1]; //This fills the new nodes with the required data
        child2->archived[0] = current->archived[2];
        current->archived[1] = NULL; //And also clears them out of the current full node
        current->archived[2] = NULL;

        parent->children[0] = current; //Sets the left child of the new parent node
        parent->children[1] = child2; //Sets the right child of the new parent node

        child2->children[0] = current->children[2]; //Sends the right half of the orignal node to the new sibling
        child2->children[1] = current->children[3];
        current->children[2] = NULL; //Clears the old data from the original node
        current->children[3] = NULL;

        current = parent;
    
        return insert_email(to_add, current, previous);
    }

    //Push up 
    if (current->archived[2]) //Since the middle will go up regardless, the first section splits the left and right into separate nodes and preserves the children
    { 
        vertex * leaf = new vertex;
        leaf->archived[0] = current->archived[0];
        current->archived[0] = current->archived[2];
        current->archived[2] = NULL;

        leaf->children[0] = current->children[0];
        leaf->children[1] = current->children[1];
        current->children[0] = current->children[2]; 
        current->children[1] = current->children[3];
        current->children[2] = NULL; 
        current->children[3] = NULL;
 
        if (current->archived[1]->return_number() < previous->archived[0]->return_number())
        {
            previous->archived[2] = previous->archived[1];
            previous->archived[1] = previous->archived[0];
            previous->archived[0] = current->archived[1];   
            current->archived[1] = NULL;
            
            previous->children[3] = previous->children[2];
            previous->children[2] = previous->children[1];
            previous->children[1] = current;     
            previous->children[0] = leaf;

            if (to_add.return_number() < previous->archived[0]->return_number() )
                return insert_email(to_add, previous->children[0], previous);

            return insert_email(to_add, previous->children[1], previous);
        }

        else if (!previous->archived[1] || current->archived[1]->return_number() < previous->archived[1]->return_number()) 
        {
            previous->archived[2] = previous->archived[1];
            previous->archived[1] = current->archived[1];   
            current->archived[1] = NULL;
            
            previous->children[3] = previous->children[2];
            previous->children[2] = current;
            previous->children[1] = leaf; 
            
            if (to_add.return_number() < previous->archived[1]->return_number()  )
                return insert_email(to_add, previous->children[1], previous);       
            
            return insert_email(to_add, previous->children[2], previous);
        }

        else
        {
            previous->archived[2] = current->archived[1];
            current->archived[1] = NULL;
            
            previous->children[3] = current;
            previous->children[2] = leaf;

            if (to_add.return_number() < previous->archived[2]->return_number() )
                return insert_email(to_add, previous->children[2], previous);       
            
            return insert_email(to_add, previous->children[3], previous);
        }

        
    }

    //Traverse if possible
    if (current->children[0]) //The node is not a leaf, any data item has a corresponding child
    {
        previous = current;

        if (to_add.return_number() < current->archived[0]->return_number() )
            return insert_email(to_add, current->children[0], previous);

        if (!current->archived[1] || to_add.return_number() < current->archived[1]->return_number() ) //Depends on OR stopping eval not to seg fault
            return insert_email(to_add, current->children[1], previous);

        return insert_email(to_add, current->children[2], previous);    
    }

    //Node does not have three and is leaf
    if (to_add.return_number() < current->archived[0]->return_number() )
    {
        current->archived[2] = current->archived[1];
        current->archived[1] = current->archived[0];
        current->archived[0] = new Email(to_add);
        return current->archived[0];
    }

    if (!current->archived[1])
    {
        current->archived[1] = new Email(to_add);
        return current->archived[1];
    }
    
    if (to_add.return_number() < current->archived[1]->return_number() )
    {
        current->archived[2] = current->archived[1];
        current->archived[1] = new Email(to_add);
        return current->archived[1];
    }

    current->archived[2] = new Email(to_add);
    
    return current->archived[2];
}



message * Storage::insert_facebook(const Facebook & to_add, vertex *& current, vertex *& previous)
{
    if (current->archived[2] && previous == NULL)
    {
        vertex * parent = new vertex;
        vertex * child2 = new vertex;

        parent->archived[0] = current->archived[1]; //This fills the new nodes with the required data
        child2->archived[0] = current->archived[2];
        current->archived[1] = NULL; //And also clears them out of the current full node
        current->archived[2] = NULL;

        parent->children[0] = current; //Sets the left child of the new parent node
        parent->children[1] = child2; //Sets the right child of the new parent node

        child2->children[0] = current->children[2]; //Sends the right half of the orignal node to the new sibling
        child2->children[1] = current->children[3];
        current->children[2] = NULL; //Clears the old data from the original node
        current->children[3] = NULL;

        current = parent;
    
        return insert_facebook(to_add, current, previous);
    }

    //Push up
    if (current->archived[2]) //Since the middle will go up regardless, the first section splits the left and right into separate nodes and preserves the children
    { 
        vertex * leaf = new vertex;
        leaf->archived[0] = current->archived[0];
        current->archived[0] = current->archived[2];
        current->archived[2] = NULL;

        leaf->children[0] = current->children[0];
        leaf->children[1] = current->children[1];
        current->children[0] = current->children[2]; 
        current->children[1] = current->children[3];
        current->children[2] = NULL; 
        current->children[3] = NULL;
 
        if (current->archived[1]->return_number() < previous->archived[0]->return_number())
        {
            previous->archived[2] = previous->archived[1];
            previous->archived[1] = previous->archived[0];
            previous->archived[0] = current->archived[1];   
            current->archived[1] = NULL;
            
            previous->children[3] = previous->children[2];
            previous->children[2] = previous->children[1];
            previous->children[1] = current;     
            previous->children[0] = leaf;

            if (to_add.return_number() < previous->archived[0]->return_number() )
                return insert_facebook(to_add, previous->children[0], previous);

            return insert_facebook(to_add, previous->children[1], previous);
        }

        else if (!previous->archived[1] || current->archived[1]->return_number() < previous->archived[1]->return_number()) 
        {
            previous->archived[2] = previous->archived[1];
            previous->archived[1] = current->archived[1];   
            current->archived[1] = NULL;
            
            previous->children[3] = previous->children[2];
            previous->children[2] = current;
            previous->children[1] = leaf; 
            
            if (to_add.return_number() < previous->archived[1]->return_number()  )
                return insert_facebook(to_add, previous->children[1], previous);        
            
            return insert_facebook(to_add, previous->children[2], previous);
        }

        else
        {
            previous->archived[2] = current->archived[1];
            current->archived[1] = NULL;
            
            previous->children[3] = current;
            previous->children[2] = leaf;

            if (to_add.return_number() < previous->archived[2]->return_number() )
                return insert_facebook(to_add, previous->children[2], previous);        
            
            return insert_facebook(to_add, previous->children[3], previous);
        }

        
    }

    //Traverse if possible
    if (current->children[0]) //The node is not a leaf, any data item has a corresponding child
    {
        previous = current;

        if (to_add.return_number() < current->archived[0]->return_number() )
            return insert_facebook(to_add, current->children[0], previous);

        if (!current->archived[1] || to_add.return_number() < current->archived[1]->return_number() ) //Depends on OR stopping eval not to seg fault
            return insert_facebook(to_add, current->children[1], previous);

        return insert_facebook(to_add, current->children[2], previous); 
    }

    //Node does not have three and is leaf
    if (to_add.return_number() < current->archived[0]->return_number() )
    {
        current->archived[2] = current->archived[1];
        current->archived[1] = current->archived[0];
        current->archived[0] = new Facebook(to_add);
        return current->archived[0];
    }

    if (!current->archived[1])
    {
        current->archived[1] = new Facebook(to_add);
        return current->archived[1];
    }
    
    if (to_add.return_number() < current->archived[1]->return_number() )
    {
        current->archived[2] = current->archived[1];
        current->archived[1] = new Facebook(to_add);
        return current->archived[1];
    }

    current->archived[2] = new Facebook(to_add);
    
    return current->archived[2];
}



message * Storage::insert_text(const Text & to_add, vertex *& current, vertex *& previous)
{
    if (current->archived[2] && previous == NULL)
    {
        vertex * parent = new vertex;
        vertex * child2 = new vertex;

        parent->archived[0] = current->archived[1]; //This fills the new nodes with the required data
        child2->archived[0] = current->archived[2];
        current->archived[1] = NULL; //And also clears them out of the current full node
        current->archived[2] = NULL;

        parent->children[0] = current; //Sets the left child of the new parent node
        parent->children[1] = child2; //Sets the right child of the new parent node

        child2->children[0] = current->children[2]; //Sends the right half of the orignal node to the new sibling
        child2->children[1] = current->children[3];
        current->children[2] = NULL; //Clears the old data from the original node
        current->children[3] = NULL;

        current = parent;
    
        return insert_text(to_add, current, previous);
    }

    //Push up
    if (current->archived[2]) //Since the middle will go up regardless, the first section splits the left and right into separate nodes and preserves the children
    { 
        vertex * leaf = new vertex;
        leaf->archived[0] = current->archived[0];
        current->archived[0] = current->archived[2];
        current->archived[2] = NULL;

        leaf->children[0] = current->children[0];
        leaf->children[1] = current->children[1];
        current->children[0] = current->children[2]; 
        current->children[1] = current->children[3];
        current->children[2] = NULL; 
        current->children[3] = NULL;
 
        if (current->archived[1]->return_number() < previous->archived[0]->return_number())
        {
            previous->archived[2] = previous->archived[1];
            previous->archived[1] = previous->archived[0];
            previous->archived[0] = current->archived[1];   
            current->archived[1] = NULL;
            
            previous->children[3] = previous->children[2];
            previous->children[2] = previous->children[1];
            previous->children[1] = current;     
            previous->children[0] = leaf;

            if (to_add.return_number() < previous->archived[0]->return_number() )
                return insert_text(to_add, previous->children[0], previous);

            return insert_text(to_add, previous->children[1], previous);
        }

        else if (!previous->archived[1] || current->archived[1]->return_number() < previous->archived[1]->return_number()) 
        {
            previous->archived[2] = previous->archived[1];
            previous->archived[1] = current->archived[1];   
            current->archived[1] = NULL;
            
            previous->children[3] = previous->children[2];
            previous->children[2] = current;
            previous->children[1] = leaf; 
            
            if (to_add.return_number() < previous->archived[1]->return_number()  )
                return insert_text(to_add, previous->children[1], previous);        
            
            return insert_text(to_add, previous->children[2], previous);
        }

        else
        {
            previous->archived[2] = current->archived[1];
            current->archived[1] = NULL;
            
            previous->children[3] = current;
            previous->children[2] = leaf;

            if (to_add.return_number() < previous->archived[2]->return_number() )
                return insert_text(to_add, previous->children[2], previous);        
            
            return insert_text(to_add, previous->children[3], previous);
        }

        
    }

    //Traverse if possible
    if (current->children[0]) //The node is not a leaf, any data item has a corresponding child
    {
        previous = current;

        if (to_add.return_number() < current->archived[0]->return_number() )
            return insert_text(to_add, current->children[0], previous);

        if (!current->archived[1] || to_add.return_number() < current->archived[1]->return_number() ) //Depends on OR stopping eval not to seg fault
            return insert_text(to_add, current->children[1], previous);

        return insert_text(to_add, current->children[2], previous); 
    }

    //Node does not have three and is leaf
    if (to_add.return_number() < current->archived[0]->return_number() )
    {
        current->archived[2] = current->archived[1];
        current->archived[1] = current->archived[0];
        current->archived[0] = new Text(to_add);
        return root->archived[0];
    }

    if (!current->archived[1])
    {
        current->archived[1] = new Text(to_add);
        return root->archived[1];
    }
    
    if (to_add.return_number() < current->archived[1]->return_number() )
    {
        current->archived[2] = current->archived[1];
        current->archived[1] = new Text(to_add);
        return root->archived[1];
    }

    current->archived[2] = new Text(to_add);
    
    return root->archived[2];
}



int Storage::copy_storage(vertex * source, vertex *& current)
{
    if (!source)
    {
        current = NULL;
        return 1;
    }

    current = new vertex;   
    current->copy_vertex(source);
    
    copy_storage(source->children[0], current->children[0]);
    copy_storage(source->children[1], current->children[1]);
    copy_storage(source->children[2], current->children[2]);
    copy_storage(source->children[3], current->children[3]);

    return 1;
}


Storage & Storage::operator=(Storage & to_copy)
{
    copy_storage(to_copy.root, root);
    return *this;
}




message * operator+(Storage & source, const Email & to_add)
{
    message * temp = source.insert_email(to_add);
    return temp;
}



message * operator+(Storage & source, const Facebook & to_add)
{
    message * temp = source.insert_facebook(to_add);
    return temp;
}



message * operator+(Storage & source, const Text & to_add)
{
    message * temp = source.insert_text(to_add);
    return temp;
}
