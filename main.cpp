#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// ============================================================
//                      STRUCTURE DEFINITIONS
// ============================================================

struct Student {
    string name;
    int rollNumber;
    string department;
    int semester;
    bool isActive;
    string password;
};

struct Teacher {
    string name;
    int teacherID;
    string department;
    bool isActive;
};

struct Course {
    string courseName;
    string courseCode;
    int creditHours;
    bool isActive;
};

struct Enrollment {
    int rollNumber;
    string courseCode;
    bool isEnrolled;
};

struct Attendance {
    int rollNumber;
    string courseCode;
    int totalClasses;
    int classesPresent;
};

struct Marks {
    int rollNumber;
    string courseCode;
    float marks;
    float totalMarks;
};

// ============================================================
//                      GLOBAL VARIABLES
// ============================================================

// Arrays to store data (Static allocation as per original logic)
Student students[100];
Teacher teachers[50];
Course courses[50];
Enrollment enrollments[500];
Attendance attendanceRecords[500];
Marks marksRecords[500];

// Record Counters
int studentCount = 0;
int teacherCount = 0;
int courseCount = 0;
int enrollmentCount = 0;
int attendanceCount = 0;
int marksCount = 0;

// Administrative State
string adminUsername = "admin";
string adminPassword = "admin123";
bool isAdminLoggedIn = false;
bool isStudentLoggedIn = false;
int loggedInStudentRoll = -1;

// ============================================================
//                    FUNCTION PROTOTYPES
// ============================================================

void displayMainMenu();
void processMainMenu();
void adminLogin();
void studentLogin();
void logout();

void studentManagementMenu();
void addStudent();
void viewAllStudents();
void searchStudentByRoll();
void updateStudent();
void deleteStudent();

void teacherManagementMenu();
void addTeacher();
void viewAllTeachers();
void searchTeacherByID();
void updateTeacher();

void courseManagementMenu();
void addCourse();
void viewAllCourses();
void assignCourseToStudent();
void viewStudentCourses();

void attendanceManagementMenu();
void markAttendance();
void viewAttendanceReport();
void viewStudentAttendance();

void marksManagementMenu();
void enterMarks();
void viewStudentMarks();
void viewAllResults();
void calculateResult();

void clearScreen();
void pauseScreen();
int findStudentIndex(int rollNumber);
int findTeacherIndex(int teacherID);
int findCourseIndex(string courseCode);
bool isStudentEnrolled(int rollNumber, string courseCode);
void displayHeader(string title);

// ============================================================
//                        MAIN FUNCTION
// ============================================================

int main() {
    // Initializing system with sample data for demonstration
    students[0].name = "Ali Khan";
    students[0].rollNumber = 1001;
    students[0].department = "Computer Science";
    students[0].semester = 1;
    students[0].isActive = true;
    students[0].password = "ali123";
    studentCount = 1;

    teachers[0].name = "Dr. Ahmad";
    teachers[0].teacherID = 2001;
    teachers[0].department = "Computer Science";
    teachers[0].isActive = true;
    teacherCount = 1;

    courses[0].courseName = "Introduction to Programming";
    courses[0].courseCode = "CS101";
    courses[0].creditHours = 3;
    courses[0].isActive = true;
    courseCount = 1;

    // Execution Loop
    while (true) {
        displayMainMenu();
        processMainMenu();
    }

    return 0;
}

// ============================================================
//                    CORE SYSTEM FUNCTIONS
// ============================================================

void displayHeader(string title) {
    cout << "\n\t\t________________________________________________\n";
    cout << "\t\t|                                              |\n";
    cout << "\t\t|        UNIVERSITY MANAGEMENT SYSTEM          |\n";
    cout << "\t\t|______________________________________________|\n";
    cout << "\t\t             >>> " << title << " <<<\n";
    cout << "\t\t------------------------------------------------\n";
}

