#include <iostream>
using namespace std;

template <class T>
class ArrayQueue {
private:
    T* storage;
    int capacity;
    int First, Last;

public:
    ArrayQueue(int initialCapacity = 5) : capacity(initialCapacity) {
        storage = new T[capacity];
        First = Last = -1;
    }

    ~ArrayQueue() {
        delete[] storage;
    }

    bool isFull() {
        return (First == 0 && Last == capacity - 1) || (Last == First - 1);
    }

    bool isEmpty() {
        return First == -1;
    }

    void enqueue(T el) {
        if (isFull()) {
            cout << "Queue is Full" << endl;
            return;
        }
        if (isEmpty()) {
            First = Last = 0;
        } else {
            Last = (Last + 1) % capacity;
        }
        storage[Last] = el;
    }

    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return 0;
        }
        else {
            T el = storage[First];
            if (First == Last) {
                First = Last = -1;
            }
            else {
                First = (First + 1) % capacity;
            }
            return el;
        }
    }

    void first() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
        } else {
            cout << "First element of Queue is: " << storage[First] << endl;
        }
    }

    void queueSize() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
        } else {
            int size;
            if (Last >= First)
                size = Last - First + 1;
            else
                size = capacity - First + Last + 1;
            cout << "Queue Size is: " << size << endl;
        }
    }

    void clear() {
        First = Last = -1;
    }

    void print() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }
        int i = First;
        while (i != Last) {
            cout << storage[i] << endl;
            i = (i + 1) % capacity;
        }
        cout << storage[Last] << endl;
    }
};

int main() {
    ArrayQueue<int> queue;
    int choice, value;
    while (true) {
        cout << "\nMenu:\n1. Enqueue\n2. Dequeue\n3. Print Queue\n"
                "4. Clear queue\n5. Return size\n6. print first\n7. Exit\nEnter your choice: " << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: " << endl;
                cin >> value;
                queue.enqueue(value);
                break;
            case 2:
                cout << "Dequeued element: " << queue.dequeue() << endl;
                break;
            case 3:
                cout << "Queue elements:" << endl;
                queue.print();
                break;
            case 4:
                cout << "Queue is cleared" << endl;
                queue.clear();
                break;
            case 5:
                queue.queueSize();
                break;
            case 6:
                queue.first();
                break;
            case 7:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid Choice" << endl;
        }
    }
    return 0;
}
