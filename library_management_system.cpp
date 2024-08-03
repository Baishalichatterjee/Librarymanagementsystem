#include<iostream>
#include<cstring>
#include<iomanip>

using namespace std;

//Constants
const int MAX_STUDENTS=20;
const int MAX_BOOKS=15;
const int MAX_NAME_LENGTH=50;

//Global variables
int student_count=0;
int book_count=0;
double student_balance[MAX_STUDENTS];
int student_roll[MAX_STUDENTS];
char student_name[MAX_STUDENTS][MAX_NAME_LENGTH];
char book_title[MAX_BOOKS][MAX_NAME_LENGTH];
char book_author[MAX_BOOKS][MAX_NAME_LENGTH];
int book_isbn[MAX_BOOKS];
bool book_available[MAX_BOOKS];

//Function prototypes
void createaccount();
void display(int roll);
void deposit_amount(int roll,double amount);
void issue_item(int roll);
void display_sorted();
int find_student(int roll);
int find_book(int isbn);
void addbook();
void editbook();
void view_books();

int main(){
for(int i=0;i<MAX_BOOKS;i++){
strcpy(book_title[i],"Title");
strcpy(book_author[i],"Author");
book_isbn[i]=i+1000;
book_available[i]=true;
}
book_count=MAX_BOOKS;

int option;
bool is_admin;
string password;
while(true){
cout<<"Login as:\n1. Admin\n2.Student\n0.Exit\n";
cin>>option;

if(option==0){
break;
}

is_admin= (option == 1);
cout<<"Enter password:";
cin>>password;

if(password == "khushi@123"){
if(is_admin){
cout<<"Admin option:\n1.Add book\n2.Edit book\n3. View book status\n4.View enrolled students\n5.View student balance\n";
cin>>option;

switch(option){
 case 1:{
 addbook();
 break;
 }
case 2:{
editbook();
break;
}
case 3:{
view_books();
break;
}
case 4:{
display_sorted();
break;
}
case 5:{
int roll;
cout<<"Enter student roll number:";
cin>>roll;
display(roll);
break;
}
}
}else{
int roll;
cout<<"Enter your roll number: ";
cin>>roll;

int index = find_student(roll);
if(index == -1){
cout<<"Student not found.Create an account? (1. Yes / 2. No):";
cin>>option;
if(option == 1){
createaccount();
}
}else{
cout<<"Student options:\n1. View balance\n2. Deposit amount\n3. Issue item\n";
cin>>option;

switch(option){
case 1:{
display(roll);
break;
}
case 2:{
double amount;
cout<<"Enter the amount to deposit:";
cin>>amount;
deposit_amount(roll,amount);
break;
}
case 3:{
issue_item(roll);
break;
}
}

}

}

}else{
cout<<"Incorrect password.\n";
}

}
return 0;
}
void createaccount(){
if(student_count >= MAX_STUDENTS){
cout<<"Student limit reached.Cannot create more accounts.\n";
return ;
}

int roll;
cout<<"Enter roll number:";
cin>>roll;

if(find_student(roll)!=-1){
cout<<"Account already exists for this roll number.\n";
return ;
}
student_roll[student_count] = roll;
cout<<"Enter student name:";
cin.ignore();
cin.getline(student_name[student_count],MAX_NAME_LENGTH);

double initial_deposit;
cout<<"Enter initial deposit amount :";
cin>>initial_deposit;

if(initial_deposit < 50){
cout<<"Initial deposit must be at least $50.\n";
return ;
}

student_balance[student_count] = initial_deposit - 20 - 30;
student_count++;
}

void display(int roll){
int index = find_student(roll);
if(index == -1){
cout<<"Student not found.\n";
return ;
}

cout<<"Roll No:"<<student_roll[index]<<endl;
cout<<"Name: "<<student_name[index]<<endl;
cout<<"Balance: "<<fixed<<setprecision(2)<<student_balance[index]<<endl;
}

void deposit_amount(int roll,double amount){
    int index=find_student(roll);
    if(index == -1){
        cout<<"Student not found.\n";
        return ;
    }

    student_balance[index]+=amount;
    cout<<"New balance:$"<<fixed<<setprecision(2)<<student_balance[index]<<endl;
    }
void issue_item(int roll){
int index = find_student(roll);
if(index == -1){
 cout<<"student not found.\n";
 return ;
}

cout<<"Available books:\n";
for(int i=0;i<book_count;i++){
    if(book_available[i]){
        cout<<i+1<<" ."<<book_title[i]<<"by"<<book_author[i]<<"(ISBN:"<<book_isbn[i]<<")\n";
    }
}

int choice;
cout<<"Enter the number of the book you want to issue (0 to cancel):";
cin>>choice;

if(choice == 0){
    return ;
}

if(book_available[choice-1] && student_balance[index] >= 2){
    book_available[choice-1]=false;
    student_balance[index]-=2;
    cout<<"Book issued successfully.New balance:$"<<fixed<<setprecision(2)<<student_balance[index]<<endl;
}else{
cout<<"Cannot issue the book.Insufficient balance or book is unavailable.\n";
}
}
void display_sorted(){
for(int i=0;i<student_count;i++){
    for(int j=0;j<student_count-i-1;j++){
        if(student_roll[j] > student_roll[j+1]){
            int temp=student_roll[j];
            student_roll[j]=student_roll[j+1];
            student_roll[j+1]=temp;
        }
    }
}
for(int i=0;i<student_count;i++){
    cout<<student_roll[i]<<" - "<<student_name[i]<<" - Balance:$"<<fixed<<setprecision(2)<<student_balance[i]<<endl;
}
}

int find_student(int roll){
for(int i=0;i<student_count;i++){
    if(student_roll[i] == roll){
        return i;
    }
}
return -1;
}

int find_book(int isbn){
for(int i=0;i<book_count;i++){
    if(book_isbn[i] == isbn){
        return i;
    }
}
return -1;
}

void addbook(){
if(book_count >= MAX_BOOKS){
    cout<<"Book limit reached. cannot add more books\n.";
    return ;
}
cout<<"Enter book title:";
cin.ignore();
cin.getline(book_title[book_count],MAX_NAME_LENGTH);

cout<<"Enter book author: ";
cin.getline(book_author[book_count],MAX_NAME_LENGTH);

int isbn;
cout<<"Enter book ISBN: ";
cin>>isbn;

if(find_book(isbn) != -1){
    cout<<"A book with this ISBN already exists.\n";
    return ;
}

book_isbn[book_count] = isbn;
book_available[book_count]=true;
book_count++;
}

void editbook(){
int isbn;
cout<<"Enter books ISBN to edit: ";
cin>>isbn;
int index = find_book(isbn);
if(index == -1){
    cout<<"Book not found.\n";
    return ;
}

cout<<"Current book title: "<<book_title[index]<<endl;
cout<<"Enter new book title: ";
cin.ignore();
cin.getline(book_title[index],MAX_NAME_LENGTH);

cout<<"BOOk details update.\n";
}

void view_books(){
for(int i=0;i<book_count;i++){
    cout<<"Title: "<<book_title[i]<<endl;
    cout<<"Author: "<<book_author[i]<<endl;
    cout<<"ISBN: "<<book_isbn[i]<<endl;
    cout<<"Available: "<<(book_available[i] ? "Yes" : "No")<<endl<<endl;
    }
}
