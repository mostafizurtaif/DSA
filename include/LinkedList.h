#ifndef DSA_LINKEDLIST_H
#define DSA_LINKEDLIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace dsa {
template <typename T> class LinkedList {
private:
  struct Node {
    T value;
    Node *next;

    explicit Node(const T &value) : value{value}, next{nullptr} {}
  };

  Node *head;
  std::size_t node_count;

public:
  LinkedList() : head{nullptr}, node_count{0} {}
  ~LinkedList();

  // Insertion
  void insert_front(const T &value);
  void insert_rear(const T &value);
  void insert(const T &value, std::size_t index);

  // Removal
  void remove_front();
  void remove_rear();
  void remove(std::size_t index);

  // Utility
  [[nodiscard]] bool contains(const T &value) const;
  [[nodiscard]] std::size_t length() const;
  void reset();
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const LinkedList<U> &list);
};

template <typename T> LinkedList<T>::~LinkedList() { reset(); }

template <typename T> void LinkedList<T>::insert_front(const T &value) {
  Node *new_node{new Node(value)};
  new_node->next = head;
  head = new_node;
  node_count++;
}

template <typename T> void LinkedList<T>::insert_rear(const T &value) {
  if (head == nullptr) {
    insert_front(value);
    return;
  }
  Node *last{head};
  while (last->next != nullptr)
    last = last->next;
  Node *new_node{new Node(value)};
  last->next = new_node;
  node_count++;
}

template <typename T>
void LinkedList<T>::insert(const T &value, const std::size_t index) {
  if (index > node_count) {
    throw std::out_of_range("Index out of bounds!");
  }
  if (index == 0) {
    insert_front(value);
    return;
  }
  if (index == node_count) {
    insert_rear(value);
    return;
  }
  Node *previous{head};
  for (std::size_t i = 0; i < index - 1; i++) {
    previous = previous->next;
  }
  Node *new_node{new Node(value)};
  new_node->next = previous->next;
  previous->next = new_node;
  node_count++;
}

template <typename T> void LinkedList<T>::remove_front() {
  if (head == nullptr)
    return;
  Node *front{head};
  head = front->next;
  delete front;
  node_count--;
}

template <typename T> void LinkedList<T>::remove_rear() {
  if (head == nullptr)
    return;
  if (head->next == nullptr) {
    remove_front();
    return;
  }
  Node *previous{head};
  while (previous->next->next != nullptr) {
    previous = previous->next;
  }
  Node *last{previous->next};
  previous->next = nullptr;
  delete last;
  node_count--;
}

template <typename T> void LinkedList<T>::remove(const std::size_t index) {
  if (index >= node_count) {
    throw std::out_of_range("Index out of bounds!");
  }
  if (index == 0) {
    remove_front();
    return;
  }
  if (index == node_count - 1) {
    remove_rear();
    return;
  }
  Node *previous{head};
  for (std::size_t i = 0; i < index - 1; i++) {
    previous = previous->next;
  }
  Node *target{previous->next};
  previous->next = target->next;
  delete target;
  node_count--;
}

template <typename T> bool LinkedList<T>::contains(const T &value) const {
  const Node *current{head};
  while (current != nullptr) {
    if (current->value == value)
      return true;
    current = current->next;
  }
  return false;
}

template <typename T> std::size_t LinkedList<T>::length() const {
  return node_count;
}

template <typename T> void LinkedList<T>::reset() {
  while (head != nullptr) {
    Node *front{head};
    head = front->next;
    delete front;
  }
  node_count = 0;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list) {
  os << "HEAD->";
  typename LinkedList<T>::Node *current{list.head};
  while (current != nullptr) {
    os << current->value << "->";
    current = current->next;
  }
  os << "NULL";
  return os;
}

} // namespace dsa

#endif // DSA_LINKEDLIST_H
