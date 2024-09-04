#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

const string ansiiBlue = "\033[34m";
const string ansiiRed = "\033[31m";
const string ansiiGreen = "\033[32m";
const string ansiiReset = "\33[0m";

namespace color
{
    string generateQuestion(string message)
    {
        return ansiiBlue + message + ansiiReset;
    }

    string generateReply(string message)
    {
        return ansiiGreen + message + ansiiReset;
    }

    string generateErrorReply(string message)
    {
        return ansiiRed + message + ansiiReset;
    }
}

namespace transformString
{
    string &toLowercase(string &message)
    {
        transform(
            message.begin(),
            message.end(),
            message.begin(),
            [](unsigned char c)
            {
                return tolower(c);
            });

        return message;
    }

    string &ltrim(string &s, const char *t = " \t\n\r\f\v")
    {
        s.erase(0, s.find_first_not_of(t));

        return s;
    }

    string &rtrim(string &s, const char *t = " \t\n\r\f\v")
    {
        s.erase(s.find_last_not_of(t) + 1);

        return s;
    }

    string &trim(string &s, const char *t = " \t\n\r\f\v")
    {
        return ltrim(rtrim(s, t), t);
    }
}
