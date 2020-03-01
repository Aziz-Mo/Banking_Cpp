//214

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <string.h>
#include <iomanip>
#include <sstream>
using namespace std;

struct _Account { // acc = Account
    int acc_no;
    char name[50];
    int balance;
    char type;
};

struct Account { // acc = Account
    int acc_no;
    char name[50];
    int balance;
    char type;
    Account *next;

};


/***************  GLOBAL  VARIABLES  ***************/
struct Account *Prev, *Curr;
struct Account *Head = NULL; // Head of the Linked List
// will write something here



/*********************  FUNCTIONS PROTOTYPES  ********************/
void create_account(void); //Adding new account
void DeleteAccount(void);
void show_account(int);
void dep(int); // deposit amount
void draw(int); // withdraw amount
Account* search(int);
void LoadList(void);
void SaveList(void);
//      void modify();

/******************  FUNCTION  DEFINITIONS  **********************/

/*
bool is_empty(Account *head) {
    return head == nullptr;
} */

/******************  CREATE Function  **********************/
void create_account() {
    struct Account *NewNode = new Account;

    // Account *NewNode = new Account;
    cout << "Enter the account ID\n";
    cin >> NewNode->acc_no;
    cout << "Enter the account name\n";
    //cin >> NewNode->name;
    cin.ignore();
    cin.getline(NewNode->name, 50);
    cout << "Enter the amount of balance\n";
    cin >> NewNode->balance;
    cout << "Enter the type of Saving or Current (S/C)";
    cin >> NewNode->type;
    NewNode->next = NULL;

    if (Head == NULL) {
        Head = NewNode;
        cout << "Account Added\n";
        return;
    }
    if(NewNode->acc_no == Head->acc_no){
        cout<<"\nAccount ID already exists\n\n";
        return;
    }
    if (NewNode->acc_no < Head->acc_no) {
        NewNode->next = Head;
        Head = NewNode;
        cout <<"Account Added\n";
        return;
    }

    Prev = Curr = NULL; // To find the pre and cur position, Loop
    for (Curr = Head; Curr != NULL; Curr = Curr->next) {
         if(NewNode->acc_no == Head->acc_no){
        cout<<"\nAccount ID already exists\n\n";
        return;
    }
        if (NewNode->acc_no < Curr->acc_no)
            break;
        Prev = Curr;
    }
    NewNode->next = Prev->next;
    Prev->next = NewNode;

    cout << "\nAccount Added\n\n";
} // End of Creation function

/******************  SHOW    FUNCTION   **********************/
void DeleteAccount(void){
    if(Head == NULL){
        cout<< "Empty\n\n";
        return;
    }
    int key;
    cout << "Enter account ID to delete: ";
    cin >> key;
    if(Head->acc_no == key){
        Head = Head->next;
        return;
          cout <<"Account Deleted\n\n";
    }
    for(Curr = Head; Curr != NULL; Curr = Curr->next){
        if (Curr->acc_no == key)
            break;
        Prev = Curr;
    } if(Curr = NULL){
        cout << "Account not Found\n\n";
    }else{
        Prev->next = Curr->next;
        delete(Curr);
        cout <<"Account Deleted\n\n";
    }
}
/******************  Show All Accounts **********************/
void show_account(void) {
    if (Head == NULL) {
        cout << "Empty Linked List!";
        cout << "\nNothing to Show\n";
        return;
    }

    Curr = Head;
    while (Curr != NULL) {
        cout << "Account No. : " << Curr->acc_no;
        cout << "\tAccount Name: " << Curr->name;
        cout << "\tAccount Balance: " << Curr->balance;
        cout << "\tAccount Type: " << Curr->type;
        cout << "\n";
        Curr = Curr->next;

    }

}
/******************  Show Single Account **********************/
void show_one() {
    int key;
    cout << "Enter the Account No. using ID\n";
    cin >> key;
    if(Curr = search(key)){
 cout << "Account No. : " << Curr->acc_no;
 cout << "\tAccount Name: " << Curr->name;
 cout << "\tAccount Deposit: " << Curr->balance;
 cout << "\tAccount Type: "<< Curr->type;
    }
 }



