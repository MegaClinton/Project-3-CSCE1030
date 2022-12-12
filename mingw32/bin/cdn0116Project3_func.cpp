/* Author: Clinton Nguyen
   Instructor:  Shrestha
   Description: CSCE 1030 Project 03
*/

#include "cdn0116Project3_header.h"

int findMinimum(const int testScores[], int numTests)
{
    int minimum;
    if(numTests < TESTS)
    {
        minimum = 0;
        return minimum;
    }
    else if(numTests == TESTS)
    {
        minimum = testScores[0];
        for(int i = 1; i < numTests; i++)
        {
            if(testScores[i] < minimum)
            {
                minimum = testScores[i];
            }
        }
    }
    return minimum;
}

void add_Student()
{
    Student newStudent;
    string lastName;
    string firstName;

    cout << "Enter last name of the student:";
    cin.ignore(); //account for the newline character being created in the main function from cin
    getline(cin, lastName);
    cout << "Enter first name of the student:";
    getline(cin, firstName);


    newStudent.name = lastName + "," + firstName; //combines lastName and firstName together and formatted

    cout << "Enter student ID:";
    cin >> newStudent.ID;
    cout << "How many tests did this student take?";
    cin >> newStudent.numTests;

    newStudent.testScores = new int[newStudent.numTests]; //create dynamic array for test scores using numTests

    for(int i = 0; i < newStudent.numTests; i++) //prompts user for scores for numTests
    {
        cout << "Enter score #" << i + 1 << ":";
        cin >> newStudent.testScores[i];
    }

    ofstream fout;
    fout.open("student.dat", ios::app); //allows output stream to append data to the file instead of overwriting
    if(fout.fail())
    {
        cout << "File error." << endl;
        exit(1);
    }

    fout << endl;

    fout << newStudent.name << "," << newStudent.ID << "," << newStudent.numTests << ","; //writes data to file in given format
    for(int i = 0; i < newStudent.numTests; i++)
    {
        fout << newStudent.testScores[i] << ",";
    }
    delete [] newStudent.testScores;
    fout.close();
}

void remove_Student(string studentID)
{
    int numStudents = getNumber();
    Student* students = new Student[numStudents];
    bool match = false;

    ifstream fin;
    fin.open("student.dat"); //reads file
    if(fin.fail())
    {
        cout << "File error." << endl;
        exit(1);
    }

    for(int i = 0; i < numStudents; i++) //store contents of student.dat into dynamic array
    {
        string lastName;
        string firstName;
        string str;
        getline(fin, lastName, ',');
        getline(fin, firstName, ',');

        students[i].name = lastName + "," + firstName;
        getline(fin, students[i].ID, ',');
        if(students[i].ID == studentID)
        {
            match = true;
        }
        getline(fin, str, ',');
        students[i].numTests = stoi(str);
        students[i].testScores = new int[students[i].numTests];
        for(int j = 0; j < students[i].numTests; j++)
        {
            getline(fin, str, ',');
            students[i].testScores[j] = stoi(str);
        }
        fin.ignore(); //throwaway remaining whitespace so that buffer goes to next line
    }
    fin.close();
    if(match)
    {
        ofstream fout;
        fout.open("student.dat"); //overwrites file to remove the specified student ID
        if(fout.fail())
        {
            cout << "File error." << endl;
            exit(1);
        }
        int count = 0;
        for(int i = 0; i < numStudents; i++) //output new data to file
        {
            if (students[i].ID != studentID)
            {
                fout << students[i].name << "," << students[i].ID << "," << students[i].numTests << ",";
                for (int j = 0; j < students[i].numTests; j++)
                {
                    fout << students[i].testScores[j] << ",";
                }
                if(count != numStudents -2) //makes a new line (number of students - the removed student - 1) times
                {
                    fout << endl;
                    count++;
                }
            }
        }
        fout.close();
    }
    else
    {
        cout << "Student does not exist." << endl;
    }
    for(int i = 0; i < numStudents; i++)
    {
        delete [] students[i].testScores;
    }
    delete [] students;
}

