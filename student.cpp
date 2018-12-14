#include <iostream>
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


class student
{
    studentStruct * head;
    studentStruct * tail;
public:
    student()
    {
        head = tail = NULL;
    }

    ~student()
    {
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
        cout << "  No.\t| " << "ID" << "\t| "<< "First Name" << "\t| "<< "Last Name" <<"\t| "<< "Age" << "\t| " << "Department ID" << endl;
        while (temp != NULL)
        {
            printRow(temp,counter++);
            temp = temp -> next;
        }
    }

    // Search
    // Search Student by ID
    studentStruct * searchByID( string _id)
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
    int searchStudentByID( string _id)
    {
        studentStruct * temp = head;
        while (temp != NULL)
        {
            if( _id == temp -> id )
            {
                return 1;
            }
            temp = temp -> next;
        }
        return 0;
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

    void deleteByID(string _id,string operation)
    {
        if(operation == "=")
        {
            studentStruct * temp = searchByID( _id);
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
            else if ( temp == tail)
            {
                tail = temp -> prev;
                tail -> next = NULL;
                delete temp;
            }
            else
            {
                temp -> next -> prev = temp -> prev;
                temp -> prev -> next = temp -> next;
                delete temp;
            }
        }

    }


    // Insert any student to the table after the current student ID
    void insertByID_after(string _id, string _fName, string _lName, int _age, int _depID, string oldID)
    {
        studentStruct * temp = searchByID( oldID );
        if ( temp == NULL || temp == tail )
        {
            append( _id, _fName, _lName, _age, _depID );
        }
        else
        {
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

    void deleteALL()
    {
        studentStruct * temp = head;
        while ( temp != NULL)
        {
            head = head -> next;
            delete temp;
            temp = head;
        }
    }

    void displayWhere(string columnName,string operation,string value)
    {
        studentStruct * temp = head;
        int counter =0;
        cout << "  No.\t| " << "ID" << "\t| "<< "First Name" << "\t| "<< "Last Name" <<"\t| "<< "Age" << "\t| " << "Department ID" << endl;
        while (temp != NULL)
        {
            if(columnName == "id")
                if(operation == "=")
                    if(temp ->id == value)
                        printRow(temp,counter++);
            if(operation == "!=")
                if(temp ->id != value)
                    printRow(temp,counter++);
            if(operation == ">=")
                if(temp ->id >= value)
                    printRow(temp,counter++);
            if(operation == "<=")
                if(temp ->id <= value)
                    printRow(temp,counter++);
            if(operation == "<")
                if(temp ->id < value)
                    printRow(temp,counter++);
            if(operation == ">")
                if(temp ->id > value)
                    printRow(temp,counter++);
            temp = temp -> next;
        }
    }
    void printRow(studentStruct * temp,int counter)
    {
        cout <<"  " << counter << "\t| " << temp -> id << "\t| "<< temp -> fName
             << "\t\t| "<< temp -> lName << "\t| " << temp -> age << "\t| " << temp -> depID << endl;
    }
};
