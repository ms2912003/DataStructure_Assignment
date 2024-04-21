#include <bits/stdc++.h>
using namespace std;
template <class T>
class Node{
public:
    T data;
    Node* next;
};
template <class T>
class LL{
public:
    Node<T>* head;
    Node<T>* last;
    LL(){
        head=NULL;
        last=NULL;
    }
    ~LL(){
        clear();
    }
    //==========================================================================================
    void insertAtHead (T element){ //✔
        Node<T>* new_node=new Node<T>();
        new_node->data=element;
        new_node->next=head;
        if(isEmpty()){
            last=new_node;
        }
        head=new_node;// I was made it above condition so it make error

    }
    //==========================================================================================
    void insertAtTail (T element){ //✔
        Node<T>* new_node=new Node<T>();
        new_node->data=element;
        if(isEmpty()){
            head=new_node;
            last=new_node;
        }
        else{
            last->next=new_node;
            last=new_node;
        }

    }
    //===========================================================================================
    void insertAt (int element, int index){//✔
        if(index<linkedListSize()&&index>=0){
            Node<T>* new_node=new Node<T>();
            new_node->data=element;
             if(index==0){
                 new_node->next=head;
                 head=new_node;
             }
             else {

                 Node<T>* temp=head;
                 int i=0;
                 while(temp!=NULL){
                     if(i==index-1){//before required index
                         new_node->next=temp->next;
                         temp->next=new_node;
                     }
                     temp=temp->next;
                     i++;// sorry I miss it
                 }

             }

        }
        else{
            cout<<"THERE IS NO SUCH INDEX\n";
        }

    }
    //==========================================================================================
    void removeAtHead (){//✔
        Node<T>* del_ptr=head;
        if(linkedListSize()==1){
            delete del_ptr;
            head=NULL;
            last=NULL;
        }
        else{
            head=head->next;
            delete del_ptr;
        }
    }
    //==========================================================================================
    void removeAtTail (){//✔
        Node<T>* del_ptr=last;
        if(linkedListSize()==1){
            delete del_ptr;
            head=NULL;
            last=NULL;
        }
        else{
             Node<T>* temp=head;
             while(temp->next!=last){//to be out when it equals before last
                 temp=temp->next;
             }
             last=temp;
             temp->next=NULL;
             delete del_ptr;
        }
    }
    //==========================================================================================
    void removeAt (int index){ //✔
        if(index<linkedListSize()&&index>=0){
            Node<T>* del_ptr=head;
             if(index==0){
                  del_ptr=head;
                 head=head->next;
                 delete del_ptr;

             }
             else{
                 Node<T>* temp=head;
                 int i=0;

                 while(temp!=NULL){
                     if(i==index-1){
                        del_ptr=temp->next;
                        temp->next=temp->next->next;
                        delete del_ptr;
                     }
                     i++;
                     temp=temp->next;
                 }

             }
        }
        else{
            cout<<"THERE IS NO SUCH INDEX\n";
        }

    }
    //==========================================================================================
    T retrieveAt (int index){//✔
        if(index<linkedListSize()&&index>=0){
            Node<T>* temp=head;
            int i=0;
            T element ;
            while(temp!=NULL){
                if(index==i){
                    element= temp->data;
                    break;
                }
                temp=temp->next;
                i++;// sorry I miss if
            }
            return element ;
        }
        else{
            cout<<"THERE IS NO SUCH INDEX\n";
            return 0 ;
        }


    }
    //==========================================================================================
    void replaceAt (int newElement, int index){ //✔to change value og given index with given element
        if(index<linkedListSize()&&index>=0){
            Node<T>* temp=head;
            int i=0;
            while(temp!=NULL){
                if(i==index){
                    temp->data=newElement;
                    break;
                }
                    temp=temp->next;
                    i++;
            }
        }
        else{
            cout<<"THERE IS NO SUCH INDEX\n";
        }
    }
    //==========================================================================================
    bool isExist (int element){//✔
        Node<T>* temp=head;
        bool found=false;
        while(temp!=NULL){
            if(temp->data==element){
               found=true;}
            temp=temp->next;
        }
        return found;
    }
    //==========================================================================================
    bool isItemAtEqual (int element, int index){//✔
        if(index<linkedListSize()&&index>=0){
            Node<T>* temp=head;
            int i=0;
            bool equal=false;
            while(temp!=NULL){
                if(i==index&&temp->data==element){
                     equal=true;
                }
                    temp=temp->next;
                    i++;
            }
            return equal;
        }
        else{
            cout<<"THERE IS NO SUCH INDEX\n";
            return 0;
        }
    }
    //==========================================================================================
    void swap (int firstItemIdx, int secondItemIdx) {// swap two nodes without swapping data.
        Node<T>* prev_firstItem=NULL;
        Node<T>* prev_secondItem=NULL;
        Node<T>* firstItem=head;
        Node<T>* secondItem=head;
        if(firstItemIdx<linkedListSize()&&firstItemIdx>=0&&secondItemIdx<linkedListSize()&&secondItemIdx>=0){
            Node<T>* temp=head;
            int i=0;
            while(temp!=NULL){
                if(i==firstItemIdx-1&&i!=-1){
                     prev_firstItem=temp;
                     firstItem=temp->next;
                }
                if(i==secondItemIdx-1&&i!=-1){
                     prev_secondItem=temp;
                     secondItem=temp->next;
                }
                temp=temp->next;
                i++;
            }
            //هنا بشوف مين قبليا يشاور عليا===========
            if(prev_firstItem!=NULL){
                 prev_firstItem->next=secondItem;
            }
            else{
                head=secondItem;
            }
            if(prev_secondItem!=NULL){
                prev_secondItem->next=firstItem;
            }
            else{
                head=firstItem;
            }
            //هنا بشوف انا هشاور على مين بعديا ============
            Node<T>* x=firstItem->next;
            firstItem->next=secondItem->next;
            secondItem->next=x;
        }
        else{
            cout<<"THERE IS NO SUCH INDEX\n";
        }
    }
    //==========================================================================================
    bool isEmpty (){//✔
        if(head==NULL)
            return true;
        else
            return false;
    }
    //==========================================================================================
    int linkedListSize (){//✔
        Node<T>* temp=head;
        int count=0;
        while(temp!=NULL){
            count++;
            temp=temp->next;
        }
        return count;
    }
    //==========================================================================================
    void clear (){//✔
        Node<T>* temp=head;
        while(temp!=NULL){
            Node<T>* del_ptr=temp;
            temp=temp->next;
            delete del_ptr;
        }
    }
    //==========================================================================================
    void print (){ //✔
        Node<T>* temp=head;
        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
    }
};
int main(){
    LL<int> list;
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

    cout<<list.linkedListSize();cout<<endl;

    list.swap(1,2);
    list.print();cout<<endl;


}