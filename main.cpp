#include <iostream>
#include <limits>

#include "./utils.h"
#include "./school.h"

using namespace std;

bool askConfirm()
{
    string isCorrectResponse;

    while (true)
    {
        askString(isCorrectResponse, "Is this correct? (y/n) ", 3);

        toLowercase(isCorrectResponse);

        bool isNotCorrect = isCorrectResponse == "n" || isCorrectResponse == "no";
        bool isCorrect = isCorrectResponse == "y" || isCorrectResponse == "yes";

        if (isNotCorrect)
        {
            cout << generateReply("Alright... Restarting...") << endl;

            return false;
        }

        if (isCorrect)
        {
            return true;
        }

        cout << generateErrorReply("Please respond with 'y', 'yes', 'n', or 'no'");
        cout << endl;
    }
}

void askDemographics(string &name, string &section)
{
    askString(name, "What is your name? ", 50);
    cout << generateReply("Welcome, " + name) << endl;

    askString(section, "What is your section? ", 20);
    cout << generateReply("You are " + name + " from " + section + ".") << endl;

    if (!askConfirm())
    {
        return askDemographics(name, section);
    }
}

void askCourseInfo(string &courseCode, double &grade, int &units, int currIdx, Student *student)
{
    string courseNumberStr = to_string(currIdx + 1);

    askString(courseCode, "Enter course code " + courseNumberStr + ": ", 10);

    if (student->doesCourseExist(courseCode))
    {
        cerr << generateErrorReply("The course " + courseCode + " already exists.") << endl;
        return askCourseInfo(courseCode, grade, units, currIdx, student);
    }

    askDouble(grade, "Enter course grade " + courseNumberStr + ": ", 100.0);
    askInt(units, "Enter course unit " + courseNumberStr + ": ", 10);

    cout
        << generateReply("You have a grade of " + to_string(grade) + " for the course, " + courseCode + ", with " + to_string(units) + " unit/s.")
        << endl;

    if (!askConfirm())
    {
        return askCourseInfo(courseCode, grade, units, currIdx, student);
    }

    cout
        << generateReply("Awesome! Let's move on.")
        << endl;
}

void addCoursesToStudent(Student &student)
{
    int totalCourses;

    askInt(totalCourses, "How many courses do you have (1-6)? ", 6);
    cout << generateReply("You have a total of: " + to_string(totalCourses) + " course/s.") << endl;

    if (!askConfirm())
    {
        return addCoursesToStudent(student);
    }

    cout
        << generateReply("Great! Please fill out the information for all " + to_string(totalCourses) + " courses.")
        << endl;

    for (int i = 0; i < totalCourses; ++i)
    {
        string courseCode;
        int units;
        double grade;

        askCourseInfo(courseCode, grade, units, i, &student);

        student.addCourse(
            CourseWithGrade(
                courseCode,
                units,
                grade));
    }
}

void handleSIGINT(int signal)
{
    cerr << endl
         << generateErrorReply("Program abruptly interrupted... Exiting.");

    exit(0);
}

int main()
{
    signal(SIGINT, handleSIGINT);

    string name, section;

    try
    {
        askDemographics(name, section);

        Student student(name, section);

        addCoursesToStudent(student);

        cout
            << generateReply("Thank you for filling out all the necessary details.")
            << endl;
        cout << endl;
        cout
            << generateReply("Below is a table of your courses with your respective grades and your GWA.")
            << endl
            << endl;

        cout
            << ("Name: " + student.name)
            << (", Section: " + student.section)
            << endl
            << endl;

        int maxCourseNameLength;

        for (int i = 0; i < student.courses.size(); ++i)
        {
            int courseNameLength = student.courses[i].name.length();

            if (courseNameLength > maxCourseNameLength)
            {
                maxCourseNameLength = courseNameLength;
            }
        }

        const string COURSES_TITLE = "COURSES";
        const string UNITS_TITLE = "Units";
        const string GRADES_TITLE = "Grade";

        cout << COURSES_TITLE;

        // Max is 10
        const int MAX_UNIT_VALUE_LENGTH = 2;

        int courseTitleLengthDiff = maxCourseNameLength - COURSES_TITLE.length();
        int unitsTitleLengthDiff = UNITS_TITLE.length() - MAX_UNIT_VALUE_LENGTH;
        bool isMaxCourseNameLengthLessThanCourseTitleLength = maxCourseNameLength < COURSES_TITLE.length();

        if (!isMaxCourseNameLengthLessThanCourseTitleLength)
        {
            for (int i = 0; i < courseTitleLengthDiff; ++i)
            {
                cout << " ";
            }
        }

        cout
            << " | "
            << UNITS_TITLE
            << " | "
            << GRADES_TITLE
            << endl;

        for (int i = 0; i < student.courses.size(); ++i)
        {
            string *courseName = &student.courses[i].name;
            int *units = &student.courses[i].units;
            double *grade = &student.courses[i].grade;

            cout << *courseName;

            if (
                (isMaxCourseNameLengthLessThanCourseTitleLength &&
                 (courseName->length() < COURSES_TITLE.length())) ||
                (!isMaxCourseNameLengthLessThanCourseTitleLength &&
                 (courseName->length() < maxCourseNameLength)))
            {
                int courseNameLengthDiff;

                if (isMaxCourseNameLengthLessThanCourseTitleLength)
                {
                    courseNameLengthDiff = COURSES_TITLE.length() - courseName->length();
                }
                else
                {
                    courseNameLengthDiff = maxCourseNameLength - courseName->length();
                }

                for (int j = 0; j < courseNameLengthDiff; ++j)
                {
                    cout << " ";
                }
            }

            cout << " | "
                 << *units;

            for (int j = 0; j < unitsTitleLengthDiff; ++j)
            {
                cout << " ";
            }

            cout << "  | "
                 << *grade
                 << endl;
        }

        cout << endl
             << "General Weighted Average (GWA) = "
             << student.getGWA();
    }
    catch (const runtime_error &e)
    {
        string err = e.what();

        if (err != "eof")
        {
            cerr << endl
                 << generateErrorReply(err);
        }
    }

    return 0;
}
