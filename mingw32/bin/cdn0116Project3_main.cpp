/* Author: Clinton Nguyen
   Instructor:  Shrestha
   Description: CSCE 1030 Project 03
*/

#include "cdn0116Project3_header.h"

int main()
{
    do
    {
        cout << "1.Add\n2.Remove\n3.Display\n4.Search\n5.Results\n6.Quit" << endl; //display menu
        cout << "Enter choice:";
        int num;
        cin >> num;
        Menu choice = static_cast<Menu>(num);
        switch (choice)
        {
            case (Add): //user entered 1
            {
                add_Student();
                break;
            }
            case (Remove): //user entered 2
            {
                cout << "Enter ID of student to remove:";
                string idRemove;
                cin >>  idRemove;
                remove_Student(idRemove);
                break;
            }
            case (Display): //user entered 3
            {
                display();
                break;
            }
            case (Search): //user entered 4
            {
                cout << "Enter ID of student to search:";
                string idSearch;
                cin >>  idSearch;
                search(idSearch);
                break;

            }
            case (Results): //user entered 5
            {
                exportResults();
                break;
            }
            case (Quit): //user entered 6
            {
                cout << "Bye!!!" << endl;
                exit(1);
            }
            default: //user entered an unsuitable number
            {
                cout << "Incorrect choice. Please enter again." << endl;
                break;
            }
        }
    }
    while(true); //keeps looping if user chooses not to quit
}
