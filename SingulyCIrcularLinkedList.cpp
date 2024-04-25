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
        Node<T> *bf = new Node<T>;
        Node<T> *f = new Node<T>;
        Node<T> *af = new Node<T>;
        Node<T> *bs = new Node<T>;
        Node<T> *s = new Node<T>;
        Node<T> *as = new Node<T>;

        Node<T> *temp = new Node<T>;

        bf = first;
        f = first;
        af = first;
        bs = first;
        s = first;
        as = first;
        for (int i = 0; i < min(firstIndex,secondIndex); i++) {
            bf = f;
            f = f->next;
        }
        for (int i = 0; i < max(firstIndex, secondIndex); i++) {
            bs = s;
            s = s->next;
        }
        af = f->next;
        as = s->next;
        if(abs(secondIndex-firstIndex)>1) {

            if(firstIndex==0||secondIndex==0){
                if(firstIndex==cnt-1||secondIndex==cnt-1){
                    bs->next=f;
                    f->next=s;
                    s->next=af;
                    first=s;
                    last=f;
                    last->next=first;
                }
                else{
                    bs->next=f;
                    bf->next=s;
                    s->next=af;
                    f->next=as;
                    first=s;
                    last->next=first;
                }
            }
            else{
                bf->next=s;
                s->next=af;
                bs->next=f;
                f->next=as;
            }

        }
        else{

            bf->next=s;
            s->next=f;
            f->next=as;
            if(firstIndex==0||secondIndex==0){
                first=s;
            }

        }
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
        for(int i=0;i<cnt*2;++i){
            cout<<current->data<<"\n";
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
    ll.swap(0,3);
    ll.swap(0,7);
    ll.swap(0,5);
    ll.insertAt(100,0);
    ll.insertAt(200,9);
    ll.removeAtHead();
    ll.removeAtTail();
    ll.removeAt(5);
    if(ll.isEmpty()){
        cout<<"List is empty\n";
    }
    else{
        cout<<"List is not empty\n";
    }
    cout<<"Size of the list: "<<ll.size()<<"\n";
    cout<<"The fifth element of the list: "<<ll.retrieveAt(4)<<"\n";
    ll.replaceAt(40,3);
    if(ll.isExist(8)){
        cout<<"Found the element\n";
    }
    else{
        cout<<"Element not found\n";
    }
    if(ll.isItemAtEqual(7,3)){
        cout<<"Item is equal\n";
    }
    else{
        cout<<"Item is not equal\n";
    }
    ll.print();
    ll.clear();
    return 0;
}