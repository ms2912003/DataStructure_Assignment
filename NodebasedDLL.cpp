#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <class T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    void push_back(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void push_front(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void push_at_position(int position, T val) {
        if (position < 0 || position > size) {
            cout << "Invalid position" << endl;
            return;
        }
        if (position == 0) {
            push_front(val);
            return;
        }
        if (position == size) {
            push_back(val);
            return;
        }
        Node<T>* newNode = new Node<T>(val);
        Node<T>* current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
        size++;
    }

    void pop_front() {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        Node<T>* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        size--;
    }

    void pop_back() {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        Node<T>* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        size--;
    }

    void delete_at_position(int position) {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        if (position < 0 || position >= size) {
            cout << "Invalid position" << endl;
            return;
        }
        if (position == 0) {
            pop_front();
            return;
        }
        if (position == size - 1) {
            pop_back();
            return;
        }
        Node<T>* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }

    T front() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        return head->data;
    }

    T back() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        return tail->data;
    }

    bool isEmpty() {
        return size == 0;
    }

    void print() {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void clear() {
        while (!isEmpty()) {
            pop_back();
        }
    }

    int Size() {
        return size;
    }

    T retrieveAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void replaceAt(T newElement, int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->data = newElement;
    }

    bool isExist(T element) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == element) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool isItemAtEqual(T element, int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data == element;
    }

    void swap(int firstItemIdx, int secondItemIdx) {
        if (firstItemIdx < 0 || firstItemIdx >= size || secondItemIdx < 0 || secondItemIdx >= size) {
            throw out_of_range("Invalid index");
        }
        Node<T>* firstItem = head;
        for (int i = 0; i < firstItemIdx; i++) {
            firstItem = firstItem->next;
        }
        Node<T>* secondItem = head;
        for (int i = 0; i < secondItemIdx; i++) {
            secondItem = secondItem->next;
        }
        T temp = firstItem->data;
        firstItem->data = secondItem->data;
        secondItem->data = temp;
    }
};

int main() {
    DoublyLinkedList<int> list;
    int choice, value, position;
    while (true) {
        cout << "\nMenu:\n1. Insert element at end\n2. Delete element from end\n3. Insert element at beginning\n"
                "4. Delete element from beginning\n5. Insert element at certain position\n6. Delete element from certain position\n"
                "7. Print first element\n8. Print last\n9. Print list\n10. Clear list\n11. Print size of list\n"
                "12. Retrieve element at index\n13. Replace element at index\n14. Check if element exists\n"
                "15. Check if item at index is equal to element\n16. Swap two elements by index\n17. Exit Program.\nEnter your choice: " << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value to insert at end: " << endl;
                cin >> value;
                list.push_back(value);
                break;
            case 2:
                if (!list.isEmpty()) {
                    cout << "Deleted element from end: " << list.back() << endl;
                    list.pop_back();
                } else {
                    cout << "List is empty" << endl;
                }
                break;
            case 3:
                cout << "Enter value to insert at beginning: " << endl;;
                cin >> value;
                list.push_front(value);
                break;
            case 4:
                if (!list.isEmpty()) {
                    cout << "Deleted element from beginning: " << list.front() << endl;
                    list.pop_front();
                } else {
                    cout << "List is empty" << endl;
                }
                break;
            case 5:
                cout << "Enter value to insert: " << endl;;
                cin >> value;
                cout << "Enter position to insert at: " << endl;;
                cin >> position;
                list.push_at_position(position, value);
                break;
            case 6:
                cout << "Enter position to delete from: " << endl;;
                cin >> position;
                list.delete_at_position(position);
                break;
            case 7:
                if (!list.isEmpty()) {
                    cout << "First element: " << list.front() << endl;
                } else {
                    cout << "List is empty" << endl;
                }
                break;
            case 8:
                if (!list.isEmpty()) {
                    cout << "Last element: " << list.back() << endl;
                } else {
                    cout << "List is empty" << endl;
                }
                break;
            case 9:
                cout << "List elements: " << endl;;
                list.print();
                break;
            case 10:
                list.clear();
                cout << "List cleared" << endl;
                break;
            case 11:
                cout << "Size of the list: " << list.Size() << endl;
                break;
            case 12:
                cout << "Enter index to retrieve from: " << endl;;
                cin >> position;
                try {
                    cout << "Element at index " << position << ": " << list.retrieveAt(position) << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            case 13:
                cout << "Enter index to replace: " << endl;;
                cin >> position;
                cout << "Enter new value: " << endl;;
                cin >> value;
                try {
                    list.replaceAt(value, position);
                    cout << "Element replaced successfully" << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            case 14:
                cout << "Enter element to check if it exists: " << endl;;
                cin >> value;
                if (list.isExist(value)) {
                    cout << "Element exists in the list" << endl;
                } else {
                    cout << "Element does not exist in the list" << endl;
                }
                break;
            case 15:
                cout << "Enter element to compare: " << endl;;
                cin >> value;
                cout << "Enter index to compare with: " << endl;;
                cin >> position;
                try {
                    if (list.isItemAtEqual(value, position)) {
                        cout << "Item at index " << position << " is equal to " << value << endl;
                    } else {
                        cout << "Item at index " << position << " is not equal to " << value << endl;
                    }
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            case 16:
                cout << "Enter first element index to swap: " << endl;;
                cin >> position;
                cout << "Enter second element index to swap: " << endl;;
                cin >> value;
                try {
                    list.swap(position, value);
                    cout << "Elements swapped successfully" << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            case 17:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
    }
    return 0;
}
