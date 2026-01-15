#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

// --- UTILS ---
void loadingBar(string taskName) {
    cout << "\n>> " << taskName << "... \n[";
    for(int i = 0; i < 20; i++) {
        cout << "■" << flush;
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    cout << "] 100%\n";
}

// --- COLLEGE GRADING LOGIC ---

struct Course {
    string name;
    int marks;      // Input: Marks out of 100
    int credits;    // Input: Credit hours
    int gradePoint; // Calculated: 10, 9, 8, etc.
    string gradeLetter; // Calculated: O, A+, A, etc.
};

// Standard University 10-Point Grading Scale
void calculateGrade(Course &c) {
    if (c.marks >= 90) { c.gradePoint = 10; c.gradeLetter = "O"; }
    else if (c.marks >= 80) { c.gradePoint = 9; c.gradeLetter = "A+"; }
    else if (c.marks >= 70) { c.gradePoint = 8; c.gradeLetter = "A"; }
    else if (c.marks >= 60) { c.gradePoint = 7; c.gradeLetter = "B+"; }
    else if (c.marks >= 50) { c.gradePoint = 6; c.gradeLetter = "B"; }
    else if (c.marks >= 45) { c.gradePoint = 5; c.gradeLetter = "C"; }
    else if (c.marks >= 40) { c.gradePoint = 4; c.gradeLetter = "P"; }
    else { c.gradePoint = 0; c.gradeLetter = "F (Fail)"; }
}

// --- MAIN ENGINE ---

int main() {
    cout << "\n==============================================" << endl;
    cout << "   COLLEGE EXAMINATION SYSTEM (CGPA ENGINE)   " << endl;
    cout << "==============================================" << endl;
    loadingBar("LOADING GRADING STANDARDS");

    int numCourses;
    vector<Course> semester;
    float totalPoints = 0;
    int totalCredits = 0;

    cout << "\n[DATA ENTRY PROTOCOL]" << endl;
    cout << "Enter number of subjects: ";
    cin >> numCourses;

    for (int i = 0; i < numCourses; i++) {
        Course c;
        cout << "\n--- Subject " << i + 1 << " ---" << endl;
        cout << "Subject Name: "; cin >> c.name;
        cout << "Marks Obtained (out of 100): "; cin >> c.marks;
        cout << "Course Credits: "; cin >> c.credits;

        // Auto-calculate the Grade Point based on Marks
        calculateGrade(c);

        semester.push_back(c);
        
        // Formula: Sum of (GradePoint * Credits)
        if (c.gradePoint > 0) { // Only add points if not failed
            totalPoints += (c.gradePoint * c.credits);
            totalCredits += c.credits;
        }
    }

    loadingBar("GENERATING OFFICIAL MARK SHEET");

    // --- OFFICIAL TRANSCRIPT DISPLAY ---
    cout << "\n" << setfill('=') << setw(60) << "" << endl;
    cout << "           OFFICIAL SEMESTER MARK SHEET           " << endl;
    cout << setfill('=') << setw(60) << "" << endl << setfill(' ');

    cout << left << setw(15) << "SUBJECT" 
         << setw(10) << "MARKS" 
         << setw(10) << "GRADE" 
         << setw(10) << "POINT" 
         << setw(10) << "CREDITS" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (const auto& c : semester) {
        cout << left << setw(15) << c.name 
             << setw(10) << c.marks 
             << setw(10) << c.gradeLetter
             << setw(10) << c.gradePoint 
             << setw(10) << c.credits << endl;
    }

    // Final Calculation like final destination
    float sgpa = (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;

    cout << "------------------------------------------------------------" << endl;
    cout << right << setw(45) << "TOTAL CREDITS EARNED: " << totalCredits << endl;
    cout << right << setw(45) << "SEMESTER SGPA: " << fixed << setprecision(2) << sgpa << " / 10.0" << endl;
    cout << setfill('=') << setw(60) << "" << endl;
    
    // Pass/Fail Status
    if (sgpa > 0) cout << "\n>> STATUS: PROMOTED TO NEXT SEMESTER" << endl;
    else cout << "\n>> STATUS: DETAINED (Check F Grades)" << endl;

    return 0;
}