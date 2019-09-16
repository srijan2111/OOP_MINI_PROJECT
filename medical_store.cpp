#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<cstdlib>
#include<unistd.h>

using namespace std;

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
  store s;
  fout.open("database.txt",ios::app);
  s.add_item();
  fout.write((char*)&s,sizeof(s));
  fout.close();

}

int main(){
store i;
int ch;
do {
 cout<<"Enter your choice"<<endl;
 cout<<"1. add item.\n 2.Search item \n 3. modify item \n 4.delete item\n 5.Display item";
 cin>>ch;
 switch(ch){
   case 1:
     i.create_item();
     break;

}
} while(ch!= 0);

return 0;

}
