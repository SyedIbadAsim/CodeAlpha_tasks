#include <iostream>
#include <vector>
using namespace std;


double Gradepoint(char grade) {
    switch (grade) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default: return 0.0;
    }
}

int main() {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    vector<int> credits(numCourses);
    vector<char> grades(numCourses);
    double totalCredits = 0.0, totalGradePoints = 0.0;

    for (int i = 0; i < numCourses; ++i) {
        cout << "\nCourse " << i + 1 << ":\n";
        cout << "  - Credits: ";
        cin >> credits[i];
        cout << "  - Grade (A, B, C, D, F): ";
        cin >> grades[i];

        double gradePoint = gradeToPoint(grades[i]);
        totalCredits += credits[i];
        totalGradePoints += credits[i] * gradePoint;
    }

    double CGPA = (totalCredits > 0) ? totalGradePoints / totalCredits : 0.0;


    cout << "\n+-----------------------------+\n";
    cout << "| Total Credits:     " << totalCredits << "      |\n";
    cout << "| Total Grade Points: " << totalGradePoints << "    |\n";
    cout << "| CGPA:              " << CGPA << "    |\n";
    cout << "+-----------------------------+\n";

    return 0;
}
