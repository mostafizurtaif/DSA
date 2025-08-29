#include <iostream>
#include "include/LinkedList.h"

int main() {
  dsa::LinkedList<int> list;

  list.insert_front(5);
  list.insert_rear(7);
  list.insert_at(0, 2);
  std::cout << list;


  return 0;
}
