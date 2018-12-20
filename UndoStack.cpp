#include <iostream>
#include<string.h>
#include<fstream>
#include <sstream>

using namespace std;

struct node
{
    string command ;

    node * prev ;
};
class Stack
{
    int counter;
    node *tail;
public:
    Stack()
    {
        counter = 0;
        tail=NULL;
    }
    ~Stack()
    {
        ifstream ifile;
        ifile.open("studentBackup.txt");
        if (ifile)
        {
            ifile.close();
            remove("studentBackup.txt");
        }
         ifile.open("deptBackup.txt");
        if (ifile)
        {
            ifile.close();
            remove("deptBackup.txt");
        }
    }

    int isEmpty()
    {
        return tail == NULL;
    }
    int isFull()
    {
        node * ptr=new node;
        if(ptr!=NULL)
        {
            delete ptr;
            return 0;
        }
        return 1;
    }
    void push()
    {
        node * ptr=new node;
        if(ptr!=NULL)
        {

            std::string out_string;
            std::stringstream ss;
            ss << counter;
            out_string = ss.str();
            ptr->command ="command "+out_string;
            counter++;
            if(tail==NULL)
            {
                tail=ptr;
                ptr->prev=NULL;
            }
            else
            {
                ptr->prev=tail;
                tail=ptr;
            }
        }

    }

    string pop()
    {
        node * data=new node;

        if(tail!=NULL)
        {
            data->command=tail->command;
            node * temp=tail;
            tail=tail->prev;
            delete temp;
            return data -> command;
        }
    }
    string peak()
    {
        node * data=new node;
        if(tail!=NULL)
        {
            data->command=tail->command;
            return data -> command;
        }
    }
    void deleteAll()
    {
      while(!isEmpty())
      {
       pop();
      }
    }
};


