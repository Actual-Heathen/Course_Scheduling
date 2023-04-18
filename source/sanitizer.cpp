#include <string>
#include <sanitizer.h>

bool isValidDay(std::string s)
{
    if (s == "MW" || s == "TR")
    {
        return true;
    }
    
    return false;
}

bool isValidTime(std::string s)
{
    if (s == "8:00 AM")
    {
        return true;
    }
    else if (s == "9:40 AM")
    {
        return true;
    }
    else if (s == "11:20 AM")
    {
        return true;
    }
    else if (s == "1:00 PM")
    {
        return true;
    }
    else if (s == "2:40 PM")
    {
        return true;
    }
    else if (s == "4:20 PM")
    {
        return true;
    }
    else if (s == "6:00 PM")
    {
        return true;
    }

    return false;
}

static bool isInt(std::string s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}