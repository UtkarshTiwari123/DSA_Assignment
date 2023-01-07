#include <iostream>
#include<cstring>
using namespace std;
const int ALPHABET_SIZE = 256;
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE]; //array of pointers
    bool isEndOfWord;
};

struct TrieNode* getNode(void)  //creates new empty Trienode and returns TrieNode*
{
    struct TrieNode *tempNode = new TrieNode; //dynamically creating a TrieNode

    tempNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) //setting children as 0
        tempNode->children[i] = NULL;

    return tempNode;
}

struct TrieNode *Root = getNode(); //creating root node which signifies start of trie data structure.

void insert_into_trie(struct TrieNode *root, char key[]) //insertion function
{
    struct TrieNode *temp  = root;

    for (int i = 0; key[i]!='\0'; i++)
    {
        int index = key[i] - 'a';
        if (!temp->children[index]){          //creating new node if a node corresponding to that node DNE
            temp->children[index] = getNode();
        }
        temp = temp->children[index];
    }
    temp->isEndOfWord = true;
}

bool isLastNode(TrieNode* root) // Check whether trie is empty or not
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

TrieNode* remove_from_trie(TrieNode* root, string key, int i) //deletion using recursion
{
    if (!root) //exception handling
        return NULL;

    if (i == key.size()) //base case
    {
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        if (isLastNode(root)) {  //to check whether a leaf node or not
            delete (root);
            root = NULL;
        }
        return root;
    }
    int index = key[i] - 'a';
    root->children[index] =
          remove_from_trie(root->children[index], key, i + 1); //upon deletion, the value in the parent root array gets updated to NULL indicating deletion

    if (isLastNode(root) && root->isEndOfWord == false)
    {
        delete (root);
        root = NULL;
    }
    return root;
}

void suggestionsRec(struct TrieNode* root, string currPrefix) //here root is last letter of currPrefix (mp)
{
    if (root->isEndOfWord) //to print every word
    {
        cout << currPrefix;
        cout << endl;
    }
    if (isLastNode(root)) // to move on to the next branch after having exhausted the first. For eg pq->rs then pq->sr
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            currPrefix.push_back(97 + i);

            suggestionsRec(root->children[i], currPrefix);
            currPrefix.substr(0, currPrefix.size()-1);
        }
    }
}

int printAutoSuggestions(TrieNode* root, const string query) //to check for 3 diff options: refer main() for 3 options
{
    struct TrieNode* temp = root;
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);

        if (!temp->children[index])
            return 0;

        temp = temp->children[index];
    }
    bool isWord = (temp->isEndOfWord == true);
    bool isLast = isLastNode(temp);

    if (isWord && isLast)
    {
        cout << query << endl;
        return -1;
    }
    if (!isLast)
    {
        string prefix = query;
        suggestionsRec(temp, prefix);
        return 1;
    }
    return 0;
}

class dnode
{
    public:
        char number[50];
        char gmail[40];
        string name;
        dnode *prev,*next;
        dnode(string n,char r[],char g[]) //constructor
{
        name = n;
        strcpy(number,r);
        strcpy(gmail,g);
        next=NULL;
        prev=NULL;
}
	friend class dlist;  //to make all properties of dnode accessible to dlist
};

class dlist
{
    dnode *head,*temp,*ptr;
    dnode *ptr1, *ptr2, *dup;

    public:
    void insert();
    void sort();
    void deletecontact(string n);
    void deletesamename();
    void searchbyname(string p);
    void searchbynumber(char no[30]);
    void searchbygmail(char g[20]);

        void accept();
        void display();
        void update(char ch[10]);
        dlist() //constructor
                {
                    head=NULL;
                    temp=NULL;
                    ptr=NULL;
                    ptr1=NULL;
                    ptr2=NULL;
                    dup=NULL;
                }
};

