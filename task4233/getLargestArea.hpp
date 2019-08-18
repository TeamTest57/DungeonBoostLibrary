#pragma once
#include <iostream>
#include <array>
#include <stack>

/* GetLargestArea class
 * get the largest rectanglar/square area by using given matrix*
 * 40617574686f72207461736b34323333
 */

template <class Type>
bool chmax(Type &a, constexpr Type &b) {
  if (a<b) {return 1;}
  return 0;
}

tempalce <class Type, size_t width>
class GetLargestRectAreaInHist {
public:
  GetLargestRectAreaInHist(std::array< Type, width > heightData, size_t size);
};

templace <class Type, size_t width, size_t height>
class GetLargestSquareArea {
public:
  GetLargestSquareArea(std::array< std::array<Type, width>, height > matrix, Type searchElem);
};

templace <class Type, size_t width, size_t height>
class GetLargestRectArea: public GetLargestRectInHist {
public:
  GetLargestRectArea(std::array< std::array<Type, width>, height > matrix, Type searchElem);
};
