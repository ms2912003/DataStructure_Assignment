#include <iostream>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* next;

    Node(T val) : data(val), next(nullptr) {}
};

template <class T>
class ListbasedQueue {
private:
    Node<T>* front;
    Node<T>* back;

public:
    ListbasedQueue() : front(nullptr), back(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(T n) {
        Node<T>* newNode = new Node<T>(n);
        if (isEmpty()) {
            front = back = newNode;
        } else {
            back->next = newNode;
            back = newNode;
        }
    }

    T dequeue() {
        if (isEmpty()) {
            cerr << "Queue is empty. Cannot dequeue." << endl;
            exit(1);
        }
        T tmp = front->data;
        Node<T>* tempNode = front;
        front = front->next;
        delete tempNode;
        return tmp;
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void first() {
        if (isEmpty()) {
            cerr << "Queue is empty." << endl;
            return;
        }
        cout << front->data << endl;
    }

    void queueSize() {
        int count = 0;
        Node<T>* current = front;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        cout << count << endl;
    }

    void print() {
        if (isEmpty()) {
            cout << "Queue is Empty !" << endl;
        } else {
            Node<T>* current = front;
            while (current != nullptr) {
                cout << current->data << endl;
                current = current->next;
            }
        }
    }

    ~ListbasedQueue() {
        clear();
    }
};

int main() {
    ListbasedQueue<int> queue;
    int choice, value;
    while (true) {
        cout << "\nMenu:\n1. Enqueue\n2. Dequeue\n3. Print Queue\n"
                "4. Clear queue\n5. Return size\n6. Print first\n7. Exit\nEnter your choice: \n";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: \n";
                cin >> value;
                queue.enqueue(value);
                break;
            case 2:
                if (!queue.isEmpty())
                    cout << "Dequeued element:" << queue.dequeue() << endl;
                else
                    cout << "Queue is empty. Cannot dequeue.\n" << endl;
                break;
            case 3:
                cout << "Queue elements:\n" << endl;
                queue.print();
                break;
            case 4:
                cout << "Queue is cleared\n" << endl;
                queue.clear();
                break;
            case 5:
                cout << "Queue Size is: \n";
                queue.queueSize();
                break;
            case 6:
                cout << "First element of Queue is: ";
                queue.first();
                break;
            case 7:
                cout << "Exiting program.\n" << endl;
                return 0;
            default:
                cout << "Invalid Choice\n" << endl;
        }
    }
    return 0;
}
