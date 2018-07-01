/**
 * SimpleDate v0.1.0
 * (c) 2018 Pedro Augusto de Paula Barbosa
 * License: MIT
 */

#include <iostream>
#include "./../src/date.h"

void test() {
    Date date1;
    std::cout << "Date now: " << date1.toString() << "\n";

    Date date2("2016-02-29");
    Date shifted1 = date2.shift(10); // Gives "2016-03-10"
    Date shifted2 = date2.shift(-10); // Gives "2016-02-19"
    std::cout << date2.toString() << "\n";
    std::cout << shifted1.toString() << "\n";
    std::cout << shifted2.toString() << "\n";

    Date date3("2016-02-15");
    Date monthBegin = date3.getMonthBegin(); // Gives "2016-02-01"
    Date monthEnd = date3.getMonthEnd(); // Gives "2016-02-29"
    std::cout << date3.toString() << "\n";
    std::cout << monthBegin.toString() << "\n";
    std::cout << monthEnd.toString() << "\n";

    Date date4("2016-10-10");
    Date date5("2017-01-27");
    bool b = Date::lteq(date4, date5); // true
    std::cout << b << "\n";
}

int main(int argc, char **argv) {
    try {
        test();
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}