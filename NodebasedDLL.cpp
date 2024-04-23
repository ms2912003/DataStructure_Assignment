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
        if (firstItemIdx == secondItemIdx) {
            // No need to swap if indices are the same
            return;
        }
        Node<T>* firstItem = head;
        Node<T>* secondItem = head;
        // Find the nodes to swap
        for (int i = 0; i < firstItemIdx; i++) {
            firstItem = firstItem->next;
        }
        for (int i = 0; i < secondItemIdx; i++) {
            secondItem = secondItem->next;
        }
        // Swap the nodes without swapping their data
        if (firstItem->next == secondItem) {
            // If the nodes are adjacent
            firstItem->next = secondItem->next;
            secondItem->prev = firstItem->prev;
            if (secondItem->next) {
                secondItem->next->prev = firstItem;
            }
            secondItem->next = firstItem;
            firstItem->prev = secondItem;
            if (secondItem->prev) {
                secondItem->prev->next = secondItem;
            } else {
                // If the first node is the head
                head = secondItem;
            }
        } else if (secondItem->next == firstItem) {
            // If the nodes are adjacent in the opposite order
            secondItem->next = firstItem->next;
            firstItem->prev = secondItem->prev;
            if (firstItem->next) {
                firstItem->next->prev = secondItem;
            }
            firstItem->next = secondItem;
            secondItem->prev = firstItem;
            if (firstItem->prev) {
                firstItem->prev->next = firstItem;
            } else {
                // If the second node is the head
                head = firstItem;
            }
        } else {
            // If the nodes are not adjacent
            Node<T>* temp = firstItem->next;
            firstItem->next = secondItem->next;
            secondItem->next = temp;
            if (firstItem->next) {
                firstItem->next->prev = firstItem;
            }
            if (secondItem->next) {
                secondItem->next->prev = secondItem;
            }
            temp = firstItem->prev;
            firstItem->prev = secondItem->prev;
            secondItem->prev = temp;
            if (firstItem->prev) {
                firstItem->prev->next = firstItem;
            } else {
                head = firstItem;
            }
            if (secondItem->prev) {
                secondItem->prev->next = secondItem;
            } else {
                head = secondItem;
            }
        }
    }
};

int main() {
    DoublyLinkedList<int> list;
    int choice, value, position, firstItemIdx, secondItemIdx;
    while (true) {
        cout << "\nMenu:\n1. Insert element at end\n2. Delete element from end\n3. Insert element at beginning\n"
                "4. Delete element from beginning\n5. Insert element at certain position\n6. Delete element from certain position\n"
                "7. Print first element\n8. Print last\n9. Print list\n10. Clear list\n11. Print size of list\n"
                "12. Retrieve element at index\n13. Replace element at index\n14. Check if element exists\n"
                "15. Check if item at index is equal to element\n16. Swap two elements by index\n17. Exit Program.\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value to insert at end: ";
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
                cout << "Enter value to insert at beginning: ";
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
                cout << "Enter value to insert: ";
                cin >> value;
                cout << "Enter position to insert at: ";
                cin >> position;
                list.push_at_position(position, value);
                break;
            case 6:
                cout << "Enter position to delete from: ";
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
                cout << "List elements: ";
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
                cout << "Enter index to retrieve from: ";
                cin >> position;
                try {
                    cout << "Element at index " << position << ": " << list.retrieveAt(position) << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            case 13:
                cout << "Enter index to replace: ";
                cin >> position;
                cout << "Enter new value: ";
                cin >> value;
                try {
                    list.replaceAt(value, position);
                    cout << "Element replaced successfully" << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            case 14:
                cout << "Enter element to check if it exists: ";
                cin >> value;
                if (list.isExist(value)) {
                    cout << "Element exists in the list" << endl;
                } else {
                    cout << "Element does not exist in the list" << endl;
                }
                break;
            case 15:
                cout << "Enter element to compare: ";
                cin >> value;
                cout << "Enter index to compare with: ";
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
                cout << "Enter first element index to swap: ";
                cin >> firstItemIdx;
                cout << "Enter second element index to swap: ";
                cin >> secondItemIdx;
                try {
                    list.swap(firstItemIdx, secondItemIdx);
                    cout << "Nodes swapped successfully" << endl;
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

