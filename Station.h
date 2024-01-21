// Name: Temitope Adebayo
// Date of completion: 2023-11-03
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>

namespace sdds {
  class Station {
      int m_id = 0;
      std::string m_name = {};
      std::string m_description = {};
      size_t m_serialNumber = {};
      size_t m_quantity = {};
    
      static size_t m_widthField;
      static size_t id_generator;
    public:
      // a one-argument constructor that receives a reference to an unmodifiable string.
      Station(const std::string& str);

      // a query function that returns the name of the current Station object
      const std::string& getItemName() const;

      // a query function that returns the next serial number to be used on the assembly line and increments m_nxtSerialNum
      size_t getNextSerialNumber();

      // a query function that returns the remaining quantity of the current Station object
      size_t getQuantity() const;

      // a modifier function that subtracts 1 from the available quantity, if the Station has available inventory
      void updateQuantity();

      // a read function that inserts information about the current object into stream os.
      void display(std::ostream& os, bool full) const;
  };
}

#endif