void displayMainMenu() {
    clearScreen();
    displayHeader("MAIN NAVIGATION");
    
    cout << "\n\tCurrent Status: ";
    if (isAdminLoggedIn) {
        cout << "[AUTHORIZED ADMIN]\n\n";
        cout << "\t1. Student Database Management\n";
        cout << "\t2. Faculty / Teacher Records\n";
        cout << "\t3. Course Curriculum Management\n";
        cout << "\t4. Student Attendance Tracking\n";
        cout << "\t5. Examination & Marks Module\n";
        cout << "\t6. Secure Logout\n";
        cout << "\t7. Shutdown System\n";
    } else if (isStudentLoggedIn) {
        cout << "[STUDENT PORTAL - Roll: " << loggedInStudentRoll << "]\n\n";
        cout << "\t1. My Registered Courses\n";
        cout << "\t2. My Attendance History\n";
        cout << "\t3. My Academic Transcript\n";
        cout << "\t4. Secure Logout\n";
        cout << "\t5. Shutdown System\n";
    } else {
        cout << "[GUEST / NOT LOGGED IN]\n\n";
        cout << "\t1. Admin Portal Login\n";
        cout << "\t2. Student Portal Login\n";
        cout << "\t3. Exit Application\n";
    }
    cout << "\n\t------------------------------------------------\n";
}

void processMainMenu() {
    int choice;
    cout << "\n\tPlease enter your selection: ";
    if(!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    if (isAdminLoggedIn) {
        switch (choice) {
            case 1: studentManagementMenu(); break;
            case 2: teacherManagementMenu(); break;
            case 3: courseManagementMenu(); break;
            case 4: attendanceManagementMenu(); break;
            case 5: marksManagementMenu(); break;
            case 6: logout(); break;
            case 7:
                cout << "\n\tSaving changes and shutting down...\n";
                exit(0);
            default:
                cout << "\n\tInvalid selection! System requires 1-7.\n";
                pauseScreen();
        }
    } else if (isStudentLoggedIn) {
        switch (choice) {
            case 1: viewStudentCourses(); break;
            case 2: viewStudentAttendance(); break;
            case 3: viewStudentMarks(); break;
            case 4: logout(); break;
            case 5: exit(0);
            default:
                cout << "\n\tInvalid selection! System requires 1-5.\n";
                pauseScreen();
        }
    } else {
        switch (choice) {
            case 1: adminLogin(); break;
            case 2: studentLogin(); break;
            case 3: exit(0);
            default:
                cout << "\n\tInvalid selection! System requires 1-3.\n";
                pauseScreen();
        }
    }
}

// ============================================================
//                  AUTHENTICATION MODULE
// ============================================================

void adminLogin() {
    clearScreen();
    displayHeader("ADMIN AUTHENTICATION");
    
    string u, p;
    cout << "\n\tEnter Admin Username: "; cin >> u;
    cout << "\tEnter Admin Password: "; cin >> p;
    
    if (u == adminUsername && p == adminPassword) {
        isAdminLoggedIn = true;
        cout << "\n\tAccess Granted! Welcome to the Admin Dashboard.\n";
    } else {
        cout << "\n\tAccess Denied! Username or Password incorrect.\n";
    }
    pauseScreen();
}

void studentLogin() {
    clearScreen();
    displayHeader("STUDENT AUTHENTICATION");
    
    int roll;
    string pass;
    cout << "\n\tEnter Roll Number: "; cin >> roll;
    cout << "\tEnter Account Password: "; cin >> pass;
    
    int idx = findStudentIndex(roll);
    if (idx != -1 && students[idx].password == pass) {
        isStudentLoggedIn = true;
        loggedInStudentRoll = roll;
        cout << "\n\tLogin Successful! Welcome, " << students[idx].name << ".\n";
    } else {
        cout << "\n\tInvalid Roll Number or Password. Try again.\n";
    }
    pauseScreen();
}

void logout() {
    isAdminLoggedIn = false;
    isStudentLoggedIn = false;
    loggedInStudentRoll = -1;
    cout << "\n\tSession ended successfully. Returning to login screen...\n";
    pauseScreen();
}

// ============================================================
//                  STUDENT MANAGEMENT MODULE
// ============================================================

void studentManagementMenu() {
    while (true) {
        clearScreen();
        displayHeader("STUDENT DATABASE");
        cout << "\n\t1. Add New Student Record\n";
        cout << "\t2. Display All Student Records\n";
        cout << "\t3. Find Student (Roll Number Search)\n";
        cout << "\t4. Modify Existing Record\n";
        cout << "\t5. Deactivate Student Account\n";
        cout << "\t6. Return to Main Menu\n";
        
        int choice;
        cout << "\n\tEnter choice: "; cin >> choice;
        
        if (choice == 1) addStudent();
        else if (choice == 2) viewAllStudents();
        else if (choice == 3) searchStudentByRoll();
        else if (choice == 4) updateStudent();
        else if (choice == 5) deleteStudent();
        else if (choice == 6) break;
        else {
            cout << "\n\tError: Unrecognized option.\n";
            pauseScreen();
        }
    }
}

void addStudent() {
    clearScreen();
    displayHeader("ENROLL NEW STUDENT");
    
    if (studentCount >= 100) {
        cout << "\n\tDatabase Limit Reached (Max 100 students).\n";
        pauseScreen();
        return;
    }
    
    Student &s = students[studentCount];
    cout << "\n\tFull Name: "; cin.ignore(); getline(cin, s.name);
    cout << "\tAssign Roll Number: "; cin >> s.rollNumber;
    
    if (findStudentIndex(s.rollNumber) != -1) {
        cout << "\n\tConflict: Roll number already allocated to another student.\n";
        pauseScreen();
        return;
    }
    
    cout << "\tDepartment Name: "; cin.ignore(); getline(cin, s.department);
    cout << "\tAcademic Semester (1-8): "; cin >> s.semester;
    cout << "\tSet Portal Password: "; cin >> s.password;
    
    s.isActive = true;
    studentCount++;
    cout << "\n\tSuccess: New student profile created.\n";
    pauseScreen();
}

void viewAllStudents() {
    clearScreen();
    displayHeader("STUDENT DIRECTORY");
    
    cout << left << setw(12) << "Roll No" << setw(25) << "Full Name" 
         << setw(20) << "Department" << "Semester" << endl;
    cout << "------------------------------------------------------------------------\n";
    
    int active = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            cout << left << setw(12) << students[i].rollNumber 
                 << setw(25) << students[i].name 
                 << setw(20) << students[i].department 
                 << students[i].semester << endl;
            active++;
        }
    }
    
    if (active == 0) cout << "\n\tNo active student records found in the database.\n";
    cout << "\n\tTotal Count of Active Students: " << active << endl;
    pauseScreen();
}

