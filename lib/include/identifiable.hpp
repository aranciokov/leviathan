#pragma once

#include <cstdint>
#include <iostream>
#include <limits>

namespace LTL {
namespace detail {

template <typename Derived>
class Identifiable {
public:
  constexpr Identifiable() : _id(0) {}
  constexpr explicit Identifiable(uint64_t id) : _id(id) {}
  constexpr Identifiable(const Derived &d) : _id(d._id) {}
  inline Derived &operator=(const Derived &d)
  {
    _id = d._id;
    return *this;
  }

  inline constexpr operator size_t() const { return static_cast<size_t>(_id); }
  /*
  inline constexpr operator unsigned long() const
  {
          return static_cast<unsigned long>(_id);
  }

  inline constexpr operator unsigned long long() const
  {
          return static_cast<unsigned long long>(_id);
  }
  */

  inline constexpr friend bool operator==(const Derived &d1, const Derived &d2)
  {
    return d1._id == d2._id;
  }

  inline constexpr friend bool operator!=(const Derived &d1, const Derived &d2)
  {
    return d1._id != d2._id;
  }

  inline Derived &operator++()
  {
    ++_id;
    return *this;
  }

  inline Derived operator++(int)
  {
    Derived temp(*this);
    ++_id;
    return temp;
  }

  inline Derived &operator--()
  {
    --_id;
    return *this;
  }

  inline Derived operator--(int)
  {
    Derived temp(*this);
    --_id;
    return temp;
  }

  inline constexpr friend bool operator<(const Derived &d1, const Derived &d2)
  {
    return d1._id < d2._id;
  }

  inline constexpr friend bool operator>(const Derived &d1, const Derived &d2)
  {
    return d1._id > d2._id;
  }

  inline constexpr friend bool operator<=(const Derived &d1, const Derived &d2)
  {
    return d1._id <= d2._id;
  }

  inline constexpr friend bool operator>=(const Derived &d1, const Derived &d2)
  {
    return d1._id >= d2._id;
  }

  template <typename T>
  inline constexpr friend Derived operator+(const Derived &d, T c)
  {
    return Derived(d._id + c);
  }

  template <typename T>
  inline constexpr friend Derived operator-(const Derived &d, T c)
  {
    return Derived(d._id - c);
  }

  inline static constexpr Derived max()
  {
    return Derived(std::numeric_limits<uint64_t>::max());
  }

  inline static constexpr Derived min()
  {
    return Derived(std::numeric_limits<uint64_t>::max());
  }

private:
  uint64_t _id;
};

class FrameID : public Identifiable<FrameID> {
public:
  constexpr FrameID() {}
  constexpr explicit FrameID(uint64_t id) : Identifiable(id) {}
  constexpr FrameID(const FrameID &id) : Identifiable(id) {}
};

class FormulaID : public Identifiable<FormulaID> {
public:
  constexpr FormulaID() {}
  constexpr explicit FormulaID(uint64_t id) : Identifiable(id) {}
  constexpr FormulaID(const FormulaID &id) : Identifiable(id) {}
};
}
}

template <typename T>
std::ostream &operator<<(std::ostream &os, LTL::detail::Identifiable<T> id)
{
  return os << (uint64_t)id;
}

namespace std {
template <>
struct hash<LTL::detail::FormulaID> {
  size_t operator()(LTL::detail::FormulaID id) const
  {
    return hash<uint64_t>()(static_cast<uint64_t>(id));
  }
};
}
