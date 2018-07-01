/**
 * SimpleDate v0.1.0
 * (c) 2018 Pedro Augusto de Paula Barbosa
 * License: MIT
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <regex>
#include "date.h"

// ---------------------------- HELPER FUNCTIONS ---------------------------- //

bool testRegex(std::string str, std::string regexString) {
    std::regex regex(regexString, std::regex_constants::ECMAScript);
    return std::regex_search(str, regex);
}

std::string leftPadZeros(int number, int amount) {
    std::string fixedStr = std::to_string(number);
    while (fixedStr.length() < amount) {
        std::ostringstream oss;
        oss << "0" << fixedStr;
        fixedStr = oss.str();
    }
    return fixedStr;
}

// https://stackoverflow.com/a/10467633/4135063
std::string getTodayString() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return buf;
}

typedef struct PseudoDate {
    int y;
    int m;
    int d;
} PseudoDate;

long pseudoDateToLong(PseudoDate pd) {
    // https://stackoverflow.com/a/2344365/4135063
    // https://alcor.concordia.ca//~gpkatch/gdate-algorithm.html
    // Dates before Oct. 1582 are inaccurate.
    long m = (pd.m + 9) % 12;
    long y = pd.y - m/10;
    return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (pd.d - 1);
}

PseudoDate longToPseudoDate(long daysCount) {
    // https://stackoverflow.com/a/2344365/4135063
    // https://alcor.concordia.ca//~gpkatch/gdate-algorithm.html
    // Dates before Oct. 1582 are inaccurate.
    int y = (10000*daysCount + 14780)/3652425;
    long _d = daysCount - (365*y + y/4 - y/100 + y/400);
    if (_d < 0) {
        y--;
        _d = daysCount - (365*y + y/4 - y/100 + y/400);
    }
    long m_ = (100*_d + 52)/3060;
    int m = (m_ + 2)%12 + 1;
    y = y + (m_ + 2)/12;
    int d = _d - (m_*306 + 5)/10 + 1;

    PseudoDate pd;
    pd.d = d;
    pd.m = m;
    pd.y = y;
    return pd;
}

bool isPseudoDateValid(PseudoDate pd) {
    PseudoDate converted = longToPseudoDate(pseudoDateToLong(pd));
    return pd.d == converted.d && pd.m == converted.m && pd.y == converted.y;
}

bool Date::isValidISO8601DateStr(std::string dateStr) {
    if (!testRegex(dateStr, "^\\d{4}-\\d{2}-\\d{2}$")) return false;

    PseudoDate pd;
    pd.d = std::stoi(dateStr.substr(8, 2));
    pd.m = std::stoi(dateStr.substr(5, 2));
    pd.y = std::stoi(dateStr.substr(0, 4));

    return isPseudoDateValid(pd);
}

// -------------------------------------------------------------------------- //

Date::Date(int y, int m, int d) : y(y), m(m), d(d) {}

Date::Date() : Date(getTodayString()) {}

Date::Date(std::string dateStr) {
    if (!Date::isValidISO8601DateStr(dateStr)) {
        throw std::logic_error("Invalid date string.");
    }
    this->y = std::stoi(dateStr.substr(0, 4));
    this->m = std::stoi(dateStr.substr(5, 2));
    this->d = std::stoi(dateStr.substr(8, 2));
}

Date Date::getMonthBegin() const {
    return Date(this->y, this->m, 1);
}

Date Date::getMonthEnd() const {
    int d = 31;
    if (this->m == 4 || this->m == 6 || this->m == 9 || this->m == 11) d = 30;
    if (this->m == 2) {
        d = 28;

        // Attempt to use d = 29
        PseudoDate pd;
        pd.d = 29;
        pd.m = this->m;
        pd.y = this->y;
        if (isPseudoDateValid(pd)) d = 29;
    }
    return Date(this->y, this->m, d);
}

Date Date::shift(int days) const {
    PseudoDate pd;
    pd.y = this->y;
    pd.m = this->m;
    pd.d = this->d;
    pd = longToPseudoDate(pseudoDateToLong(pd) + days);
    return Date(pd.y, pd.m, pd.d);
}

std::string Date::toString() const {
    std::string yearStr = leftPadZeros(this->y, 4);
    std::string monthStr = leftPadZeros(this->m, 2);
    std::string dayStr = leftPadZeros(this->d, 2);
    std::ostringstream oss;
    oss << yearStr << "-" << monthStr << "-" << dayStr;
    return oss.str();
}

bool Date::lteq(Date date1, Date date2) {
    return date1.toString() <= date2.toString();
}