#include <iostream>
#include <vector>

using namespace std;

struct Course
{
    string name;
    int units;

    Course(string &name, int units) : name(name), units(units) {}
};

class CourseWithGrade : public Course
{
private:
    double weightedGrade = 0;

public:
    double grade;

    CourseWithGrade(string &name, int units, double grade)
        : Course(name, units), grade(grade) {}

    double getWeightedGrade()
    {
        if (weightedGrade == 0)
        {
            weightedGrade = grade * units;
        }

        return weightedGrade;
    }
};

class Student
{
private:
    double gwa;

public:
    string name;
    string section;
    vector<CourseWithGrade> courses;

    Student(string &name, string &section) : name(name), section(section) {}

    void resetCalculations()
    {
        gwa = 0;
    }

    void addCourse(CourseWithGrade course)
    {
        if (doesCourseExist(course.name))
        {
            throw runtime_error("The course, " + course.name + ", already exists.");
        }

        courses.push_back(course);
        resetCalculations();
    }

    bool doesCourseExist(string &courseName)
    {
        for (int i = 0; i < courses.size(); ++i)
        {
            if (courses[i].name == courseName)
            {
                return true;
            }
        }

        return false;
    }

    int getTotalUnits()
    {
        int sum;

        for (int i = 0; i < courses.size(); ++i)
        {
            sum += courses[i].units;
        }

        return sum;
    }

    double getGWA()
    {
        if (!gwa)
        {
            double sum;

            for (int i = 0; i < courses.size(); ++i)
            {
                sum += courses[i].getWeightedGrade();
            }

            gwa = sum / getTotalUnits();
        }

        return gwa;
    }
};