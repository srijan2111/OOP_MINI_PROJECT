#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<termios.h>
#include<cstdlib>
#include<unistd.h>
#include<ctime>               //for adding date and time
#include<cmath>
using namespace std;

class store{
protected:
  int cost,quantity;
  long int code;
  char name[20],DOE[10];
public:
  void add_item(){
    cout<<"CODE : "<<endl;
    cin>>code;
    cout<<"NAME : "<<endl;
    cin>>name;
    cout<<"COST : "<<endl;
    cin>>cost;
    cout<<"QUANTITY : "<<endl;
    cin>>quantity;
    cout<<"Date Of Expiry(DD/MM/YY) : "<<endl;
    cin>>DOE;
  }
  void show_item(){
      cout<<"\t\tCODE : "<<code<<endl;
      cout<<"\t\tNAME : "<<name<<endl;
      cout<<"\t\tCOST : "<<cost<<endl;
      cout<<"\t\tQUANTITY : "<<quantity<<endl;
      cout<<"\t\tDate Of Expiry(DD/MM/YY) : "<<DOE<<endl;
      cout<<"\t\t-------------------------------------------------------"<<endl;
  }
void purchase();
void create_item();
void displayALL();
void search_item();
void modify();
void delete_item();
void shopkeeper_pass();
void Shopkeeper_menu();
void customer_menu();
void Login();

};

void store :: create_item(){
  fstream fout;
  char ch;
  //system("clear");
  store s;
  fout.open("database.txt",ios::app);
    add:
    {
        s.add_item();
        fout.write((char*)&s,sizeof(s));
        cout<<"Want to add more items\n(press y)";
        cin>>ch;
    }
    if(ch == 'y' || ch == 'Y'){
        goto add;
    }

  fout.close();
}


void store :: displayALL()
{
  store s;
  //system("clear");
  fstream file;
  file.open("database.txt");
  cout<<" -----------------------------------------------------------------------------------------------------------------------"<<endl;
  //cout<<"|_______________________________________________________________________________________________________________________|"<<endl;
  cout<<"|"<<setw(15)<<"Item Code"<<"\t|"<<setw(15)<<"Item Name"<<"\t|"<<setw(15)<<"Quantity"<<"\t|"<<setw(15)<<"Cost"<<"\t|"<<setw(15)<<"Expiry Date"<<"\t|"<<endl;
  //cout<<"|-----------------------------------------------------------------------------------------------------------------------|"<<endl;
  while(file.read((char*)&s,sizeof(s))){
    while (!file.eof()) {
            cout<<"|-----------------------------------------------------------------------------------------------------------------------|"<<endl;
            cout<<"|"<<setw(15)<<s.code<<"\t|"<<setw(15)<<s.name<<"\t|"<<setw(15)<<s.quantity<<"\t|"<<setw(15)<<s.cost<<"\t|"<<setw(15)<<s.DOE<<"\t|"<<endl;
            //cout<<"|-----------------------------------------------------------------------------------------------------------------------|"<<endl;
            break;
    }
  }
  cout<<" -----------------------------------------------------------------------------------------------------------------------"<<endl;
     // cout<<"|_______________________________________________________________________________________________________________________|"<<endl;
  cout<<"\n\nPress Enter to return to Main Menu\t\t";
          cin.ignore();
          cin.get();
   file.close();
   cout<<endl;
}

void wait ( int seconds )                   // for creating time wait function
{
	clock_t endwait;
	endwait = clock () + seconds * CLOCKS_PER_SEC ;
	while (clock() < endwait) {}
}


void store :: search_item(){
    fstream fin;
    store s1;
    //system("clear");
    int ch,flag = 0,code;
    char name[20];
    fin.open("database.txt",ios::in);
    cout<<"Search by : \n1.Item Code\n2.Item Name";
    cin>>ch;
    switch (ch) {
      case 1:
          cout<<"Enter a code of  item\n";
          cin>>code;
          while(fin.read((char*)&s1,sizeof(s1))){
              if(code == s1.code){
                  flag = 1;
                  s1.show_item();
              }
              }
          if (flag == 0){
              cout<<"item not found";}
          break;
      case 2:
          cout<<"Enter a name of  item\n";
          cin>>name;
          cout<<name;
          while(fin.read((char*)&s1,sizeof(s1))){
              if(name == s1.name){
                  flag = 1;
                  s1.show_item();
              }
              }
          if (flag == 0){
              cout<<"item not found";
          }
          break;
    }


    cout<<"\n\nPress Enter to return to Main Menu\t\t";
        cin.ignore();
        cin.get();
    fin.close();
}


