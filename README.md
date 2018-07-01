# SimpleDate

A simple library to handle dates in C++.

## Quick start

The default constructor gives the current date:

```c++
Date date; // Date now
```

A constructor receiving an [ISO8601 string](https://en.wikipedia.org/wiki/ISO_8601) is also available:

```c++
Date date("2016-02-29");
```

Attempting to construct invalid dates will throw `std::logic_error`:

```c++
Date date("2016-02-29"); // Works
Date date("2017-02-29"); // Throws std::logic_error
Date date("qwerty"); // Throws std::logic_error
```

Check if a string is a valid date:

```
Date::isValidISO8601DateStr("2016-02-29"); // true
Date::isValidISO8601DateStr("2017-02-29"); // false
Date::isValidISO8601DateStr("qwerty"); // false
```

Shift a date by any number of days:

```c++
Date date("2016-02-29");
Date shifted1 = date.shift(10); // Gives "2016-03-10"
Date shifted2 = date.shift(-10); // Gives "2016-02-19"
// Note: the original object is unchanged
```

Obtain the beginning and end of the month of a given date:

```c++
Date date("2016-02-15");
Date monthBegin = date.getMonthBegin(); // Gives "2016-02-01"
Date monthEnd = date.getMonthEnd(); // Gives "2016-02-29"
```

Convert a Date to string with the `toString()` method:

std::cout << date.toString() << "\n";

Check if a date is less-than-or-equal-to another date (i.e. is the same or older):

```c++
Date date1("2016-10-10");
Date date2("2017-01-27");
bool b = Date::lteq(date1, date2); // true
```

## Development

Extra functionalities might be added in the future. I agree that more methods should be available.

## License

MIT © Pedro Augusto de Paula Barbosa