#include"Application.h"
#include"Globals.h"
#include<iostream>
#include<cstring>

using namespace std;

Application::Application()
{
    total_inbox = 0;
}



Application::~Application()
{
}



void Application::enter_contacts()
{
    char    choice = 'k';
    char    name_choice[MAX];
    int     result;

    while (choice != 'e' && choice != 'E')
    {
        cout << "Please choose one of the following: " << endl;
        cout << "A: View your contacts" << endl;
        cout << "B: View all messages from a given contact" << endl;
        cout << "E: Exit back to main menu" << endl;
    
        cin >> choice;
        cin.ignore();
        cout << endl;

        if (choice == 'a' || choice == 'A')
            contact_list.Display_All();

        else if (choice == 'b' || choice == 'B')
        {
            cout << "What is the name of the contact?" << endl;

            cin.getline(name_choice, MAX_BODY, '\n');
            cout << endl;

            result = contact_list.display_single(name_choice);
        
            if (result == 0) //Error check 1
                cout << "This contact is not in your list!" << endl << endl;

            if (result == -1) //Error check 2
                cout << "There are no messages from this user!" << endl << endl;
        }

        else if (choice != 'e' && choice != 'E')
            cout << "Invalid option!  Please try again!" << endl << endl;
    }
}



void Application::enter_inbox()
{
    char *      array;
    char        new_body[MAX_BODY];
    int         choice = 0;
    char        menu_choice = 'k';
    message *   temp = NULL;

    cout << endl << "You have " << total_inbox << " messages in your inbox" << endl << endl;

    while (menu_choice != 'e' && menu_choice != 'E')
    {
        Email *     e_temp = NULL; //Resets the pointers for each while iteration
        Facebook *  f_temp = NULL;
        Text *      t_temp = NULL; 

        my_archive.display_inbox();

        cout << endl << endl;
        cout << "Please choose one of the following: " << endl;
        cout << "A: Choose a message to read" << endl;
        cout << "E: Exit back to main menu" << endl;
    
        cin >> menu_choice;

        if (menu_choice == 'a' || menu_choice == 'A')
        {
            cout << "Enter the message number you would like to read: ";
            cin >> choice;
            cout << endl;

            temp = my_archive.return_message(choice);  //Get the pointer to the message

            if (!temp)
                cout << "There's no email corresponding to this number!" << endl << endl;

            else
            {
                array = temp->return_author(); //Get the sender info

                if (strchr(array, '@') != NULL) //Check if the message is an email
                    e_temp = (Email*)(temp); //Explicit downcasting

                else
                {
                    for (unsigned int x = 0; x < strlen(array); x++)
                    {
                        if (isdigit(array[x])) //Check if it is a text
                        {
                            t_temp = (Text*)(temp); //Explicit downcasting
                            x = strlen(array); //Break the loop if so
                        }
                    }               
                }

                if (!e_temp && !t_temp) //If not the others, it must be a facebook msg
                    f_temp = (Facebook*)(temp);  //Explicit downcasting
            
                cout << temp;

                cout << "Reply: R " << endl;
                cout << "Forward: F " << endl;
                cout << "Exit to main menu: E" << endl;
                cin >> menu_choice;

                if (menu_choice == 'r' || menu_choice == 'R')
                {
                    cout << "Enter your reply and type '#' then enter when done:" << endl;
                    cin.getline(new_body, MAX_BODY, '#');

                    if (e_temp)
                    {
                        if (*e_temp + new_body == 0) //Error check to make sure message size is within global constant
                            cout << "I'm sorry, your message was too big!  We are a start-up, so please understand" << endl << endl;
                        else
                        {
                            cout << e_temp;
                            cout << "Your message will now appear in your inbox with the reply appended as above" << endl << endl;                  
                            cout << "Hit enter to continue" << endl << endl;
                            cin.ignore();
                            cin.ignore();
                        }
                    }
                    else if (f_temp)
                    {
                        if (*f_temp + new_body == 0)
                            cout << "I'm sorry, your message was too big!  We are a start-up, so please understand" << endl << endl;
                        else
                        {
                            cout << f_temp;
                            cout << "Your message will now appear in your inbox with the reply appended as above" << endl << endl;                  
                            cout << "Hit enter to continue" << endl << endl;
                            cin.ignore();
                            cin.ignore();
                        }
                    }
                    else
                    {
                        if (*t_temp + new_body == 0)
                            cout << "I'm sorry, your message was too big!  We are a start-up, so please understand" << endl << endl;
                        else
                        {
                            cout << t_temp;
                            cout << "Your message will now appear in your inbox with the reply appended as above" << endl << endl;                  
                            cout << "Hit enter to continue" << endl << endl;
                            cin.ignore();
                            cin.ignore();
                        }

                    }
                        
                }

                if (menu_choice == 'f' || menu_choice == 'F')
                {
                    if (e_temp)
                        forward_email(e_temp);
                    else if (f_temp)
                        forward_facebook(f_temp);
                    else
                        forward_text(t_temp);
                }
            }
        }
    }
}



