// ..................................................
// CPSC221 Lab 2: CDate lab exercise
// Copyright 2007 Hagit Schechter
// ..................................................

#include <iostream>
#include <string>
#include "CDate.h"

CDate::CDate(void) {
  m_year = m_month = m_day = 0;
}

CDate::CDate(int year, int month, int day) {
  setDate(year, month, day);
}

CDate::CDate(int year, std::string month, int day) {
  // you need to set the code here
  setDate(year, month, day);
}

bool CDate::isValidDate(int year, int month, int day) {
  // you need to fill in the code here (replace the return below)
  // and check the validity of a day, month, and year.
  return isValidDay(year, month, day);
}

bool CDate::isValidDate(int year, std::string month, int day) {
  // you need to fill in the code here (replace the return below)
  // hint it is very similar to the int month routine, but you need to
  // use monthStr2Num here
  return isValidDay(year, monthStr2Num(month), day);
}

int CDate::monthStr2Num(std::string month) {
  // you need to fill in the code here (replace the return below)
  if (month == "January") {
    return 1;
  } else if (month == "February") {
    return 2;
  } else if (month == "March") {
    return 3;
  } else if (month == "April") {
    return 4;
  } else if (month == "May") {
    return 5;
  } else if (month == "June") {
    return 6;
  } else if (month == "July") {
    return 7;
  } else if (month == "August") {
    return 8;
  } else if (month == "September") {
    return 9;
  } else if (month == "October") {
    return 10;
  } else if (month == "November") {
    return 11;
  } else if (month == "December") {
    return 12;
  } else {
    return -1;  // no valid value
  }
}

bool CDate::isValidDay(int year, int month, int day) {
  if ((day < 1) || (day > 31) || year < 0)
    return false;

  bool valid;

  switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      // you need to fill in the code here
      valid = (day <= 31);
      break;
    case 2:
      // Don't worry about this code too much.
      // It handles all the leap year rules for February.
      if ((year % 4) != 0) {
        valid = (day <= 28);
      } else if ((year % 400) == 0) {
        valid = (day <= 29);
      } else if ((year % 100) == 0) {
        valid = (day <= 28);
      } else {
        valid = (day <= 29);
      }
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      // you need to fill in the code here
      valid = (day <= 30);
      break;
    default:
      // you need to fill in the code here
      valid = false;
      break;
  }

  return valid;
}

void CDate::setDate(int year, int month, int day) {
  if (isValidDate(year, month, day)) {
    m_year = year;
    m_month = month;
    m_day = day;
  } else {
    m_year = m_month = m_day = 0;
  }
}

void CDate::setDate(int year, std::string month, int day) {
  // you need to fill in the code here
  // hint: use monthStr2Num here
  setDate(year, monthStr2Num(month), day);
}

void CDate::print(void) {
  std::cout << m_day << "/" << m_month << "/" << m_year << std::endl;
}

// main
int main(void) {
  CDate myDate0(2000, 5, 25);
  CDate myDate1(-1, "May", 25);
  CDate myDate2(2000, "April", 31);
  CDate myDate3(2001, "February", 29);
  CDate myDate4(2000, "February", 29);
  CDate myDate5(2000, "December", 32);
  CDate myDate6(2000, "December", 31);
  CDate myDate7(2000, "November", 31);
  CDate myDate8(2000, "November", 30);

  myDate0.print();
  myDate1.print();
  myDate2.print();
  myDate3.print();
  myDate4.print();
  myDate5.print();
  myDate6.print();
  myDate7.print();
  myDate8.print();

#ifdef _WIN32
  system("PAUSE");  // needed for windows
#endif

  return 0;
}