void searchStudentByRoll() {
    clearScreen();
    displayHeader("STUDENT LOOKUP");
    
    int roll;
    cout << "\n\tEnter Roll Number to Search: "; cin >> roll;
    
    int i = findStudentIndex(roll);
    if (i == -1) {
        cout << "\n\tResult: No student found with ID " << roll << ".\n";
    } else {
        cout << "\n\tRecord Detail found:\n";
        cout << "\t------------------------------\n";
        cout << "\tName: " << students[i].name << endl;
        cout << "\tDept: " << students[i].department << endl;
        cout << "\tSem:  " << students[i].semester << endl;
        cout << "\t------------------------------\n";
    }
    pauseScreen();
}

void updateStudent() {
    clearScreen();
    displayHeader("MODIFY STUDENT DATA");
    
    int roll;
    cout << "\n\tEnter Roll Number to Update: "; cin >> roll;
    
    int i = findStudentIndex(roll);
    if (i == -1) {
        cout << "\n\tError: Subject roll number not found.\n";
    } else {
        cout << "\n\tUpdate for: " << students[i].name << endl;
        cout << "\tNew Name (use _ for spaces): "; cin.ignore(); getline(cin, students[i].name);
        cout << "\tNew Department: "; getline(cin, students[i].department);
        cout << "\tNew Semester: "; cin >> students[i].semester;
        cout << "\n\tSuccess: Student profile synchronized.\n";
    }
    pauseScreen();
}

void deleteStudent() {
    clearScreen();
    displayHeader("REMOVE STUDENT RECORD");
    
    int roll;
    cout << "\n\tEnter Roll Number to delete: "; cin >> roll;
    int i = findStudentIndex(roll);
    
    if (i != -1) {
        char confirm;
        cout << "\tWarning: Deleting " << students[i].name << ". Continue? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            students[i].isActive = false;
            cout << "\n\tStatus: Record marked as inactive.\n";
        } else {
            cout << "\n\tAborted: No changes made.\n";
        }
    } else {
        cout << "\n\tError: Identity not verified in system.\n";
    }
    pauseScreen();
}

