#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include<fstream>

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
    ofstream outFile;
    ifstream inFile;
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
    void append(string _id, string _fName, string _lName, int _age, int _depID)
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
    //search by student id and return boolen
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

    int searchStudentByDeptID( int dept_id)
    {
        studentStruct * temp = head;
        while (temp != NULL)
        {
            if( dept_id == temp -> depID )
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

    //display concat between fName & lName
    void displayConcat()
    {
        studentStruct * temp = head;
        int counter =0;
        cout << "  No.\t| " << "ID" << "\t| "<< "Name" <<"\t\t| "<< "Age" << "\t| " << "Department ID" << endl;
        while (temp != NULL)
        {
            cout <<"  " << counter++ << "\t| " << temp -> id << "\t| "<< temp -> fName
                 << " "<< temp -> lName << "\t| " << temp -> age << "\t| " << temp -> depID << endl;
            temp = temp -> next;
        }
    }
    //save in file
    void save ()
    {
        outFile.open("student.txt");
        studentStruct * temp = head;
        while (temp != NULL)
        {
            outFile << temp ->id << " "
                    << temp ->fName <<" "
                    << temp ->lName << " "
                    << temp ->age << " "
                    << temp ->depID<<endl ;

            temp = temp -> next;
        }
        outFile.close();
    }
    //read from file
    void read ()
    {
        string _id,_fnam,_lname;
        int _age,_dept_id;
        inFile.open("student.txt");
        while(inFile>>_id>>_fnam>>_lname>>_age>>_dept_id)
        {
            append(_id,_fnam,_lname,_age,_dept_id);
        }
        inFile.close();
    }

    void displayWhere(string columnName,string operation,string value)
    {
        studentStruct * temp = head;
        int counter =0;
        cout << "  No.\t| " << "ID" << "\t| "<< "First Name" << "\t| "<< "Last Name" <<"\t| "<< "Age" << "\t| " << "Department ID" << endl;
        while (temp != NULL)
        {
            if(columnName == "id")
            {
                if(operation == "=")
                {
                    if(temp ->id == value)
                        printRow(temp,counter++);
                }
                else if(operation == "!=")
                {
                    if(temp ->id != value)
                        printRow(temp,counter++);
                }
                else if(operation == ">=")
                {
                    if(temp ->id >= value)
                        printRow(temp,counter++);
                }
                else if(operation == "<=")
                {
                    if(temp ->id <= value)
                        printRow(temp,counter++);
                }
                else if(operation == "<")
                {
                    if(temp ->id < value)
                        printRow(temp,counter++);
                }
                else if(operation == ">")
                {
                    if(temp ->id > value)
                        printRow(temp,counter++);
                }
                else
                    cout<<"invalid command, operator doesn't exist"<<endl;
                temp = temp -> next;
            }
            else if(columnName == "fname")
            {
                if(operation == "=")
                {
                    if(temp -> fName == value)
                        printRow(temp,counter++);
                }
                else if(operation == "!=")
                {
                    if(temp -> fName != value)
                        printRow(temp,counter++);
                }
                else
                    cout<<"invalid command"<<endl;
                temp = temp -> next;
            }
            else if(columnName == "lname")
            {
                if(operation == "=")
                {
                    if(temp -> lName == value)
                        printRow(temp,counter++);
                }
                else if(operation == "!=")
                {
                    if(temp -> lName != value)
                        printRow(temp,counter++);
                }
                else
                    cout<<"invalid command"<<endl;
                temp = temp -> next;
            }
            else if(columnName == "age")
            {
                if(operation == "=")
                {
                    if(temp ->age == atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == "!=")
                {
                    if(temp ->age != atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == ">=")
                {
                    if(temp ->age >= atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == "<=")
                {
                    if(temp ->age <= atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == "<")
                {
                    if(temp ->age < atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == ">")
                {
                    if(temp ->age > atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else
                    cout<<"invalid command, operator doesn't exist"<<endl;

                temp = temp -> next;
            }
            else if(columnName == "deptId")
            {
                if(operation == "=")
                {
                    if(temp -> depID == atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == "!=")
                {
                    if(temp -> depID != atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == ">=")
                {
                    if(temp -> depID >= atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == "<=")
                {
                    if(temp -> depID <= atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == "<")
                {
                    if(temp -> depID < atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == ">")
                {
                    if(temp -> depID > atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else
                    cout<<"invalid command, operator doesn't exist"<<endl;
                temp = temp -> next;
            }
        }
    }


    void deleteWhere(string columnName,string operation,string value)
    {
        studentStruct * temp = head;
        while (temp != NULL)
        {
            if(columnName == "id")
            {
                if(operation == "=")
                {
                    if(temp -> id == value )
                        //temp = searchByID(value);
                    {
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
                else if(operation == ">")
                {
                    if(temp -> id > value)
                        //temp = searchByID(value);
                    {
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
                else if(operation == ">=")
                {
                    if(temp -> id >= value)
                        //temp = searchByID(value);
                    {
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
                else if(operation == "<")
                {
                    if(temp -> id < value)
                        //temp = searchByID(value);
                    {
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
                else if(operation == "<=")
                {
                    if(temp -> id <= value)
                        //temp = searchByID(value);
                    {
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
                else if(operation == "!=")
                {
                    if(temp -> id != value)
                        //temp = searchByID(value);
                    {
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
                else
                    cout<<"invalid command, operator doesn't exist"<<endl;
            }
            else if(columnName == "fname")
            {
                if(operation == "=")
                {
                    if(temp -> fName == value )
                        //temp = searchByID(value);
                    {
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
                else if(operation == "!=")
                {
                    if(temp -> fName != value)
                        //temp = searchByID(value);
                    {
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
                else
                    cout<<"invalid command, operator doesn't exist"<<endl;
            }
            else if(columnName == "lname")
            {
                if(operation == "=")
                {
                    if(temp -> lName == value )
                        //temp = searchByID(value);
                    {
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
                else if(operation == "!=")
                {
                    if(temp -> lName != value)
                        //temp = searchByID(value);
                    {
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
                else
                    cout<<"invalid command, operator doesn't exist"<<endl;
            }
            else if(columnName == "age")
            {
                {
                    if(operation == "=")
                    {
                        if(temp -> age == atoi(value.c_str()))
                            //temp = searchByID(value);
                        {
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
                    else if(operation == ">")
                    {
                        if(temp -> age > atoi(value.c_str()))
                            //temp = searchByID(value);
                        {
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
                    else if(operation == ">=")
                    {
                        if(temp -> age >= atoi(value.c_str()))
                            //temp = searchByID(value);
                        {
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
                    else if(operation == "<")
                    {
                        if(temp -> age < atoi(value.c_str()))
                            //temp = searchByID(value);
                        {
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
                    else if(operation == "<=")
                    {
                        if(temp -> age <= atoi(value.c_str()))
                            //temp = searchByID(value);
                        {
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
                    else if(operation == "!=")
                    {
                        if(temp -> age != atoi(value.c_str()))
                            //temp = searchByID(value);
                        {
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
                    else
                        cout<<"invalid command, operator doesn't exist"<<endl;
                }
            }
            else if(columnName == "deptId")
            {
                {
                    {
                        if(operation == "=")
                        {
                            if(temp -> depID == atoi(value.c_str()))
                                //temp = searchByID(value);
                            {
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
                        else if(operation == ">")
                        {
                            if(temp -> depID > atoi(value.c_str()))
                                //temp = searchByID(value);
                            {
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
                        else if(operation == ">=")
                        {
                            if(temp -> depID >= atoi(value.c_str()))
                                //temp = searchByID(value);
                            {
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
                        else if(operation == "<")
                        {
                            if(temp -> depID < atoi(value.c_str()))
                                //temp = searchByID(value);
                            {
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
                        else if(operation == "<=")
                        {
                            if(temp -> depID <= atoi(value.c_str()))
                                //temp = searchByID(value);
                            {
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
                        else if(operation == "!=")
                        {
                            if(temp -> depID != atoi(value.c_str()))
                                //temp = searchByID(value);
                            {
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
                        else
                            cout<<"invalid command, operator doesn't exist"<<endl;
                    }
                }
            }
            temp = temp -> next;
        }
    }

    //delete by department id
    void deleteByDepartmentID(int dept_id)
    {
        studentStruct *temp = head;
        while(temp != NULL)
        {
            if(temp -> depID == dept_id)
            {
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
            temp = temp -> next;
        }
    }

    //print row from table
    void printRow(studentStruct * temp,int counter)
    {
        cout <<"  " << counter << "\t| " << temp -> id << "\t| "<< temp -> fName
             << "\t\t| "<< temp -> lName << "\t| " << temp -> age << "\t| " << temp -> depID << endl;
    }

    //display custom column from table
    void displayColumns(string * columnsNames)
    {
        cout << "  No.";
        for(int i=0; i<5; i++)
        {
            if(columnsNames[i] == "id")
                cout << "\t| "<< "ID";
            if(columnsNames[i] == "fname")
                cout << "\t| "<< "First Name";
            if(columnsNames[i] == "lname")
                cout << "\t| "<< "Last Name";
            if(columnsNames[i] == "age")
                cout <<"\t| "<< "Age";
            if(columnsNames[i] == "deptid")
                cout << "\t| " << "Department ID";
        }
        studentStruct * temp = head;
        int counter =0;
        cout << endl;
        while (temp != NULL)
        {
            cout <<"  " << counter++ ;
            for(int i=0; i<5; i++)
            {
                if(columnsNames[i] == "id")
                    cout << "\t| "<< temp -> id;
                if(columnsNames[i] == "fname")
                    cout <<"\t| "<< temp -> fName;
                if(columnsNames[i] == "lname")
                    cout << "\t| "<< temp -> lName ;
                if(columnsNames[i] == "age")
                    cout << "\t| " << temp -> age;
                if(columnsNames[i] == "deptid")
                    cout << "\t| " << temp -> depID;
            }
            cout<< endl;
            temp = temp -> next;
        }
    }
};
