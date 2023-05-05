#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<regex>
#include<windows.h>
using namespace std;

class Student
{
    private:
    string name,rollno,course,email,mobile_number;
    int semester;

    public:
    bool validEmail(string email)
    {
        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(email, pattern);
    }
    bool validMobile(string mobile)
    {
        if(mobile.length()==10 && (mobile[0]=='9'||mobile[0]=='8'||mobile[0]=='7'||mobile[0]=='6'))
        {
            return true;
        }
        return false;
    }
    //MENU OF THE STUDENT MANAGEMENT SYSTEM
    void menu()
    {
        beginning:
            int choice;
            system("cls");
            cout<<"\t\t||STUDENT MANAGEMENT SYSTEM||"<<endl;
            cout<<"\t\t_____________________________"<<endl;
            cout<<endl;
            cout<<"\t\t1. ADD NEW STUDENT DATA"<<endl;
            cout<<"\t\t2. DISPLAY STUDENT DATA"<<endl;
            cout<<"\t\t3. SEARCH"<<endl;
            cout<<"\t\t4. DELETE STUDENT DATA"<<endl;
            cout<<"\t\t5. EXIT"<<endl;

            cout<<"\t\tPlease enter your choice [1-6]:"<<endl;
            cin>>choice;
            //USING SWITCH CASE FOR THE MENU DRIVEN PROGRAM
            switch(choice)
            {
                case 1:
                addNewStudentData();
                break;
                case 2:
                displayData();
                break;
                case 3:
                search();
                break;
                case 4:
                deleteData();
                break;
                case 5:
                cout<<"Exiting the program\n";
                exit(0);
                default:
                cout<<"INVALID CHOICE. PLEASE ENTER AGAIN."<<endl;
            }
            goto beginning;


    }
    //A METHOD TO ADD NEW STUDENT DATA ON THE DATABASE.
    void addNewStudentData()
    {

        //TAKING INPUT INTO VARIABLES
        system("cls");
        cout<<"\t\t\t||ADD NEW STUDENT DATA||"<<endl;
        cout<<"\t\t\t________________________"<<endl<<endl;
        
        //roll number
        cout<<"\t\tEnter roll number: ";
        cin>>rollno;
        //name
        cout<<"\t\tEnter name: ";
        cin.ignore();
        getline(cin,name);
        //course
        cout<<"\t\tEnter course: ";
        cin>>course;
        //semester
        sem:
        cout<<"\t\tEnter semester: ";
        cin>>semester;
        if(semester<0 || semester>10)
        {
            cout<<"Invalid semester entered. Kindly input again:"<<endl;
            goto sem;
        }
        //E-Mail
        em:
        cout<<"\t\tEnter E-mail: ";
        cin>>email;
        if(validEmail(email)==false)
        {
            cout<<"Invalid Email"<<endl;
            goto em;
        }
        //Contact Number
        cont:
        cout<<"\t\tEnter mobile number: ";
        cin>>mobile_number;
        if(validMobile(mobile_number)==false)
        {
            cout<<"Invalid Phone Number\n";
            goto cont;
        }

        //STORING THE DATA ON TO A FILE
        fstream file;
        file.open("studentDB.txt", ios::app | ios::out);
        file<<"ROLL NUMBER: "<<rollno<<endl<<"NAME: "<<name<<endl<<"COURSE: "<<course<<endl<<"SEMESTER: "<<semester<<endl<<"EMAIL: "<<email<<endl
        <<"CONTACT NUMBER: "<<mobile_number<<endl<<"end"<<endl<<"------------------------------------------------------------------------------"<<endl<<endl;
        file.close();
    }
    void displayData()
    {
        system("cls");
        fstream file;
        cout<<"\t\t\t||STUDENT RECORD||"<<endl;
        cout<<"\t\t\t__________________"<<endl;
        file.open("studentDB.txt",ios::in);

        if(!file)
        {
            cout<<"NO DATA PRESENT!"<<endl;
            file.close();
            return;
        }
        else
        {
            string temp;
            while(getline(file,temp))
            {
                cout<<temp<<endl;
            }
            file.close();
        }
        system("pause");
        
    }
    
    void search()
    {
        system("cls");
        string roll;

        cout<<"\t\t\t||SEARCH RECORDS||"<<endl;
        cout<<"\t\t\t__________________"<<endl;

        cout<<"\t\t\tENTER STUDENT'S ROLL NUMBER: ";
        cin>>roll;
        fstream file;
        file.open("studentDB.txt",ios::in);
        if(!file)
        {
            cout<<"CANT OPEN FILE\n";
            return;
        }
        else
        {
            int flag=0;
            string temp,temp2;
            while(getline(file,temp))
            {
                if(temp==("ROLL NUMBER: "+roll))
                {
                    flag=1;
                    while(getline(file,temp2))
                    {
                        if(temp2=="end")
                        break;
                        cout<<temp2<<endl;
                    }
                    break;
                }
            }
            if(flag==0)
            {
                cout<<"\t\t\tNO DATA FOUND\n";
            }
        }
        file.close();
        system("pause");
    }
    void deleteData()
    {
        system("cls");
        string roll;

        cout<<"\t\t\t||DELETE RECORD||"<<endl;
        cout<<"\t\t\t__________________"<<endl;

        cout<<"\t\t\tENTER STUDENT'S ROLL NUMBER: ";
        cin>>roll;
        fstream file,filetemp;
        file.open("studentDB.txt",ios::in);
        if(!file)
        {
            cout<<"CANT OPEN FILE\n";
            return;
        }
        else
        {
            filetemp.open("temporary.txt",ios::out|ios::app);
            int flag=0;
            string temp,temp2;
            while(getline(file,temp))
            {
                if(temp==("ROLL NUMBER: "+roll))
                {
                    flag=1;
                    while(getline(file,temp2))
                    {
                        if(temp2=="end")
                        break;
                    }
                    
                }
                else
                {
                    filetemp<<temp<<endl;
       
                }
                

            }
            if(flag==0)
            {
                cout<<"\t\t\tNO DATA FOUND\n";
            }
        }
        file.close();
        filetemp.close();
        remove("studentDB.txt");
        rename("temporary.txt","studentDB.txt");
        system("pause");


    }
 
};
int main()
{
    system("Color 04");
    Student obj;
    obj.menu();
    return 0;
}