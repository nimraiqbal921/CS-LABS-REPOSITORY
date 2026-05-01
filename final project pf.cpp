#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 50;  // Max students that can be added 
const string TEACHER_PASSWORD = "teach123"; // teacher's password for security 

struct Student {
    int id;            //student ids are 201 to 210 
    string name;
    double grade;
    int attendance;
};

Student students[MAX_STUDENTS]; 
int numStudents = 0; // file handling

void loadDataFromFile() {
    ifstream inFile("students.txt");
    if (inFile.is_open()) {
        numStudents = 0; 
        while (inFile >> students[numStudents].id >> students[numStudents].name >> students[numStudents].grade >> students[numStudents].attendance) {
            numStudents++;
            if (numStudents >= MAX_STUDENTS) break;
        }
        inFile.close();
        cout << "Data loaded successfully from file.\n";
    }
    else {
        cout << "No data file found. Using default values.\n";
       
        students[0] = { 201, "ali", 65.5, 70 };
        students[1] = { 202, "maya", 70.0, 83 };
        students[2] = { 203, "nida", 58.2, 65 };
        students[3] = { 204, "amir", 38.5, 33 };
        students[4] = { 205, "anaya", 32.3, 34 };
        students[5] = { 206, "fatima", 93.0, 80 };
        students[6] = { 207, "seher", 74.0, 88 };
        students[7] = { 208, "maria", 91.5, 94 };
        students[8] = { 209, "hassan", 77.8, 89 };
        students[9] = { 210, "alia", 82.5, 86 };
        numStudents = 10; 
    }
}
void saveDataToFile() {
    ofstream outFile("students.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < numStudents; i++) {//lopp to save student details in file
            outFile << students[i].id << " "
                << students[i].name << " "
                << students[i].grade << " "
                << students[i].attendance << "\n";
        }
        outFile.close();
        cout << "Data saved successfully to file.\n";
    }
    else {
        cerr << "Error: Unable to open file for saving data.\n";
    }
}

void showAllStudents() {
    cout << "\nAll Students' Grades and Attendance:\n";
    for (int i = 0; i < numStudents; i++) {
        cout << "Name: " << students[i].name
            << ", ID: " << students[i].id
            << ", Grade: " << students[i].grade
            << ", Attendance: " << students[i].attendance << "%\n";
    }
}
void addStudent() {// to add new student
    if (numStudents < MAX_STUDENTS) {
        Student newStudent;
        cout << "Enter Student ID: ";
        cin >> newStudent.id;
        cout << "Enter Student Name: ";
        cin >> newStudent.name;
        cout << "Enter Student Grade: ";
        cin >> newStudent.grade;
        cout << "Enter Student Attendance: ";
        cin >> newStudent.attendance;

        students[numStudents] = newStudent;
        numStudents++; 
        cout << "New student added successfully.\n";
    }
    else {
        cout << "Maximum number of students reached.\n";
    }
}


void updateStudentInfo() {
    int id;
    cout << "Enter the student ID to update their information: ";
    cin >> id;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            cout << "Current details for " << students[i].name << " (ID: " << students[i].id << "):\n";
            cout << "Grade: " << students[i].grade << "\n";
            cout << "Attendance: " << students[i].attendance << "%\n";
            cout << "Enter new grade: ";
            cin >> students[i].grade;
            cout << "Enter new attendance: ";
            cin >> students[i].attendance;
            cout << "Information updated successfully!\n";
            saveDataToFile(); 
            return;
        }
    }
    cout << "Student with ID " << id << " not found.\n";
}
bool authenticateTeacher() {//authentication to check if its a tecaher or another person
    string enteredPassword;
    cout << "Enter Teacher Password: ";
    cin >> enteredPassword;

    if (enteredPassword == TEACHER_PASSWORD) {
        return true;
    }
    else {
        cout << "Authentication failed. Please try again.\n";
        return false;
    }
}
void showStudentInfoById() {// shows student information
    int id;
    cout << "Enter your Student ID: ";
    cin >> id;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            cout << "\nStudent Info:\n";
            cout << "Name: " << students[i].name
                << ", Grade: " << students[i].grade
                << ", Attendance: " << students[i].attendance << "%\n";
            return;
        }
    }
    cout << "Student with ID " << id << " not found.\n";
}

int main() {
    loadDataFromFile(); 

    int mainMenuChoice;

    do {
        cout << "\nMain Menu:\n"; // main interface 
        cout << "1. Teacher's Menu\n";
        cout << "2. Student Menu\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> mainMenuChoice;

        switch (mainMenuChoice) {
        case 1: {
            if (authenticateTeacher()) {
                int teacherMenuChoice;
                do {
                    cout << "\nTeacher's Menu:\n";
                    cout << "1. Show All Students' Grades and Attendance\n";
                    cout << "2. Add a New Student\n";
                    cout << "3. Update Student Info\n";
                    cout << "4. Exit\n";
                    cout << "Choose an option: ";
                    cin >> teacherMenuChoice;

                    switch (teacherMenuChoice) {
                    case 1:
                        showAllStudents();
                        break;
                    case 2:
                        addStudent();
                        break;
                    case 3:
                        updateStudentInfo();
                        break;
                    case 4:
                        cout << "Exiting Teacher's Menu.\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (teacherMenuChoice != 4);
            }
            else {
                cout << "Access denied.\n";
            }
            break;
        }
        case 2: {
            showStudentInfoById();
            break;
        }
        case 3:
            cout << "Exiting the program.\n";
            saveDataToFile(); 
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (mainMenuChoice != 3);

    return 0;
}
