//#include <iostream>
//using namespace std;
//#include <list>
//
//template <class T>
//class DDLQueue{
//private: list <T> queue;
//public:
//    bool isEmpty(){
//        return queue.empty();
//    }
//    void enqueue(T n){
//            queue.push_back(n);
//    }
//    T dequeue(){
//        T tmp = queue.front();
//        queue.pop_front();
//        return tmp;
//    }
//    void clear(){
//        queue.clear();
//    }
//    void first(){
//        cout << queue.front() << endl;
//    }
//    void queueSize(){
//        cout << queue.size() << endl;
//    }
//    void print () {
//        if (isEmpty()) {
//            cout << "Queue is Empty !" << endl;
//        } else {
//            for (auto i: queue) {
//                cout << i << endl;
//            }
//        }
//    }
//};
//int main() {
//    DDLQueue<int> queue;
//    int choice, value;
//    while (true) {
//        cout << "\nMenu:\n1. Enqueue\n2. Dequeue\n3. Print Queue\n"
//                "4. Clear queue\n5. Return size\n6. print first\n7. Exit\nEnter your choice: " << endl;
//        cin >> choice;
//        switch (choice) {
//            case 1:
//                cout << "Enter value to enqueue: " << endl;
//                cin >> value;
//                queue.enqueue(value);
//                break;
//            case 2:
//                cout << "Dequeued element: " << queue.dequeue() << endl;
//                break;
//            case 3:
//                cout << "Queue elements:" << endl;
//                queue.print();
//                break;
//            case 4:
//                cout << "Queue is cleared" << endl;
//                queue.clear();
//                break;
//            case 5:
//                cout << "Queue Size is: ";
//                queue.queueSize();
//                break;
//            case 6:
//                cout << "First element of Queue is: ";
//                queue.first();
//                break;
//            case 7:
//                cout << "Exiting program." << endl;
//                return 0;
//            default:
//                cout << "Invalid Choice" << endl;
//        }
//    }
//    return 0;
//}