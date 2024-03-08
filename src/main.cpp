#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string, std::vector;

vector<string> getStudentCourses();
void checkTransferRequirements(const string& school,
                               const string& major,
                               const vector<string>& courses);

int main()
{
    std::cout << "Student Counseler Service:\n";

    vector<string> courses = getStudentCourses();

    string school;
    std::cout << "Please enter your transfer school of choice: ";
    std::cin >> school;

    string major;
    std::cout << "Please enter your major: ";
    std::cin >> major;

    checkTransferRequirements(school, major, courses);

    return 0;
}

vector<string> getStudentCourses()
{
    vector<string> courses;
    std::cout << "Enter your enrolled and future courses: ";

    string allCourses;
    std::getline(std::cin, allCourses);
    std::stringstream coursesInput(allCourses);

    string course;
    while (coursesInput >> course) {
        courses.push_back(course);
    }

    return courses;
}
void checkTransferRequirements(const string& school,
                               const string& major,
                               const vector<string>& courses)
{
    std::ifstream transferDataFile("../res/transfer_data.txt");

    string currentLine;
    string currentSchool;
    string currentMajor;
    string currentCourse;
    std::stringstream lineParser;
    while (std::getline(transferDataFile, currentLine)) {
        lineParser.str(currentLine);

        lineParser >> currentSchool;
        if (currentSchool != school) {
            break;
        }

        lineParser >> currentMajor;
        if (currentMajor != major) {
            break;
        }

        bool isValidTransfer = true;

        // Get all of the required courses listed for the university and major
        while (lineParser >> currentCourse) {
            auto foundPos =
                std::find(courses.cbegin(), courses.cend(), currentCourse);

            // Check whether the needed course is in the student's courses
            if (foundPos == courses.cend()) {
                isValidTransfer = false;
                std::cout << "ERROR: you require " << currentCourse
                          << " to transfer as a " << currentMajor << " to "
                          << currentSchool << '\n';
            }
        }

        if (isValidTransfer) {
            std::cout << "Your chosen courses meet all of the requirements to "
                         "transfer as a "
                      << currentMajor << " to " << currentSchool << '\n';
        }

        // Successfully checked the course list, function is done
        return;
    }

    std::cout << "ERROR: your selection to transfer as a " << currentMajor
              << " to " << currentSchool << "does not exist in the database!\n";
}
