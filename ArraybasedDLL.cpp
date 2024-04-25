#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class ArrayDoublyLinkedList {
private:
    T* arr;
    int capacity;
    int size;
    int first;
    int last;
public:
    ArrayDoublyLinkedList(int initialCapacity = 5) : capacity(initialCapacity), size(0), first(-1), last(-1) {
        arr = new T[capacity];
    }

    ~ArrayDoublyLinkedList() {
        delete[] arr;
    }

    bool isFull() {
        return size == capacity;
    }

    void push_back(T val) {
        if(isFull()){
            expandCapacity();
        }
        if (isEmpty()) {
            first = last = 0;
        } else {
            last = (last + 1) % capacity;
        }
        arr[last] = val;
        size++;
    }

    void push_front(T val) {
        if(isFull()){
            expandCapacity();
        }
        if (isEmpty()) {
            first = last = 0;
        } else {
            first = (first - 1 + capacity) % capacity;
        }
        arr[first] = val;
        size++;
    }

    void push_at_position(int position, T val) {

        if (position < 0 || position > size) {
            cout << "Invalid position" << endl;
            return;
        }
        if(isFull()){
            expandCapacity();
        }
        if (position == 0) {
            push_front(val);
            return;
        }
        if (position == size) {
            push_back(val);
            return;
        }
        // Shift elements to the right to make space for the new element
        for (int i = last; i >= position; i = (i - 1 + capacity) % capacity) {
            arr[(i + 1) % capacity] = arr[i];
        }
        arr[position] = val;
        size++;
        last = (last + 1) % capacity;
    }

    void pop_front() {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        if (first == last) {
            first = last = -1;
        } else {
            first = (first + 1) % capacity;
        }
        size--;
    }

    void pop_back() {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        if (first == last) {
            first = last = -1;
        } else {
            last = (last - 1 + capacity) % capacity;
        }
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
        // Shift elements to the left to fill the gap created by deleting the element
        for (int i = position; i != last; i = (i + 1) % capacity) {
            arr[i] = arr[(i + 1) % capacity];
        }
        last = (last - 1 + capacity) % capacity;
        size--;
    }

    T front() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        return arr[first];
    }

    T back() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        return arr[last];
    }

    bool isEmpty() {
        return size == 0;
    }

    void print() {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        for (int i = first; i != (last + 1) % capacity; i = (i + 1) % capacity) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void clear() {
        size = 0;
        first = last = -1;
    }

    int Size() {
        return size;
    }

    T retrieveAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }
        return arr[(first + index) % capacity];
    }

    void replaceAt(T newElement, int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }
        arr[(first + index) % capacity] = newElement;
    }

    bool isExist(T element) {
        for (int i = first; i != (last + 1) % capacity; i = (i + 1) % capacity) {
            if (arr[i] == element) {
                return true;
            }
        }
        return false;
    }

    bool isItemAtEqual(T element, int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }
        return arr[(first + index) % capacity] == element;
    }

    void swap(int firstItemIdx, int secondItemIdx) {
        if (firstItemIdx < 0 || firstItemIdx >= size || secondItemIdx < 0 || secondItemIdx >= size) {
            throw out_of_range("Invalid index");
        }
        T temp = arr[(first + firstItemIdx) % capacity];
        arr[(first + firstItemIdx) % capacity] = arr[(first + secondItemIdx) % capacity];
        arr[(first + secondItemIdx) % capacity] = temp;
    }
    void expandCapacity() {
        int newCapacity = capacity * 2;
        T* newArr = new T[newCapacity];

        for (int i = 0; i < size; ++i) {
            newArr[i] = arr[(first + i) % capacity];
        }

        capacity = newCapacity;
        first = 0;
        last = size - 1;

        delete[] arr;
        arr = newArr;
    }
};


int main() {
    ArrayDoublyLinkedList<int> list;
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
                cout << "Enter index to retrieve element: ";
                cin >> position;
                try {
                    cout << "Element at index " << position << ": " << list.retrieveAt(position) << endl;
                } catch (const out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            case 13:
                cout << "Enter index to replace element: ";
                cin >> position;
                cout << "Enter new element value: ";
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
                cin >> position;
                cout << "Enter second element index to swap: ";
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
