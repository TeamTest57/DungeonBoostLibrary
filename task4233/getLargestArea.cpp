#include "getLargestArea.hpp"

constexpr size_t height = 4;
constexpr size_t width = 5;

int main(){
  size_t searchElem;
  while(std::cin>>searchElem) {
    if(searchElem==0) break;
    GetLargestSquareArea<size_t, width, height>  gsa;
    GetLargestRectArea<size_t, width, height> gra;
    std::array< std::array<size_t, width>, height> matrix;
    for(size_t hi=0; hi<height; ++hi){
      for(size_t wi=0; wi<width; ++wi){
        std::cin>>matrix[hi][wi];
      }
    }
    
    std::cout << gsa.getLargestSquareArea(matrix, searchElem) << std::endl;
    std::cout << gra.getLargestRectArea(matrix, searchElem) << std::endl;
  }
  return 0;
}
