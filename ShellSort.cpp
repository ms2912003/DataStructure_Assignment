#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Student {
public:
    string name;
    string id;
    double gpa;

    Student(string n = "", string i = "", double g = 0.0) : name(n), id(i), gpa(g) {}

    // Overloaded operator for comparing students by name
    bool operator<(const Student& other) const {
        return name < other.name;
    }

    // Overloaded operator for comparing students by GPA
    bool operator>(const Student& other) const {
        return gpa > other.gpa;
    }
};

// Shell sort function with comparison and time measurement
template<typename T, typename Compare>
pair<int, double> shellSort(T arr[], int n, Compare comp)
{
    int comparisons = 0;
    auto start = high_resolution_clock::now();

    // Start with a big gap, halve it every iteration
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        for (int i = gap; i < n; i += 1) {
            // Save arr[i] in temp and make a hole at position i
            T temp = arr[i];
            // Shift earlier gap-sorted elements up until the correct
            // location for arr[i] is found (Insertion sort)
            int j;
            for (j = i; j >= gap && comp(arr[j - gap], temp); j -= gap) {
                arr[j] = arr[j - gap];
                comparisons++;
            }
            // Put temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double time_taken = duration.count() / 1000.0; // Convert to milliseconds

    return make_pair(comparisons, time_taken);
}

// Function to read student data from file
vector<Student> readStudentData(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return students;
    }
    int numStudents;
    file >> numStudents; // Read the number of students
    file.ignore(); // Ignore the newline character

    for (int i = 0; i < numStudents; ++i) {
        string name;
        getline(file, name); // Read student name
        string id;
        getline(file, id); // Read student ID
        double gpa;
        file >> gpa; // Read student GPA
        file.ignore(); // Ignore the newline character
        students.push_back(Student(name, id, gpa));
    }

    file.close(); // Close the file
    return students;
}

void writeStudentData(const string& filename, const vector<Student>& students, const string& algorithmName, int comparisons, double timeTaken) {
    ofstream file(filename);
    if (file.is_open()) {
        // Write algorithm name, number of comparisons, running time, and sorted student elements
        file << "Algorithm Name: " << algorithmName << "\n";
        file << "Number of Comparisons: " << comparisons << "\n";
        file << "Running Time : " << timeTaken << " milliseconds" << "\n";
        file << "Sorted Student Elements:\n";
        for (const auto& student : students) {
            file << student.name << "\n" << student.id << "\n" << student.gpa << "\n";
        }
        file.close();
        cout << "Sorted data written to " << filename << endl;
    } else {
        cerr << "Failed to open " << filename << " for writing." << endl;
    }
}

int main() {
    vector<Student> students = readStudentData("students.txt");

    // Sort students by name using shell sort and measure comparisons and time
    auto [nameComparisons, nameTime] = shellSort(students.data(), students.size(), [](const Student& a, const Student& b) {
        return a.name > b.name;
    });
    writeStudentData("SortedByName.txt", students, "Shell Sort by Name", nameComparisons, nameTime);

    // Sort students by GPA using shell sort and measure comparisons and time
    auto [gpaComparisons, gpaTime] = shellSort(students.data(), students.size(), [](const Student& a, const Student& b) {
        return a.gpa < b.gpa;
    });
    writeStudentData("SortedByGPA.txt", students, "Shell Sort by GPA", gpaComparisons, gpaTime);

    return 0;
}
