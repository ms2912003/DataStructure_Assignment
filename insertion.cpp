
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <sys/timeb.h>

using namespace std;
using namespace std::chrono;

class Student {
public:
    string name;
    int id;
    double gpa;

    Student(string n = "", int i = 0, double g = 0.0) : name(n), id(i), gpa(g) {}

    bool operator<(const Student& other) const {
        return name < other.name;
    }

    bool operator>(const Student& other) const {
        return gpa > other.gpa;
    }
};

template<class T>
void insertionSort(T data[], int n, bool compare(const T&, const T&), int& comparisons) {
    for (int i = 1; i < n; i++) {
        T tmp = data[i];
        int j = i;
        while (j > 0 && compare(tmp, data[j - 1])) {
            comparisons++;
            data[j] = data[j - 1];
            j--;
        }
        data[j] = tmp;
    }
}
vector<Student> readStudentData(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return students;
    }

    int numStudents;
    file >> numStudents;
    file.ignore();

    for (int i = 0; i < numStudents; ++i) {
        string name;
        getline(file, name);
        int id;
        file >> id;
        double gpa;
        file >> gpa;
        file.ignore();
        students.push_back(Student(name, id, gpa));
    }

    file.close();
    return students;
}
bool compareByName(const Student& a, const Student& b) {
    return a < b;
}

bool compareByGPA(const Student& a, const Student& b) {
    return a.gpa < b.gpa;
}

void writeStudentData(const string& filename, const string& algorithmName, int comparisons, double runningTime, const vector<Student>& students) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Algorithm: " << algorithmName << endl;
        file << "Number of comparisons: " << comparisons << endl;
        file << "Running time: " << runningTime << " milliseconds" << endl;
        file << "Sorted Student Elements:\n";
        for (const auto& student : students) {
            file << student.name << " " << student.id << " " << student.gpa << endl;
        }
        file.close();
        cout << "Sorted data written to " << filename << endl;
    } else {
        cerr << "Failed to open " << filename << " for writing." << endl;
    }
}

long timecost(void (*dosomething)()) {
    struct timeb begin, end;
    long cost;
    ftime(&begin);
    dosomething();
    ftime(&end);
    cost = (long)(end.time - begin.time) * 1000 + (end.millitm - begin.millitm);
    return cost;
}

int main() {
    vector<Student> students = readStudentData("students.txt");

    if (students.empty()) {
        cerr << "No student data found or unable to read from file." << endl;
        return 1;
    }

    cout << "Student data read from file:\n";
    for (const auto& student : students) {
        cout << student.name << " " << student.id << " " << student.gpa << endl;
    }
    cout << endl;

    int comparisonsByName = 0;
    auto sortByNameStart = high_resolution_clock::now();
    insertionSort(students.data(), students.size(), compareByName, comparisonsByName);
    auto sortByNameStop = high_resolution_clock::now();
    auto sortByNameDuration = duration_cast<duration<double>>(sortByNameStop - sortByNameStart).count() * 1000; // Convert to milliseconds

    cout << "Sorted data by name:\n";
    for (const auto& student : students) {
        cout << student.name << " " << student.id << " " << student.gpa << endl;
    }
    cout << endl;

    writeStudentData("SortedByName.txt", "Insertion Sort", comparisonsByName,
                     sortByNameDuration, students);

    int comparisonsByGPA = 0;
    auto sortByGPAStart = high_resolution_clock::now();
    insertionSort(students.data(), students.size(), compareByGPA, comparisonsByGPA);
    auto sortByGPAStop = high_resolution_clock::now();
    auto sortByGPADuration = duration_cast<duration<double>>(sortByGPAStop - sortByGPAStart).count() * 1000; // Convert to milliseconds

    cout << "Sorted data by GPA:\n";
    for (const auto& student : students) {
        cout << student.name << " " << student.id << " " << student.gpa << endl;
    }
    cout << endl;

    writeStudentData("SortedByGPA.txt", "Insertion Sort", comparisonsByGPA,
                     sortByGPADuration, students);

    return 0;
}
