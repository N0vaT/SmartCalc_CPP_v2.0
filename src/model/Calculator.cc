#include "Calculator.h"

namespace s21 {
Calculator::Calculator() noexcept : first(0), second(0), x(0) {}
Calculator::Calculator(const Calculator& other)
    : first(other.first),
      second(other.second),
      stackNumber(other.stackNumber),
      x(other.x) {}
Calculator::Calculator(Calculator&& other) noexcept : Calculator() {
  std::swap(first, other.first);
  std::swap(second, other.second);
  std::swap(stackNumber, other.stackNumber);
  std::swap(x, other.x);
}
Calculator& Calculator::operator=(const Calculator& other) {
  if (this != &other) {
    first = other.first;
    second = other.second;
    stackNumber = other.stackNumber;
    x = other.x;
  }
  return *this;
}

Calculator& Calculator::operator=(Calculator&& other) {
  if (this != &other) {
    first = std::move(other.first);
    second = std::move(other.second);
    stackNumber = std::move(other.stackNumber);
    x = std::move(other.x);
  }
  return *this;
}

double Calculator::calculate(const std::string& input_string) {
  const char* str = input_string.c_str();
  double num = 0;
  while (str && *str != '\0') {
    if (*str >= '0' && *str <= '9') {
      int n = 0;
      sscanf(str, "%lf%n", &num, &n);
      stackNumber.push(num);
      str = str + n - 1;
    } else if (*str == 'x') {
      stackNumber.push(x);
    } else if (*str == '~') {
      if (stackNumber.empty()) {
        throw std::runtime_error("Input Error");
      } else {
        double value = stackNumber.top();
        stackNumber.pop();
        stackNumber.push(value * -1);
      }
    } else {
      execute(*str);
    }
    str++;
  }
  if (!stackNumber.empty()) {
    num = stackNumber.top();
    stackNumber.pop();
  } else {
    throw std::runtime_error("Input Error");
  }
  if (!stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  }
  return num;
}

void Calculator::execute(char ch) {
  if (ch == 'c') {
    execute_cos();
  } else if (ch == 's') {
    execute_sin();
  } else if (ch == 't') {
    execute_tan();
  } else if (ch == 'C') {
    execute_acos();
  } else if (ch == 'S') {
    execute_asin();
  } else if (ch == 'T') {
    execute_atan();
  } else if (ch == 'l') {
    execute_log();
  } else if (ch == 'L') {
    execute_log10();
  } else if (ch == 'q') {
    execute_sqrt();
  } else if (ch == '+') {
    execute_plus();
  } else if (ch == '-') {
    execute_minus();
  } else if (ch == '*') {
    execute_mul();
  } else if (ch == '/') {
    execute_div();
  } else if (ch == '%') {
    execute_mod();
  } else if (ch == '^') {
    execute_pow();
  } else if (ch == ' ') {
  } else {
    throw std::runtime_error("Input Error");
  }
}

void Calculator::execute_cos() {
  if (stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  } else {
    first = stackNumber.top();
    stackNumber.pop();
    stackNumber.push(cos(first));
  }
}

void Calculator::execute_sin() {
  if (stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  } else {
    first = stackNumber.top();
    stackNumber.pop();
    stackNumber.push(sin(first));
  }
}

void Calculator::execute_tan() {
  if (stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  } else {
    first = stackNumber.top();
    stackNumber.pop();
    stackNumber.push(tan(first));
  }
}

void Calculator::execute_acos() {
  if (stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  } else {
    first = stackNumber.top();
    stackNumber.pop();
    stackNumber.push(acos(first));
  }
}

void Calculator::execute_asin() {
  if (stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  } else {
    first = stackNumber.top();
    stackNumber.pop();
    stackNumber.push(asin(first));
  }
}

void Calculator::execute_atan() {
  if (stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  } else {
    first = stackNumber.top();
    stackNumber.pop();
    stackNumber.push(atan(first));
  }
}

void Calculator::execute_log() {
  if (stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  } else {
    first = stackNumber.top();
    stackNumber.pop();
    stackNumber.push(log(first));
  }
}

void Calculator::execute_log10() {
  if (stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  } else {
    first = stackNumber.top();
    stackNumber.pop();
    stackNumber.push(log10(first));
  }
}

void Calculator::execute_sqrt() {
  if (stackNumber.empty()) {
    throw std::runtime_error("Input Error");
  } else {
    first = stackNumber.top();
    stackNumber.pop();
    stackNumber.push(sqrt(first));
  }
}

void Calculator::execute_plus() {
  if (!stackNumber.empty()) {
    first = stackNumber.top();
    stackNumber.pop();
    if (!stackNumber.empty()) {
      second = stackNumber.top();
      stackNumber.pop();
      stackNumber.push(first + second);
    } else {
      throw std::runtime_error("Input Error");
    }
  } else {
    throw std::runtime_error("Input Error");
  }
}

void Calculator::execute_minus() {
  if (!stackNumber.empty()) {
    first = stackNumber.top();
    stackNumber.pop();
    if (!stackNumber.empty()) {
      second = stackNumber.top();
      stackNumber.pop();
      stackNumber.push(second - first);
    } else {
      throw std::runtime_error("Input Error");
    }
  } else {
    throw std::runtime_error("Input Error");
  }
}

void Calculator::execute_mul() {
  if (!stackNumber.empty()) {
    first = stackNumber.top();
    stackNumber.pop();
    if (!stackNumber.empty()) {
      second = stackNumber.top();
      stackNumber.pop();
      stackNumber.push(second * first);
    } else {
      throw std::runtime_error("Input Error");
    }
  } else {
    throw std::runtime_error("Input Error");
  }
}

void Calculator::execute_div() {
  if (!stackNumber.empty()) {
    first = stackNumber.top();
    stackNumber.pop();
    if (!stackNumber.empty()) {
      second = stackNumber.top();
      stackNumber.pop();
      stackNumber.push(second / first);
    } else {
      throw std::runtime_error("Input Error");
    }
  } else {
    throw std::runtime_error("Input Error");
  }
}

void Calculator::execute_mod() {
  if (!stackNumber.empty()) {
    first = stackNumber.top();
    stackNumber.pop();
    if (!stackNumber.empty()) {
      second = stackNumber.top();
      stackNumber.pop();
      stackNumber.push(fmod(second, first));
    } else {
      throw std::runtime_error("Input Error");
    }
  } else {
    throw std::runtime_error("Input Error");
  }
}

void Calculator::execute_pow() {
  if (!stackNumber.empty()) {
    first = stackNumber.top();
    stackNumber.pop();
    if (!stackNumber.empty()) {
      second = stackNumber.top();
      stackNumber.pop();
      stackNumber.push(pow(second, first));
    } else {
      throw std::runtime_error("Input Error");
    }
  } else {
    throw std::runtime_error("Input Error");
  }
}

void Calculator::setX(double x) { this->x = x; }

}  // namespace s21