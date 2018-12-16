#include <iostream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include "department.cpp"

using namespace std;

department d1;
student s1;

string separate(string & inputData,string delemeter);
void insertInto(string & inputData);
void selectFrom(string & inputData);
void deleteFrom(string & inputData);
void updateFrom(string & inputData);
int main()
{
    d1.read();
    s1.read();
    do
    {
        string inputData;
        getline (cin,inputData);
        string operation = separate(inputData," ");
        if(operation == "help")
        {
            cout<<"to insert data in table : insert into tableName id,fname,lname,age,deptId"<<endl;
            cout<<"to delete all data in table : delete from tableName"<<endl;
            cout<<"to delete all data in table : delete from tableName where columnName = value"<<endl;
            cout<<"to select all data in table : select * from tableName"<<endl;
        }
        else if(operation == "insert")
        {
            insertInto(inputData);
        }
        else if(operation == "select")
        {
            selectFrom(inputData);
        }
        else if(operation == "delete")
        {
            deleteFrom(inputData);
        }
        else if(operation == "update")
        {
            updateFrom(inputData);
        }
        else if(operation == "save")
        {
            s1.save();
            d1.save();
        }
        else
            cout<<"invalid command"<<endl;
    }
    while(1);

    return 0;
}

string separate(string & inputData,string delemeter)
{
    string operation = inputData.substr(0,inputData.find(delemeter));
    inputData=inputData.substr(inputData.find(delemeter)+1);
    if(inputData == operation)
    {
        inputData = "";
        return operation;
    }
    return operation;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//insert into student or dept using command line
void insertInto(string & inputData)
{
    string operation =separate(inputData," ");
    if(operation == "into")
    {
        operation =separate(inputData," ");
        if(operation == "student")
        {
            string id =separate(inputData,",");
            string fname =separate(inputData,",");
            string lname =separate(inputData,",");
            string age =separate(inputData,",");
            string deptid =separate(inputData,",");
            if(id != "" && fname != "" && lname != "" && age != "" && deptid != "")
            {
                if(d1.searchDepartmentByID(atoi(deptid.c_str())))
                    if(!(s1.searchStudentByID(id)))
                        s1.append(id,fname, lname, atoi(age.c_str()), atoi(deptid.c_str()));
                    else
                        cout<<"invalid student id"<<endl;
                else
                    cout<<"invalid department id"<<endl;
            }
            else
                cout<<"invalid command"<<endl;
        }
        else if(operation == "dept")
        {
            string id =separate(inputData,",");
            string name =separate(inputData,",");
            if(id != "" && name != "")
                if(!(d1.searchDepartmentByID(atoi(id.c_str()))))
                    d1.append(atoi(id.c_str()), name);
                else
                    cout<<"invalid dept id"<<endl;
            else
                cout<<"invalid command"<<endl;
        }
        else
            cout<<"invalid table name"<<endl;
    }
    else
        cout<<"invalid command"<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//select from student or dept using command line
void selectFrom(string & inputData)
{
    string operation =separate(inputData," ");
    if(operation == "*")
    {
        operation =separate(inputData," ");
        if(operation == "from")
        {
            operation =separate(inputData," ");
            if(operation == "student")
            {
                operation =separate(inputData," ");
                if(operation == "where")
                {
                    string columnName =separate(inputData," ");
                    if(columnName == "id" ||columnName == "fname"||columnName == "lname"
                            ||columnName == "deptId" ||columnName == "age")
                    {
                        operation =separate(inputData," ");
                        if(operation == "=" ||operation == "<=" ||operation == ">=" ||operation == "<" ||
                                operation == ">" ||operation == "!=")
                        {
                            string value = separate(inputData," ");
                            if(value != "")
                            {
                                s1.displayWhere(columnName,operation,value);
                                //here we will call function that take (columnName ,operation,value)
                            }
                            else
                                cout<<"invalid command"<<endl;
                        }
                        else
                            cout<<"invalid command"<<endl;
                    }
                    else
                        cout<<"invalid command"<<endl;
                }
                else
                    s1.display();
            }
            else if (operation == "dept")
            {
                operation =separate(inputData," ");
                if(operation == "where")
                {
                    string columnName =separate(inputData," ");
                    if(columnName == "id" ||columnName == "name")
                    {
                        operation =separate(inputData," ");
                        if(operation == "=" ||operation == "<=" ||operation == ">=" ||operation == "<" ||
                                operation == ">" ||operation == "!=")
                        {
                            string value = separate(inputData," ");
                            if(value != "")
                                d1.displayWhere(columnName,operation,value);
                            else
                                cout<<"invalid command"<<endl;
                        }
                        else
                            cout<<"invalid command"<<endl;
                    }
                    else
                        cout<<"invalid command"<<endl;
                }
                else
                    d1.display();
            }
            else
                cout<<"invalid command"<<endl;
        }
        else
            cout<<"invalid command"<<endl;
    }
    else if(operation == "concat")
    {
        operation =separate(inputData,",");
        if(operation == "fname")
        {
            operation =separate(inputData," ");
            if(operation == "lname")
            {
                operation =separate(inputData," ");
                if(operation == "from")
                {
                    operation =separate(inputData," ");
                    if(operation == "student")
                    {
                        s1.displayConcat();
                    }
                    else
                        cout<<"invalid command"<<endl;
                }
                else
                    cout<<"invalid command"<<endl;
            }
            else
                cout<<"invalid command"<<endl;
        }
        else
            cout<<"invalid command"<<endl;
    }
    else
    {
        string columnsNameArr[5];
        columnsNameArr[0] = separate(operation,",");
        if(columnsNameArr[0] == "id" || columnsNameArr[0] =="fname" || columnsNameArr[0] =="lname"
                || columnsNameArr[0] =="age" || columnsNameArr[0] =="deptid")
        {
            for(int i=1; i<5; i++)
                columnsNameArr[i] = separate(operation,",");

            for(int i=0; i<5; i++)
            {
                if(!(columnsNameArr[i] == "id" || columnsNameArr[i] =="fname" || columnsNameArr[i] =="lname"
                        || columnsNameArr[i] =="age" || columnsNameArr[i] =="deptid" || columnsNameArr[i] == ""))
                {
                    cout<<"invalid command"<<endl;
                    return;
                }

            }
            operation =separate(inputData," ");
            if(operation == "from")
            {
                operation =separate(inputData," ");
                if(operation == "student")
                {
                    s1.displayColumns(columnsNameArr);
                }
            }
        }
        else
            cout<<"invalid command"<<endl;
    }

}

void deleteFrom(string & inputData)
{
    string operation = separate(inputData," ");
    if(operation == "from")
    {
        operation = separate(inputData," ");
        if(operation == "student")
        {
            operation = separate(inputData," ");
            if(operation == "where")
            {
                string columnName =separate(inputData," ");
                if(columnName == "id" ||columnName == "name" ||columnName == "fname"
                        ||columnName == "lname" ||columnName == "deptId" ||columnName == "age")
                {
                    operation =separate(inputData," ");
                    if(operation == "=" ||operation == "<=" ||operation == ">=" ||operation == "<" ||
                            operation == ">" ||operation == "!=")
                    {
                        string value = separate(inputData," ");
                        if(value != "")
                        {

                            s1.deleteWhere(columnName,operation,value);
                            //s1.deleteByID(value, operation);
                            //here we will call function that take (columnName ,operation,value)
                        }
                        else
                            cout<<"invalid command"<<endl;
                    }
                    else
                        cout<<"invalid command"<<endl;
                }
                else
                    cout<<"invalid command"<<endl;
            }
            else
                s1.deleteALL();
        }
        else if(operation == "dept")
        {
            operation = separate(inputData," ");
            if(operation == "where")
            {
                string columnName =separate(inputData," ");
                if(columnName == "id" ||columnName == "name")
                {
                    operation =separate(inputData," ");
                    if(operation == "=" ||operation == "<=" ||operation == ">=" ||operation == "<" ||
                            operation == ">" ||operation == "!=")
                    {
                        string value = separate(inputData," ");
                        if(value != "")
                        {
                            // d1.deleteByID(atoi(value.c_str()), operation);
                            d1.deleteWhere(s1,columnName,operation,value);
                        }
                        else
                            cout<<"invalid command"<<endl;
                    }
                    else
                        cout<<"invalid command"<<endl;
                }
                else
                    cout<<"invalid command"<<endl;
            }
            else
                d1.deleteALL(s1);
        }
        else
            cout<<"invalid command"<<endl;
    }
    else
        cout<<"invalid command"<<endl;
}

void updateFrom (string & inputData)
{
    string operation = separate(inputData," ");
    if (operation == "into")
    {
        operation = separate(inputData," ");
        if( operation == "student" )
        {
            string columnsNameArr[5];
            string columnsValueArr[5];
            operation =separate(inputData," ");
            columnsNameArr[0] = separate(operation,"=");
            columnsValueArr[0] = separate(operation,",");
            if(columnsNameArr[0] == "id" || columnsNameArr[0] =="fname" || columnsNameArr[0] =="lname"
                    || columnsNameArr[0] =="age" || columnsNameArr[0] =="deptid")
            {
                for(int i=1; i<5; i++)
                {
                    columnsNameArr[i] = separate(operation,"=");
                    columnsValueArr[i] = separate(operation,",");
                    if ( columnsValueArr[i] == "" && columnsNameArr[i] != "" )
                    {
                        cout<<"invalid command, check inputs value."<<endl;
                        return;
                    }
                }
                for(int i=0; i<5; i++)
                {
                    if(!(columnsNameArr[i] == "id" || columnsNameArr[i] =="fname" || columnsNameArr[i] =="lname"
                            || columnsNameArr[i] =="age" || columnsNameArr[i] =="deptid" || columnsNameArr[i] == ""))
                    {
                        cout<<"invalid command, check column name."<<endl;
                        return;
                    }
                    if (s1.searchStudentByID(columnsValueArr[i]))
                    {
                        cout<<"invalid student id"<<endl;
                        return;
                    }
                }
                operation =separate(inputData," ");
                if(operation == "where")
                {
                    string columnName =separate(inputData," ");
                    if(columnName == "id")
                    {
                        operation =separate(inputData," ");
                        if(operation == "=")
                        {
                            string value = separate(inputData," ");
                            if(value != "")
                            {
                                //here we will call function that take (columnName ,operation,value) to check and update
                                s1.updateStudent(columnsNameArr, columnsValueArr, columnName, operation, value);
                            }
                            else
                                cout<<"invalid command"<<endl;
                        }
                        else
                            cout<<"invalid command, accepts '=' only"<<endl;
                    }
                    else
                        cout<<"invalid command, can get 'id' only"<<endl;
                }
                else
                    cout<<"invalid command, add 'where' to compare"<<endl;
            }
            else
                cout<<"invalid command, check column name"<<endl;
        }
        else if(operation == "dept")
        {
            string columnsNameArr[2];
            string columnsValueArr[2];
            operation =separate(inputData," ");
            columnsNameArr[0] = separate(operation,"=");
            columnsValueArr[0] = separate(operation,",");
            if( columnsNameArr[0] == "id" || columnsNameArr[0] =="name" )
            {
                for(int i=1; i<2; i++)
                {
                    columnsNameArr[i] = separate(operation,"=");
                    columnsValueArr[i] = separate(operation,",");
                    if ( columnsValueArr[i] == "" && columnsNameArr[i] != "" )
                    {
                        cout<<"invalid command, check inputs value."<<endl;
                        return;
                    }
                }

                for(int i=0; i<2; i++)
                {
                    if(!(columnsNameArr[i] == "id" || columnsNameArr[i] =="name" || columnsNameArr[i] == ""))
                    {
                        cout<<"invalid command, check column name."<<endl;
                        return;
                    }
                    if ( d1.searchDepartmentByID(atoi(columnsValueArr[i].c_str())) )
                    {
                        cout<<"invalid department id"<<endl;
                        return;
                    }
                }
                operation =separate(inputData," ");
                if(operation == "where")
                {
                    string columnName =separate(inputData," ");
                    if(columnName == "id")
                    {
                        operation =separate(inputData," ");
                        if(operation == "=")
                        {
                            string value = separate(inputData," ");
                            if(value != "")
                            {
                                //here we will call function that take (columnName ,operation,value) to check and update
                                d1.updateDepartment(s1,columnsNameArr, columnsValueArr, columnName, operation, value);
                            }
                            else
                                cout<<"invalid command"<<endl;
                        }
                        else
                            cout<<"invalid command, accepts '=' only"<<endl;
                    }
                    else
                        cout<<"invalid command, can get 'id' only"<<endl;
                }
                else
                    cout<<"invalid command, add 'where' to compare"<<endl;
            }
            else
                cout<<"invalid command, check column name"<<endl;
        }
        else
            cout<<"invalid command, table name doesn't exist!"<<endl;
    }
    else
        cout<<"invalid command"<<endl;
}
