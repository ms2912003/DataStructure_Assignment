#include <iostream>
#include <cassert>
using namespace std;

template<typename Type>
struct nodeType {
    Type info;
    nodeType<Type>* link;
};

template<typename Type>
class LinkedStack {
private:
    nodeType<Type>* stackTop;

public:
    LinkedStack() {
        stackTop = NULL;
    }

    ~LinkedStack() {
        initializeStack();
    }

    void initializeStack() {
        nodeType<Type>* temp;
        while (stackTop != NULL) {
            temp = stackTop;
            stackTop = stackTop->link;
            delete temp;
        }
    }

    void push(const Type& newElement) {
        nodeType<Type>* newNode = new nodeType<Type>;
        newNode->info = newElement;
        newNode->link = stackTop;
        stackTop = newNode;
    }

    Type top() const {
        assert(stackTop != NULL);
        return stackTop->info;
    }

    void pop() {
        if (stackTop != NULL) {
            nodeType<Type>* temp = stackTop;
            stackTop = stackTop->link;
            delete temp;
        } else {
            cout << "Cannot remove from an empty stack." << endl;
        }
    }

    bool isEmpty() {
        return (stackTop == NULL);
    }

    bool isFull() {
        return false; // Linked list-based stack can't be full
    }

    int size() {
        int count = 0;
        nodeType<Type>* current = stackTop;
        while (current != NULL) {
            count++;
            current = current->link;
        }
        return count;
    }

    void print() {
        if (isEmpty()) {
            cout << "Stack is Empty !" << endl;
        } else {
            cout << "Stack elements (top to bottom):" << endl;
            nodeType<Type>* current = stackTop;
            while (current != NULL) {
                cout << current->info << endl;
                current = current->link;
            }
            cout << "................................................" << endl;
        }
    }
};

int main() {
    LinkedStack<int> myIntStack;
    int choice;
    int value;

    while (true) {
        cout << "Choose an operation:\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Clear\n";
        cout << "4. Display stack\n";
        cout << "5. Get size\n";
        cout << "6. Check if stack is full\n";
        cout << "7. Get top element\n";
        cout << "8. Check if stack is empty\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter element to push: ";
                cin >> value;
                myIntStack.push(value);
                break;
            case 2:
                myIntStack.pop();
                break;
            case 3:
                myIntStack.initializeStack();
                cout << "Stack cleared." << endl;
                break;
            case 4:
                myIntStack.print();
                break;
            case 5:
                cout << "Size of the stack: " << myIntStack.size() << endl;
                break;
            case 6:
                cout << "Stack is never full (linked list-based)." << endl;
                break;
            case 7:
                if (!myIntStack.isEmpty()) {
                    cout << "Top element: " << myIntStack.top() << endl;
                } else {
                    cout << "Cannot get top, stack is empty." << endl;
                }
                break;
            case 8:
                if (myIntStack.isEmpty()) {
                    cout << "Stack is Empty." << endl;
                } else {
                    cout << "Stack is not Empty." << endl;
                }
                break;
            case 9:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    }
}
