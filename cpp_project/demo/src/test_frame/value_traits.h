#pragma once
#include <cassert>
#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>
class Value {
public:
  template <typename T> void convert(const T &t) {
    str += std::to_string(t) + "|";
  }
  std::string str;
};

template <typename T> struct ValueTypeTraits {
  static const bool CONVERTIBLE = false;
};

#define DEFINE_VALUE_TRAITS(type, convertible)                                 \
  template <> struct ValueTypeTraits<type> {                                   \
    static const bool CONVERTIBLE = convertible;                               \
  };

DEFINE_VALUE_TRAITS(bool, true);
DEFINE_VALUE_TRAITS(int8_t, true);
DEFINE_VALUE_TRAITS(int16_t, true);
DEFINE_VALUE_TRAITS(int32_t, true);
DEFINE_VALUE_TRAITS(int64_t, true);

DEFINE_VALUE_TRAITS(uint8_t, true);
DEFINE_VALUE_TRAITS(uint16_t, true);
DEFINE_VALUE_TRAITS(uint32_t, true);
DEFINE_VALUE_TRAITS(uint64_t, true);

DEFINE_VALUE_TRAITS(float, true);
DEFINE_VALUE_TRAITS(double, true);

class KeyGenerator {
public:
  Value val;

public:
  template <typename T, typename... Ts> Value &&GenKey(T arg, Ts... args) {
    Serialize(arg);
    if constexpr (sizeof...(args) > 0) {
      GenKey(args...);
    }
    return std::move(val);
  }

private:
  template <typename T> void Serialize(const T &arg) {
    _Serialize(arg,
               std::integral_constant<bool, ValueTypeTraits<T>::CONVERTIBLE>{});
  }

  template <typename T> void _Serialize(const T &arg, std::true_type) {
    // todo: add arg to val
    val.convert(arg);
  }

  template <typename T> void _Serialize(const T &arg, std::false_type) {
    assert(0);
  }
};
