#ifndef PERSONHOOD
#define PERSONHOOD
#include"Message.h"
#include<iostream>


class Person {
    public:
        Person(); //Line 7
        Person(const char * to_name, const char * to_tag, const char * to_contact); //Line 17
        Person(const Person & to_copy); //Line 34
        ~Person(); //Line 59

        void display_person(); //Line 87
        int display_user_msgs(); //Line 97
        char * return_name(); //Line 115
        char * return_contact_info(); //Line 122

        int add_message(message & to_add); //Line 129
        int copy_person(const Person * to_copy); //Line 141
        
        Person & operator=(Person & to_copy);

    private:
        char * name;
        char * tag;
        char * contact_info;

        struct user_node {
            message * data;
            user_node * next;
        };
    
        user_node * head;

        int copy_list(user_node * copy_head); //Line 191
};

#endif
