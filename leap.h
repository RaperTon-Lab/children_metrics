#if !defined(LEAP_H)
#define LEAP_H

namespace leap
{
    bool is_leap_year(int year)
    {
        bool flag = false;
        if ((year % 4 == 0) && (year % 100 != 0))
            flag = true;
        else if (year % 400 == 0)
            flag = true;
        else
            flag = false;
        return flag;
    }

} // namespace leap

#endif // LEAP_H