#include <bits/stdc++.h>
using namespace std;
string type_by;
int num_comp=0;
//=====================
class student{
public:
    string name;
    string id;
    double gpa;
    student(string name="",string id="",double gpa=0){
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
    bool operator>(student x){
        if(type_by=="name"){
            if(name>x.name)
                return 1;
            else
                return 0;
        }
        else{
            if(gpa>x.gpa)
                return 1;
            else
                return 0;
        }

    }
    bool operator<=(student x){
        if(type_by=="name"){
            if(name<=x.name)
                return 1;
            else
                return 0;
        }
        else{
            if(gpa<=x.gpa)
                return 1;
            else
                return 0;
        }

    }
};
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
                num_comp++;
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
            if(v[j]<v[j-1]){
                num_comp++;
                swap(v[j],v[j-1]);}
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
            num_comp++;
            i++;
            swap(v[j],v[i]);}
    }
    swap(v[i],v[low]);
    return i;
}
template<class T>
void Quick_sort(vector<T>&v,int low,int high){
    if(low<high){
        num_comp++;
        int p=partition(v,low,high);
        Quick_sort(v,low,p-1);
        Quick_sort(v,p+1,high);
    }
}
// ====================   insertion_sort() function  ================================
template<class T>
void insertion_sort(vector<T>&v){
    for(int i=1,j;i<v.size();i++){
        T temp=v[i];
        for(j=i;j>=1&&v[j-1]>temp;j--){
            num_comp++;
            v[j]=v[j-1];
        }
        v[j]=temp;
    }
}
// ====================   shell_sort() function  ================================
template<class T>
void shell_sort(vector<T>&v){
    for(int gap=v.size()/2;gap>0;gap/=2){
        for(int i=gap,j;i<v.size();i++){
            T temp=v[i];
            for(j=i;j>=gap&&v[j-gap]>temp;j-=gap){
                v[j]=v[j-gap];
            }
            v[j]=temp;
        }
    }
}
// ====================   merge_sort() function  ================================
template<class T>
void merge(vector<T>&v,int left,int mid,int right){
    int n1=mid-left+1;
    int n2=right-mid;
    T left_array[n1],right_array[n2];
    for(int i=0;i<n1;i++){
        num_comp++;
        left_array[i]=v[left+i];
    }
    for(int i=0;i<n2;i++){
        num_comp++;
        right_array[i]=v[mid+1+i];
    }
    int i=0,j=0,k=left;
    while(i<n1&&j<n2){
        num_comp++;
        if(left_array[i]<=right_array[j]){
            v[k]=left_array[i];
            i++;}
        else{
            v[k]=right_array[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        num_comp++;
        v[k]=left_array[i];
        i++;k++;
    }
    while(j<n2){
        num_comp++;
        v[k]=right_array[j];
        j++;k++;
    }
}
// first dividing array to sub arrays
template<class T>
void merge_sort(vector<T>&v,int left,int right){
    if(left<right) {
        int mid = (left + right) / 2;
        merge_sort(v, left, mid);
        merge_sort(v, mid + 1, right);
        //second merge sub arrays
        merge(v, left, mid, right);
    }
}

// ====================   count_sort() function  ================================
void count_sort(vector<student>&v){
    //take big number in array
    int k=int(v[0].gpa);
    int n=v.size();
    for(int i=1;i<n;i++){
        if(int(v[i].gpa)>k)
            num_comp++;
            k=int(v[i].gpa);
    }
    //intialize count vector
    int count_arr[k+1];
    for(int i=0;i<=k;i++){
        num_comp++;
        count_arr[int(v[i].gpa)]=0;
    }
    //count how many times each item occur
    for(int i=0;i<n;i++){
        num_comp++;
        count_arr[int(v[i].gpa)]++;
    }
    //cumulative sum of count arr
    for(int i=1;i<=k;i++){
        num_comp++;
        count_arr[i]+=count_arr[i-1];
    }
    // to make sort
    int B[n];
    for(int i=n-1;i>=0;i--){
        num_comp++;
        B[count_arr[int(v[i].gpa)]-1]=int(v[i].gpa);
        count_arr[int(v[i].gpa)]--;
    }
    //return sorted array from outer array B to origin
    for(int i=0;i<n;i++){
        v[i].gpa=B[i];
    }
}
// ================================================================================

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
    auto start = std::chrono::high_resolution_clock::now();
    selection_sort<student>(container);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    ofstream write_infile;
    write_infile.open("result_by_gpa.txt",ios::app);
    write_infile<<"Algorithm : "<<"selection_sort\n";
    write_infile<< "Running time: " << duration / 1000000.0 << " milliseconds\n";
    write_infile<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="name";
    start = std::chrono::high_resolution_clock::now();
    selection_sort<student>(container);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile1;
    write_infile1.open("result_by_name.txt",ios::app);
    write_infile1<<"Algorithm : "<<"selection_sort\n";
    write_infile1<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile1<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile1<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }
    // =================== bubble===============
    type_by="gpa";
    start = std::chrono::high_resolution_clock::now();
    selection_sort<student>(container);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile2;
    write_infile2.open("result_by_gpa.txt",ios::app);
    write_infile2<<"Algorithm : "<<"bubble_sort\n";
    write_infile2<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile2<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile2<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="name";
    start = std::chrono::high_resolution_clock::now();
    bubble_sort<student>(container);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile3;
    write_infile3.open("result_by_name.txt",ios::app);
    write_infile3<<"Algorithm : "<<"bubble_sort\n";
    write_infile3<< "Running time: " << duration / 1000000.0<< " milliseconds\n";
    write_infile3<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile3<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }
    // ===================quick===============
    type_by="gpa";
    start = std::chrono::high_resolution_clock::now();
    Quick_sort<student>(container,0,container.size()-1);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile4;
    write_infile4.open("result_by_gpa.txt",ios::app);
    write_infile4<<"Algorithm : "<<"Quick_sort\n";
    write_infile4<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile4<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile4<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="name";
    start = std::chrono::high_resolution_clock::now();
    Quick_sort<student>(container,0,container.size()-1);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile5;
    write_infile5.open("result_by_name.txt",ios::app);
    write_infile5<<"Algorithm : "<<"Quick_sort\n";
    write_infile5<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile5<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile5<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }
    // ===================insertion===============
    type_by="gpa";
    start = std::chrono::high_resolution_clock::now();
    insertion_sort<student>(container);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile6;
    write_infile6.open("result_by_gpa.txt",ios::app);
    write_infile6<<"Algorithm : "<<"insertion_sort\n";
    write_infile6<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile6<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile6<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="name";
    start = std::chrono::high_resolution_clock::now();
    insertion_sort<student>(container);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile7;
    write_infile7.open("result_by_name.txt",ios::app);
    write_infile7<<"Algorithm : "<<"insertion_sort\n";
    write_infile7<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile7<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile7<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }
    // ===================shell===============
    type_by="gpa";
    start = std::chrono::high_resolution_clock::now();
    shell_sort<student>(container);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile8;
    write_infile8.open("result_by_gpa.txt",ios::app);
    write_infile8<<"Algorithm : "<<"shell_sort\n";
    write_infile8<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile8<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile8<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="name";
    start = std::chrono::high_resolution_clock::now();
    shell_sort<student>(container);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile9;
    write_infile9.open("result_by_name.txt",ios::app);
    write_infile9<<"Algorithm : "<<"shell_sort\n";
    write_infile9<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile9<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile9<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }
