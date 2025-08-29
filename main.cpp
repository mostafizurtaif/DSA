#include <iostream>
#include "include/LinkedList.h"

int main() {
  dsa::LinkedList<int> list;

  list.insert_front(5);
  list.insert_rear(2);
  list.insert(7, 1);
  list.insert_rear(11);
  std::cout << list;


  return 0;
}
