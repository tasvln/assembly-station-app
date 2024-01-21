// Name: Temitope Adebayo
// Date of completion: 2023-11-03
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

namespace sdds {
  char Utilities::m_delimiter = {};

  void Utilities::setFieldWidth(size_t newWidth) {
    m_widthField = newWidth;
  }

  size_t Utilities::getFieldWidth() const {
    return m_widthField;
  }

  std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
    std::string token;
    size_t currPos = str.find(m_delimiter, next_pos);

    if (currPos == next_pos) {
      more = false;
      throw "Delimiter found at next_pos";
    }
    else if (currPos == std::string::npos) {
      more = false;
    }

    // Extract token
    token = str.substr(next_pos, currPos - next_pos);

    // Update width field
    if (m_widthField < token.length()) {
      m_widthField = token.length();
    }

    // Update the next_pos for the next token
    next_pos = currPos + 1;

    // Trim spaces from the beginning and end of the token
    token = trim(token);

    return token;
  }

  void Utilities::setDelimiter(char newDelimiter) {
    if (newDelimiter != '\0') {
      m_delimiter = newDelimiter;
    }
  }

  char Utilities::getDelimiter() {
    return m_delimiter;
  }

  std::string Utilities::trim(const std::string& str) {
    std::string tempStr = str;
    // remove leading spaces
    while (tempStr[0] == ' ') {
      tempStr.erase(0, 1);
    }

    // remove trailing spaces
    while (tempStr[tempStr.length() - 1] == ' ') {
      tempStr.erase(tempStr.length() - 1, 1);
    }

    return tempStr;
  }
}