// Name: Temitope Adebayo
// Date of completion: 2023-11-03
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
  // a struct that manages a single item on the customer order
  struct Item
  {
    std::string m_itemName{};
    size_t m_serialNumber{0};
    bool m_isFilled{false};

    Item(const std::string& src) : m_itemName(src) {};
  };

  // a class that manages a customer order
  class CustomerOrder {
    std::string m_name{};
    std::string m_product{};
    size_t m_cntItem{};
    Item** m_lstItem{};

    static size_t m_widthField;
  public:
    // default constructor
    CustomerOrder(){};

    // a one-argument constructor that receives a reference to an unmodifiable string
    CustomerOrder(const std::string&);

    // copy constructor
    CustomerOrder(const CustomerOrder& src);
    // delete copy assignment operator
    CustomerOrder& operator=(const CustomerOrder&) = delete;

    // move constructor and move assignment operator that doesn't throw exceptions
    CustomerOrder(CustomerOrder&& src) noexcept;
    CustomerOrder& operator=(CustomerOrder&& src) noexcept;

    // a destructor
    ~CustomerOrder();

    // this function returns true if all the items in the order have been filled, otherwise false
    bool isOrderFilled() const;
    // this function returns true if all items specified by itemName have been filled. If the item 
    // doesn't exist in the order, this query returns true
    bool isItemFilled(const std::string& itemName) const;
    // this modifier fills one item in the current order that the Station specified in the first parameter handles
    void fillItem(Station& station, std::ostream& os);
    // this query displays the state of the current object in the format
    void display(std::ostream& os) const;
  };
}

#endif