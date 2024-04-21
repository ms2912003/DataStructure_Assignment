#include <bits/stdc++.h>
using namespace std;
string type_by;
// ==================== isinteger() function ================================
/*help me in getting elements from file and setting them in student objects*/
bool isinteger(string s){
    int size=s.size();//49 -> 57
    bool d=true;
    for(int i=0;i<size;i++){
        if((int(s[i])<48&&int(s[i])!=46)||int(s[i])>57)
            d=false;
    }
    return d;
}
// ==================== selection_sort() function ================================
template<class T>
void selection_sort(vector<T>&v){
    for(int i=0,least,j;i<v.size();i++){
        for( j=i+1,least=i;j<v.size();j++){
            if(v[j]<v[least]){
                least=j;
            }
        }
        swap(v[least],v[i]);
    }
}
// ====================   bubble_sort() function  ================================
template<class T>
void bubble_sort(vector<T>&v){
    for(int i=0;i<v.size()-1;i++){
        for(int j=v.size()-1;j>i;j--){
            if(v[j]<v[j-1])
                swap(v[j],v[j-1]);
        }
    }
}

// ================================================================================
class student{
    string name;
    string id;
    double gpa;
public:
    student(string name,string id,double gpa){
        this->id=id;
        this->name=name;
        this->gpa=gpa;
    }
    string get_id(){
        return id;
    };
    string get_name(){
        return name;
    };
    double get_gpa(){
        return gpa;
    };
    bool operator<(student x){
        if(type_by=="name"){
            if(name<x.name)
                return 1;
            else
                return 0;
        }
        else{
            if(gpa<x.gpa)
                return 1;
            else
                return 0;
        }

    }
};
int main(){
    vector<student>container;
    vector<string>v;
    ifstream infile;
    infile.open("input.txt",ios::in);
    int number;
    infile>>number;
    string m;
    while(infile>>m){
        v.push_back(m);
    }
    //setting items in vector of students
    string name="",id,gpa;
    bool p=0;
    for(auto item:v){
         if(!isinteger(item)){
             name+=item+" ";
         }
         else if(p==0){
             id=item;
             p=1;
         }
         else{
             gpa=item;
             int si=name.size();
             string ss="";
             for(int i=0;i<si-1;i++){
                 ss+=name[i];
             }
             student obj(ss,id,stod(gpa));
             container.push_back(obj);
             name="";
             p=0;
         }
    }
    // ==================================
    type_by="name";
    bubble_sort<student>(container);
    ofstream file;
    file.open("result_by_name.txt",ios::out);
    file<<"Algorithm : "<<"bubble sort\n";
    file<<"running time : \n";
    for(auto x:container){
        file<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="gpa";
    bubble_sort<student>(container);
    ofstream file1;
    file1.open("result_by_gpa.txt",ios::out);
    file1<<"Algorithm : "<<"bubble sort\n";
    file1<<"running time : \n";
    for(auto x:container){
        file1<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

}








