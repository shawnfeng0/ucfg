//
// Created by shawnfeng on 2021-01-25.
//

#ifndef UCFG__VALUE_H_
#define UCFG__VALUE_H_

#include <cassert>
#include <exception>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace ucfg {

enum class value_t : std::uint8_t {
  empty = 0,
  string = 4,
  array = 9,
  table = 10,
};

std::string TypeMap(value_t value) {
  switch (value) {
    case value_t::string:
      return "string";
    case value_t::array:
      return "array";
    case value_t::table:
      return "table";
    default:
      return "empty";
  }
}

class Node {
 public:
  using comment_type = std::vector<std::string>;
  using key_type = std::string;
  using string_type = std::string;
  using array_type = std::vector<Node>;
  using table_type = std::map<std::string, Node>;

  Node(const Node& node) : type_(node.type()) {
    switch (node.type()) {
      case value_t::string:
        assigner(this->string_, node.string_);
        break;
      case value_t::array:
        assigner(this->array_, node.array_);
        break;
      case value_t::table:
        assigner(this->table_, node.table_);
        break;
      default:
        break;
    }
  }

  Node(Node&& node) noexcept : type_(node.type()) {
    switch (node.type()) {
      case value_t::string:
        assigner(this->string_, std::move(node.string_));
        break;
      case value_t::array:
        assigner(this->array_, std::move(node.array_));
        break;
      case value_t::table:
        assigner(this->table_, std::move(node.table_));
        break;
      default:
        break;
    }
  }

#define UCFG_NODE_CREATE(TYPE)                             \
  explicit Node(const TYPE##_type& value)                  \
      : type_(value_t::TYPE), TYPE##_{std::move(value)} {} \
  explicit Node(TYPE##_type&& value)                       \
      : type_(value_t::TYPE), TYPE##_{std::move(value)} {}
  UCFG_NODE_CREATE(string)
  UCFG_NODE_CREATE(array)
  UCFG_NODE_CREATE(table)
#undef UCFG_NODE_CREATE

  Node() : type_(value_t::empty) {}
  ~Node() noexcept { this->cleanup(); }

  bool contains(const key_type& k) const {
    if (!this->is_table()) {
      throw std::runtime_error("contains(key): " + TypeMap(this->type_));
    }
    return (this->as_table().count(k) != 0);
  }

  bool is(value_t t) const noexcept { return t == this->type_; }
  bool is_uninitialized() const noexcept { return this->is(value_t::empty); }
  bool is_string() const noexcept { return this->is(value_t::string); }
  bool is_array() const noexcept { return this->is(value_t::array); }
  bool is_table() const noexcept { return this->is(value_t::table); }

#define UCFG_AS_VALUE_FUNCTIONS(TYPE)                     \
  TYPE##_type& as_##TYPE()& {                             \
    if (this->type_ != value_t::TYPE) {                   \
      throw std::runtime_error("as_" #TYPE ", type is " + \
                               TypeMap(this->type()));    \
    }                                                     \
    return this->TYPE##_;                                 \
  }                                                       \
  const TYPE##_type& as_##TYPE() const& {                 \
    if (this->type_ != value_t::TYPE) {                   \
      throw std::runtime_error("as_" #TYPE ", type is " + \
                               TypeMap(this->type()));    \
    }                                                     \
    return this->TYPE##_;                                 \
  }
  UCFG_AS_VALUE_FUNCTIONS(string)
  UCFG_AS_VALUE_FUNCTIONS(table)
  UCFG_AS_VALUE_FUNCTIONS(array)
#undef UCFG_AS_VALUE_FUNCTIONS

  value_t type() const noexcept { return type_; }

  void cleanup() noexcept {
    switch (this->type_) {
      case value_t::string:
        string_.~basic_string();
        return;
      case value_t::array:
        array_.~vector();
        return;
      case value_t::table:
        table_.~map();
        return;
      default:
        return;
    }
  }

 private:
  template <typename T, typename U>
  static void assigner(T& dst, U&& v) {
    const auto tmp = ::new (std::addressof(dst)) T(std::forward<U>(v));
    assert(tmp == std::addressof(dst));
    (void)tmp;
  }

  value_t type_;
  union {
    std::string string_;
    std::vector<Node> array_;
    std::map<std::string, Node> table_;
  };
};

inline bool operator==(const Node& lhs, const Node& rhs) {
  if (lhs.type() != rhs.type()) {
    return false;
  }

  switch (lhs.type()) {
    case value_t::string: {
      return lhs.as_string() == rhs.as_string();
    }
    case value_t::array: {
      return lhs.as_array() == rhs.as_array();
    }
    case value_t::table: {
      return lhs.as_table() == rhs.as_table();
    }
    case value_t::empty: {
      return true;
    }
    default: {
      return false;
    }
  }
}

inline bool operator!=(const Node& lhs, const Node& rhs) {
  return !(lhs == rhs);
}

inline bool operator<(const Node& lhs, const Node& rhs) {
  if (lhs.type() != rhs.type()) {
    return (lhs.type() < rhs.type());
  }
  switch (lhs.type()) {
    case value_t::string: {
      return lhs.as_string() < rhs.as_string();
    }
    case value_t::array: {
      return lhs.as_array() < rhs.as_array();
    }
    case value_t::table: {
      return lhs.as_table() < rhs.as_table();
    }
    case value_t::empty:
    default:
      return false;
  }
}

inline bool operator<=(const Node& lhs, const Node& rhs) {
  return (lhs < rhs) || (lhs == rhs);
}
inline bool operator>(const Node& lhs, const Node& rhs) {
  return !(lhs <= rhs);
}
inline bool operator>=(const Node& lhs, const Node& rhs) {
  return !(lhs < rhs);
}

}  // namespace ucfg

#endif  // UCFG__VALUE_H_
