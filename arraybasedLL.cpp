#include <bits/stdc++.h>
using namespace std;
template <class T>
class ArrayList {
private:
    T *array;
    int capacity;
    int size;
public:
    ArrayList(int initialCapacity=5): capacity(initialCapacity),size(0) {
        array = new T[capacity];
    }
    ~ArrayList() {
        delete[] array;
    }
    //==========================================================================================
    void  resize(int newCapacity) {
        T* newArray =new T[newCapacity];
        for (int i = 0; i < size; ++i)
            newArray[i] = array[i];
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }
    //==========================================================================================
    void  insertAtHead(const T& val) {
        insert(val,0);
    }
    void  insert(const T& val,int index) {

        for (int i = size; i > index;--i){
            array[i] = array[i - 1];
        }
        array[index] = val;
        size++;
    }
    //==========================================================================================
    void  insertAtTail(const T& val) {
        if (size == capacity){
            resize(capacity * 2);
        }
        else{
            array[size++] = val;
        }
    }
    //===========================================================================================
    void  insertAt(const T& val,int index) {
        if (index < 0 || index > size){
            cout<<"THERE IS NO SUCH INDEX\n";
        }
        else{
            if (size == capacity)
                resize(capacity * 2);
            for (int i = size; i > index;--i){
                //كل واحد ياخد قيمة اللى قبله بداية من اندكس خارجى عشان يفضى مكان عند اندكس اللى هيتحط فيه
                array[i] = array[i - 1];
            }
            array[index] = val;
            size++;
        }
    }
    //==========================================================================================
    void removeAtHead() {
        remove(0);
    }
    void remove(int index) {
        for (int i = index;i < size - 1; ++i){
            array[i] = array[i + 1];
        }
        size--;
    }
    //==========================================================================================
    void  removeAtTail() {
        if (size > 0) size--;
    }
    //==========================================================================================
    void  removeAt(int index) {
        if (index < 0 || index >= size){
            cout<<"THERE IS NO SUCH INDEX\n";
        }
         else{
            for (int i = index;i < size - 1; ++i){
                //كل واحد ياخد قيمة اللى بعده عشان كدة وقفنا عند قبل الاخير عشان هو ياخد قيمة الاخير
                array[i] = array[i + 1];}
            size--;
         }

    }
    //==================================== retrieveAt ======================================================
    T retrieveAt(int index){
        if (index < 0 || index >= size){
            cout<<"THERE IS NO SUCH INDEX\n";
        }
        else{
            return array[index];
        }
    }
    //==========================================================================================
    void replaceAt (int newElement, int index){ //✔to change value og given index with given element
        if(index<getSize()&&index>=0){
            array[index]=newElement;
        }
        else{
            cout<<"THERE IS NO SUCH INDEX\n";
        }
    }
    //==========================================================================================
    bool isExist (int element){//✔
        bool found=0;
        for(int i=0;i<size;i++){
            if(array[i]==element)
                found=1;
        }
        return found;
    }
    //==========================================================================================
    bool isItemAtEqual (int element, int index){//✔
        if(index<getSize()&&index>=0){
            bool equal=0;
            for(int i=0;i<size;i++){
                if(i==index){
                    if(array[i]==element)
                        equal=1;
                }

            }
            return equal;
        }
        else{
            cout<<"THERE IS NO SUCH INDEX\n";
            return 0;
        }
    }
    //==========================================================================================
    void swap (int firstItemIdx, int secondItemIdx) {
        if(firstItemIdx<getSize()&&firstItemIdx>=0&&secondItemIdx<getSize()&&secondItemIdx>=0){
            int temp=array[firstItemIdx];
            array[firstItemIdx]=array[secondItemIdx];
            array[secondItemIdx]=temp;
        }
        else{
            cout<<"THERE IS NO SUCH INDEX\n";
        }
    }
    //==========================================================================================
    bool  isEmpty()const {
        return size == 0;
    }
    //==========================================================================================
    int getSize() const {
        return size;
    }
    //==========================================================================================
    void clear() {
        size = 0;
    }
    //==========================================================================================
    void print (){ //✔
        for(int i=0;i<size;i++){
            cout<<array[i]<<" ";
        }
        cout<<"\n";
    }
};
int main(){
    ArrayList<int> list;
    list.isEmpty()?cout<<"yes\n":cout<<"NO\n";

    list.insertAtHead(2);
    list.insertAtHead(1);
    list.insertAtHead(0);
    list.print();cout<<endl;

    list.insertAtTail(3);
    list.print();cout<<endl;

    list.insertAt(5,3);
    list.print();cout<<endl;

    list.isEmpty()?cout<<"yes\n":cout<<"NO\n";

    list.replaceAt(10,4);
    list.print();cout<<endl;

    cout <<list.retrieveAt(2)<<"\n";

    list.isExist(1)?cout<<"yes\n":cout<<"NO\n";

    list.isItemAtEqual(1,1)?cout<<"yes\n":cout<<"NO\n";

    cout<<list.getSize();cout<<endl;

    list.swap(1,2);
    list.print();cout<<endl;


}
