#include "integer_base.h"
#include <stdexcept>
#include <vector>

integer_base::integer_base(int num, unsigned base)
    : m_base(base), m_sign(num >= 0 ? POSITIVE : NEGATIVE) {
  if (base > 36)
    throw std::invalid_argument("Base is too big.");
  initialize_digits(abs(num));
}

// digits are in reverse order
void integer_base::initialize_digits(int num) {
  m_digits.clear();
  while (num > 0) {
    m_digits.push_back(static_cast<unsigned>(num) % 10);
    num /= 10;
  }
  if (m_digits.size() == 0) {
    m_digits.push_back(0);
  }
}

unsigned integer_base::base() const { return m_base; }

bool integer_base::abs_greater(const integer_base &first,
                               const integer_base &second) const {
  if (first.m_digits.size() > second.m_digits.size()) {
    return true;
  } else if (first.m_digits.size() < second.m_digits.size()) {
    return false;
  }

  // digits are in reverse order
  for (int i = static_cast<int>(first.m_digits.size()) - 1; i >= 0; i--) {
    if (first.m_digits[static_cast<unsigned>(i)] >
        second.m_digits[static_cast<unsigned>(i)])
      return true;
    else if (first.m_digits[static_cast<unsigned>(i)] <
             second.m_digits[static_cast<unsigned>(i)])
      return false;
  }
  // case x==y

  return true;
}

void integer_base::abs_add(const integer_base &greater,
                           const integer_base &smaller,
                           integer_base &new_num) const {
  unsigned base = new_num.m_base = greater.m_base;
  unsigned carry = 0;
  unsigned num_digits_smaller = static_cast<unsigned>(smaller.m_digits.size());
  unsigned num_digits_greater = static_cast<unsigned>(greater.m_digits.size());

  for (unsigned i = 0; i < num_digits_greater; i++) {
    unsigned digit = greater.m_digits[i] +
                     (num_digits_smaller > i ? smaller.m_digits[i] : 0) + carry;
    if (digit >= m_base) {
      carry = 1;
      digit -= base;
    } else {
      carry = 0;
    }
    new_num.m_digits.push_back(digit);
  }
  if (carry > 0)
    new_num.m_digits.push_back(carry);
  while (new_num.m_digits.front() == 0)
    new_num.m_digits.erase(new_num.m_digits.begin());
}

void integer_base::abs_subt(const integer_base &greater,
                            const integer_base &smaller,
                            integer_base &new_num) const {
  unsigned base = new_num.m_base = greater.m_base;
  unsigned borrow = 0;
  unsigned num_digits_smaller = static_cast<unsigned>(smaller.m_digits.size());
  unsigned num_digits_greater = static_cast<unsigned>(greater.m_digits.size());

  for (unsigned i = 0; i < num_digits_greater; i++) {
    int digit =
        static_cast<int>(greater.m_digits[i]) -
        static_cast<int>(num_digits_smaller > i ? smaller.m_digits[i] : 0) -
        static_cast<int>(borrow);
    if (digit < 0) {
      borrow = 1;
      digit += base;
    } else {
      borrow = 0;
    }
    new_num.m_digits.push_back(static_cast<unsigned>(digit));
  }
  // deletion of leading 0's
  while (new_num.m_digits.size() > 1 && new_num.m_digits.back() == 0)
    new_num.m_digits.pop_back();
}

int integer_base::sign() const { return m_sign; }

integer_base integer_base::operator+(const integer_base &other) const {
  if (base() != other.base())
    throw std::invalid_argument("The bases are different!");
  integer_base new_num;

  if (sign() == other.sign()) {
    if (abs_greater(*this, other)) {
      abs_add(*this, other, new_num);
    } else {
      abs_add(other, *this, new_num);
    }
  } else if (abs_greater(*this, other)) {
    // if their signs are not the same,subtract them
    abs_subt(*this, other, new_num);

  } else {
    abs_subt(other, *this, new_num);
  }
  new_num.m_sign = sign() < 0 ? NEGATIVE : POSITIVE;
  return new_num;
}

