#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<cstdlib>
#include<unistd.h>


class store{
public:
  int code,cost,quantity;
  char name[20],DOE[10];

  void add_item(){
    cout<<"CODE : "<<endl;
    cin>>code;
    cout<<"NAME : "<<endl;
    cin>>name;
    cout<<"COST : "<<endl;
    cin>>cost;
    cout<<"QUANTITY : "<<endl;
    cin>>quantity;
    cout<<"Date Of Expiry : "<<endl;
    cin>>DOE;
  }
void create_item();
void display();
};

void store :: create_item(){
	fstream fout;
	inventory i;
	fout.open("inventory.txt",ios::app);
	i.add_item();
	fout.write((char*)&i,sizeof(i));
	fout.close();
}
