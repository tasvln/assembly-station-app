// Name: Temitope Adebayo
// Date of completion: 2023-11-22
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
  LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
    std::ifstream fs(file);
    if (fs.is_open()) {
      string line;
      Utilities util;

      while (getline(fs, line)) {
        size_t pos = 0;
        bool more = true;
        string token;
        string nextToken;

        Workstation* currentStation = nullptr;
        Workstation* nextStation = nullptr;

        // extract the first token
        token = util.extractToken(line, pos, more);

        if (more) {
          nextToken = util.extractToken(line, pos, more);
        }

        // find the station with the same name as the token using std::find_if
        auto it = std::find_if(stations.begin(), stations.end(), [=](Workstation* station) {
          return station->getItemName() == token;
        });

        if (it != stations.end()) {
          currentStation = *it;
        }

        // find the station with the same name as the nextToken using std::find_if
        if (!nextToken.empty()) {
          auto nextIt = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
            return station->getItemName() == nextToken;
          });

          if (nextIt != stations.end()) {
            nextStation = *nextIt;
            // set the next station for the current station
            currentStation->setNextStation(nextStation);
          }
        }

        // add the current station to the active line
        m_activeLine.push_back(currentStation);
      }

      // find the first station in the active line
      auto it = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station1) {
        return std::all_of(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* station2) {
          return !(station2->getNextStation() != nullptr && station1->getItemName() == station2->getNextStation()->getItemName());
        });
      });

      if (it != m_activeLine.end()) {
        m_firstStation = *it;
      }

      // update the count of customer orders
      m_cntCustomerOrder = g_pending.size();
    } else {
      throw std::string("Unable to open file");
    }

    fs.close();
  }

  void LineManager::reorderStations() {
    std::vector<Workstation*> temp = {};

    Workstation* currentStation = m_firstStation;

    // loop through the active line and push each station into the vector
    while (currentStation != nullptr) {
      temp.push_back(currentStation);
      currentStation = currentStation->getNextStation();
    }

    m_activeLine = temp;
  }

  bool LineManager::run(std::ostream& os) {
    static size_t count = 1;
    os << "Line Manager Iteration: " << count << endl;

    // check if there are any pending orders
    if (!g_pending.empty()) {
      // move the pending order to the first station
      *m_firstStation += std::move(g_pending.front());
      // remove the order from the pending queue
      g_pending.pop_front();
    }

    // loop through the active line and fill each station
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
      station->fill(os);
    });

    // loop through the active line and attempt to move each order
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
      station->attemptToMoveOrder();
    });

    // increment the count
    count++;

    // return true if all the orders have been filled
    return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
  }

  void LineManager::display(std::ostream& os) const {
    // loop through the active line and display each station
    for (auto station : m_activeLine) {
      station->display(os);
    }
  }
}