#include"Person.h"
#include<iostream>
#include<cstring>

using namespace std;

Person::Person()
{
    name            = NULL;
    tag             = NULL;
    contact_info    = NULL;
    head            = NULL;
}



Person::Person(const char * to_name, const char * to_tag, const char * to_contact)
{
    name = new char[strlen(to_name) + 1];
    strcpy(name, to_name);

    tag = new char[strlen(to_tag) + 1];
    strcpy(tag, to_tag);

    contact_info= new char[strlen(to_contact) + 1];
    strcpy(contact_info, to_contact);

    head = NULL;

}



Person::Person(const Person & to_copy)
{
    if (to_copy.name)
    {
        name = new char[strlen(to_copy.name) + 1];
        strcpy(name, to_copy.name);
    }

    if (to_copy.tag)
    {
        tag = new char[strlen(to_copy.tag) + 1];
        strcpy(tag, to_copy.tag);
    }

    if (to_copy.contact_info)
    {
        contact_info= new char[strlen(to_copy.contact_info) + 1];
        strcpy(contact_info, to_copy.contact_info);
    }

    copy_list(to_copy.head);
}



Person::~Person()
{
    if (name)
    {
        delete [] name;
        name = NULL;
    }
    if (tag)
    {
        delete [] tag;
        tag = NULL;
    }
    if (contact_info)
    {
        delete [] contact_info;
        contact_info = NULL;
    }

    while (head)
    {
        user_node * temp = head;
        head = head->next;
        delete temp;
    }
}



void Person::display_person()
{
    if (name && tag && contact_info)
        cout << name << "  " << tag << "  " << contact_info << endl;    

    return;
}



int Person::display_user_msgs()
{
    if (!head)
        return -1;

    user_node * current = head;

    while (current)
    {
        cout << current->data;
        current = current->next;
    }   

    return 1;
}



char * Person::return_name()
{
    return name;
}



char * Person::return_contact_info()
{
    return contact_info;
}



int Person::add_message(message & to_add)
{
    user_node * temp = new user_node;
    temp->data = &to_add;   
    temp->next = head;
    head = temp;
    
    return 1;
}



int Person::copy_person(const Person * to_copy)
{
    if (to_copy->name)
    {
        name = new char[strlen(to_copy->name) + 1];
        strcpy(name, to_copy->name);
    }

    if (to_copy->tag)
    {
        tag = new char[strlen(to_copy->tag) + 1];
        strcpy(tag, to_copy->tag);
    }

    if (to_copy->contact_info)
    {
        contact_info= new char[strlen(to_copy->contact_info) + 1];
        strcpy(contact_info, to_copy->contact_info);
    }

    return copy_list(to_copy->head);
}



Person & Person::operator=(Person & to_copy)
{
    if (to_copy.name)
    {
        name = new char[strlen(to_copy.name) + 1];
        strcpy(name, to_copy.name);
    }

    if (to_copy.tag)
    {
        tag = new char[strlen(to_copy.tag) + 1];
        strcpy(tag, to_copy.tag);
    }

    if (to_copy.contact_info)
    {
        contact_info= new char[strlen(to_copy.contact_info) + 1];
        strcpy(contact_info, to_copy.contact_info);
    }

    copy_list(to_copy.head);
    return *this;
}


int Person::copy_list(user_node * copy_head)
{
    if (!copy_head)
    {
        head = NULL;
        return -1;
    }

    head = new user_node;
    head->data = copy_head->data;
    head->next = NULL;

    user_node * current = head;

    while (copy_head->next)
    {
        current->next = new user_node;
        current->next->data = copy_head->next->data;
        current->next->next = NULL;

        current = current->next;
        copy_head = copy_head->next;    
    }   

    return 1;
}
