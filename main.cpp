#include <iostream>
#include <string.h>
#include <string>

using namespace std;

struct studentStruct
{
    string id;
    string fName;
    string lName;
    int age, depID;
    studentStruct * next;
    studentStruct * prev;
};

struct departmentStruct
{
    int depID;
    string depName;
    departmentStruct * next;
    departmentStruct * prev;
};

class student
{
    studentStruct * head;
    studentStruct * tail;
public:
    student()
    {
        head = tail = NULL;
    }

    ~student(){
    deleteALL();
    }

    // Append function to add new student
    append(string _id, string _fName, string _lName, int _age, int _depID)
    {
        studentStruct * temp;
        temp = new studentStruct;
        // Data
        temp -> id = _id;
        temp -> fName = _fName;
        temp -> lName = _lName;
        temp -> age = _age;
        temp -> depID = _depID;

        if(head == NULL)
        {
            head = tail = temp;
            temp -> prev = NULL;
            temp -> next = NULL;
        }
        else
        {
            temp -> prev = tail;
            temp -> next = NULL;
            tail -> next = temp;
            tail = temp;
        }
    }

    // Display all students
    void display()
    {
        studentStruct * temp = head;
        int counter =0;
        cout << "No.  |  " << "ID" << "  |  " << "First Name" << "  |  " << "Last Name" << "  |  " << "Age" << "  |  " << "Department ID" << endl;
        while (temp != NULL)
        {
            cout << counter++ << "  |  " << temp -> id << "  |  " << temp -> fName << "  |  " << temp -> lName << "  |  " << temp -> age << "  |  " << temp -> depID << endl;
            temp = temp -> next;
        }
    }

    // Search
    // Search Student by ID
    studentStruct * searchByID( string _id )
    {
        studentStruct * temp = head;
        while (temp != NULL)
        {
            if( _id == temp -> id )
            {
                return temp;
            }
            temp = temp -> next;
        }
        return NULL;
    }

    // Search Student by First Name
    studentStruct * searchByName( string _fName )
    {
        studentStruct * temp = head;
        while (temp != NULL)
        {
            if( _fName == temp -> fName )
                {
                    return temp;
                }
            temp = temp -> next;
        }
        return NULL;
    }

    void deleteByID(string _id)
    {
        studentStruct * temp = searchByID( _id );
        if ( temp == NULL )
            return;
        if ( head == tail )
        {
            delete temp;
            head = tail = NULL;
        }
        else if ( temp == head )
        {
            head = temp -> next;
            head -> prev = NULL;
            delete temp;
        }
        else if ( temp == tail){
            tail = temp -> prev;
            tail -> next = NULL;
            delete temp;
        } else {
        temp -> next -> prev = temp -> prev;
        temp -> prev -> next = temp -> next;
        delete temp;
        }
    }


    // Insert any student to the table after the current student ID
    void insertByID_after(string _id, string _fName, string _lName, int _age, int _depID, string oldID){
    studentStruct * temp = searchByID( oldID );
    if ( temp == NULL || temp == tail ){
        append( _id, _fName, _lName, _age, _depID );
    } else {
    studentStruct * newS = new studentStruct;
    // Data
    temp -> id = _id;
    temp -> fName = _fName;
    temp -> lName = _lName;
    temp -> age = _age;
    temp -> depID = _depID;

    newS -> prev = temp;
    newS -> next = temp -> next;
    temp -> next = newS;
    newS -> next -> prev = newS;
    }
    }

    void deleteALL(){
    studentStruct * temp = head;
    while ( temp != NULL){
        head = head -> next;
        delete temp;
        temp = head;
    }
    }
};

class department
{
    departmentStruct * head;
    departmentStruct * tail;
public:
    department()
    {
        head = tail = NULL;
    }

    ~department(){
    //deleteALL();
    }

    // Append function to add new student
    append(int _depID, string _depName)
    {
        departmentStruct * temp;
        temp = new departmentStruct;
        // Data
        temp -> depID = _depID;
        temp -> depName = _depName;

        if(head == NULL)
        {
            head = tail = temp;
            temp -> prev = NULL;
            temp -> next = NULL;
        }
        else
        {
            temp -> prev = tail;
            temp -> next = NULL;
            tail -> next = temp;
            tail = temp;
        }
    }

    // Search Department by ID
    departmentStruct * searchDepByID( int _depID )
    {
        departmentStruct * temp = head;
        while (temp != NULL)
        {
            if( _depID == temp -> depID )
            {
                return temp;
            }
            temp = temp -> next;
        }
        cout << "Department is not exist!" << endl;
        return NULL;
    }
};

int main()
{
    department d1;
    d1.append(956, "Java");

    student s1;
    s1.append("123", "Ahmed", "Hassan", 132, 956);
    s1.append("16512", "Ahmed", "Ashraf", 132, 956);
    s1.append("asdas16", "Esraa", "Fathy", 485, 956);
    s1.display();
/*
    student s1;
    s1.append(1,"Ahmed");
    s1.append(2,"Mohamed");
    s1.append(5,"Ibrahim");
    s1.append(10,"Hassan");

    cout << endl << "All items:" << endl;
    s1.display();

    cout << endl << "No. of items:" <<endl;
    cout << s1.count();

    s1.deleteByID(5);
    cout << endl << "~~Delete item id (5):" <<endl;
    cout << "~~Delete item name (Mohamed):" <<endl;
    cout << endl << "All items:" << endl;
    s1.deleteByName("Mohamed");
    s1.display();

*/

    return 0;
}