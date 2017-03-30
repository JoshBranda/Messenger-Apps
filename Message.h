#ifndef HEN_DUO_MESSAGES
#define HEN_DUO_MESSAGES
#include<iostream>

class message {
    public:
        message();//Line 8
        message(const char * this_author, const char * initial_msg, const char * c_time, int num);//Line 18
        message(const message & to_copy); //Line 34
        virtual ~message(); //Line 47 

        virtual int print_message() = 0;
        char* return_author(); //Line 59
        char* return_body(); //Line 66
        char* return_time(); //Line 73
        int print_number(); //Line 80
        int print_inbox(); //Line 88
        int return_number() const; //Line 109

        int change_values(const char * this_author, const char * initial_msg, const char * c_time); //Line 116
        int replace_body(const char * to_replace); //Line 143
        int get_values(message * to_copy); //Line 159
    
        friend std::ostream & operator<<(std::ostream & os, message * m);//Line 190

    private:
        char * author;
        char * body;
        char * time;
        int number;
};



class Facebook: public message {
    public:
        Facebook(); //Line 198
        Facebook(const char * msg_author, const char * to_start, const char * c_time, int num);//Line 205
        Facebook(const char * msg_author, const char * to_start, const char * c_time, int num, char is_friend); //Line 212
        Facebook(const Facebook & to_copy); //Line 219
        virtual ~Facebook(); //Line 226

        virtual int print_message(); //Line 232

        int copy_facebook(Facebook * to_copy); //Line 245

        Facebook & operator=(Facebook * to_copy); //Line 259
        friend int operator+(Facebook & original, char to_copy[]); //Line 271

    private:
        char friends;       

};



class Email: public message {
    public:
        Email(); //Line 292
        Email(const char * subject, const char * msg_author, const char * to_start, const char * c_time, int num);//Line 299
        Email(const Email & to_copy);//Line 307
        virtual ~Email(); //Line 315
        
        virtual int print_message(); //Line 323

        int copy_email(Email * to_copy); //Line 336

        Email & operator=(Email * to_copy); //Line 351
        friend int operator+(Email & original, char to_copy[]); //Line 372

    private:
        char * subject_line;

};



class Text: public message {
    public:
        Text(); //Line 393
        Text(const char * msg_author, const char * to_start, const char * c_time, int num); //Line 399
        Text(const Text & to_copy); //Line 406
        virtual ~Text(); //Line 412
        
        virtual int print_message(); //Line 418

        int copy_text(Text * to_copy); //Line 430

        Text & operator=(Text * to_copy); //Line 442
        friend int operator+(Text & original, char to_copy[]); //Line 454

    private:
};
#endif