// ============================================================
//                  TEACHER MANAGEMENT MODULE
// ============================================================

void teacherManagementMenu() {
    while (true) {
        clearScreen();
        displayHeader("FACULTY MANAGEMENT");
        cout << "\n\t1. Hire/Add Teacher\n";
        cout << "\t2. View Faculty List\n";
        cout << "\t3. Find Faculty by ID\n";
        cout << "\t4. Update Teacher Profile\n";
        cout << "\t5. Back to Main Menu\n";
        
        int choice;
        cout << "\n\tSelection: "; cin >> choice;
        
        switch (choice) {
            case 1: addTeacher(); break;
            case 2: viewAllTeachers(); break;
            case 3: searchTeacherByID(); break;
            case 4: updateTeacher(); break;
            case 5: return;
            default: cout << "\n\tInvalid Option.\n"; pauseScreen();
        }
    }
}

void addTeacher() {
    clearScreen();
    displayHeader("FACULTY REGISTRATION");
    
    if (teacherCount >= 50) {
        cout << "\n\tFaculty limit reached.\n";
        pauseScreen();
        return;
    }
    
    Teacher &t = teachers[teacherCount];
    cout << "\n\tFull Name: "; cin.ignore(); getline(cin, t.name);
    cout << "\tTeacher ID: "; cin >> t.teacherID;
    
    if (findTeacherIndex(t.teacherID) != -1) {
        cout << "\n\tConflict: ID already assigned.\n";
        pauseScreen();
        return;
    }
    
    cout << "\tDepartment: "; cin.ignore(); getline(cin, t.department);
    t.isActive = true;
    teacherCount++;
    cout << "\n\tSuccess: Faculty member added to system.\n";
    pauseScreen();
}

void viewAllTeachers() {
    clearScreen();
    displayHeader("FACULTY DIRECTORY");
    cout << left << setw(15) << "ID" << setw(30) << "Name" << "Department" << endl;
    cout << "------------------------------------------------------------------------\n";
    
    int found = 0;
    for (int i = 0; i < teacherCount; i++) {
        if (teachers[i].isActive) {
            cout << left << setw(15) << teachers[i].teacherID 
                 << setw(30) << teachers[i].name 
                 << teachers[i].department << endl;
            found++;
        }
    }
    if (found == 0) cout << "\n\tNo Faculty found.\n";
    pauseScreen();
}

void searchTeacherByID() {
    clearScreen();
    displayHeader("FACULTY SEARCH");
    int id;
    cout << "\n\tEnter Faculty ID: "; cin >> id;
    int idx = findTeacherIndex(id);
    if (idx != -1) {
        cout << "\n\tName: " << teachers[idx].name;
        cout << "\n\tDept: " << teachers[idx].department << endl;
    } else cout << "\n\tRecord Not Found.\n";
    pauseScreen();
}

void updateTeacher() {
    clearScreen();
    displayHeader("FACULTY UPDATE");
    int id;
    cout << "\n\tEnter ID: "; cin >> id;
    int idx = findTeacherIndex(id);
    if (idx != -1) {
        cout << "\tNew Name: "; cin.ignore(); getline(cin, teachers[idx].name);
        cout << "\tNew Dept: "; getline(cin, teachers[idx].department);
        cout << "\n\tProfile Synced.\n";
    } else cout << "\n\tNot found.\n";
    pauseScreen();
}

// ============================================================
//                  COURSE MANAGEMENT MODULE
// ============================================================

void courseManagementMenu() {
    while (true) {
        clearScreen();
        displayHeader("CURRICULUM CONTROL");
        cout << "\n\t1. Create New Course\n";
        cout << "\t2. View All Courses\n";
        cout << "\t3. Assign Course to Student\n";
        cout << "\t4. View Enrollments by Student\n";
        cout << "\t5. Return to Main Menu\n";
        
        int choice;
        cout << "\n\tAction: "; cin >> choice;
        
        if (choice == 1) addCourse();
        else if (choice == 2) viewAllCourses();
        else if (choice == 3) assignCourseToStudent();
        else if (choice == 4) viewStudentCourses();
        else if (choice == 5) return;
        else pauseScreen();
    }
}