void Application::run()
{
    char choice = 'k';

    cout << "Welcome to your message app!" << endl << endl;

    while (choice != 'e' && choice != 'E')
    {
        cout << "Please choose one of the following: " << endl;
        cout << "A: View your inbox" << endl;
        cout << "B: Send a message" << endl;
        cout << "C: Contacts list" << endl;
        cout << "D: Display all messages" << endl;
        cout << "E: Exit app" << endl;
        cout << "F: Check copy constructors (programmers only!)" << endl;

        cin >> choice;
        cout << endl;

        if (choice == 'a' || choice == 'A')
            enter_inbox();

        else if (choice == 'b' || choice == 'B')
            send_message();

        else if (choice == 'c' || choice == 'C')
            enter_contacts();

        else if (choice == 'd' || choice == 'D')
            my_archive.display_in_order();

        else if (choice == 'f' && choice != 'F')
            check_copy();

        else if (choice != 'e' && choice != 'E')
            cout << "Invalid option!  Please try again!" << endl << endl;
    }   

    
}



int Application::add_email(const Email & to_add)
{
    message * temp = my_archive.insert_email(to_add); //Adds the email and returns a pointer to it
    
    return contact_list.add_msg(temp); //Takes the pointer and adds it to the contacts list of messages
}



int Application::add_facebook(const Facebook & to_add)
{
    message * temp = my_archive.insert_facebook(to_add);

    return contact_list.add_msg(temp);
}



int Application::add_text(const Text & to_add)
{
    message * temp = my_archive.insert_text(to_add);
    
    return contact_list.add_msg(temp);
}



int Application::increment_inbox()
{
    return ++total_inbox;
}



int Application::return_inbox()
{
    return total_inbox;
}



int Application::add_contact(Person & to_add)
{
    return contact_list.insert_contact(to_add);     
}



int Application::forward_email(Email * to_copy)
{
    Email e_forward;

    e_forward = to_copy; //Assignment operator overload

    cout << "We have a copy of your message to forward, " << endl;
    cout << "but there doesn't seem to be an internet connection!" << endl << endl;     

    return 0;
}




int Application::forward_text(Text * to_copy)
{
    Text t_forward;

    t_forward = to_copy;

    cout << "We have a copy of your message to forward, " << endl;
    cout << "but there doesn't seem to be an internet connection!" << endl << endl;     

    return 0;
}



int Application::forward_facebook(Facebook * to_copy)
{
    Facebook f_forward;

    f_forward = to_copy;

    cout << "We have a copy of your message to forward, " << endl;
    cout << "but there doesn't seem to be an internet connection!" << endl << endl;     

    return 0;
}


