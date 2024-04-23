
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Stack {
private:
    T* array;
    int top;
    int capacity;
    void expandCapacity();

public:
    Stack() {
        top = 0;
        capacity =100;
        array = new T[capacity];
    }

    ~Stack() {
        delete[] array;
    }

    bool isEmpty() {
        return (top == 0);
    }

    bool isFull() {
        return (top == capacity);
    }

    void push(T val) {
        if (isFull()) {
            expandCapacity();
        }
        array[top++] = val;
        cout << val << " pushed to the stack." << endl;
    }

    void pop() {
        if (!isEmpty()) {
            T popped = array[--top]; // Decrement top before accessing array
            cout << "Popped element: " << popped << " from the stack." << endl;
        } else {
            cout << "Cannot pop, stack is empty!" << endl;
        }
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
        cout << "Stack cleared." << endl;
    }

    T topElement() {
        if (!isEmpty()) {
            return array[top - 1];
        } else {
            cout << "Stack is empty." << endl;
            return T(); // Return a default-constructed value of type T
        }
    }

    int size() {
        return top;
    }

    void print() {
        if (isEmpty()) {
            cout << "Stack is Empty !" << endl;
        } else {
            cout << "Stack elements (top to bottom):" << endl;
            for (int i = top - 1; i >= 0; --i) {
                cout << array[i] << endl;
            }
            cout << "................................................" << endl;
        }
    }
};

template<typename T>
void Stack<T>::expandCapacity() {
    capacity *= 2;
    T* new_array = new T[capacity];
    for (int i = 0; i < top; ++i) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
}

int main() {
    Stack<int> myIntStack;
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
                myIntStack.clear();
                break;
            case 4:
                myIntStack.print();
                break;
            case 5:
                cout << "Size of the stack: " << myIntStack.size() << endl;
                break;
            case 6:
                if (myIntStack.isFull()) {
                    cout << "Stack is full." << endl;
                } else {
                    cout << "Stack is not full." << endl;
                }
                break;
            case 7:
                if (!myIntStack.isEmpty()) {
                    cout << "Top element: " << myIntStack.topElement() << endl;
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
