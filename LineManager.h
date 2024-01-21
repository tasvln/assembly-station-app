// Name: Temitope Adebayo
// Date of completion: 2023-11-16
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <iostream>
#include <vector>
#include "Workstation.h"

namespace sdds {
  class LineManager {
    std::vector<Workstation*> m_activeLine = {};
    size_t m_cntCustomerOrder = 0;
    Workstation* m_firstStation = {};
  public:
    // a two argument constructor that receives the name of the file that identifies the active stations on the assembly line
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
    // a modifier reorders the workstations present in the instance variable m_activeLine
    void reorderStations();
    // a modifier performs one iteration of operations on all of the workstations in the current assembly line
    bool run(std::ostream& os);
    // a query displays all active stations on the assembly line in their current order
    void display(std::ostream& os) const;
  };
}

#endif