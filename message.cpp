#include"Message.h"
#include"Globals.h"
#include<iostream>
#include<cstring>

using namespace std;

message::message()
{
    author  = NULL;
    body    = NULL;
    time    = NULL;
    number  = 0;
}



message::message(const char * this_author, const char * initial_msg, const char * c_time, int num)
{
    author = new char[strlen(this_author) + 1];
    strcpy(author, this_author);

    body = new char[strlen(initial_msg) + 1];
    strcpy(body, initial_msg);

    time = new char[strlen(c_time) + 1];
    strcpy(time, c_time);

    number = num; 
}



message::message(const message & to_copy)
{
    author = new char[strlen(to_copy.author) + 1];
    strcpy(author, to_copy.author);
    body = new char [strlen(to_copy.body) + 1];
    strcpy(body, to_copy.body);
    time = new char [strlen(to_copy.time) + 1];
    strcpy(time, to_copy.time);
    number = to_copy.number;
}



message::~message()
{
    if (author)
        delete [] author;
    if (body)
        delete [] body;
    if (time)
        delete [] time;
}



char* message::return_author()
{
    return author;
}



char* message::return_body()
{
    return body;
}



char* message::return_time()
{
    return time;
}



int message::print_number()
{
    cout << number << " ";
    return 1;
}



int message::print_inbox()
{
    cout << number << "  " << author << "  " << time << "  ";

    int str_max = strlen(body);
    
    for (int x = 0; x < 25; x++) //Shows a small portion of the message
    {
        if (body[x] == '\n')
            x = 25;
        else if (x < str_max)
            cout << body[x];
    }

    cout << "..." << endl; //Followed by ...

    return 1;
}



int message::return_number () const
{
    return number;
}



int message::change_values(const char * this_author, const char * initial_msg, const char * c_time)
{
    if (author)
        delete [] author;

    author = new char[strlen(this_author) + 1];
    strcpy(author, this_author);

    if (body)
        delete [] body;

    body = new char[strlen(initial_msg) + 1];
    strcpy(body, initial_msg);

    if (time)
        delete [] time;

    time = new char[strlen(c_time) + 1];
    strcpy(time, c_time);

    number = 0;

    return 1;
}



int message::replace_body(const char to_replace[])
{
    if (!to_replace)
        return 0;

    if (body)
        delete [] body;

    body = new char[strlen(to_replace) + 1];
    strcpy(body, to_replace);

    return 1;
}



int message::get_values(message * to_copy)
{
    if (!to_copy)
        return 0;

    if (author)
        delete [] author;

    author = new char[strlen(to_copy->author) + 1];
    strcpy(author, to_copy->author);    

    if (body)
        delete [] body;

    body = new char[strlen(to_copy->body) + 1];
    strcpy(body, to_copy->body);

    if (time)
        delete [] time;

    time = new char[strlen(to_copy->time) + 1];
    strcpy(time, to_copy->time);

    number = to_copy->number;


    return 1;
}



ostream & operator<<(ostream & os, message * s)
{
    s->print_message();
    return os;
}



Facebook::Facebook(): message()
{
    friends = 'N';
}



Facebook::Facebook(const char * msg_author, const char * to_start, const char * c_time, int num) : message(msg_author, to_start, c_time, num)
{
    friends = 'N';
}



Facebook::Facebook(const char * msg_author, const char * to_start, const char * c_time, int num, char is_friend) : message(msg_author, to_start, c_time, num)
{
    friends = is_friend;;
}



Facebook::Facebook(const Facebook & to_copy): message(to_copy)
{
    friends = to_copy.friends;
}



Facebook::~Facebook()
{
}



int Facebook::print_message()
{
    cout << "Facebook: " << return_author() << endl;
    cout << "Friends: " << friends << endl;
    cout << return_time() << endl << endl;

    cout << return_body() << endl;

    return 1;
}



int Facebook::copy_facebook(Facebook * to_copy)
{
    if (!to_copy) //Error check
        return 0;

    friends = to_copy->friends;

    this->get_values(to_copy);

    return 1;
}



