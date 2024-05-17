#include <bits/stdc++.h>
using namespace std;
int type=0;
class AVLNode {
public:
    string name;
    string category;
    int key;

    AVLNode* left;
    AVLNode* right;
    AVLNode* parent; // Add parent pointer for iterative insert
    int height;

    AVLNode(string na,string cat,int ele,AVLNode* l = nullptr, AVLNode* r = nullptr, AVLNode* p = nullptr) {
        name=na;
        category=cat;
        key = ele;


        left = l;
        right = r;
        parent = p; // Initialize parent pointer
        height = 0;
    }
    bool operator<=(const AVLNode& i)
    {
        if(type==1){
            if((key)<=(i.key))
                return 1;
            else
                return 0;
        }
        else{
            if((name)<=(i.name))
                return 1;
            else
                return 0;
        }

    }
    bool operator!=(const AVLNode& i)
    {
        if(type==1){
            if((key)!=(i.key))
                return 1;
            else
                return 0;
        }
        else{
            if((name)!=(i.name))
                return 1;
            else
                return 0;
        }

    }


};


class AVL {
public:
    AVLNode* root;
    AVL(){
        root=nullptr;
    }

    //Height___________________________________________
    int Height(AVLNode* N) { // return h=-1 if is empty else return height
        return N ? N->height : -1;
    }
    //getBalance_________________________________________
    int getBalanceFactor(AVLNode* N) {
        return N ? Height(N->right) - Height(N->left) : 0;
    }
    //updateHeight_______________________________________
    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + max(Height(node->left), Height(node->right));
        }
    }
    //rightRotate_____________________________________
    AVLNode* rightRotate(AVLNode* &y) {
        AVLNode* x = y->left;
        AVLNode* z = x->right;

        // Step 1: Perform rotation
        x->right = y;
        y->left = z;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        // Update parent pointers
        if (y->parent) {
            if (y->parent->left == y)
                y->parent->left = x;
            else
                y->parent->right = x;
        }
        x->parent = y->parent;
        y->parent = x;
        if (z)
            z->parent = y;

        // Update root if necessary
        if (y == root)
            root = x;

        return x;
    }
    //leftRotate_________________________________________
    AVLNode* leftRotate(AVLNode* &x) {
        AVLNode* y = x->right;
        AVLNode* z = y->left;

        // Step 1: Perform rotation
        y->left = x;
        x->right = z;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        // Update parent pointers
        if (x->parent) {
            if (x->parent->left == x)
                x->parent->left = y;
            else
                x->parent->right = y;
        }
        y->parent = x->parent;
        x->parent = y;
        if (z)
            z->parent = x;

        // Update root if necessary
        if (x == root)
            root = y;

        return y;
    }
    //insert_________________________________________
    void Add_item(string na,string cat,int ele) {
        AVLNode* newNode = new AVLNode(na,cat,ele);
        AVLNode* p=root;//we used it to search
        AVLNode* prev=NULL; // it equals last Node that I will add newNode in its left or right next after while loop .
        while(p!=NULL){
            prev=p;
            if(*newNode<=*p){

                p=p->left;

            }// if it equals null then in next iteration we will go out with prev=lastNode .
            else{

                p=p->right;

            }
        }
        if(root==NULL){ //Note:we say if root==0 not if p==0 -> as here p is always true as we out of while
            root=newNode;
        }
        else if(*newNode<=*prev){

            prev->left=newNode;

        }
        else{

            prev->right=newNode;

        }

        // Update parent pointer of the new node
        newNode->parent = prev;

        // Update height of the newly inserted node
        newNode->height = 0;

        // Update height of ancestors and balance the tree
        while (prev != nullptr) {
            updateHeight(prev);
            prev = balanceTree(prev);
            prev = prev->parent; // Move up in the tree towards the root
        }
    }
    //Delete_______________________________________________
    AVLNode* remove_item(AVLNode* Root, string na,string cat,int ele)
    {
        AVLNode* d=new AVLNode(na,cat,ele);
        AVLNode* curr = Root;
        AVLNode* prev = NULL;

        // Check if the key is actually present in the BST.
        // the variable prev points to the parent of the key to be deleted.
        // [ search ]
        while (curr != NULL && *curr!= *d) {
            prev = curr;
            if (*d<=*curr)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (curr == NULL) {
            cout << "Key " << d->key<< " not found in the"
                 << " provided BST.\n";
            return Root;
        }

        // ========= CASE 1 :Check if the node to be deleted has at most one child =========
        if (curr->left == NULL || curr->right == NULL) {

            // newCurr will replace
            // the node to be deleted.
            AVLNode* newCurr;

            // if the left child does not exist.
            if (curr->left == NULL)
                newCurr = curr->right;
            else
                newCurr = curr->left;



            // check if the node to be deleted is the root.
            if (prev == NULL){
                root=newCurr;
                return newCurr;
            }

            // [ important part ] --> which reflect deleting to prevs ;
            // check if the node to be deleted is prev's left or right child
            // and then replace this with newCurr
            if (curr == prev->left)
                prev->left = newCurr;
            else
                prev->right = newCurr;


            // free memory of the node to be deleted.
            delete curr;

            // Update height of ancestors and balance the tree
            while (prev != nullptr) {
                updateHeight(prev);
                prev = balanceTree(prev);
                prev = prev->parent; // Move up in the tree towards the root
            }
        }

            //========= CASE2 : node to be deleted has two children =========
        else {
            AVLNode* p = curr;
            AVLNode* successor;

            // Compute the inorder successor
            successor = curr->right;
            while (successor->left != NULL) {
                p = successor;
                successor = successor->left;
            }

            if (p != curr)
                //p != curr --> means that we enter while loop --> and we end with most successor which didn't
                p->left = successor->right;
            else
                //p == curr --> means tat we didn't enter while loop --> successor didn't have left
                p->right = successor->right;



            curr->key = successor->key;
            delete successor;
            // Update height of ancestors and balance the tree
            while (p != nullptr) {
                updateHeight(p);
                p = balanceTree(p);
                p = p->parent; // Move up in the tree towards the root
            }
        }
        return Root;
    }
    //balanceTree___________________________________________
    AVLNode* balanceTree(AVLNode* node) {
        if (node == nullptr)
            return node; // as Balance Factor =0;

        int balance = getBalanceFactor(node);

        // If this node becomes unbalanced, then there are 4 cases
        if (balance > 1) { // Right heavy
            if (getBalanceFactor(node->right) < 0) { // Right (left)
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }
        else if (balance < -1) { // Left heavy
            if (getBalanceFactor(node->left) > 0) { // Left right
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }

        return node;
    }

    //__________Ascending_(InOrder)_______________________
    void Ascending(AVLNode* p) { // it prints elements in ascending order (ordered)
        if (p != NULL) {
            Ascending(p->left);
            cout << p->key << " "<<p->name<<" "<<p->category<<"\n";
            Ascending(p->right);
        }
    }
    //__________Descending__________________________________
    void Descending(AVLNode* p) { // it prints elements in ascending order (ordered)
        if (p != NULL) {
            Descending(p->right);
            cout << p->key << " "<<p->name<<" "<<p->category<<"\n";
            Descending(p->left);
        }
    }
    //_________display_level_by_level__________________________
    void Display_level_by_level(){
        AVLNode* p=root;
        queue<AVLNode*>q;
        if(p!=NULL){
            q.push(p);
        }
        while(!q.empty()){
            p=q.front();
            cout<<p->key;
            if(p->left!=NULL){
                q.push(p->left);}
            if(p->right!=NULL){
                q.push(p->right);
            }
            q.pop();
        }

    }
    //____________________________________________
};

int main() {
    type=1;
    AVL avl;
    avl.Add_item("chocolate milk","drink",10);//[1]add
    avl.Add_item("bananas","fruit",75);
    avl.Add_item("pepsi","drink",20);
    avl.Add_item("cheddar cheese","dairy",49);
    avl.Add_item("tuna","meat",90);
    avl.Add_item("fanta orange","drink",20);
    avl.Add_item("yought","dairy",13);
    avl.Add_item("mint gum","candy",2);
    avl.Add_item("water","drink",9);
    avl.Add_item("apples","fruit",66);
    avl.Add_item("beef","meat",284);
    avl.Add_item("cheese cake","dessert",68);
    //____________________
    cout<<"price in ascending order \n";
    avl.Ascending(avl.root);//[4] display with price in ascending
    //____________________
    cout<<"\n\n";
    avl.remove_item(avl.root,"cheese cake","dessert",68);//[2] remove
    avl.remove_item(avl.root,"beef","meat",284);
    //____________________
    cout<<"price in descending order \n";
    avl.Descending(avl.root); //[5] display with price in descending
    //____________________
    cout<<"price level by level \n";
    avl.Display_level_by_level(); // [3] display level by level
    //____________________________________________________
    cout<<"\n\n";
    type=0;
    AVL avl1;
    avl1.Add_item("chocolate milk","drink",10);
    avl1.Add_item("bananas","fruit",75);
    avl1.Add_item("pepsi","drink",20);
    avl1.Add_item("cheddar cheese","dairy",49);
    avl1.Add_item("tuna","meat",90);
    avl1.Add_item("fanta orange","drink",20);
    avl1.Add_item("yought","dairy",13);
    avl1.Add_item("mint gum","candy",2);
    avl1.Add_item("water","drink",9);
    avl1.Add_item("apples","fruit",66);
    avl1.Add_item("beef","meat",284);
    avl1.Add_item("cheese cake","dessert",68);
    //____________________
    cout<<"name in ascending order \n";
    avl1.Ascending(avl1.root);//[6] display with name in ascending
    cout<<"\n\n";
    //____________________
    cout<<"name in descending order \n";
    avl1.Descending(avl1.root); //[7] display with name in descending
    //____________________________
    avl1.Display_level_by_level();
}

