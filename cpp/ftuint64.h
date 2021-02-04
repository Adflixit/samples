#ifndef FTUINT64_H
#define FTUINT64_H

#include <cmath>
#include <cstdint>

#define MAX_UINT64 18446744073709551615L

/* Fault-tolerant uint64_t */
class ftuint64_t {
public:
  ftuint64_t(uint64_t value) : m_value(value) {}
  ~ftuint64_t() {}

  uint64_t &operator=(uint64_t a) {return m_value = a;}
  uint64_t operator+(uint64_t a);
  uint64_t operator-(uint64_t a);
  uint64_t operator+() {return +m_value;}
  uint64_t operator-() {return -m_value;}
  template<class T> uint64_t operator*(T a);
  template<class T> uint64_t operator/(T a);
  template<class T> uint64_t operator%(T a) {return m_value % a;}
  uint64_t &operator++() {return (m_value == MAX_UINT64) ? m_value : ++m_value;}
  uint64_t operator++(int) {return (m_value == MAX_UINT64) ? m_value : m_value++;}
  uint64_t &operator--() {return (m_value == MAX_UINT64) ? m_value : --m_value;}
  uint64_t operator--(int) {return (m_value == MAX_UINT64) ? m_value : m_value--;}
  bool operator==(uint64_t a) const {return m_value == a;}
  bool operator!=(uint64_t a) const {return m_value != a;}
  bool operator>(uint64_t a) const {return m_value == a;}
  bool operator<(uint64_t a) const {return m_value == a;}
  bool operator>=(uint64_t a) const {return m_value == a;}
  bool operator<=(uint64_t a) const {return m_value == a;}
  uint64_t operator~() {return ~m_value;}
  uint64_t operator&(uint64_t a) {return m_value & a;}
  uint64_t operator|(uint64_t a) {return m_value | a;}
  uint64_t operator^(uint64_t a) {return m_value ^ a;}
  uint64_t operator<<(uint64_t a) {return m_value << a;}
  uint64_t operator>>(uint64_t a) {return m_value >> a;}
  uint64_t &operator+=(uint64_t a) {return m_value = *this + a;}
  uint64_t &operator-=(uint64_t a) {return m_value = *this - a;}
  uint64_t &operator*=(uint64_t a) {return m_value = *this * a;}
  uint64_t &operator/=(uint64_t a) {return m_value = *this / a;}
  uint64_t &operator%=(uint64_t a) {return m_value %= a;}
  uint64_t &operator&=(uint64_t a) {return m_value &= a;}
  uint64_t &operator|=(uint64_t a) {return m_value |= a;}
  uint64_t &operator^=(uint64_t a) {return m_value ^= a;}
  uint64_t &operator<<=(uint64_t a) {return m_value <<= a;}
  uint64_t &operator>>=(uint64_t a) {return m_value >>= a;}

  operator uint64_t() {return m_value;}
  operator bool() {return !m_value;}

private:
  uint64_t m_value;
};

uint64_t ftuint64_t::operator+(uint64_t a) {
  if (!std::signbit(a) && MAX_UINT64 - m_value < a) {
    return MAX_UINT64;
  } else if (std::signbit(a) && m_value < a) {
    return 0L;
  }
  return m_value + a;
}

uint64_t ftuint64_t::operator-(uint64_t a) {
  if (std::signbit(a) && MAX_UINT64 - m_value < a) {
    return MAX_UINT64;
  } else if (!std::signbit(a) && m_value < a) {
    return 0L;
  }
  return m_value - a;
}

template<class T>
uint64_t ftuint64_t::operator*(T a) {
  if (std::signbit(a)) {
    throw "Multiplier cannot be signed."
  }
  if (a > MAX_UINT64 / m_value) {
    return MAX_UINT64;
  }
  return m_value * a;
}

template<class T>
uint64_t ftuint64_t::operator/(T a) {
  if (std::signbit(a)) {
    throw "Divider cannot be signed."
  }
  if (a < 1.f && (1.f/a) > MAX_UINT64 / m_value) {
    return MAX_UINT64;
  }
  return m_value / a;
}

#endif