Facebook & Facebook::operator=(Facebook * to_copy)
{
    char * new_author = to_copy->return_author();
    char * new_body = to_copy->return_body();
    char * new_time = to_copy->return_time();

    this->change_values(new_author, new_body, new_time);
    return *this;
} 



int operator+(Facebook & original, char to_copy[])
{
    char    array[]         = "\n\nYou replied:\n";

    int length = strlen(original.return_body()) + strlen(array) + strlen(to_copy) + 1;
    char new_body[length];

    if (length >= MAX_BODY)
        return 0;   

    strcpy(new_body,original.return_body());
    strcat(new_body, array);
    strcat(new_body, to_copy);
    
    original.replace_body(new_body);

    return 1;
} 



Email::Email(): message()
{
    subject_line = NULL;
}



Email::Email(const char * subject, const char * msg_author, const char * to_start, const char * c_time, int num): message(msg_author, to_start, c_time, num)
{
    subject_line = new char [strlen(subject) + 1];
    strcpy(subject_line, subject);
}



Email::Email(const Email & to_copy): message(to_copy)
{
    subject_line = new char [strlen(to_copy.subject_line) + 1];
    strcpy(subject_line, to_copy.subject_line);
}



Email::~Email()
{
    if (subject_line)
        delete [] subject_line;
}



int Email::print_message()
{
    cout << "Email: " << return_author() << endl;
    cout << return_time() << endl << endl;
    cout << "Subject: " << subject_line << endl << endl;

    cout << return_body() << endl;

    return 0;
}



int Email::copy_email(Email * to_copy)
{
    if (!to_copy)
        return 0;

    subject_line = new char [strlen(to_copy->subject_line) + 1];
    strcpy(subject_line, to_copy->subject_line);

    this->get_values(to_copy);

    return 1;
}



Email & Email::operator=(Email * to_copy)
{
    char * new_author = to_copy->return_author();
    char * new_body = to_copy->return_body();
    char * new_time = to_copy->return_time();

    if (to_copy->subject_line)
    {
        if (this->subject_line)
            delete this->subject_line;
    
        this->subject_line = new char[strlen(to_copy->subject_line) + 1];
        strcpy(this->subject_line, to_copy->subject_line);  
    }
    
    this->change_values(new_author, new_body, new_time);
    return *this;
}



int operator+(Email & original, char to_copy[])
{
    char    array[]         = "\n\nYou replied:\n";

    int length = strlen(original.return_body()) + strlen(array) + strlen(to_copy) + 1;
    char new_body[length];

    if (length >= MAX_BODY)
        return 0;   

    strcat(new_body,original.return_body());
    strcat(new_body, array);
    strcat(new_body, to_copy);
    
    original.replace_body(new_body);

    return 1;
} 



Text::Text(): message()
{
}



Text::Text(const char * msg_author, const char * to_start, const char * c_time, int num): message(msg_author, to_start, c_time, num)
{

}



Text::Text(const Text & to_copy): message(to_copy)
{
}



Text::~Text()
{
}



int Text::print_message()
{
    cout << "Text: " << return_author() << endl;
    cout << return_time() << endl << endl;

    cout << return_body() << endl;

    return 1;
}



int Text::copy_text(Text * to_copy)
{
    if (!to_copy)
        return 0;

    this->get_values(to_copy);

    return 1;
}



Text & Text::operator=(Text * to_copy)
{
    char * new_author = to_copy->return_author();
    char * new_body = to_copy->return_body();
    char * new_time = to_copy->return_time();

    this->change_values(new_author, new_body, new_time);
    return *this;
} 



int operator+(Text & original, char to_copy[])
{
    char    array[]         = "\n\nYou replied:\n";

    int length = strlen(original.return_body()) + strlen(array) + strlen(to_copy) + 1;
    char new_body[length];

    if (length >= MAX_BODY)
        return 0;   

    strcat(new_body,original.return_body());
    strcat(new_body, array);
    strcat(new_body, to_copy);
    
    original.replace_body(new_body);

    return 1;
} 