void  store :: modify() {
    fstream file;
    store s2;
    //system("clear");
    int code ,ch, flag = 0 , temp = 0;
    //long int pos;
    file.open("database.txt");
    cout<<"Enter a code"<<endl;
    cin>>code;
    while(file.read((char*)&s2,sizeof(s2))){
        if(code == s2.code){
            flag = 1;
            break;
        }
        else
            temp++;
    }
    if(flag == 1){
        long int pos = (temp)*sizeof(s2);
        file.seekp(pos);
        cout<<"What do you want to update\n";
        //s2.add_item();
        cout<<"\n1.Name\n2.Cost\n3.Quantity.\n4.Expiry date\n5.complete item\n";
        cin>>ch;
        switch (ch)
        {
        case 1:
            cout<<"Enter a new name\n";
            cin>>s2.name;
            break;
        case 2:
            cout<<"Enter a new cost\n";
            cin>>s2.cost;
            break;
        case 3:
            cout<<"Enter a new quantity\n";
            cin>>s2.quantity;
            break;
        case 4:
            cout<<"Enter a new Date of expiry\n";
            cin>>s2.DOE;
            break;
        case 5:
            cout<<"Enter a new record\n";
            s2.add_item();
            break;
        default:
            break;
        }
        file.write((char*)&s2,sizeof(s2));
        cout<<"New record Created"<<endl;
    }
    else{
        cout<<"Item Not Found";
    }
    cout<<"\n\nPress Enter to return to Main Menu\t\t";
        cin.ignore();
        file.close();
        cin.get();

}


void store :: delete_item(){
    fstream file;
    //system("clear");
    store s3;
    int flag=0;
    long int del;                                       ///for delete
    file.open("database.txt");
    fstream file1;
    file1.open("tempdel.txt",ios::app);
    file.seekg(0,ios::beg);
    cout<<"\n\t\tEnter the Item Code: ";
    cin>>del;
    while(file.read((char*)&s3,sizeof(s3)))
	{
		if(del!=s3.code)
		{
            file1.write((char*)&s3,sizeof(s3));
		}
		else
		{
			flag=1;
		}
	}
	if(flag==0)
	{
		cout<<"\n\n\tItem not found";
	}
	else{
		cout<<"\n\n\tRecord Deleted ..";
    }
    cout<<"\n\nPress Enter to return to Main Menu\t\t";
    cin.ignore();
    cin.get();
    file.close();
    file1.close();

    remove("database.txt");
    rename("tempdel.txt","database.txt");
}


void store :: purchase()
{
fstream file;
store s4;
int sr_no=1;
int code,flag = 0,temp = 0,amt,bill;
string name;
string date;
file.open("database.txt");
cout<<endl<<endl;
cout<<"Enter code of item : ";
cin>>code;
while(file.read((char*)&s4,sizeof(s4))){
  if(code == s4.code){
    flag = 1;
    break;
  }else
    temp++;
}
if (flag == 1){
  long int pos = (temp)*sizeof(s4);
  file.seekp(pos);
  file.read((char*)&s4,sizeof(s4));
  name=s4.name;
  cout<<"Enter number of item"<<endl;
  cin>>amt;
  if((s4.quantity - amt) >= 0){
  bill = amt * s4.cost;
  cout<<bill;
  file.seekp(pos);
  s4.quantity = s4.quantity - amt;
  date=s4.DOE;
  file.write((char*)&s4,sizeof(s4));
  cout<<endl<<endl<<endl;
  cout<<" __________________________________________________________________________________________________ "<<endl;
  cout<<"|                                             INVOICE                                              |"<<endl;
  cout<<"|--------------------------------------------------------------------------------------------------|"<<endl;
  time_t t = time(NULL);
  tm* tPtr = localtime(&t);
  cout <<"|                 Date: " <<(tPtr->tm_mday)<<"/"<< (tPtr->tm_mon)+1 <<"/"<< (tPtr->tm_year)+1900;
  cout <<"                                \tTime: " << (tPtr->tm_hour)<<":"<< (tPtr->tm_min)<<":"<< (tPtr->tm_sec) <<"\t           |"<< endl;
  cout<<"|                                                                                                  |"<<endl;
  cout<<"|                                                                                                  |"<<endl;
  cout<<"|  ---------------------------------------------------------------------------------------------   |"<<endl;
  cout<<"|  | Sr.No |  Item Code   |     Item NAME    |   Quantity   |   Date of Expiry   |    Price    |   |"<<endl;
  cout<<"|  ---------------------------------------------------------------------------------------------   |"<<endl;
  cout<<"|  |   "<<sr_no<<"   |    "<<setw(5)<<code<<setw(5)<<"     |  "<<setw(9)<<s4.name<<setw(9)<<" | "<<setw(7)<<amt<<"      |     "<<setw(8)<<s4.DOE<<"      |    "<<setw(5)<<bill<<"    |   |"<<endl;
  cout<<"|  ---------------------------------------------------------------------------------------------   |"<<endl;
  cout<<"|                                                                                                  |"<<endl;
  cout<<"|                                                                                                  |"<<endl;
  cout<<"|__________________________________________________________________________________________________|"<<endl;
  cout<<endl<<endl;
  file.close();
  }

  else
    cout<<"item not available";
}
else
  cout<<endl;
  cout<<"Code not found"<<endl;
  cout<<endl;


}


