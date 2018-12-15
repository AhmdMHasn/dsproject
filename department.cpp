#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include<fstream>
#include "student.cpp"

using namespace std;

struct departmentStruct
{
    int deptID;
    string deptName;
    departmentStruct * next;
    departmentStruct * prev;
};

class department
{
    ofstream outFile;
    ifstream inFile;
    departmentStruct * head;
    departmentStruct * tail;
public:
    department()
    {
        head = tail = NULL;
    }

    ~department()
    {
        //deleteALL();
    }

    // Append function to add new student
    void append(int _deptID, string _deptName)
    {
        departmentStruct * temp;
        temp = new departmentStruct;
        // Data
        temp -> deptID = _deptID;
        temp -> deptName = _deptName;

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
    departmentStruct * searchDepByID( int _deptID )
    {
        departmentStruct * temp = head;
        while (temp != NULL)
        {
            if( _deptID == temp -> deptID )
            {
                return temp;
            }
            temp = temp -> next;
        }
        cout << "Department is not exist!" << endl;
        return NULL;
    }
    //search department by id and return boolean
    int searchDepartmentByID( int _deptID )
    {
        departmentStruct * temp = head;
        while (temp != NULL)
        {
            if( _deptID == temp -> deptID )
            {
                return 1;
            }
            temp = temp -> next;
        }
        return 0;
    }
    void deleteByID(int _id,string operation)
    {
        if(operation == "=")
        {
            departmentStruct * temp = searchDepByID( _id);
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
    void deleteALL(student & s1)
    {
        departmentStruct * temp = head;
        while ( temp != NULL)
        {
            if(!(s1.searchStudentByDeptID(temp -> deptID)))
            {
                head = head -> next;
                delete temp;
                temp = head;
            }
            else
            {
                cout << " All students in this department will be removed" << endl <<
                     " Are you sure to delete this department ?[y/n] :";
                char input;
                cin>>input;
                if(input == 'y')
                {
                    s1.deleteByDepartmentID(temp -> deptID);
                    head = head -> next;
                    delete temp;
                    temp = head;
                }
                else if(input == 'n')
                {

                }

            }

        }
    }
    // Display all students
    void display()
    {
        departmentStruct * temp = head;
        int counter =0;
        cout << "  No.\t| " << "ID" << "\t| "<< "Name" << endl;
        while (temp != NULL)
        {
            printRow(temp,counter++);
            temp = temp -> next;
        }
    }

    void save()
    {
        outFile.open("dept.txt");
        departmentStruct * temp = head;
        while (temp != NULL)
        {
            outFile << temp -> deptID << " "<< temp -> deptName <<" "<<endl;
            temp = temp -> next;
        }
        outFile.close();
    }

    void read()
    {
        inFile.open("dept.txt");
        int d_id;
        string d_name;
        while (inFile>>d_id>>d_name)
        {
            append(d_id,d_name);
        }
        inFile.close();
    }
    void displayWhere(string columnName,string operation,string value)
    {
        departmentStruct * temp = head;
        int counter =0;
        cout << "  No.\t| " << "ID" << "\t| "<< "Name" << endl;
        while (temp != NULL)
        {
            if(columnName == "id")
            {
                if(operation == "=")
                {
                    if(temp -> deptID == atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == "!=")
                {
                    if(temp ->deptID != atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == ">=")
                {
                    if(temp ->deptID >= atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == "<=")
                {
                    if(temp ->deptID <= atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == "<")
                {
                    if(temp ->deptID < atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else if(operation == ">")
                {
                    if(temp ->deptID > atoi(value.c_str()))
                        printRow(temp,counter++);
                }
                else
                    cout<<"invalid command, operator doesn't exist"<<endl;
                temp = temp -> next;
            }
            if(columnName == "name")
            {
                if(operation == "=")
                {
                    if(temp -> deptName == value)
                        printRow(temp,counter++);
                }
                else if(operation == "!=")
                {
                    if(temp ->deptName != value)
                        printRow(temp,counter++);
                }
                else
                    cout<<"invalid command, operator doesn't exist"<<endl;
                temp = temp -> next;
            }
        }
    }

    void deleteWhere(student & s1,string columnName,string operation,string value)
    {
        departmentStruct * temp = head;
        while (temp != NULL)
        {
            if(columnName == "id")
            {
                if(operation == "=")
                {
                    if(temp -> deptID == atoi(value.c_str()))
                    {
                        deleteWhereDeptID(s1,temp -> deptID);
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
                    if(temp -> deptID > atoi(value.c_str()))
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
                    if(temp ->deptID >= atoi(value.c_str()))
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
                    if(temp -> deptID < atoi(value.c_str()))
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
                    if(temp -> deptID <= atoi(value.c_str()))
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
                    if(temp -> deptID != atoi(value.c_str()))
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

            else if(columnName == "name")
            {
                if(operation == "=")
                {
                    if(temp -> deptName == value )
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
                    if(temp -> deptName != value)
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
            temp = temp -> next;
        }
    }


    void deleteWhereDeptID(student & s1, int dept_id)
    {
        departmentStruct * temp = head;
        while ( temp != NULL)
        {
            if(temp -> deptID == dept_id)
            {
                if(!(s1.searchStudentByDeptID(temp -> deptID)))
                {
                    head = head -> next;
                    delete temp;
                    temp = head;
                }
                else
                {
                    cout << " All students in this department will be removed" << endl <<
                         " Are you sure to delete this department ?[y/n] :";
                    char input;
                    cin>>input;
                    if(input == 'y')
                    {
                        s1.deleteByDepartmentID(temp -> deptID);
                        head = head -> next;
                        delete temp;
                        temp = head;
                    }
                    else if(input == 'n')
                    {

                    }
                }
            }
            temp = temp -> next;
        }
    }

    void printRow(departmentStruct * temp,int counter)
    {
        cout <<"  " << counter << "\t| " << temp -> deptID << "\t| "<< temp -> deptName << endl;
    }
};