integer_base integer_base::operator-(const integer_base &other) const {
  if (base() != other.base()) {
    throw std::invalid_argument("The bases are different!");
  }

  integer_base new_num;

  if (sign() != other.sign()) {
    if (abs_greater(*this, other)) {
      abs_add(*this, other, new_num);
    } else {
      abs_add(other, *this, new_num);
    }
    new_num.m_sign = sign() > 0 ? POSITIVE : NEGATIVE;
  } else if (abs_greater(*this, other)) {
    abs_subt(*this, other, new_num);
    new_num.m_sign = sign() > 0 ? POSITIVE : NEGATIVE;
  } else {
    abs_subt(other, *this, new_num);
    new_num.m_sign = sign() > 0 ? POSITIVE : NEGATIVE;
  }
  return new_num;
}

integer_base integer_base::operator*(const integer_base &other) const {
  if (base() != other.base())
    throw std::invalid_argument("The bases are different!");

  integer_base new_num;
  new_num.m_base = m_base;
  new_num.m_sign = POSITIVE;

  for (int i = static_cast<int>(m_digits.size()) - 1; i >= 0; i--) {
    new_num.m_digits.insert(new_num.m_digits.begin(), 0);

    integer_base step;
    step.m_base = m_base;
    step.m_sign = POSITIVE;

    abs_multiply_by_digit(other, m_digits[static_cast<unsigned>(i)], step);
    new_num = new_num + step;
  }
  new_num.m_sign = sign() == other.sign() ? POSITIVE : NEGATIVE;
  return new_num;
}

bool integer_base::operator==(const integer_base &other) const {
  if (base() != other.base())
    std::cout << "The bases are different,but in decimal: " << std::endl;
  if (sign() != other.sign())
    return false;
  int num1 = *this->convert_to_decimal();
  int num2 = *this->convert_to_decimal();
  return num1 == num2;
}

integer_base integer_base::operator/(const integer_base &other) const {

  int num1 = *this->convert_to_decimal();

  std::cout << "num1:" << num1;
  int num2 = *this->convert_to_decimal();
  std::cout << " num2:" << num2 << std::endl;
  int new_num_decimal = num1 / num2;
  integer_base new_num(new_num_decimal, this->base());

  return new_num;
}

std::ostream &operator<<(std::ostream &out, const integer_base &num) {
  if (num.sign() < 0)
    out << '-';
  for (int i = (static_cast<int>(num.m_digits.size()) - 1); i >= 0; i--)
    out << num.m_digits[static_cast<unsigned>(i)];
  return out;
}

std::optional<int> integer_base::convert_to_decimal() const {
  if (m_digits.size() > std::numeric_limits<int>::max()) {
    return {};
  }

  int new_num =
      std::accumulate(m_digits.cbegin(), m_digits.cend(), 0,
                      [](int acc, auto current) { return 10 * acc + current; });
  return m_sign * new_num;
}

std::optional<integer_base> integer_base::from_array(std::string &string_num,
                                                     unsigned base) {
  integer_base new_num;
  new_num.m_digits.resize(string_num.length());

  std::transform(string_num.begin(), string_num.end(), string_num.begin(),
                 toupper);

  std::transform(string_num.cbegin(), string_num.cend(),
                 new_num.m_digits.begin(), [](char c) {
                   return c >= '0' && c <= '9'
                              ? c - '0'
                              : c >= 'A' && c <= 'Z' ? c - 'A' + 10 : -1;
                 });
  auto invalid_digit =
      std::find_if(new_num.m_digits.cbegin(), new_num.m_digits.cend(),
                   [base](auto digit) { return digit >= base; });
  if (invalid_digit != new_num.m_digits.cend()) {
    return {};
  }
  return std::move(new_num);
}
