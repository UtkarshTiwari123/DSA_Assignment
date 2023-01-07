#include <iostream>
#include<cstring>
#include "Driver Class.h"

using namespace std;

int main()
{
    string n;
    string name;
	char number[10];
    char gmail[20];
    string query;
    dlist d1;
    char ans;
    int ch,a;
    cout<<"*                                **PHONE BOOK**                          *";
    cout<<"\n\nENTER YOUR NAME?\n";
    cin>>name;
    cout<<"\n\n!!!   WELCOME "<<name<<" LETS CREATE YOUR PHONEBOOK   !!!\n \n";
    d1.accept();
    d1.sort();
    do
    {
        cout<<"\n\n\n KINDLY SELECT FROM GIVEN OPTIONS:\n1) DISPLAY YOUR PHONE BOOK\n2) INSERT NEW CONTACT\n3) UPDATE DETAILS ON EXISTING CONTACT\n4) DELETE CONTACT\n5) DELETE SAME NAMES IN PHONEBOOK\n6) SEARCH\n7) Advanced Search\n\n";
        cin>>ch;

        switch(ch)
        {
            case 2:
            d1.accept();
            d1.sort();
            break;

            case 1:
            d1.display();
            break;

            case 3:
            cout<<"\n\nENTER THE NAME OF PERSON WHOSE DETAILS YOU WANT TO UPDATE...\n";
            cin>>n;
            d1.update(n);
            d1.sort();
            break;

            case 4:
            cout<<"\nENTER THE NAME YOU WANT TO DELETE FROM PHONEBOOK\n";
            cin>>name;
            d1.deletecontact(name);
            break;

            case 5:
            d1.deletesamename();
            d1.display();
            break;

            case 6:
            do
            {
                cout<<"KINDLY SELECT FROM GIVEN OPTIONS"<<endl;
                cout<<"1.SEARCH BY NAME\n2.SEARCH BY NUMBER\n3.SEARCH BY GMAIL ID\n";
                cin>>a;
                switch(a)
                {
                    case 1:
                    cout<<"ENTER THE NAME TO BE SEARCHED\n";
                    cin>>name;
                    d1.searchbyname(name);
                    break;

                    case 2:
                    cout<<"ENTER THE NUMBER TO BE SEARCHED\n";
                    cin>>number;
                    d1.searchbynumber(number);
                    break;

                    case 3:
                    cout<<"ENTER THE GMAIL ID TO BE SEARCHED\n";
                    cin>>gmail;
                    d1.searchbygmail(gmail);
                    break;
                    default:cout<<"\nNO VALID INPUT GIVEN...\n";
                }
                cout<<"\nDO YOU WANT TO CONTINUE SEARCHING? (Y/N) \n";
                cin>>ans;
            }while(ans=='y' || ans=='Y');

            break;

            case 7:
                //struct TrieNode *root = getNode();
                cout<<"ENTER THE NAME TO BE SEARCHED\n";
                cin>>query;
                int comp = printAutoSuggestions(Root, query);

                if (comp == -1)
                        cout << "NO OTHER STRING FOUND WITH THIS PREFIX\n";

                    else if (comp == 0)
                        cout << "NO STRING FOUND WITH THIS PREFIX\n";
                break;
                cout<<"\nNO VALID INPUT GIVEN..\n";
        }

        cout<<"\n\nDO YOU WANT TO CONTINUE OPERATIONS? (Y/N)\n";
        cin>>ans;
}while(ans=='y' || ans=='Y');
}
