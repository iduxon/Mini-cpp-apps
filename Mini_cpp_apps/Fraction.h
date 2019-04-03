#ifndef FRACTION_H
#define FRACTION_H
#include "function_declarations.h"
#include <QString>
#include <iostream>

class Fraction : public equality<Fraction> {
public:
  Fraction(int m_numerator = 0, unsigned int m_denominator = 1);
  Fraction(const QString &v);

  int numerator() const;
  void set_numerator(int value);

  unsigned int denumerator() const;
  void set_denumeraotr(unsigned int value);

  // fraction++
  Fraction operator++(int);
  //++fraction
  Fraction &operator++();

  // fraction--
  Fraction operator--(int);
  //--fraction
  Fraction &operator--();

  Fraction operator+(const Fraction &other) const;

  Fraction operator-() const;
  Fraction operator-(const Fraction &other) const;

  Fraction operator*(const Fraction &other) const;
  Fraction operator/(const Fraction &other) const;

  // reverse value
  Fraction operator~() const;

  operator double() const;
  operator QString() const;

  bool operator==(const Fraction &other) const;

  void simplify();

private:
  int m_numerator;
  unsigned int m_denominator;

  friend std::ostream &operator<<(std::ostream &out, const Fraction &value);
  friend std::istream &operator>>(std::istream &in, Fraction &value);
};

std::ostream &operator<<(std::ostream &out, const Fraction &value);
std::istream &operator>>(std::istream &in, Fraction &value);

#endif // FRACTION_H
