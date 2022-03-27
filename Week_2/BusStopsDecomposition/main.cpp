#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>

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
    if (!q.stops.empty()) {
        q.stops.clear();
    }
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
  // хранит список автобусов, проезжающих через заданную остановку и название остановки
  string stop;
  vector <string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    //вывести через пробел список автобусов, если остановки нет - вывести No stop
    if (!r.buses.empty()) {
        for (const auto& bus : r.buses) {
            os << bus << " ";
        }
    } else {
        os << "No stop";
    }
    return os;
}

bool operator == (const BusesForStopResponse& r1, const BusesForStopResponse& r2) {
    return (r1.stop == r2.stop && r1.buses == r2.buses);
}

struct StopsForBusResponse {
  // Наполните полями эту структуру
  string bus;
  vector <BusesForStopResponse> buses_for_stop; //вектор всех остановок маршрута со списком автобусов для каждой остановки
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    //вывести описание всех остановок маршрута bus
    if (r.bus.empty()) {
        os << "No bus";
    } else {
        for (const auto& item : r.buses_for_stop) {
            os << "Stop " << item.stop << ": ";
            if (item.buses.size() == 1 && item.buses[0] == r.bus) {
                os << "no interchange";
            } else {
                for (const auto& current_bus : item.buses) {
                    if (current_bus != r.bus) {
                        os << current_bus << " ";
                    }
                }
            }
            os << endl;
        }
    }
  return os;
}


struct AllBusesResponse {
     map <string, vector <string>> all_busses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
  //если нет автобусов вывести No buses
    if (r.all_busses.empty()) {
        os << "No buses";
    } else {
        for (const auto& [key, value] : r.all_busses) {
            //key - автобус, value - список остановок
            os << "Bus " << key << ": ";
            for (const auto& current_stop : value) {
                os << current_stop << " ";
            }
            os << endl;
        }
    }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
      //метод добавления нового маршрута в словари
      //добавить новый ключ bus со значениями stops в bus_to_stops
      bus_to_stops[bus] = stops;
      //последовательно добавить новые ключи из вектора stops в словарь stop_to_buses со значением bus
      for (const auto& stop : stops) {
              stop_to_buses[stop].push_back(bus);
      }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
      BusesForStopResponse r;
      r.stop = stop;
      if (stop_to_buses.count(stop)) {
         r.buses = stop_to_buses.at(stop);
      }
      return r;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse r;

    if (bus_to_stops.count(bus)) { //если словарь автобус - остановки имеет такой автобус
        r.bus = bus;
        //получить список остановок этого автобуса и проитерироваться по нему
        for (const auto& stop : bus_to_stops.at(bus)) {
            //для каждой остановки получаем GetBusesForStop и добавляем в конец вектора
            r.buses_for_stop.push_back(GetBusesForStop(stop));
        }
    }
    return r;
  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse r;
    if (!bus_to_stops.empty()) {
        r.all_busses = bus_to_stops;
    }
    return r;
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
