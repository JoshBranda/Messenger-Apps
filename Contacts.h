#ifndef CONTACTS_LIST
#define CONTACTS_LIST
#include"Person.h"

class Contacts {
    public:
        Contacts(); //Line 8
        Contacts(const Contacts & to_copy); //Line 15
        ~Contacts(); //Line 23

        void Display_All(); //Line 37
        int display_single(char * to_search); //Line 51

        int insert_contact(Person & to_add); //Line 70
        int add_msg(message * to_add); //Line 82

        Contacts & operator=(Contacts & to_copy); //Line 100

    private:
        class node { //Nested class
            public:
                node(); //Line 107
                node(Person & to_add); //Line 114
                ~node();    //122

            private:
                Person * my_person;
                node * next;

                friend class Contacts;
        };

        node * head;

        int copy_c_list(node * to_copy); //Line 130
};

#endif
