#ifndef DSA_LINKEDLIST_H
#define DSA_LINKEDLIST_H

#include <cstddef>
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
  Node *tail;
  std::size_t node_count;

public:
  LinkedList() : head{nullptr}, tail{nullptr}, node_count{0} {}

  // Rule of Five
  ~LinkedList();
  LinkedList(const LinkedList &other);
  LinkedList &operator=(const LinkedList &other);
  LinkedList(const LinkedList &&other);
  LinkedList &operator=(const LinkedList &&other);

  // Insertion
  void insert_front(const T &value);
  void insert_rear(const T &value);
  void insert_at(std::size_t index, const T &value);

  // Removal
  void remove_front();
  void remove_rear();
  void remove_at(std::size_t index);

  // Utilities
  [[nodiscard]] bool contains(const T &value) const;
  [[nodiscard]] bool is_empty() const;
  void erase();

  // << overloading
  template <typename U>
  friend std::ostream &operator<<(std::ostream &stream,
                                  const LinkedList<U> &list);
};

template <typename T> LinkedList<T>::~LinkedList() { erase(); }

template <typename T> void LinkedList<T>::insert_front(const T &value) {
  Node *new_node{new Node(value)};
  if (head == nullptr) {
    head = new_node;
    tail = new_node;
  } else {
    new_node->next = head;
    head = new_node;
  }
  node_count++;
}

template <typename T> void LinkedList<T>::insert_rear(const T &value) {
  Node *new_node{new Node(value)};
  if (head == nullptr) {
    head = new_node;
    tail = new_node;
  } else {
    tail->next = new_node;
    tail = new_node;
  }
  node_count++;
}

template <typename T>
void LinkedList<T>::insert_at(const std::size_t index, const T &value) {
  if (index > node_count) {
    throw std::out_of_range("Index out of bounds!");
  }
  if (index == 0) {
    insert_front(value);
  } else if (index == node_count) {
    insert_rear(value);
  } else {
    Node *previous{head};
    for (std::size_t i = 0; i < index - 1; i++) {
      previous = previous->next;
    }
    Node *new_node{new Node(value)};
    new_node->next = previous->next;
    previous->next = new_node;
    node_count++;
  }
}

template <typename T> void LinkedList<T>::remove_front() {
  if (head == nullptr) {
    return;
  }
  Node *first{head};
  head = head->next;
  delete first;
  node_count--;
  if (head == nullptr) {
    tail = nullptr;
  }
}

template <typename T> void LinkedList<T>::remove_rear() {
  if (head == nullptr) {
    return;
  }
  if (head->next == nullptr) {
    remove_front();
  } else {
    Node *previous{head};
    while (previous->next->next != nullptr) {
      previous = previous->next;
    }
    previous->next = nullptr;
    delete tail;
    tail = previous;
    node_count--;
  }
}

template <typename T> void LinkedList<T>::remove_at(const std::size_t index) {
  if (index >= node_count) {
    throw std::out_of_range("Index out of bounds!");
  }
  if (index == 0) {
    remove_front();
  } else if (index == node_count - 1) {
    remove_rear();
  } else {
    Node *previous{head};
    for (std::size_t i = 0; i < index - 1; i++) {
      previous = previous->next;
    }
    Node *target{previous->next};
    previous->next = target->next;
    delete target;
    node_count--;
  }
}

template <typename T>
[[nodiscard]] bool LinkedList<T>::contains(const T &value) const {
  Node *current{head};
  while (current != nullptr) {
    if (current->value == value) {
      return true;
    }
    current = current->next;
  }
  return false;
}

template <typename T> [[nodiscard]] bool LinkedList<T>::is_empty() const {
  return node_count == 0;
}

template <typename T> void LinkedList<T>::erase() {
  while (head != nullptr) {
    Node *first{head};
    head = head->next;
    delete first;
  }
  tail = nullptr;
  node_count = 0;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, const LinkedList<T> &list) {
  stream << "HEAD->";
  typename LinkedList<T>::Node *current{list.head};
  while (current != nullptr) {
    stream << current->value << (current->next != nullptr ? "->" : "");
    current = current->next;
  }
  return stream;
}
} // namespace dsa

#endif // DSA_LINKEDLIST_H
