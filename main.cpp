/* 
Joshua Sander
CS261
Project 3

This project represents a messaging app that stores messages from 3 different services: email, facebook, and text.

Deliverables:
REQUIRED balanced tree
USED 2-3-4 tree, as seen in file Storage.h/storage.cpp and Vertex.h/vertex.cpp

REQUIRED overloaded operators
USED overloaded '=' '+' and '<<'
The assignment operator was overloaded with ALL objects with dynamic memory.  Examples of it in use can be seen at:
application.cpp Line 288

The addition operator was overloaded with messages for append:
Interface: Message.h Line 48
Implementation: message.cpp Line 271
Example in use: application.cpp Line 136 

The addition operator was also overloaded for adding messages to the tree:
Interface:Storage.h Lines 38-40
Implementation: Storage.cpp Lines 658, 666, 674
Example in use: Main.cpp (this file) Line 106

The cout << operator was overloaded for printing messages to the screen:
Interface: Message.h Line 24 
Implementation: message.cpp Line 190
Example in use: application.cpp Line 122

REQUIRED copy constructors for all dynamic memory classes
USED copy constructors for all dynamic memory classes,
however, since many of the class objects were represented with pointers
and not actual data types, some of the copy constructors were not used (though defined)
and instead a separate copy function that took a pointer as an argument was chosen

REQUIRED Users can send/receive/read messages
USED
For sending, there are three methods:
1. A send message function that creates a message object, but since this is a simulation, it goes nowhere.
2. A reply function that appends the user reply to the original in the inbox
3. A forward function that copies a message for sending, but since this is a simluation, it goes nowhere.

For reading, users may enter their inbox or display all messages.

For receiving, since this is a simulation, no explicit receive function was implemented.  However, the insert
function for the 2-3-4 tree archive could work for incoming messages in a real world application as well.

*/
#include<iostream>
#include"Message.h"
#include"Application.h"
#include"Globals.h"
#include<cstring>
#include<fstream>


using namespace std;

int load_file(Application & my_application);
int load_contacts(Application & my_application);

int main()
{
	cout << "CS261 - Assignment 3 - Joshua Sander (Sorry, I forgot this last time!)" << endl << endl;
    Application my_application;

    load_contacts(my_application);

    load_file(my_application);  

    my_application.run();
    return 0;
}


//Loads messages into the 2-3-4 tree
int load_file(Application & my_application)
{
    char    tag[MAX];
    char    author[MAX];
    char    subject[MAX];
    char    date[MAX];
    char    body[MAX_BODY];
    int     total_msgs; //In this application, used for both the total inbox and kth message added

    ifstream text_file;
    text_file.open("input_file.txt");

    while (!text_file.eof())
    {
        text_file.getline(tag, MAX, '\n');
        text_file.ignore();

        total_msgs = my_application.increment_inbox();

        if (strcmp (tag, "#email") == 0)
        {
            text_file.getline(author, MAX, '\n');
            text_file.getline(date, MAX, '\n');
            text_file.getline(subject, MAX, '\n');
            text_file.getline(body, MAX_BODY, '#');

            Email temp(subject, author, body, date, total_msgs);
            my_application + temp; //Addition operator overloaded
        }

        else if (strcmp (tag, "#facebook") == 0)
        {
            text_file.getline(author, MAX, '\n');
            text_file.getline(date, MAX, '\n');
            text_file.getline(body, MAX_BODY, '#');

            Facebook temp(author, body, date, total_msgs);
            my_application + temp; //Same as above
        }

        else if (strcmp (tag, "#text") == 0)
        {
            text_file.getline(author, MAX, '\n');
            text_file.getline(date, MAX, '\n');
            text_file.getline(body, MAX_BODY, '#');

            Text temp(author, body, date, total_msgs);
            my_application + temp; //Same as above
        }
    }

    text_file.close();

    return 1;
}



int load_contacts(Application & my_application)
{
    char    name[MAX];
    char    tag[MAX];
    char    contact[MAX];

    ifstream text_file;
    text_file.open("file_people.txt");

    while (!text_file.eof())
    {
        text_file.getline(name, MAX, '\n');
        text_file.getline(tag, MAX, '\n');
        text_file.getline(contact, MAX, '\n');
        text_file.ignore();

        Person temp(name, tag, contact);
        my_application.add_contact(temp);
    }

    text_file.close();

    return 1;
}