void addCourse() {
    clearScreen();
    displayHeader("COURSE CREATION");
    if (courseCount >= 50) return;
    
    Course &c = courses[courseCount];
    cout << "\n\tCourse Name: "; cin.ignore(); getline(cin, c.courseName);
    cout << "\tUnique Code: "; cin >> c.courseCode;
    
    if (findCourseIndex(c.courseCode) != -1) {
        cout << "\n\tError: Code duplicate.\n";
        pauseScreen(); return;
    }
    
    cout << "\tCredit Hours: "; cin >> c.creditHours;
    c.isActive = true;
    courseCount++;
    cout << "\n\tCourse Established.\n";
    pauseScreen();
}

void viewAllCourses() {
    clearScreen();
    displayHeader("SYSTEM COURSES");
    cout << left << setw(15) << "Code" << setw(35) << "Course Name" << "Credits" << endl;
    cout << "------------------------------------------------------------------------\n";
    for (int i = 0; i < courseCount; i++) {
        if (courses[i].isActive) {
            cout << left << setw(15) << courses[i].courseCode 
                 << setw(35) << courses[i].courseName 
                 << courses[i].creditHours << endl;
        }
    }
    pauseScreen();
}

void assignCourseToStudent() {
    clearScreen();
    displayHeader("STUDENT ENROLLMENT");
    int roll;
    string code;
    cout << "\n\tEnter Student Roll: "; cin >> roll;
    cout << "\tEnter Course Code: "; cin >> code;
    
    if (findStudentIndex(roll) != -1 && findCourseIndex(code) != -1) {
        if (isStudentEnrolled(roll, code)) {
            cout << "\n\tAlready Registered.\n";
        } else {
            enrollments[enrollmentCount++] = {roll, code, true};
            cout << "\n\tEnrollment Authorized.\n";
        }
    } else cout << "\n\tValidation Failed: Roll or Code missing.\n";
    pauseScreen();
}

void viewStudentCourses() {
    clearScreen();
    displayHeader("ENROLLMENT LIST");
    int roll;
    if (isStudentLoggedIn) roll = loggedInStudentRoll;
    else { cout << "\n\tEnter Roll: "; cin >> roll; }
    
    cout << "\n\tRegistered Courses for Roll #" << roll << ":\n";
    int count = 0;
    for (int i = 0; i < enrollmentCount; i++) {
        if (enrollments[i].rollNumber == roll && enrollments[i].isEnrolled) {
            int cIdx = findCourseIndex(enrollments[i].courseCode);
            if (cIdx != -1) {
                cout << "\t- " << courses[cIdx].courseCode << ": " << courses[cIdx].courseName << endl;
                count++;
            }
        }
    }
    if (count == 0) cout << "\tNo courses found.\n";
    pauseScreen();
}

// ============================================================
//                  ATTENDANCE MANAGEMENT MODULE
// ============================================================

void attendanceManagementMenu() {
    while (true) {
        clearScreen();
        displayHeader("ATTENDANCE PORTAL");
        cout << "\n\t1. Mark Daily Attendance\n";
        cout << "\t2. Course Attendance Summary\n";
        cout << "\t3. Individual Attendance Report\n";
        cout << "\t4. Back to Main Menu\n";
        
        int choice;
        cout << "\n\tChoice: "; cin >> choice;
        if (choice == 1) markAttendance();
        else if (choice == 2) viewAttendanceReport();
        else if (choice == 3) viewStudentAttendance();
        else if (choice == 4) return;
    }
}

