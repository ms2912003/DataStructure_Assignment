#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono> // For timing

using namespace std;
using namespace std::chrono;

class Student {
public:
    string name;
    int id;
    double gpa;

    // Constructor to initialize
    Student(string name = "", int id = 0, double gpa = 0.0) : name(name), id(id), gpa(gpa) {}
    //overload for name
    bool operator<(const Student& other) const {
        return name < other.name;
    }
    //overload for gpa
    bool operator>(const Student& other) const {
        return gpa > other.gpa;
    }
};

void mergeByName(vector<Student>& students, int left, int mid, int right, int& comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Student> leftHalf(students.begin() + left, students.begin() + mid + 1);
    vector<Student> rightHalf(students.begin() + mid + 1, students.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        comparisons++; // Counting comparison here
        if (leftHalf[i].name <= rightHalf[j].name) {
            students[k++] = leftHalf[i++];
        } else {
            students[k++] = rightHalf[j++];
        }
    }

    while (i < n1) {
        students[k++] = leftHalf[i++];
    }

    while (j < n2) {
        students[k++] = rightHalf[j++];
    }
}


void mergeSortByName(vector<Student>& students, int left, int right, int& comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByName(students, left, mid, comparisons);
        mergeSortByName(students, mid + 1, right, comparisons);
        mergeByName(students, left, mid, right, comparisons);
    }
}

void mergeByGPA(vector<Student>& students, int left, int mid, int right, int& comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Student> leftHalf(students.begin() + left, students.begin() + mid + 1);
    vector<Student> rightHalf(students.begin() + mid + 1, students.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        comparisons++;
        if (leftHalf[i].gpa <= rightHalf[j].gpa) {
            students[k++] = leftHalf[i++];
        } else {
            students[k++] = rightHalf[j++];
        }
    }

    while (i < n1) {
        students[k++] = leftHalf[i++];
    }

    while (j < n2) {
        students[k++] = rightHalf[j++];
    }
}

void mergeSortByGPA(vector<Student>& students, int left, int right, int& comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByGPA(students, left, mid, comparisons);
        mergeSortByGPA(students, mid + 1, right, comparisons);
        mergeByGPA(students, left, mid, right, comparisons);
    }
}

// Function to read student data
vector<Student> readStudentData(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return students;
    }

    int numStudents;
    file >> numStudents; // Read the number of students
    file.ignore(); // Ignore the newline
    //read from file according to data type
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

// Function to write student data to file with additional information
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

    // Sort students by name using merge sort
    int comparisonsByName = 0;
    auto sortByNameStart = high_resolution_clock::now();
    mergeSortByName(students, 0, students.size() - 1, comparisonsByName);
    auto sortByNameStop = high_resolution_clock::now();
    auto sortByNameDuration = duration_cast<duration<double>>(sortByNameStop - sortByNameStart).count() * 1000; // Convert to milliseconds

    cout << "Sorted data by name:\n";
    for (const auto& student : students) {
        cout << student.name << " " << student.id << " " << student.gpa << endl;
    }
    cout << "Number of comparisons (by name): " << comparisonsByName << endl;
    cout << endl;

    // Write sorted data by name to file
    writeStudentData("SortedByName.txt", "Merge Sort", comparisonsByName,
                     sortByNameDuration, students);

    // Sort students by GPA in descending order using merge sort
    int comparisonsByGPA = 0;
    auto sortByGPAStart = high_resolution_clock::now();
    mergeSortByGPA(students, 0, students.size() - 1, comparisonsByGPA);
    auto sortByGPAStop = high_resolution_clock::now();
    auto sortByGPADuration = duration_cast<duration<double>>(sortByGPAStop - sortByGPAStart).count() * 1000; // Convert to milliseconds

    cout << "Sorted data by GPA:\n";
    for (const auto& student : students) {
        cout << student.name << " " << student.id << " " << student.gpa << endl;
    }
    cout << "Number of comparisons (by GPA): " << comparisonsByGPA << endl;
    cout << endl;

    // Write sorted data by GPA to file
    writeStudentData("SortedByGPA.txt", "Merge Sort", comparisonsByGPA,
                     sortByGPADuration, students);

    return 0;
}
