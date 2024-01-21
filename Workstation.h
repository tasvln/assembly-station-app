// Name: Temitope Adebayo
// Date of completion: 2023-11-16
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {
  extern std::deque<CustomerOrder> g_pending;
  extern std::deque<CustomerOrder> g_completed;
  extern std::deque<CustomerOrder> g_incomplete;

  class Workstation : public Station {
      std::deque<CustomerOrder> m_orders = {};
      Workstation* m_pNextStation = {};
    public:
      // a one argument constructor that receives a reference to an unmodifiable std::string
      Workstation(const std::string& str);
      // a modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing
      void fill(std::ostream& os);
      //  attempts to move the order order at the front of the queue to the next station in the assembly line
      bool attemptToMoveOrder();
      // this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation
      void setNextStation(Workstation* station = nullptr);
      // this query returns the address of next Workstation
      Workstation* getNextStation() const;
      // this query inserts the name of the Item for which the current object is responsible into stream os
      void display(std::ostream& os) const;
      // moves the CustomerOrder referenced in parameter newOrder to the back of the queue
      Workstation& operator+=(CustomerOrder&& newOrder);
  };
}

#endif