/******************  DEPOSIT  FUNCTION  **********************/
void dep(int x) { // Balance
    // how to access to the client
    int key;
    cout << "Enter the search key now\n";
    cin >> key;

    Curr = search(key);
    if (Curr != NULL)
        Curr->balance += x;
    else
        cout << key << " Not found in database \n";
}

/******************  WITHDRAW  FUNCTION   **********************/
void draw(int x) {

    int key;
    cout << "Enter the search key now\n";
    cin >> key;
    Curr = search(key);
    if (Curr != NULL)
        Curr->balance -= x;
    else
        cout << key << " Not found in database \n";
}

/******************  SEARCH  FUNCTION   **********************/
Account * search(int key) {
    Curr = Head;

    // Iterate till last element until key is not found
    while (Curr != NULL && Curr->acc_no != key) {

        Curr = Curr->next;
    }
    if (Curr != NULL) {
        return Curr;
    } else
        return NULL;
}

/******************  SAVE LIST  **********************/
void SaveList(void) {
    ofstream pFile;
    pFile.open("Account.dat", ios::binary);
    if (!pFile.is_open()) {
        cout << "Can't Open File\n Updated data not saved into file\n";
        return;
    }

     _Account AC;
     Account *Curr;
    // copy record from linked list into file record structure
    for (Curr = Head; Curr != NULL; Curr->next) {
        AC.acc_no = Curr->acc_no;
        strcpy(AC.name, Curr->name);
        AC.balance = Curr->balance;
        AC.type = Curr->type;

        pFile.write((char *) &AC, sizeof (AC)); //write record into a file
    }
    pFile.close();
    cout << "Saved to File!\n\n";
}

/******************  LOAD LIST  **********************/
void LoadList(void) {
    ifstream iFile;
    iFile.open("Account.dat", ios::binary);
    if (!iFile.is_open()) {
        Head = NULL;
        cout << "File not Exist\n";
        return;
    }
    _Account AC; //Structure variable to hold data from file
    Account *NewNode,  *Tail = Head =NULL;; // Structure pointer to add data into linked list
     
        // Read First Record from file
    iFile.read((char*) &AC, sizeof (AC)); 
    while(!iFile.eof())
    {
        NewNode = new Account;
        NewNode->acc_no = AC.acc_no;
        strcpy(NewNode->name, AC.name);
        NewNode->balance = AC.balance;
        NewNode->type = AC.type;
        NewNode->next = NULL;
        
        if(Head == NULL){   
            Head = NewNode;
            Tail = Head;
            
        }else {
            Tail->next = NewNode;
            Tail = NewNode;
        }
          // read next record from file
          iFile.read((char*) &AC, sizeof (AC));
    }
    iFile.close();
    cout << "Successfully Loaded File\n";
}

/*************************MAIN FUNCTION****************************/

int main() {
    int choice;
    int val;
    //LoadList();
    while (true) {
        cout << "\n1.Create account\n";
        cout << "2.Show account\n";
        cout << "3.To Deposit\n";
        cout << "4.To Withdraw\n";
        cout << "5.To LoadList\n6.To SaveList\n";
        cout << "7.To Delete Account\n8.To Show Single Account\n";
        cout << "9.To Exist\n\n";

        cin>> choice;
        switch (choice) {
            case 1:
                cout << "Lets Go:\n\n";
                create_account();
                break;
            case 2:
                show_account();
                break;
            case 3:
                cout << "You have to enter the value\n";
                cin >> val;
                dep(val);
                break;
            case 4:
                cout << "You have to enter the value\n";
                cin >> val;
                draw(val);
                break;
            case 5:
                LoadList();
                break;
            case 6:
                SaveList();
                break;
            case 7:
                DeleteAccount();
                break;
            case 8:
                show_one();
                break;
            case 9: 
                cout << "Program Ended Byee~\n";
                exit(0);
                break;
                
            default:
                cout << "Nothing Entered Byee~\n";
                break;
        }
    }
}