//This class only exists to test the copy constructors for the 2-3-4 tree and contact list.  They are otherwise unused.
int Application::check_copy()
{
    Storage archive2(my_archive);
    Contacts new_list(contact_list);

    my_archive.display_in_order();
    cout << "YOUR ORIGINAL ARCHIVE^^^^^^^^^^^^^^^^^^^^^^^^^" << endl << endl;

    archive2.display_in_order();
    cout << "YOUR NEW ARCHIVE^^^^^^^^^^^^^^^^^^^^^^^^^" << endl << endl;

    cout << "Press enter to continue:" << endl;
    cin.ignore();
    cin.ignore();

    contact_list.Display_All();
    cout << "YOUR ORIGINAL CONTACTS LIST^^^^^^^^^^^^^^^^^^^^^^^^^" << endl << endl;

    new_list.Display_All();
    cout << "YOUR NEW CONTACTS LIST^^^^^^^^^^^^^^^^^^^^^^^^^" << endl << endl;

    cout << "Press enter to continue:" << endl;
    cin.ignore();

    return 1;   
}



int Application::send_message()
{
    message * to_send;
    char choice = 'x';
    char name[MAX];
    char body[MAX_BODY];

    char subject[MAX];
    char friends;   

    cout << "Would you like to send an email, text, or facebook message?" << endl << endl;
    
    while (choice != 'M' && choice != 'm')
    {
        cout << "F:Facebook, E:Email, T:Text, M:Main Menu" << endl;
        cin >> choice;
        cin.ignore();

        if (choice == 'F' || choice == 'f')
        {
            cout << "What is your facebook name?" << endl;
            cin.getline(name, MAX);
        
            cout << endl << "Are you friends with the receiver? Y/N" << endl;
            cin >> friends;

            cout << endl << "Please enter your message here and type '#' followed by enter to finish" << endl << endl;

            cin.getline(body, MAX_BODY, '#');   

            time_t current = time(nullptr);
            char * time_array = new char [strlen(ctime(&current)) + 1]; //Takes the current time and places it into the new message
            strcpy(time_array,ctime(&current));

            to_send = new Facebook(name, body, time_array, 0, friends);  
            delete time_array;
        }

        else if (choice == 'E' || choice == 'e')
        {
            cout << "What is your email address?" << endl;
            cin.getline(name, MAX);
        
            cout << endl << "Enter your subject line:" << endl;
            cin.getline(subject, MAX);

            cout << endl << "Please enter your message here and type '#' followed by enter to finish" << endl << endl;

            cin.getline(body, MAX_BODY, '#');   

            time_t current = time(nullptr);
            char * time_array = new char [strlen(ctime(&current)) + 1];
            strcpy(time_array,ctime(&current));

            to_send = new Email(subject, name, body, time_array, 0);  
            delete time_array;
        }

        else if (choice == 'T' || choice == 't')
        {
            cout << "What is your phone number?" << endl;
            cin.getline(name, MAX);
        
            cout << endl << "Please enter your message here and type '#' followed by enter to finish" << endl << endl;

            cin.getline(body, MAX_BODY, '#');   

            time_t current = time(nullptr);
            char * time_array = new char [strlen(ctime(&current)) + 1];
            strcpy(time_array,ctime(&current));

            to_send = new Text(name, body, time_array, 0);  
            delete time_array;
        }
        else if (choice != 'M' && choice != 'm')
            cout << "This is not a valid option!" << endl << endl;
        
        cout << "Great, we have your message ready to send.  Here's how it looks:" << endl << endl;

        if (choice != 'm' && choice != 'M')
        {
            cout << to_send << endl;
            cout << "Press enter to continue" << endl;
            cin.ignore();
            cin.ignore();
            cout << "Whoops!  Your internet appears to be down.  Please come back later to send messages!" << endl << endl;
			delete to_send;
        }
    }

    return 1;
}



int operator+(Application & source, const Email & to_add)
{
    message * temp = source.my_archive + to_add;
    
    return source.contact_list.add_msg(temp);
}



int operator+(Application & source, const Facebook & to_add)
{
    message * temp = source.my_archive + to_add;
    
    return source.contact_list.add_msg(temp);
}



int operator+(Application & source, const Text & to_add)
{
    message * temp = source.my_archive + to_add;
    
    return source.contact_list.add_msg(temp);
}