void markAttendance() {
    clearScreen();
    displayHeader("LOG ATTENDANCE");
    int roll; string code; char stat;
    cout << "\tRoll: "; cin >> roll;
    cout << "\tCode: "; cin >> code;
    
    if (!isStudentEnrolled(roll, code)) {
        cout << "\n\tError: Student not enrolled in " << code << endl;
        pauseScreen(); return;
    }
    
    int idx = -1;
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].rollNumber == roll && attendanceRecords[i].courseCode == code) {
            idx = i; break;
        }
    }
    
    if (idx == -1) {
        idx = attendanceCount++;
        attendanceRecords[idx] = {roll, code, 0, 0};
    }
    
    cout << "\tIs student Present? (P/A): "; cin >> stat;
    attendanceRecords[idx].totalClasses++;
    if (stat == 'P' || stat == 'p') attendanceRecords[idx].classesPresent++;
    cout << "\n\tAttendance updated successfully.\n";
    pauseScreen();
}

void viewAttendanceReport() {
    clearScreen();
    displayHeader("COURSE SUMMARY");
    string code; cout << "\n\tCourse Code: "; cin >> code;
    int cIdx = findCourseIndex(code);
    if (cIdx == -1) { cout << "\n\tInvalid Code.\n"; pauseScreen(); return; }
    
    cout << left << setw(10) << "Roll" << setw(15) << "Present" << setw(15) << "Total" << "Percentage" << endl;
    cout << "------------------------------------------------------------------------\n";
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].courseCode == code) {
            float p = (attendanceRecords[i].totalClasses > 0) ? 
                      (float)attendanceRecords[i].classesPresent / attendanceRecords[i].totalClasses * 100 : 0;
            cout << left << setw(10) << attendanceRecords[i].rollNumber 
                 << setw(15) << attendanceRecords[i].classesPresent 
                 << setw(15) << attendanceRecords[i].totalClasses << p << "%\n";
        }
    }
    pauseScreen();
}

void viewStudentAttendance() {
    clearScreen();
    displayHeader("STUDENT REPORT");
    int roll = (isStudentLoggedIn) ? loggedInStudentRoll : (cout << "\tRoll: ", cin >> roll, roll);
    
    cout << left << setw(15) << "Course" << setw(10) << "Present" << setw(10) << "Total" << "Percent" << endl;
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].rollNumber == roll) {
            float p = (attendanceRecords[i].totalClasses > 0) ? 
                      (float)attendanceRecords[i].classesPresent / attendanceRecords[i].totalClasses * 100 : 0;
            cout << left << setw(15) << attendanceRecords[i].courseCode 
                 << setw(10) << attendanceRecords[i].classesPresent 
                 << setw(10) << attendanceRecords[i].totalClasses << p << "%\n";
        }
    }
    pauseScreen();
}

// ============================================================
//                  EXAMINATION & MARKS MODULE
// ============================================================

void marksManagementMenu() {
    while (true) {
        clearScreen();
        displayHeader("EXAMINATION MODULE");
        cout << "\n\t1. Input Grade/Marks\n";
        cout << "\t2. View Student Transcript\n";
        cout << "\t3. Class Result Sheet\n";
        cout << "\t4. Final GPA/Result Card\n";
        cout << "\t5. Back to Main Menu\n";
        int choice; cout << "\n\tTask: "; cin >> choice;
        if (choice == 1) enterMarks();
        else if (choice == 2) viewStudentMarks();
        else if (choice == 3) viewAllResults();
        else if (choice == 4) calculateResult();
        else if (choice == 5) return;
    }
}

void enterMarks() {
    clearScreen();
    displayHeader("MARKING SYSTEM");
    int roll; string code;
    cout << "\tRoll: "; cin >> roll;
    cout << "\tCode: "; cin >> code;
    
    if (!isStudentEnrolled(roll, code)) {
        cout << "\tEnrollment verification failed.\n";
        pauseScreen(); return;
    }
    
    int idx = -1;
    for (int i = 0; i < marksCount; i++) {
        if (marksRecords[i].rollNumber == roll && marksRecords[i].courseCode == code) {
            idx = i; break;
        }
    }
    if (idx == -1) {
        idx = marksCount++;
        marksRecords[idx].rollNumber = roll;
        marksRecords[idx].courseCode = code;
    }
    
    cout << "\tMax Marks Available: "; cin >> marksRecords[idx].totalMarks;
    cout << "\tMarks Obtained: "; cin >> marksRecords[idx].marks;
    cout << "\n\tGrade saved.\n";
    pauseScreen();
}

