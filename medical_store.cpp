#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<cstdlib>
#include<unistd.h>

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
};

void store :: create_item(){
  fstream fout;
  system("clear");
  store s;
  fout.open("database.txt",ios::app);
  s.add_item();
  fout.write((char*)&s,sizeof(s));
  fout.close();

}
void store :: displayALL()
{
  store s;
  system("clear");
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
    store s;
    system("clear");
    int code,flag = 0;
    fin.open("database.txt",ios::in);
    cout<<"Enter a Code"<<endl;
    cin>>code;
    while(fin.read((char*)&s,sizeof(s))){
        if(code == s.code){
            flag = 1;
            s.show_item();
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
    store s;
    system("clear");
    int code , flag = 0 , temp = 0;
    long int pos;
    file.open("database.txt",ios::in);
    cout<<"Enter a code"<<endl;
    cin>>code;
    while(file.read((char*)&s,sizeof(s))){
        if(code == s.code){
            flag = 1;
            break;
        }
        else
            temp++;
    }

    if(flag == 1){

        pos = (temp) * sizeof(s);
        file.seekp(pos);
        cout<<"Enter a new record";
        s.add_item();
        file.write((char*)&s,sizeof(s));
        cout<<"New record Created"<<endl;
        file.close();
    }
    cout<<"\n\nPress Enter to return to Main Menu\t\t";
        cin.ignore();
        cin.get();

}
void store :: delete_item(){
    fstream file;
    //system("clear");
    store s;
    int flag=0;
    long int del;                                       ///for delete
    file.open("database.txt");
    fstream file1;
    file1.open("tempdel.txt",ios::app);
    file.seekg(0,ios::beg);
    cout<<"\n\t\tEnter the Item Code: ";
    cin>>del;
    while(file.read((char*)&s,sizeof(s)))
	{
		if(del!=s.code)
		{
            file1.write((char*)&s,sizeof(s));
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

int main(){
store i;
int ch;
do {
 cout<<"Enter your choice"<<endl;
 cout<<"1. Add Item.\n2. Display All Records\n3. Search Item\n4. Modify Item \n5. Delete Item\n6.Display Item\n";
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

}
} while(ch!= 0);

return 0;

}
