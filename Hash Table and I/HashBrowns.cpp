
#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>

using namespace std;

const int TABLE_SIZE = 1000;

class HashNode
{
    public:
       int key;
       double GPA;
       string name, academicLevel;
	   HashNode* next;
        HashNode(int key, string name, string academicLevel, double GPA)
        {
           this->key = key;
	       this->name = name;
           this->academicLevel = academicLevel;
           this->GPA = GPA;
	       this->next = NULL;
        }
};
 

class HashMap
{
    private:
        HashNode** hash_table;
    public:

        HashMap()
        {
            hash_table = new HashNode*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                hash_table[i] = NULL;
        }

        ~HashMap()
        {
            for (int i = 0; i < TABLE_SIZE; ++i)
	        {  
                HashNode* node = hash_table[i];
                while (node != NULL)
	            {
                    HashNode* prev = node;
                    node = node->next;
                    delete prev;
                }
            } delete[] hash_table;
        }
        
        int Hashing(int key)
        {
            return key % TABLE_SIZE;
        }
 
        void Insert(int key, HashNode* student)
        {
            int HashmapInsertionSlot = Hashing(key);
            HashNode* prev = NULL;
            HashNode* node = hash_table[HashmapInsertionSlot];
            while (node != NULL)
            {
                prev = node; node = node->next;
            }
            if (node == NULL)
            {
                node = new HashNode(student->key, student->name, student->academicLevel, student->GPA);
                if (prev == NULL)
                    hash_table[HashmapInsertionSlot] = node;
	        else
                    prev->next = node;
            }
            else
                node = student;
        }
        
        void Delete(int key)
        {
            int HashmapInsertionSlot = Hashing(key);
            HashNode* node = hash_table[HashmapInsertionSlot];
            HashNode* prev = NULL;

            if (node == NULL)
            {
                cout<< "Nothing found" << endl;
                return;
            }
            else
            {
                if (node->key == key)
                    hash_table[HashmapInsertionSlot] = node->next;
                else
                {
                    while(node->next != NULL)
                    {
                        if(node->key == key) break;
                        prev = node;
                        node = node->next;
                    }

                    if(node != NULL)
                        prev->next = node->next;
                    else
                        cout<< "Node not found" << endl;
                }
            }
        }

        int Search(int key)
        {
            int HashmapInsertionSlot = Hashing(key);
            HashNode* node = hash_table[HashmapInsertionSlot];
            while (node != NULL)
	           {
                if (node->key == key){
                    cout<<" "<<endl;
                    cout<<" "<<endl;
                    cout<<"Name: "<<node->name<<endl;
                    cout<<"Academic Level: "<<node->academicLevel<<endl;
                    cout<<"GPA: "<<node->GPA<<endl;
                   } node = node->next;
                }
        }
};

int main()
{
    HashMap hash;
    int choice, key, value, HashmapInsertionSlot;
    double GPA;
    string name, academicLevel;
    while (true)
    {
        cout << endl << endl;
        cout << " Hash Table Implementation " << endl;
        cout << " ----------------------------- " << endl;
        cout << " 1. Insert a Record (user enters the name, GPA, Academic level, Key (Key should be between 0 - 65536" << endl;
        cout << " 2. Search the table (user enters a key for search) Key should be between 0 - 65536" << endl;
        cout << " 3. Delete a record (user enter a key of the decord to be deleted) " << endl;
        cout << " Enter your choice : ";
        cin>>choice;
        switch(choice)
        {
        case 1:
        {
            cout<<"(string) Enter a Name: ";
            cin>>name;
            cout<<"(double) Enter a GPA: ";
            cin>>GPA;
            cout<<"(string) Enter a Academic Level: ";
            cin>>academicLevel;
            cout<<"(int) Enter a Key: ";
            cin>>key;

            HashNode* student = new HashNode(key, name, academicLevel, GPA);

            hash.Insert(key, student);
        }
            break;
        case 2:
        {
            cout<<"(int) Enter Key: ";
            cin>>key;
            cout<<"Information at Key: "<<key<<" : ";
            if (hash.Search(key) == -1)
            {
	        cout<<"Nothing found at key: "<<key<<endl;
	        continue;
	        }
        }
            break;
        case 3:
        {
            cout<<"(int) Enter key of hash to delete: ";
            cin>>key;
            hash.Delete(key);
        }
            break;
        case 4:
            exit(1);
        default:
           cout<<"\nEnter correct option\n";
       }
    } return 0;
}