void viewStudentMarks() {
    clearScreen();
    displayHeader("STUDENT TRANSCRIPT");
    int roll = (isStudentLoggedIn) ? loggedInStudentRoll : (cout << "\tRoll: ", cin >> roll, roll);
    
    float totalOb = 0, totalMax = 0;
    cout << left << setw(15) << "Course" << setw(15) << "Obtained" << "Maximum" << endl;
    for (int i = 0; i < marksCount; i++) {
        if (marksRecords[i].rollNumber == roll) {
            cout << left << setw(15) << marksRecords[i].courseCode 
                 << setw(15) << marksRecords[i].marks << marksRecords[i].totalMarks << endl;
            totalOb += marksRecords[i].marks;
            totalMax += marksRecords[i].totalMarks;
        }
    }
    if (totalMax > 0) cout << "\n\tAggregate Percentage: " << (totalOb/totalMax)*100 << "%\n";
    pauseScreen();
}

void viewAllResults() {
    clearScreen();
    displayHeader("CLASS SHEET");
    for (int s = 0; s < studentCount; s++) {
        if (!students[s].isActive) continue;
        float got = 0, tot = 0;
        for (int m = 0; m < marksCount; m++) {
            if (marksRecords[m].rollNumber == students[s].rollNumber) {
                got += marksRecords[m].marks;
                tot += marksRecords[m].totalMarks;
            }
        }
        cout << "\tRoll: " << students[s].rollNumber << " | Name: " << students[s].name;
        if (tot > 0) cout << " | Result: " << (got/tot)*100 << "%\n";
        else cout << " | Result: No records.\n";
    }
    pauseScreen();
}

void calculateResult() {
    clearScreen();
    displayHeader("OFFICIAL RESULT CARD");
    int roll; cout << "\tEnter Roll: "; cin >> roll;
    int sIdx = findStudentIndex(roll);
    if (sIdx == -1) { cout << "\tStudent not found.\n"; pauseScreen(); return; }
    
    float got = 0, tot = 0;
    for (int i = 0; i < marksCount; i++) {
        if (marksRecords[i].rollNumber == roll) {
            got += marksRecords[i].marks; tot += marksRecords[i].totalMarks;
        }
    }
    
    if (tot > 0) {
        float p = (got/tot)*100;
        cout << "\n\tName: " << students[sIdx].name;
        cout << "\n\tRoll: " << students[sIdx].rollNumber;
        cout << "\n\tPercentage: " << fixed << setprecision(2) << p << "%";
        cout << "\n\tGrade: ";
        if (p >= 80) cout << "A+";
        else if (p >= 70) cout << "A";
        else if (p >= 60) cout << "B";
        else if (p >= 50) cout << "C";
        else cout << "F";
        cout << "\n\tResult: " << ((p >= 50) ? "PASS" : "FAIL") << endl;
    } else cout << "\n\tAcademic data insufficient for calculation.\n";
    pauseScreen();
}

// ============================================================
//                  SYSTEM UTILITIES
// ============================================================

void clearScreen() {
    // Simple vertical scroll for console spacing
    for (int i = 0; i < 40; i++) cout << endl;
}

void pauseScreen() {
    cout << "\n\tSystem Idle. Press Enter to return...";
    cin.ignore(100, '\n');
    cin.get();
}

int findStudentIndex(int rollNumber) {
    for (int i = 0; i < studentCount; i++)
        if (students[i].rollNumber == rollNumber && students[i].isActive) return i;
    return -1;
}

int findTeacherIndex(int teacherID) {
    for (int i = 0; i < teacherCount; i++)
        if (teachers[i].teacherID == teacherID && teachers[i].isActive) return i;
    return -1;
}

int findCourseIndex(string courseCode) {
    for (int i = 0; i < courseCount; i++)
        if (courses[i].courseCode == courseCode && courses[i].isActive) return i;
    return -1;
}

bool isStudentEnrolled(int rollNumber, string courseCode) {
    for (int i = 0; i < enrollmentCount; i++)
        if (enrollments[i].rollNumber == rollNumber && 
            enrollments[i].courseCode == courseCode && 
            enrollments[i].isEnrolled) return true;
    return false;
}