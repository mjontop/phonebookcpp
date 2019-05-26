#include <iostream>
#include <fstream>
#include <string.h>
#include<stdlib.h>
#include<process.h>
#include<conio.h>
using namespace std;
char password[8];

class account
{
    char username[10];
    char pword[8];
public:
    void GetData();
    void showdata();

};

void checkpassword()
{
    char chkpasswrd[8];
    ifstream pswrd;
    pswrd.open("password.txt");
    pswrd>>password;
    cout<<"\n\n\t\t\tEnter password:";
    cin>>chkpasswrd;
    system("cls");
    if(strcmp(chkpasswrd,password)!=0)
    {
        cout<<" \n\n\t\t\tIncorrect password\n\n\t\t";
        getch();
        exit(1);
    }
}
void ChangePassword()
{
    system("cls");
    char oldpasswrd[8];
    cout<<"\n\n\n\t\t\tEnter old password: ";
    cin>>oldpasswrd;
    if(strcmp(oldpasswrd,password)!=0)
    {
        cout<<" \n\n\t\t\tIncorrect password\n\n\t\t";
        getch();
        cout<<"\tTry Again";
        cout<<"\n\n\n\t\t\tEnter old password";
        cin>>oldpasswrd;
        if(strcmp(oldpasswrd,password)!=0)
            {cout<<" \n\n\t\t\tIncorrect password\n\n\t\t";
                        getch();exit(1);
            }
    }
    else
        {
           cout<<"\n\n\t\t\tEnter New Password: ";
           char newpassword[8];
           cin>>newpassword;
           ofstream cp;
           cp.open("password.txt");
           cp<<newpassword;
           cout<<" \t\t\t\n\nPASSWORD CHANGED SUCESSFULLY\n\n";
        }
}
class phoneBook{
    char name[20],phno[10];
    public:
    void getdata();
    void showdata();
    char *getname(){ return name; }
    char *getphno(){ return phno; }

};

void phoneBook :: getdata()
{
    cout<<"\n\t\t\tEnter Name : ";
    cin>>name;
    cout<<"\n\t\t\tEnter MobNo.: ";
    cin>>phno;
}
void phoneBook :: showdata()
{
    cout<<"\n";
    cout<<"\t\t\t "<<name;
    cout<<"\t"<<phno<<endl;
}
int main()
{


    checkpassword();
    fstream phbk;
    phoneBook rec;
    char ch,nm[20],telno[10];
    int choice,found,exiter=0, num=0;
     ch='y';
     while (ch=='y'||ch=='Y')
     {

        cout<<"\n\n\t\t\t*******PHONE BOOK********\n\n";
        cout<<"\t\t\tPRESS 1. Add New Record.\n\n";
        cout<<"\t\t\tPRESS 2. Display All Records.\n\n";
        cout<<"\t\t\tPRESS 3. Search Telephone No.\n\n";
        cout<<"\t\t\tPRESS 4. Search Person Name.\n\n";
        cout<<"\t\t\tPRESS 5. TO CHANGE PASSWORD.\n\n";
        cout<<"\t\t\tPRESS 6. TO Delete All Records.\n\n";
        cout<<"\t\t\tChoose your choice (1/2/3/4/5/6)  : ";
        cin>>choice;
        if(!(choice==1 || choice==2 || choice==3 || choice==4 ||choice==5 || choice==6))
        {
            cout<<"\n\n\t\t\t INCORRECT CHOICE \n\t\t\t   TRY AGAIN\n\n "; cout<<"\7";
            system("pause");
            ch='y';
            exiter++;
            system("cls");
            if (exiter==3)
            {
                    cout<<" \n\n\n\n\t\t\tYou crossed your limit\t\2 \n\t\t\tTry again after some time\n\n\n\n\t\t\t";
                    system("pause");
                    exit(-1);
            }
        }
        else
        {
            switch(choice)
            {

               case 1 : //New Record

                     phbk.open("phonbk.dat", ios::binary|ios::out|ios::app);
                     rec.getdata();
                     phbk.write((char *)&rec, sizeof(rec));
                     system("cls");
                     cout<<" \n\n\t\t\t\tRecord Entered";
                     phbk.close();
                     break;

               case 2 : //Display All Records
                     num=0;//if display a record is called more than 1 time, then the value of num will add up every time, without this
                     phbk.open("phonbk.dat",ios::in|ios::binary);
                     cout<<"\n\n\t\t Records in Phone Book:\n";
                     
                     system("cls");
                     cout<<"\n\n\t\t\t\t   ---RECORDS -----";
                     cout<<"\n\n\n\t\t\t "<<"Name"<<"\t"<<"Mobile Number\n";
                     cout<<"\t\t\t ____\t_____________\n\n";

                     while(phbk.read((char *)&rec, sizeof(rec)))
                         {
                             rec.showdata();
                             cout<<"\n\n\t\t";
                             num++;
                         }
                         cout<<"\v \t\t"<<num<<" Records found";
                         phbk.close();
                         break;

              case 3 : //Search Tel. no. when person name is known.

                     phbk.open("phonbk.dat",ios::binary|ios::in);
                     system("cls");
                     cout<<"\n\n\t\tEnter Name : ";
                     cin>>nm;
                     phbk.seekg(0,ios::beg);
                     found=0;
                     phbk.read((char *) &rec, sizeof(rec));
                     while(!(phbk.eof()))
                     {
                         phbk.read((char *)&rec, sizeof(rec));
                        if(strcmp(nm,rec.getname())==0)
                        {
                            found++;
                            rec.showdata();
                            break;

                        }

                     }
                     phbk.close();
                     if(found==0)
                    cout<<"\n\n---Record Not found---\n";
                    break;

            case 4 : //Search name on basis of tel. no

                     phbk.open("phonbk.dat");
                     system("cls");
                     cout<<"\n\n\t\t\tEnter Telephone No : ";
                     {
                         cin>>telno;
                         phbk.seekg(0,ios::beg);
                         found=0;
                         while(phbk.read((char *) &rec, sizeof(rec)))
                         {
                            if(strcmp(telno,rec.getphno())==0)
                            {
                                found=1;
                                rec.showdata();
                            }
                         }
                         phbk.clear();
                         if(found==0)
                            cout<<"\n\n\t\t\t--- SORRY  Record Not found---\n";
                         break;

                case 5: ChangePassword(); break;
            //    case 6: DeleteAllRECD(); break;



          }
        }

            cout<<"\n\n\t\t\tDo you Wants to Continue?(y/n)";
            cin>>ch;
            system("cls");
         }
   }
   cout<<" \n\n\n\n\t\t\t THANK YOU FOR USING OUR APPLICATION\\n\n\t\t\t FOR MORE UPDATES FOLLOW us @mjontop_\n\n\n\n";
}
