#pragma once

namespace ucfg {
namespace internal {

template <class T>
class List;

template <class T>
class ListNode {
  friend List<T>;

 private:
  void set_next(T sibling) { list_node_sibling_ = sibling; }
  T get_next() const { return list_node_sibling_; }
  T list_node_sibling_{nullptr};
};

template <class T>
class List {
 public:
  bool Add(T new_node) {
    if (!new_node) {
      return false;
    }
    new_node->set_next(head_);
    head_ = new_node;
    return true;
  }

  bool Remove(T remove_node) {
    if (!remove_node || !head_) {
      return false;
    }

    // base case
    if (remove_node == head_) {
      head_ = head_->get_next();
      return true;
    }

    for (T node : *this) {
      if (node->get_next() == remove_node) {
        node->set_next(node->get_next()->get_next());
        return true;
      }
    }

    return false;
  }

  struct Iterator {
    T node;
    explicit Iterator(T v) : node(v) {}
    explicit operator T() const { return node; }
    explicit operator T &() const { return node; }
    inline bool operator!=(const Iterator &rhs) { return node != rhs.node; }
    T operator*() const { return node; }
    Iterator &operator++() {
      if (node) {
        node = node->get_next();
      }

      return *this;
    }
  };
  Iterator begin() { return Iterator(head_); }
  Iterator begin() const { return Iterator(head_); }
  Iterator end() { return Iterator(nullptr); }
  Iterator end() const { return Iterator(nullptr); }

  bool empty() const { return head_ == nullptr; }

  unsigned size() const {
    unsigned sz = 0;
    for (auto node : *this) sz++;
    return sz;
  }

  void DeleteNode(T node) {
    if (Remove(node)) {
      // only delete if node was successfully removed
      delete node;
    }
  }

  void DeleteAllNode() {
    while (head_) {
      auto next = head_->get_next();
      delete head_;
      head_ = next;
    }
  }

 protected:
  T head_{nullptr};
};

}  // namespace internal
}  // namespace ucfg
