#ifndef INTEGER_BASE_H
#define INTEGER_BASE_H
#include "function_declarations.h"
#include <optional>

class integer_base : public equality<integer_base> {
public:
  integer_base(int num = 0, unsigned base = 10);

  integer_base operator+(const integer_base &other) const;

  integer_base operator-(const integer_base &other) const;

  integer_base operator*(const integer_base &other) const;

  integer_base operator/(const integer_base &other) const;

  bool operator==(const integer_base &other) const;

  unsigned base() const;

  int sign() const;

  friend std::ostream &operator<<(std::ostream &, const integer_base &);

  typedef enum sign { NEGATIVE = -1, POSITIVE = 1 } SIGN;

  std::optional<int> convert_to_decimal() const;

  static std::optional<integer_base> from_array(std::string &string_num,
                                                unsigned base = 10);

private:
  void initialize_digits(int num);

  void abs_add(const integer_base &greater, const integer_base &smaller,
               integer_base &new_num) const;

  void abs_subt(const integer_base &greater, const integer_base &smaller,
                integer_base &new_num) const;

  bool abs_greater(const integer_base &first, const integer_base &second) const;

  static void abs_multiply_by_digit(const integer_base &num, unsigned int digit,
                                    integer_base &new_num) {
    unsigned carry = 0;
    for (unsigned i = 0; i < num.m_digits.size(); i++) {
      unsigned current_digit = num.m_digits[i] * digit + carry;
      new_num.m_digits.push_back(current_digit % num.m_base);
      carry = current_digit / num.m_base;
    }
    if (carry > 0)
      new_num.m_digits.push_back(carry);
  }

  unsigned m_base;
  enum sign m_sign;
  std::vector<unsigned> m_digits;
};

#endif // INTEGER_BASE_H
