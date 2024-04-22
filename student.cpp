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
// ====================   quick_sort() function  ================================
template<class T>
int partition(vector<T>&v,int low,int high){
    if(type_by=="name"){
        string pivot=v[low].get_name();
    }
    else{
        double pivot=v[low].get_gpa();
    }
    int i=low,j;
    for(j=low+1;j<=high;j++){
        if(v[j]<v[low]){
            i++;
            swap(v[j],v[i]);}
    }
    swap(v[i],v[low]);
    return i;
}
template<class T>
void Quick_sort(vector<T>&v,int low,int high){
    if(low<high){
        int p=partition(v,low,high);
        Quick_sort(v,low,p-1);
        Quick_sort(v,p+1,high);
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
    // ===================selection===============
    type_by="gpa";
    selection_sort<student>(container);
    ofstream write_infile;
    write_infile.open("result_by_gpa.txt",ios::app);
    write_infile<<"Algorithm : "<<"Quick_sort\n";
    write_infile<<"running time : \n";
    for(auto x:container){
        write_infile<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="name";
    selection_sort<student>(container);
    ofstream write_infile1;
    write_infile1.open("result_by_name.txt",ios::app);
    write_infile1<<"Algorithm : "<<"selection_sort\n";
    write_infile1<<"running time : \n";
    for(auto x:container){
        write_infile1<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }
    // =================== bubble===============
    type_by="gpa";
    selection_sort<student>(container);
    ofstream write_infile2;
    write_infile2.open("result_by_gpa.txt",ios::app);
    write_infile2<<"Algorithm : "<<"bubble_sort\n";
    write_infile2<<"running time : \n";
    for(auto x:container){
        write_infile2<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="name";
    bubble_sort<student>(container);
    ofstream write_infile3;
    write_infile3.open("result_by_name.txt",ios::app);
    write_infile3<<"Algorithm : "<<"bubble_sort\n";
    write_infile3<<"running time : \n";
    for(auto x:container){
        write_infile3<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }
    // ===================quick===============
    type_by="gpa";
    Quick_sort<student>(container,0,container.size()-1);
    ofstream write_infile4;
    write_infile4.open("result_by_gpa.txt",ios::app);
    write_infile4<<"Algorithm : "<<"Quick_sort\n";
    write_infile4<<"running time : \n";
    for(auto x:container){
        write_infile4<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="name";
    Quick_sort<student>(container,0,container.size()-1);
    ofstream write_infile5;
    write_infile5.open("result_by_name.txt",ios::app);
    write_infile5<<"Algorithm : "<<"Quick_sort\n";
    write_infile5<<"running time : \n";
    for(auto x:container){
        write_infile5<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }



}








