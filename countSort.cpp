#include <bits/stdc++.h>
using namespace std;

class Student {
public:
    string name;
    int id;
    int gpa;
    Student(string name="", int id=0, int gpa=0):name(name),id(id),gpa(gpa) {}

};

vector<Student> countSort(vector<Student> students){
    int max=students[0].gpa;
    int min=students[0].gpa;
    vector<Student> sorted(students.size());
    for(int i=1;i<students.size();++i){
        if(students[i].gpa>max){
            max=students[i].gpa;
        }
        if(students[i].gpa<min){
            min=students[i].gpa;
        }
    }

    vector<int>count(max-min+1,0);
    vector<int>cumulative(max-min+1,0);

    for(int i=0;i<students.size();++i){
        count[students[i].gpa-min]+=1;
    }
    cumulative[0]=count[0];
    for(int i=1;i<count.size();++i){
        cumulative[i]=cumulative[i-1]+count[i];
    }
    for(int i=students.size()-1;i>=0;--i){
        sorted[cumulative[students[i].gpa-min]-min]=students[i];
        cumulative[students[i].gpa-min]-=1;
    }
    return sorted;
}

int main(){
    vector<Student>students;
    Student student1("Fatma",20220000,4);
    Student student2("Menna",20220000,1);
    Student student3("Fatma2",20220000,3);
    Student student4("Menna2",20220000,2);
    students.push_back(student1);
    students.push_back(student2);
    students.push_back(student3);
    students.push_back(student4);
    vector<Student>sorted= countSort(students);
    for(Student s:sorted){
        cout<<s.name<<endl;
    }

}