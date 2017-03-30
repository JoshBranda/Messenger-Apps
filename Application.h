#ifndef APPLICATION
#define APPLICATION

#include"Contacts.h"
#include"Storage.h"

class Application {
    public:
        Application(); //Line 8
        ~Application(); //Line 15

        void enter_contacts(); //Line 21
        void enter_inbox(); //Line 64
        void run(); //Line 193
        int add_email(const Email & to_add); //Line 236
        int add_facebook(const Facebook & to_add); //Line 245
        int add_text(const Text & to_add); //Line 254
        int increment_inbox(); //Line 263
        int return_inbox(); //Line 270
        int add_contact(Person & to_add); //Line 277
        int forward_email(Email * temp); //Line 284
        int forward_text(Text * temp); //Line 299
        int forward_facebook(Facebook * temp); //Line 313
        int check_copy(); //Line 327
        int send_message(); //Line 356

        friend int operator+(Application & source, const Email & to_add);//Line 451
        friend int operator+(Application & source, const Facebook & to_add);//Line 460  
        friend int operator+(Application & source, const Text & to_add);//Line 469

    private:
        Contacts contact_list;
        Storage my_archive;
        int total_inbox;
};



#endif
