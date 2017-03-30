#ifndef MY_STORAGE
#define MY_STORAGE

#include"Vertex.h"
#include"Message.h"

class Storage {
    public:
        Storage(); //Line 7
        Storage(const Storage & to_copy); //Line 14
        ~Storage(); //Line 21

        int display_in_order(); //Line 29
        int display_inbox(); //Line 39
        message * return_message(int retrieve); //Line 49

        int destroy_archive(vertex *& current); //Line 59
        message * insert_email(const Email & to_add); //Line 86
        message * insert_facebook(const Facebook & to_add); //Line 102
        message *  insert_text(const Text & to_add); //Line 118

    private:
        int display_in_order(vertex * current); //Line 134
        int display_inbox(vertex * current); //Line 169
        message * return_message(int retrieve, vertex * current); //Line 204

        message * insert_email(const Email & to_add, vertex *& current, vertex *& previous); //Line 227
        message * insert_facebook(const Facebook & to_add, vertex *& current, vertex *& previous); //Line 361
        message * insert_text(const Text & to_add, vertex *& current, vertex *& previous); //Line 495
        int copy_storage(vertex * source, vertex *& current); //Line 629

        Storage & operator=(Storage & to_copy); //Line 649

        vertex * root;

};

message * operator+(Storage & source, const Email & to_add); //Line 658
message * operator+(Storage & source, const Facebook & to_add);  //Line 666
message * operator+(Storage & source, const Text & to_add); //Line 674

#endif
