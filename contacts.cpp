#include"Contacts.h"
#include"Person.h"
#include<iostream>
#include<cstring>

using namespace std;

Contacts::Contacts()
{
    head = NULL;
}



Contacts::Contacts(const Contacts & to_copy)
{
    head = NULL;
    copy_c_list(to_copy.head);  
}



Contacts::~Contacts()
{
    while (head)
    {
        node * temp = head;
        head = head->next;
        delete temp;
        temp = NULL;
    }

}



void Contacts::Display_All() //Displays all user names
{
    node * current = head;

    while (current)
    {
        current->my_person->display_person();   
        current = current->next;
    }
    cout << endl << endl;
}



int Contacts::display_single(char * to_search) //Displays all msgs from a single user
{
    node *  current = head;
    int     success = 0;

    while (current)
    {
        if (strcmp(to_search, current->my_person->return_name() ) == 0)
        {
            success = current->my_person->display_user_msgs();
        }
        current = current->next;    
    }
    
    return success;
}



int Contacts::insert_contact(Person & to_add)
{
    node * current = new node(to_add);

    current->next = head;
    head = current;

    return 1;
}



int Contacts::add_msg(message * to_add)
{
    node * current = head;
    
    while (current)
    {
        if (strcmp(to_add->return_author(), current->my_person->return_contact_info()) == 0)
        {
            current->my_person->add_message(*to_add);   
        }
        current = current->next;
    }
    
    return 1;   
}



Contacts & Contacts::operator=(Contacts & to_copy)
{
    head = NULL;
    copy_c_list(to_copy.head);  
    return *this;
}

Contacts::node::node()
{
    my_person   = NULL;
    next        = NULL;
}


Contacts::node::node(Person & to_add)
{
    my_person   = new Person(to_add);
    next        = NULL;
}



Contacts::node::~node()
{
    if (my_person)
        delete my_person;
}



int Contacts::copy_c_list(node * to_copy)
{
    if (!to_copy)
    {
        head = NULL;
        return -1;
    }

    head = new node;
    head->my_person = new Person;
    head->my_person->copy_person(to_copy->my_person);
    head->next = NULL;

    node * current = head;

    while (to_copy->next)
    {
        current->next = new node;
        current->next->my_person = new Person;
        current->next->my_person->copy_person(to_copy->next->my_person);
        current->next->next = NULL;

        current = current->next;
        to_copy = to_copy->next;    
    }   

    return 1;
        
}



