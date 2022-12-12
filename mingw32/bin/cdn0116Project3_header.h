/* Author: Clinton Nguyen
   Instructor:  Shrestha
   Description: CSCE 1030 Project 03
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int TESTS = 5;
enum Menu{Add = 1, Remove = 2, Display = 3, Search = 4, Results = 5, Quit = 6};

struct Student
{
    string name;
    string ID;
    int numTests;
    int* testScores; //dynamic array to store scores
    int avg;
};

int getNumber();
int findMinimum(const int testScores[], int numTests);
void add_Student();
void remove_Student(string studentID);
void display();
void search(string studentID);
void exportResults();