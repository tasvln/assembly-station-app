// Name: Temitope Adebayo
// Date of completion: 2023-11-16
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

using namespace std;

namespace sdds {
  std::deque<CustomerOrder> g_pending = {};
  std::deque<CustomerOrder> g_completed = {};
  std::deque<CustomerOrder> g_incomplete = {};

  Workstation::Workstation(const std::string& str) : Station(str) {}

  void Workstation::fill(std::ostream& os) {
    if (!m_orders.empty()) {
      m_orders.front().fillItem(*this, os);
    }
  }

  bool Workstation::attemptToMoveOrder() {
    // check if the order is empty
    if (m_orders.empty()) {
      return false;
    }
    // check if the order is filled
    if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
      // check if the next station is null
      if (m_pNextStation == nullptr) {
        // check if the order is filled
        if (m_orders.front().isOrderFilled()) {
          // move the order to the completed deque
          g_completed.push_back(std::move(m_orders.front()));
        }
        else {
          // move the order to the incomplete deque
          g_incomplete.push_back(std::move(m_orders.front()));
        }
      }
      else {
        // move the order to the next station
        *m_pNextStation += std::move(m_orders.front());
      }

      // remove the order from the deque
      m_orders.pop_front();
      return true;
    }

    return false;
  }

  void Workstation::setNextStation(Workstation* station) {
    m_pNextStation = station;
  }

  Workstation* Workstation::getNextStation() const {
    return m_pNextStation;
  }

  void Workstation::display(std::ostream& os) const {
    if (m_pNextStation) {
      os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
    }
    else {
      os << getItemName() << " --> " << "End of Line" << endl;
    }
  }

  Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
    // move the order to the back of the deque
    m_orders.push_back(std::move(newOrder));
    return *this;
  }
}