int getch() {                                       //getting character
    int ch;
    struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}


string getpass(const char *prompt, bool show_asterisk=true)             //This is to get the password and convert it into asterisks(*)
{
  const char BACKSPACE=127;
  const char RETURN=10;
  string password;
  unsigned char ch=0;
  cout <<prompt<<endl;
  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}




void store:: Login(){
    store s5;
    //system("clear");
    int ch;
    cout<<"\t\t\t\t ----LOGIN PAGE----"<<endl;
    cout<<" 1. Shopkeeper Login\n 2. Customer Login\n 3. Exit"<<endl;
    cin >> ch;
    switch(ch){
        case 1:
            s5.shopkeeper_pass();
            break;
        case 2:
            s5.customer_menu();
            break;
        case 3:
            return;
    }
}


void store :: shopkeeper_pass(){
    const char *correct_password="null";
    string password=getpass("",true); // Sho        // case 6:
        //     system("clear");
        //     //s7.invoice();
        //     break;w asterisks
    system("clear");
    do {
        string password=getpass("\bPlease enter the password: ",true); // Show asterisks
        if(password==correct_password){
            cout <<"Correct password\nLogging in\n";
            for( int i = 0; i < 1; i++ )
            {
        		printf(".\n");
        		wait(1);
        	}
            for( int i = 0; i < 1; i++ )
            {
        		printf("..\n");
        		wait(1);
        	}
            for( int i = 0; i < 1; i++ )
            {
        		printf("...\n");
        		wait(1);
        	}
            break;
        }
        else
            cout <<"Incorrect password. Try again\n"<<endl;
} while(password!=correct_password);
store s6;
s6.Shopkeeper_menu();

}



void store :: customer_menu(){
    store s8;
    int ch;
    system("clear");
      while(1){
        cout<<"\t\t\t ----CUSTOMER MODE----"<<endl;
        cout<<"Enter your choice"<<endl<<endl;
        cout<<" 1. Display All Records \n 2. Purchase Medicine \n 3. Search Medicine \n 4. Shopkeeper mode \n\n";
        cin >> ch;
        switch (ch) {
            case 1:
                system("clear");
                s8.displayALL();
                break;
            case 2:
                s8.purchase();
                break;
            case 3:
                s8.search_item();
                break;
            case 4:
                s8.shopkeeper_pass();
                break;
        }
      }

}



void store :: Shopkeeper_menu(){
    store s7;
    int ch;
    do {
        //system("clear");
        cout<<endl<<endl;
        cout<<"\t\t\t ----SHOPKEEPER MODE----"<<endl;
     cout<<"Enter your choice"<<endl;
     cout<<" 1. Add Medicine\n 2. Display All Records\n 3. Search Medicine \n 4. Modify Medicine \n 5. Delete Medicine \n 6. Enter Customer Mode\n 0. Exit\n\t\t";

     cin>>ch;
     switch(ch){
        case 1:
            system("clear");
            s7.create_item();
            break;
        case 2:
            system("clear");
            s7.displayALL();
            break;
        case 3:
            s7.search_item();
            break;
        case 4:
            s7.modify();
            break;
        case 5:
            s7.delete_item();
            break;
        case 6:
            system("clear");
            s7.customer_menu();
            return;
    }
    } while(ch!= 0);
}
int main(){
store i;
i.Login();
return 0;
}
