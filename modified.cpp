#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<cstdlib>
#include<unistd.h>

using namespace std;

class store{
protected:
  int code,cost,quantity;
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
    cout<<"Date Of Expiry : "<<endl;
    cin>>DOE;
  }

  void show_item(){
      cout<<"CODE : "<<code<<endl;
      cout<<"NAME : "<<name<<endl;
      cout<<"COST : "<<cost<<endl;
      cout<<"QUANTITY : "<<quantity<<endl;
      cout<<"Date Of Expiry : "<<DOE<<endl;
      cout<<"-------------------------------------------------------"<<endl;
  }
void create_item();
void display();
void search_item();
void modify();
};

void store :: create_item(){
  fstream fout;
  store s;
  fout.open("database.txt",ios::app);
  s.add_item();
  fout.write((char*)&s,sizeof(s));
  fout.close();
}

void store :: search_item(){
    fstream fin;
    store s;
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
    fin.close();
}

void  store :: modify() {     //checkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk kar ekda....................
    fstream file;
    store s;
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
    case 2:
        i.search_item();
        break;
    case 3:
        i.modify();
        break;


}
} while(ch!= 0);

return 0;

}
