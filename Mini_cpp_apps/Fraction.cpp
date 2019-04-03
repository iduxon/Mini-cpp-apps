#include "Fraction.h"
#include <QStringList>
#include <math.h>

Fraction::Fraction(int numerator, unsigned int denominator)
    : m_numerator(numerator), m_denominator(denominator) {
  simplify();
}

Fraction::Fraction(const QString &str) : m_numerator(0), m_denominator(1) {
  QStringList parts = str.split("/");
  if (parts.size() < 1 || parts.size() > 2)
    return;
  m_numerator = parts.at(0).toInt();
  m_denominator = parts.at(1).toUInt();
  simplify();
}

int Fraction::numerator() const { return m_numerator; }

unsigned int Fraction::denumerator() const { return m_denominator; }

void Fraction::set_numerator(int value) {
  m_numerator = value;
  simplify();
}

void Fraction::set_denumeraotr(unsigned int value) {
  m_denominator = value;
  simplify();
}

Fraction Fraction::operator+(const Fraction &other) const {
  return Fraction(numerator() * static_cast<int>(other.denumerator()) +
                      static_cast<int>(denumerator()) * other.numerator(),
                  denumerator() * other.denumerator());
}

Fraction Fraction::operator++(int) {
  return Fraction(m_numerator + static_cast<int>(m_denominator), m_denominator);
}

Fraction &Fraction::operator++() {
  m_numerator += m_denominator;
  simplify();
  return (*this);
}

Fraction Fraction::operator--(int) {
  return Fraction(m_numerator - static_cast<int>(m_denominator), m_denominator);
}
Fraction &Fraction::operator--() {
  m_numerator -= m_denominator;
  simplify();
  return (*this);
}
Fraction Fraction::operator-(const Fraction &other) const {
  return Fraction(numerator() * static_cast<int>(other.denumerator()) -
                      other.numerator() * static_cast<int>(denumerator()),
                  denumerator() * other.denumerator());
}

Fraction Fraction::operator*(const Fraction &other) const {
  return Fraction(numerator() * other.numerator(),
                  denumerator() * other.denumerator());
}
Fraction Fraction::operator/(const Fraction &other) const {
  return Fraction(numerator() * static_cast<int>(other.denumerator()),
                  denumerator() * static_cast<uint>(other.numerator()));
}
Fraction Fraction::operator~() const {
  return Fraction(static_cast<int>(m_denominator),
                  static_cast<unsigned>(m_numerator));
}

bool Fraction::operator==(const Fraction &other) const {
  return static_cast<int>(denumerator()) * other.numerator() ==
         static_cast<int>(other.denumerator()) * numerator();
}

Fraction::operator double() const {
  return m_numerator / static_cast<double>(m_denominator);
}

Fraction::operator QString() const {
  return QString::number(m_numerator) + "/" + QString::number(m_denominator);
}

std::istream &operator>>(std::istream &in, Fraction &value) {
  char c;
  return in >> value.m_numerator >> c >> value.m_denominator;
}

std::ostream &operator<<(std::ostream &out, const Fraction &value) {
  return out << value.m_numerator << "/" << value.m_denominator;
}

int gcd(const int &a, const int &b) {
  if (a == 0)
    return b;
  return gcd(b % a, a);
}

void Fraction::simplify() {
  int min = gcd(m_numerator, static_cast<int>(m_denominator));
  m_numerator = m_numerator / min;
  m_denominator = m_denominator / static_cast<uint>(min);
}