void dlist::accept()
{
        char number[50];
        char gmail[40];
        string name;
        char ans;
      do
    {
        cout<<"ENTER NAME      :";
        cin>>name;
        cout<<"ENTER NUMBER    :";
        cin>>number;
        while(strlen(number)!=10)
        {
        cout<<"ENTER VALID NUMBER  :";
        cin>>number;
        }
        cout<<"ENTER G-MAIL    :";
        cin>>gmail;
        temp=new dnode(name,number,gmail);
        if(head==NULL)
        {
            head=temp;
        }
        else
        {
        ptr=head;
            while(ptr->next!=NULL)
            {
        ptr=ptr->next;
            }
            ptr->next=temp;
            temp->prev=ptr;
        }

        //struct TrieNode *root = getNode();
        int n1 = name.length();
 
    // declaring character array
    char char_array[n1 + 1];
 
    // copying the contents of the
    // string to char array
    strcpy(char_array, name.c_str());
 
    for (int i = 0; i < n1; i++)
        cout << char_array[i];
        insert_into_trie(Root, char_array); //entering the name in the trie
            cout<<"\nDO YOU WANT TO CONTINUE? (Y/N)\n";
        cin>>ans;
    }while(ans=='y' || ans=='Y');
}
    void dlist::display()
    {
        ptr=head;
        while(ptr!=NULL)
        {
                cout<<"\n\nNAME:\t"<<ptr->name;
                cout<<"\nNUMBER:\t+91-"<<ptr->number;
                cout<<"\nG-MAIL:\t"<<ptr->gmail;
                ptr=ptr->next;
        }
    }

    void dlist::insert()
    {
        accept();
    }

    void dlist::sort()
    {
        dnode *i,*j;
        int temp;
        char n[10];
        for(i=head;i->next!=NULL;i=i->next)
        {
            for(j=i->next;j!=NULL;j=j->next)
            {
                temp=strcmp(i->name,j->name);
                if(temp>0)
                {
                   strcpy(n,i->name);
                   strcpy(i->name,j->name);
                   strcpy(j->name,n);
                }
            }
        }
    }

    void dlist::deletecontact(string s)
    {
        //struct TrieNode *root = getNode();
        Root = remove_from_trie(Root, s, 0); //deleting from trie
        int c=0;                             //used as flag
        ptr=head;
        while(ptr!=NULL)
        {
            if(strcmp(s,ptr->name)==0)  //deleting the first contact with the matching name
            {
                c=1;
                break;
            }
            else
            {
                c=2;
            }
            ptr=ptr->next;
        }
        if(c==1 && ptr!=head && ptr->next!=NULL)
        {
            ptr->prev->next=ptr->next;
           ptr->next->prev=ptr->prev;
           delete(ptr);
           cout<<"YOUR CONTACT IS SUCCESSFULLY REMOVED\n\n";
        }
		if(ptr==head)
        {
            head=head->next;
            head->prev=NULL;
            delete(ptr);
           cout<<"YOUR CONTACT IS SUCCESSFULLY REMOVED\n\n";
        }
        if(c==2)
        {
            cout<<"YOUR ENTERED NAME IS NOT IN THE LIST...\n";
        }
        if(ptr->next==NULL && ptr!=NULL)
        {
            ptr->prev->next=NULL;
            ptr->prev=NULL;
            delete(ptr);
           cout<<"YOUR CONTACT IS SUCCESSFULLY REMOVED\n\n";
        }
    }

    void dlist::deletesamename()  //only delete same name cuz rest both attributes are always unique in nature
    {                             //no need of input as the list is sorted so by comparing adjacent nodes we can delete all the same names
        ptr1=head;
        while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;
        while (ptr2->next != NULL)
        {
            if (strcmp(ptr1->name,ptr2->next->name)==0)
            {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete(dup);
            }
            else
            {
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
    }

    void dlist::searchbyname(string na)
    {
        ptr=head;
        while(ptr!=NULL)
        {
            if(strcmp(na,ptr->name)==0)
            {
                cout<<"NAME FOUND"<<endl;
                cout<<"CONTACT DETAILS ARE GIVEN BELOW:\n"<<endl;
        	    cout<<"\n\nNAME IS::\t"<<ptr->name;
			    cout<<"\nNUMBER IS::\t+91-"<<ptr->number;
			    cout<<"\nG-MAIL ID::\t"<<ptr->gmail;
            }
            ptr=ptr->next;
        }
    }

    void dlist::searchbynumber(char num[20])
    {
     ptr=head;
        while(ptr!=NULL)
        {
            if(strcmp(num,ptr->number)==0)
            {
                cout<<"NUMBER FOUND\n"<<endl;
                cout<<"CONTACT DETAILS ARE GIVEN BELOW:\n"<<endl;
        	    cout<<"\n\nNAME IS::\t"<<ptr->name;
			    cout<<"\nNUMBER IS::\t+91-"<<ptr->number;
			    cout<<"\nG-MAIL ID IS::\t"<<ptr->gmail;

            }
            ptr=ptr->next;
        }
    }

    void dlist::searchbygmail(char gm[20])
    {
        ptr=head;
        while(ptr!=NULL)
        {
            if(strcmp(gm,ptr->gmail)==0)
            {
                cout<<"G-MAIL FOUND\n"<<endl;
                cout<<"CONTACT DETAILS ARE BELOW:\n"<<endl;
        	    cout<<"\n\nNAME IS::\t"<<ptr->name;
			    cout<<"\nNUMBER IS::\t+91-"<<ptr->number;
			    cout<<"\nG-MAIL ID IS::\t"<<ptr->gmail;
            }
            ptr=ptr->next;
        }
    }

    void dlist::update(string n)
    {
        char ans;
        int c;
        ptr=head;
        while(ptr!=NULL)
        {
            if(strcmp(n,ptr->name)==0)
            {
                do
                {
                    cout<<"\nWHICH DETAIL DO YOU WANT TO UPDATE? KINDLY SELECT FROM GIVEN OPTIONS\n1.NAME\n2.PHONE NUMBER\n3.G-MAIL\n";
                    cin>>c;
                    switch(c)
                    {
                        case 1:
                        cout<<"ENTER NEW NAME=\n";
                        cin>>ptr->name;
                        break;

                        case 2:
                        cout<<"ENTER NEW PHONE NUMBER?\n";
                        cin>>ptr->number;
                        while(strlen(ptr->number)!=10)
                        {
                            cout<<"PHONE NUMBER DOESN'T CONTAINS 10 DIGITS"<<endl;
                            cout<<" KINDLY ENTER VALID NUMBER  :";
                            cin>>ptr->number;
                        }
                        break;

                        case 3:
                        cout<<"ENTER NEW GMAIL ID\n";
                        cin>>ptr->gmail;
                        break;
                    }

                    cout<<"\nDO YOU WANT TO CONTINUE UPDATING? (Y/N)\n";
                    cin>>ans;
                }while(ans=='y' || ans=='Y');
            }
            ptr=ptr->next;
        }
    }
