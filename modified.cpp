#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
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
void create_item();
void displayALL();
void search_item();
void modify();
void delete_item();
void invoice();
};

void store :: create_item(){
  fstream fout;
  //system("clear");
  store s;
  fout.open("database.txt",ios::app);
  s.add_item();
  fout.write((char*)&s,sizeof(s));
  fout.close();

}
void store :: displayALL()
{
  store s;
  //system("clear");
  fstream file;
  file.open("database.txt");
  cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
  cout<<"|"<<setw(15)<<"Item Code"<<"\t|"<<setw(15)<<"Item Name"<<"\t|"<<setw(15)<<"Quantity"<<"\t|"<<setw(15)<<"Cost"<<"\t|"<<setw(15)<<"Expiry Date"<<"\t|"<<endl;
  cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
  while(file.read((char*)&s,sizeof(s))){
    while (!file.eof()) {
            //cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"|"<<setw(15)<<s.code<<"\t|"<<setw(15)<<s.name<<"\t|"<<setw(15)<<s.quantity<<"\t|"<<setw(15)<<s.cost<<"\t|"<<setw(15)<<s.DOE<<"\t|"<<endl;
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            break;
    }
  }
  cout<<"\n\nPress Enter to return to Main Menu\t\t";
          cin.ignore();
          cin.get();
   file.close();
   cout<<endl;
}

void store :: search_item(){
    fstream fin;
    store s1;
    //system("clear");
    int code,flag = 0;
    fin.open("database.txt",ios::in);
    cout<<"Enter a Code"<<endl;
    cin>>code;
    while(fin.read((char*)&s1,sizeof(s1))){
        if(code == s1.code){
            flag = 1;
            s1.show_item();
        }

        }

    if (flag == 0){
        cout<<"item not found";
    }
    cout<<"\n\nPress Enter to return to Main Menu\t\t";
        cin.ignore();
        cin.get();
    fin.close();
}

void  store :: modify() {     //checkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk kar ekda....................
    fstream file;
    store s2;
    //system("clear");
    int code , flag = 0 , temp = 0;
    //long int pos;
    file.open("database.txt");
    cout<<"Enter a code"<<endl;
    cin>>code;
    while(file.read((char*)&s2,sizeof(s2))){
        if(code == s2.code){
            flag = 1;
            //cout<<"found!";
            return;
        }
        else
            temp++;

    }

    if(flag == 1){
        long int pos = (temp)*sizeof(s2);
        file.seekp(pos);
        cout<<"Enter a new record";
        s2.add_item();
        file.write((char*)&s2,sizeof(s2));
        cout<<"New record Created"<<endl;

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


void store :: purchase(){
fstream file;
store s4;
int code,flag = 0,temp = 0,amt,bill;
file.open("database.txt");
fstream file1;
file1.open("temp.txt");
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
  file.read((char*)&s,sizeof(s4));
  cout<<"Enter number of item"<<endl;
  cin>>amt;
  if((s4.quantity - amt) >= 0){
  bill = amt * s4.cost;
  cout<<bill;
  file.seekp(pos);
  s4.quantity = s4.quantity - amt;

  file.close();

}
  else
  cout<<"Item not available";



}
else
  cout<<"Item not found";


}

void store::invoice()
{
  cout<<" __________________________________________________________________________ "<<endl;
  cout<<"|                                 INVOICE                                  |"<<endl;
  cout<<"|--------------------------------------------------------------------------|"<<endl;


  time_t t = time(NULL);
  tm* tPtr = localtime(&t);
  cout << "|        Date: " <<(tPtr->tm_mday)<<"/"<< (tPtr->tm_mon)+1 <<"/"<< (tPtr->tm_year)+1900;
  cout << "                    \tTime: " << (tPtr->tm_hour)<<":"<< (tPtr->tm_min)<<":"<< (tPtr->tm_sec) <<"\t           |"<< endl;
  cout<<"|                                                                          |"<<endl;
  cout<<"|                                                                          |"<<endl;
  cout<<"|  ---------------------------------------------------------------------   |"<<endl;
  cout<<"|  | Sr.No |  Item Code  |     Item NAME     |   Date of   |   Price   |   |"<<endl;
  cout<<"|  ---------------------------------------------------------------------   |"<<endl;
  cout<<"|  | Sr.No |  Item Code  |     Item NAME     |   Date of   |   Price   |   |"<<endl;
  cout<<"|  ---------------------------------------------------------------------   |"<<endl;``
}


int main(){
store i;
int ch;
do {
    //system("clear");
 cout<<"Enter your choice"<<endl;
 cout<<"1. Add Item.\n2. Display All Records\n 3. Search Item \n 4. Modify Item \n 5. Delete Item\n 6. Display Item";
 cin>>ch;
 switch(ch){
    case 1:
        i.create_item();
        break;
    case 2:
        i.displayALL();
        break;
    case 3:
        i.search_item();
        break;
    case 4:
        i.modify();
        break;
    case 5:
        i.delete_item();
        break;
    case 6:
        i.invoice();
        break;

}
} while(ch!= 0);

return 0;

}
