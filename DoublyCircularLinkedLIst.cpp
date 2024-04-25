#include <bits/stdc++.h>
using namespace std;
template<typename T>

//node for doubly linked list
class Node{
public:
    Node* next;
    Node* prev;
    T data;
    Node(){
        data=T();
        next=nullptr;
        prev= nullptr;
    }
};

//CLL using doubly linked list
template<typename T>
class CLL{

public:
    Node<T>* first;
    Node<T>* current;
    Node<T>* tail;
    int cnt;
    CLL(): first(nullptr), current(nullptr), cnt(0), tail(nullptr){}

    void insertAtHead(T data){
        Node<T> *node = new Node<T>;
        node->data=data;
        if(cnt==0){
            first=node;
            tail=node;
            node->next= node;
            node->prev= node;
        }
        else{
            node->next=first;
            first->prev=node;
            first=node;
            tail->next=node;
            node->prev=tail;
        }
        cnt++;
    }
    void insertAtTail(T data){
        Node<T> *node = new Node<T>;
        node->data=data;
        if(cnt==0){
            first=node;
            tail=node;
            node->next= node;
            node->prev= node;
        }
        else{
            first->prev=node;
            node->prev=tail;
            tail->next=node;
            tail=node;
            tail->next=first;
        }
        cnt++;
    }
    void insertAt(T data, int index){
        Node<T> *node = new Node<T>;
        if(index==0){
            insertAtHead(data);
        }
        else if(index==cnt){
            insertAtTail(data);
        }
        else if(index>cnt || index<0){
            cout<<"Out of range\n";
        }
        else{
            node->data=data;
            current=first;
            for(int i=0;i<index;++i){
                current=current->next;
            }
//            cout<<current->data<<endl;
            node->next=current;
            node->prev=current->prev;
            (current->prev)->next=node;
            current->prev=node;
            cnt++;
        }
    }
    void removeAtHead(){
        if(cnt){
        current=first;
        first=first->next;
        tail->next=first;
        first->prev=tail;
        delete current;
        cnt--;
        }
        else{
            cout<<"List is empty\n";
        }
    }
    void removeAtTail(){
        if(cnt){
            current=tail;
//            (current->prev)->next=first;
            tail=current->prev;
            tail->next=first;
            first->prev=tail;
            delete current;
            cnt--;
        }
        else{
            cout<<"List is empty\n";
        }
    }
    void removeAt(int index){
        if(index==0){
            removeAtHead();
        }
        else if(index==cnt-1){
            removeAtTail();
        }
        else if(index>cnt || index<0){
            cout<<"Out of range\n";
        }
        else{
            current=first;
            for(int i=0;i<index;++i){
                current=current->next;
            }
            (current->prev)->next=current->next;
            (current->next)->prev=current->prev;
            delete current;
        }

    }
    T retrieveAt(int index){
        if(index<0||index>=cnt){
            cout<<"Index out of range\n";
        }
        else{
            current=first;
            for(int i=0;i<index;++i){
                current=current->next;
            }
            return current->data;
        }
    }
    void replaceAt(T newData, int index){
        if(index<0||index>=cnt){
            cout<<"Index out of range\n";
        }
        else{
            current=first;
            for(int i=0;i<index;++i){
                current=current->next;
            }
            current->data=newData;
        }
    }
    bool isExist(T element){
        current=first;
        for(int i=0;i<cnt;++i){
            if(current->data == element){
                return true;
                break;
            }
            current=current->next;
        }
        return false;
    }
    bool isItemAtEqual(T element, int index){
        if(index<0||index>=cnt){
            cout<<"Index out of range\n";
        }
        else{
            current=first;
            for(int i=0;i<index;++i){
                current=current->next;
            }
            if(current->data==element){
                return true;
            }
            else{
                return false;
            }
        }
    }

    void swap(int firstIndex, int secondIndex){
        if (firstIndex < 0 || firstIndex >= cnt) {
            cout << "First index out of range\n";
            return;
        } else if (secondIndex < 0 || secondIndex >= cnt) {
            cout << "Second index out of range\n";
            return;
        } else if (firstIndex == secondIndex) {
            return;
        }

        Node<T> *one = first;
        Node<T> *two = first;

        for (int i = 0; i < min(firstIndex, secondIndex); ++i) {
            one = one->next;
        }
        for (int i = 0; i < max(firstIndex, secondIndex); ++i) {
            two = two->next;
        }

//        cout<<one->data<<endl;
//        cout<<two->data<<endl;
        // Update the next and prev pointers for the adjacent nodes
        one->prev->next = two;
        two->next->prev = one;

        Node<T> *tempNext1 = one->next;
        Node<T> *tempPrev1 = one->prev;
        Node<T> *tempNext2 = two->next;
        Node<T> *tempPrev2 = two->prev;

        one->next = tempNext2;
        one->prev = tempPrev2;

        if(abs(firstIndex-secondIndex)==1){
            two->next=tempPrev2;
            one->prev=two;
//            one->next=tempNext2;
        }
        else{
            two->next = tempNext1;
        }

        two->prev = tempPrev1;

        // Update the next and prev pointers for the swapped nodes
        tempNext1->prev = two;
        tempPrev1->next = two;
        tempNext2->prev = one;
        tempPrev2->next = one;



    }
    bool isEmpty(){
        if(cnt){
            return false;
        }
        else{
            return true;
        }
    }
    int size(){
        return cnt;
    }
    void clear(){
        while(cnt>0){
            current=first;
            first=first->next;
            delete current;
            cnt--;
        }
        first=NULL;
    }
    void print(){
        current = first;
        for(int i=0;i<cnt*2;++i){
            cout<<current->data<<endl;
            current=current->next;
        }
    }

};

int main(){
    CLL<int> ll;
    ll.insertAtHead(4);
    ll.insertAtHead(3);
    ll.insertAtHead(2);
    ll.insertAtHead(1);
    ll.insertAtTail(5);
    ll.insertAtTail(6);
    ll.insertAtTail(7);
    ll.insertAtTail(8);
    ll.swap(5,6);
//    ll.insertAt(100,0);
//    ll.insertAt(200,9);
//    ll.insertAt(300,3);
//    ll.insertAt(300,100);
//    ll.removeAtHead();
//    ll.removeAtTail();
//    ll.removeAt(5);
    ll.print();
    return 0;
}