void display()
{
    int numStudents = getNumber();
    Student* students = new Student[numStudents];

    ifstream fin;
    fin.open("student.dat"); //reads file
    if(fin.fail())
    {
        cout << "File error." << endl;
        exit(1);
    }

    for(int i = 0; i < numStudents; i++) //store contents of student.dat into dynamic array
    {
        string lastName;
        string firstName;
        string str;
        getline(fin, lastName, ',');
        getline(fin, firstName, ',');

        students[i].name = lastName + "," + firstName;
        getline(fin, students[i].ID, ',');
        getline(fin, str, ',');
        students[i].numTests = stoi(str);
        students[i].testScores = new int[students[i].numTests];
        for(int j = 0; j < students[i].numTests; j++)
        {
            getline(fin, str, ',');
            students[i].testScores[j] = stoi(str);
        }
        fin.ignore(); //throwaway remaining whitespace so that buffer goes to next line
    }
    for(int i = 0; i < numStudents; i++) //display dynamic array
    {
        printf("%-30s", students[i].name.c_str()); //allocate 30 spaces for name
        printf("%-15s", students[i].ID.c_str()); //allocate 15 spaces for ID
        for(int j = 0; j < students[i].numTests; j++)
        {
            printf("%-5d", students[i].testScores[j]);
        }
        cout << endl;
    }
    for(int i = 0; i < numStudents; i++)
    {
        delete [] students[i].testScores;
    }
    delete [] students;
    fin.close();

}

void search(string studentID)
{
    bool match = false;
    ifstream fin;
    fin.open("student.dat"); //reads file
    if(fin.fail())
    {
        cout << "File error." << endl;
        exit(1);
    }
    Student* student = new Student;
    while(!fin.eof())
    {
        string lastName;
        string firstName;
        string str;
        getline(fin, lastName, ',');
        getline(fin, firstName, ',');
        student->name = lastName + "," + firstName;
        getline(fin,student->ID,',');
        getline(fin, str, ',');
        student->numTests = stoi(str);
        student->testScores = new int[student->numTests];
        for(int i = 0; i < student->numTests; i++)
        {
            getline(fin, str, ',');
            student->testScores[i] = stoi(str);
        }
        if(student->ID == studentID)
        {
            match = true;
            cout << endl;
            printf("%-30s", student->name.c_str()); //allocate 30 spaces for name
            printf("%-15s", student->ID.c_str()); //allocate 15 spaces for ID
            for(int i = 0; i < student->numTests; i++)
            {
                printf("%-5d", student->testScores[i]); //allocate 5 spaces for scores
            }
            cout << endl;
            break; //escapes loop when there has been a match
        }
        fin.ignore(); //throwaway remaining whitespace so that buffer goes to next line
    }
    delete []student->testScores;
    delete student;
    fin.close();
    if(!match)
    {
        cout << "Student does not exist." << endl;
    }
}

void exportResults()
{
    ofstream fout;
    fout.open("averages.dat"); //creates new file for writing

    ifstream fin;
    fin.open("student.dat");

    if(fout.fail() || fin.fail())
    {
        cout << "File error." << endl;
        exit(1);
    }

    int numStudents = getNumber();
    Student* students = new Student[numStudents];

    for(int i = 0; i < numStudents; i++) //store contents of student.dat into dynamic array
    {
        string lastName;
        string firstName;
        string str;
        getline(fin, lastName, ',');
        getline(fin, firstName, ',');

        students[i].name = lastName + "," + firstName;
        getline(fin, students[i].ID, ',');
        getline(fin, str, ',');
        students[i].numTests = stoi(str);
        students[i].testScores = new int[students[i].numTests];
        for(int j = 0; j < students[i].numTests; j++)
        {
            getline(fin, str, ',');
            students[i].testScores[j] = stoi(str);
        }
        fin.ignore(); //throwaway remaining whitespace so that buffer goes to next line
    }
    fin.close();

    for(int i = 0; i < numStudents; i++)
    {
        int sum = 0;
        for(int j = 0; j < students[i].numTests; j++)
        {
            sum+= students[i].testScores[j];
        }
        int minimum = findMinimum(students[i].testScores,students[i].numTests);
        sum -= minimum;
        if(minimum != 0) //if a score was dropped, decrement the number of tests
        {
            students[i].numTests--;
        }
        double average = (double)sum/(students[i].numTests); //compute average
        fout << students[i].ID << "\t" << fixed << setprecision(1) << average << endl; //write to file for each student
    }
    fout.close();
    for(int i = 0; i < numStudents; i++)
    {
        delete [] students[i].testScores;
    }
    delete [] students;
}
