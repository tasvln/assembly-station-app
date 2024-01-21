// Name: Temitope Adebayo
// Date of completion: 2023-11-03
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
  size_t Station::m_widthField = 0;
  size_t Station::id_generator = 0;

  Station::Station(const std::string& str) {
    size_t next_pos = 0;
    bool more = true;

    Utilities util{};

    // extract tokens from the string
    m_id = ++id_generator;
    m_name = util.extractToken(str, next_pos, more);
    m_serialNumber = std::stoi(util.extractToken(str, next_pos, more));
    m_quantity = std::stoi(util.extractToken(str, next_pos, more));

    // Update width fields before extracting the description
    if (m_widthField < util.getFieldWidth()) {
      m_widthField = util.getFieldWidth();
    }

    m_description = util.extractToken(str, next_pos, more);
  }

  const std::string& Station::getItemName() const {
    return m_name;
  }

  size_t Station::getNextSerialNumber() {
    return m_serialNumber++;
  }

  size_t Station::getQuantity() const {
    return m_quantity;
  }

  void Station::updateQuantity() {
    // should not go below 0, so check first
    if (m_quantity >= 0) {
      --m_quantity;
    }
  }

  void Station::display(std::ostream& os, bool full) const {
    os << right << setfill('0') << setw(3) << m_id << " | ";
    os << left << setfill(' ') << setw(m_widthField) << m_name << "| ";
    os << right << setfill('0') << setw(6) << m_serialNumber << " | ";

    if (full) {
        os << right << setfill(' ') << setw(4) << m_quantity << " | " << left << m_description;
    }
    os << std::endl;
  }
}