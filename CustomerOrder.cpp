// Name: Temitope Adebayo
// Date of completion: 2023-11-03
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"
#include <iomanip>
#include <vector>

using namespace std;

namespace sdds {
  size_t CustomerOrder::m_widthField = 0;

  CustomerOrder::CustomerOrder(const CustomerOrder& src) {
    throw "copy constructor is not allowed";
  }

  CustomerOrder::CustomerOrder(const string& str) {
    Utilities util{};
    size_t next_pos = 0;
    bool more = true;

    // temporary vector to store items
    vector<Item*> temp;

    // extract name and product
    m_name = util.extractToken(str, next_pos, more);
    m_product = util.extractToken(str, next_pos, more);

    // update the widthField
    if (m_widthField < util.getFieldWidth()) {
      m_widthField = util.getFieldWidth();
    }

    // loop through the string to extract each item, push each item into the vector
    while (more) {
      temp.push_back(new Item(util.extractToken(str, next_pos, more)));
    }

    // update the m_cntItem to the size of the vector
    m_cntItem = temp.size();

    // allocate memory for m_lstItem
    m_lstItem = new Item * [m_cntItem];

    // copy the items from the vector to m_lstItem
    for (size_t i = 0; i < m_cntItem; i++) {
      m_lstItem[i] = temp[i];
    }
  }

  CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
    *this = std::move(src);
  }

  CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
    // check for self-assignment
    if (this != &src) {
      for (size_t i = 0; i < m_cntItem; i++) {
        delete m_lstItem[i];
      }
      delete[] m_lstItem;

      // shallow copy
      m_name = src.m_name;
      m_product = src.m_product;
      m_cntItem = src.m_cntItem;
      m_lstItem = src.m_lstItem;

      // empty the source object
      src.m_name = "";
      src.m_product = "";
      src.m_cntItem = 0;
      src.m_lstItem = nullptr;
    }
    return *this;
  }

  CustomerOrder::~CustomerOrder() {
    // deallocate memory of each item
    for (size_t i = 0; i < m_cntItem; i++) {
      delete m_lstItem[i];
    }
    delete[] m_lstItem;
  }

  bool CustomerOrder::isOrderFilled() const {
    bool filled = true;

    // loop through the items to check if they are filled
    for (size_t i = 0; i < m_cntItem; i++) {
      if (!m_lstItem[i]->m_isFilled) {
        filled = false;
      }
    }
    return filled;
  }

  bool CustomerOrder::isItemFilled(const string& itemName) const {
    bool filled = true;

    // loop through the items to check if the item matches the parameter and if it is filled
    for (size_t i = 0; i < m_cntItem; i++) {
      if (m_lstItem[i]->m_itemName == itemName) {
        if (!m_lstItem[i]->m_isFilled) {
          filled = false;
        }
      }
    }
    return filled;
  }

  void CustomerOrder::fillItem(Station& station, ostream& os) {
    bool isFilled = false;

    // loop through the list of items
    for (size_t i = 0; i < m_cntItem; i++) {
      // check if the item matches the parameter and if it is filled
      if (m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isFilled == isFilled) {
        if (station.getQuantity() > 0) {
          // update the item
          station.updateQuantity();
          // update the item's serial number and filled status
          m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
          // update the item's filled status
          m_lstItem[i]->m_isFilled = true;
          isFilled = true;
          // display message
          os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
        }
        else {
          os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
        }
      }
    }
  }

  void CustomerOrder::display(ostream& os) const {
    os << m_name << " - " << m_product << endl;
    for (size_t i = 0; i < m_cntItem; i++) {
      os << "[" << right << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
      os << left << setw(m_widthField - 1) << setfill(' ') << m_lstItem[i]->m_itemName << "- ";
      if (m_lstItem[i]->m_isFilled) {
        os << "FILLED" << endl;
      }
      else {
        os << "TO BE FILLED" << endl;
      }
    }
  }
}