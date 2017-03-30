#ifndef VERTICES
#define VERTICES

#include"Message.h"

class vertex {
    public:
        vertex(); //Line 8
        vertex(vertex & to_copy); //Line 25
        ~vertex(); //Line 42

        message * copy_type(int to_copy); //Line 60

        int copy_vertex(vertex * to_copy); //Line 102
        
        vertex & operator=(vertex & to_copy); //Line 138

    private:
        message ** archived;
        vertex ** children;

    friend class Storage;
};

#endif
