#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};


double GetDiscriminant(double a, double b, double c) {
    return (b * b) - (4 * a * c);
}

int GetLinearRootCount(double b, double c) {
    if (b == 0) {
        throw invalid_argument("division by zero");
    } else {
        return 1;
    }
}

double GetFirstRoot(double a, double b, double D) {
    return ((b * -1) + sqrt(D)) / (2 * a);
}

double GetSecondRoot(double a, double b, double D) {
    return ((b * -1) - sqrt(D)) / (2 * a);
}

int GetSquareRootCount(double a, double b, double c) {
    double D = GetDiscriminant(a, b, c);

    if (D >= 0) {
        if (GetFirstRoot(a, b, D) != GetSecondRoot(a, b, D)) {
            return 2;
        } else {
            return 1;
        }
    }

    return 0;
}

int GetDistinctRealRootCount(double a, double b, double c) {
    //функция возвращает количество уникальных действительных корней квадратного уровнения уравнения
    if (a == 0) {
        try {
            return GetLinearRootCount(b, c);
        } catch (invalid_argument i) {
            cout << i.what();
        }
    } else {
        return GetSquareRootCount(a, b, c);
    }
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  return 0;
}