// ===================merge===============
    type_by="gpa";
    start = std::chrono::high_resolution_clock::now();
    merge_sort<student>(container,0,container.size()-1);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile10;
    write_infile10.open("result_by_gpa.txt",ios::app);
    write_infile10<<"Algorithm : "<<"merge_sort\n";
    write_infile10<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile10<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile10<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

    type_by="name";
    start = std::chrono::high_resolution_clock::now();
    merge_sort<student>(container,0,container.size()-1);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile11;
    write_infile11.open("result_by_name.txt",ios::app);
    write_infile11<<"Algorithm : "<<"merge_sort\n";
    write_infile11<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile11<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile11<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }

// ===================count===============
    type_by="gpa";
    start = std::chrono::high_resolution_clock::now();
    count_sort(container);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ofstream write_infile12;
    write_infile12.open("result_by_gpa.txt",ios::app);
    write_infile12<<"Algorithm : "<<"count_sort\n";
    write_infile12<< "Running time: " << duration/ 1000000.0 << " milliseconds\n";
    write_infile12<< "Number of comparisons: " << num_comp << "\n";
    num_comp=0;
    for(auto x:container){
        write_infile12<<x.get_name()<<"\n"<<x.get_id()<<"\n"<<x.get_gpa()<<"\n \n";
    }
}














