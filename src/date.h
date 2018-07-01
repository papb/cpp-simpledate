/**
 * SimpleDate v0.1.0
 * (c) 2018 Pedro Augusto de Paula Barbosa
 * License: MIT
 */

#ifndef SIMPLEDATE_H
#define SIMPLEDATE_H

#include <iostream>

// Dates before Oct. 1582 are inaccurate.

class Date {
    private:
        int y, m, d;
        Date(int d, int m, int y);
    public:
        Date();
        Date(std::string dateStr);
        std::string toString() const;
        Date getMonthBegin() const;
        Date getMonthEnd() const;
        Date shift(int days) const;
        static bool isValidISO8601DateStr(std::string dateStr);
        static bool lteq(Date date1, Date date2);
};

#endif