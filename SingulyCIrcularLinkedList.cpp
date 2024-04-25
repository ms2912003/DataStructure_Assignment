#include <bits/stdc++.h>
using namespace std;
template<typename T>

//node for singly linked list
class Node{
public:
    Node* next;
    T data;
    Node(){
        data=T();
        next=nullptr;
    }
};

//CLL using singly linked list
template<typename T>
class CLL{

public:
    Node<T>* first;
    Node<T>* current;
    Node<T>* last;
    Node<T>* before;
    Node<T> *temp;
    int cnt;
    CLL(): first(nullptr), current(nullptr), cnt(0){}

    void insertAtHead(T data){
        Node<T> *node=new Node<T>;
        node->data=data;
        if(cnt==0){
            first=node;
            last=node;
            node->next=first;
        }
        else{
            current=first;
            first=node;
            node->next=current;
            last->next=first;
        }
        cnt++;
    }

    void insertAtTail(T data){
        Node<T> *node = new Node<T>;
        node->data=data;
        if(first == nullptr){
            first=node;
            node->next=first;
            last=node;
            cnt++;
        }
        else{
            current=first;
            last->next=node;
            last=node;
            node->next=first;
            cnt++;
        }
    }

    void insertAt(T data, int index){
        Node<T> *node = new Node<T>;
        node->data=data;
        if(index>=cnt||index<0){
            cout<<"Out of range\n";
        }
        else if(index==0){
            insertAtHead(data);
        }
        else if(index==cnt){
            insertAtTail(data);
        }
        else{
            current=first;
            for(int i=0;i<index;++i){
                before=current;
                current=current->next;
            }
            node->next=current;
            before->next=node;
            cnt++;
        }
    }

    void removeAtHead(){
        current=first;
        first=first->next;
        delete current;
        cnt--;
    }

    void removeAtTail(){
        if(cnt==0){
            cout<<"The linked list is empty\n";
        }
        else{
            current=first;
            for(int i=0;i<cnt-1;++i){
                before=current;
                current=current->next;
            }
            current->next=first;
            before->next=current->next;
            delete current;
            cnt--;
//            cout<<"data: "<<before->data<<" "<<current->data<<endl;
        }
    }

    void removeAt(int index){
        if(index>=cnt||index<0){
            cout<<"Out of range\n";
        }
        else if(index==0){
            removeAtHead();
        }
        else if(index==cnt-1){
            removeAtTail();
        }
        else{
            current=first;
            for(int i=0;i<index;i++) {
                before = current;
                current = current->next;
            }
            before->next=current->next;
            cnt--;
        }

    }

    T retrieveAt(int index){
        if(index<0||index>=cnt){
            cout<<"index out of range\n";
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
            cout<<"index out of range\n";
        }
        else{
            current=first;
            for(int i=0;i<index;++i){
                current=current->next;
            }
            current->data =newData;
        }
    }

    bool isExist(T element){
        current=first;
        for(int i=0;i<cnt;i++){
            if(current->data==element){
                return true;
            }
        }
        return false;
    }

    bool isItemAtEqual(T element, int index){
        if(index<0||index>=cnt){
            cout<<"index out of range\n";
        }
        else{
            current=first;
            for(int i=0;i<index;++i){
                current=current->next;
            }
            if(current->data==element){
                return true;
            }
        }
        return false;
    }

    void swap(int firstIndex,int secondIndex){
        if(firstIndex<0||firstIndex>=cnt||secondIndex<0||secondIndex>=cnt){
            cout<<"index out of range\n";
        }
        if(firstIndex==secondIndex){
            return;
        }
        //before first, first, before second, second
        Node<T> *bf= nullptr;
        Node<T> *f=first;
        Node<T> *bs;
        Node<T> *s=first;

        Node<T> *temp2;

        if(secondIndex-firstIndex>1){
            for(int i=0;i<firstIndex;i++) {
                bf = f;
                f = f->next;
            }
            for(int i=0;i<secondIndex;i++) {
                bs = s;
                s = s->next;
            }
            temp=s->next;
            bf->next=s;
            s->next=f->next;
            bs->next=f;
            f->next=temp;
        }
        else if(firstIndex==0){
            for(int i=0;i<secondIndex;i++) {
                bs = s;
                s = s->next;
            }
            temp=s->next;
            f=first;
            first=s;
            s->next=bs;
            bs->next=f;
            f->next=temp;
//            first=s;
        }
        else{

        }
        if(secondIndex==cnt-1){
            f->next=first;\

        }








        //if adjacent
//        if(secondIndex-firstIndex==1){
//            temp=f->next;
//            f->next=s->next;
//            s->next=temp;
//            temp=f;
//            f=s;
//            s=temp;
//            temp=bf->next;
//            bf->next=s;
//            bs->next=temp;
//        }




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
            temp=first;
            first=first->next;
            delete temp;
            cnt--;
        }
        first=NULL;
    }
    void print(){
        current=first;
        for(int i=0;i<cnt;++i){
            cout<<current->data<<"\n";
            current=current->next;
        }
    }
};

//int main(){
//    CLL<int> c;
//    c.insertAtTail(5);
//    c.insertAtTail(6);
//    c.insertAtTail(7);
//    c.insertAtTail(8);
//    c.insertAtTail(9);
//    c.insertAtTail(10);
//    c.insertAtHead(4);
//    c.insertAtHead(3);
//    c.insertAtHead(2);
//    c.insertAtHead(1);
//    c.removeAtHead();
//    c.removeAtHead();
//    c.removeAtTail();
//    c.removeAt(5);
//    cout<<c.size()<<endl;
//    c.swap(0,2);
//    c.print();
//    c.clear();
//    c.print();
//    cout<<c.retrieveAt(3);
//    return 0;
//}