// Name: Temitope Adebayo
// Date of completion: 2023-11-03
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>

namespace sdds {
  class Utilities {
      size_t m_widthField = 1;
      
      static char m_delimiter;
    public:
      // a function that sets the field width of the current object to the value of the parameter
      void setFieldWidth(size_t newWidth);

      // a function that returns the field width of the current object
      size_t getFieldWidth() const;

      // a function that extracts tokens from the first parameter
      std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

      // a class function that sets the delimiter for this class to the character received
      static void setDelimiter(char newDelimiter);

      // a class function that returns the delimiter character of the current class
      static char getDelimiter();

      // remove spaces from the beginning and end of a string
      std::string trim(const std::string& str);
  };
}

#endif
