#include <iostream>
#include <vector>
#include "vector.hpp"


int main ()
{
    // ft::vector<int> ftVectorInts(5, 10);
    // size_t capacity_1 = ftVectorInts.capacity();
    // ftVectorInts.reserve(100);
    // size_t capacity_2 = ftVectorInts.capacity();

 std::vector<int> bar;
 std::cout << bar[bar.size()] << "\n";


//   std::vector<int>::size_type sz;
//   std::vector<int> foo;
//   sz = foo.capacity();
//   std::cout << "capacity is " << sz << "\n";
//   std::cout << "making foo grow:\n";
//   for (int i=0; i<100; ++i)
//   {
//     foo.push_back(i);
//     if (sz!=foo.capacity()) 
//     {
//       sz = foo.capacity();
//       std::cout << "capacity changed: " << sz << '\n';
//     }
//   }

//   std::vector<int> bar;
//   sz = bar.capacity();
//   bar.reserve(60);   // this is the only difference with foo above
//   std::cout << "making bar grow:\n";
//   for (int i=0; i<100; ++i) 
//   {
//     bar.push_back(i);
//     if (sz!=bar.capacity()) 
//     {
//       sz = bar.capacity();
//       std::cout << "capacity changed: " << sz << '\n';
//     }
//   }
//   bar.reserve(600);  
// std::cout << "BAR second time reserved capacity: " << bar.capacity() << '\n';
  return 0;
}