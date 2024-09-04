#include <iostream>
#include <string>
#include <sstream>

#include "./formatting.h"

using namespace std;
using namespace color;
using namespace transformString;

void clearInput()
{
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void getStringInput(string &input)
{
    string tmp;

    getline(cin, tmp);

    if (cin.fail() && !cin.eof())
    {
        clearInput();
        throw runtime_error("Something went wrong.");
    }

    if (cin.eof())
    {
        throw runtime_error("eof");
    }

    if (tmp.length() == 0)
    {
        throw runtime_error("Input cannot be empty");
    }

    input = tmp;
}

void getLimitedStringInput(string &input, int inputLimit)
{
    string tmp;

    getline(cin, tmp);

    if (cin.fail() && !cin.eof())
    {
        clearInput();
        throw runtime_error("Something went wrong.");
    }

    if (cin.eof())
    {
        throw runtime_error("eof");
    }

    trim(tmp);

    if (tmp.length() > inputLimit)
    {
        throw runtime_error("Character length can only be up to " + to_string(inputLimit));
    }

    if (tmp.length() == 0)
    {
        throw runtime_error("Input cannot be empty.");
    }

    input = tmp;
}

void getIntWithLimit(int &input, int inputLimit)
{
    string tmpInput;
    int tmp;

    getline(cin, tmpInput);

    if (cin.fail() && !cin.eof())
    {
        clearInput();
        throw runtime_error("Only integer values are allowed.");
    }

    if (cin.eof())
    {
        throw runtime_error("eof");
    }

    istringstream iss(tmpInput);

    if (iss >> tmp)
    {
        if (iss.eof())
        {
            if (tmp <= 0)
            {
                throw runtime_error("Value must be > 0.");
            }

            if (tmp > inputLimit)
            {
                throw runtime_error("Integer value cannot exceed " + to_string(inputLimit));
            }

            input = tmp;
        }
        else
        {
            throw runtime_error("Only integer values are allowed.");
        }
    }
    else
    {
        throw runtime_error("Only integer values are allowed.");
    }
}

void getDoubleWithLimit(double &input, double inputLimit)
{
    string tmpInput;
    double tmp;

    getline(cin, tmpInput);

    if (cin.fail() && !cin.eof())
    {
        clearInput();
        throw runtime_error("Only `double` number values are allowed.");
    }

    if (cin.eof())
    {
        throw runtime_error("eof");
    }

    istringstream iss(tmpInput);

    if (iss >> tmp)
    {
        if (iss.eof())
        {
            if (tmp <= 0)
            {
                throw runtime_error("Value must be > 0.");
            }

            if (tmp > inputLimit)
            {
                throw runtime_error("`Double` number value cannot exceed " + to_string(inputLimit));
            }

            input = tmp;
        }
        else
        {
            throw runtime_error("Only `double` number values are allowed.");
        }
    }
    else
    {
        throw runtime_error("Only `double` number values are allowed.");
    }
}

void askDouble(double &input, string question, double inputLimit)
{
    try
    {
        cout << generateQuestion(question);
        getDoubleWithLimit(input, inputLimit);
    }
    catch (const runtime_error &e)
    {
        string err = e.what();

        if (err != "eof")
        {
            cerr << generateErrorReply(err) << endl;

            return askDouble(input, question, inputLimit);
        }

        throw e;
    }
}

void askInt(int &input, string question, int inputLimit)
{
    try
    {
        cout << generateQuestion(question);
        getIntWithLimit(input, inputLimit);
    }
    catch (const runtime_error &e)
    {
        string err = e.what();

        if (err != "eof")
        {
            cerr << generateErrorReply(err) << endl;

            return askInt(input, question, inputLimit);
        }

        throw e;
    }
}

void askString(string &input, string question, int inputLimit)
{
    try
    {
        cout << generateQuestion(question);
        getLimitedStringInput(input, inputLimit);
    }
    catch (const runtime_error &e)
    {
        string err = e.what();

        if (err != "eof")
        {
            cerr << generateErrorReply(err) << endl;

            return askString(input, question, inputLimit);
        }

        throw e;
    }
}
