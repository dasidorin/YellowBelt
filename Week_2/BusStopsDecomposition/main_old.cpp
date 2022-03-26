#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

void InputNewBus(istream& is, Query& q) {
    q.type = QueryType::NewBus;
    is >> q.bus;
    size_t stop_count = 0;
    is >> stop_count;
    for (size_t i = 0; i < stop_count; ++i) {
        string current_stop;
        is >> current_stop;
        q.stops.push_back(current_stop);
    }
}

void InputBusesForStop(istream& is, Query& q) {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
}

void InputStopsForBus(istream& is, Query& q) {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
}

void InputAllBuses(istream& is, Query& q) {
    q.type = QueryType::AllBuses;
}

istream& operator >> (istream& is, Query& q) {
  string query_type;
  is >> query_type;
  if (query_type == "NEW_BUS") {
      InputNewBus(is, q);
  } else if (query_type == "BUSES_FOR_STOP") {
      InputBusesForStop(is, q);
  } else if (query_type == "STOPS_FOR_BUS") {
      InputStopsForBus(is, q);
  } else if (query_type == "ALL_BUSES") {
      InputAllBuses(is, q);
  }
  return is;
}

struct BusesForStopResponse {
    string stop;
    vector <string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.stop.empty()) {
        os << "No stop";
    } else {
        for (const auto& bus : r.buses) {
            os << bus << " ";
        }
    }
  return os;
}

struct StopsForBusResponse {
    string bus;
    vector <BusesForStopResponse> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    return os;
}

struct AllBusesResponse {
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
      bus_to_stops[bus] = stops;
      for (const auto& stop : stops) {
          stop_to_buses[stop].push_back(bus);
      }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
      return BusesForStopResponse {stop, stop_to_buses.at(stop)};
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
      StopsForBusResponse r;
      r.bus = bus;
      for (const auto& current_stop : bus_to_stops.at(bus)) {
          r.stops.push_back(GetBusesForStop(current_stop));
      }
      return r;
  }

  AllBusesResponse GetAllBuses() const {
  }

private:
    map <string, vector <string>> bus_to_stops;
    map <string, vector <string>> stop_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
