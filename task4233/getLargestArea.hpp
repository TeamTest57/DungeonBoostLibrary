#pragma once
#include <iostream>
#include <array>
#include <stack>
#include <cstring>
#include <utility>

/* GetLargestArea class
 * get the largest rectanglar/square area by using given matrix*
 * 40617574686f72207461736b34323333
 */

template <class Type>
bool chmax(Type &a, const Type &b) {
  if (a<b) {a=b;return 1;}
  return 0;
}

template <class Type, size_t width, size_t height>
class GetLargestSquareArea {
public:  
  size_t getLargestSquareArea(std::array< std::array<Type, width>, height > matrix, Type searchElem){
    std::array< std::array<size_t, width>, height> dp;
    for(size_t hi=0; hi<height; ++hi) {
      dp[hi][0] = matrix[hi][0] == searchElem;
    }
    for(size_t wi=0; wi<width; ++wi){
      dp[0][wi] = matrix[0][wi] == searchElem;
    }
    
    size_t resArea = 0;
    for(size_t hi=1; hi<height; ++hi) {
      for(size_t wi=1; wi<width; ++wi) {
        if(matrix[hi][wi] != searchElem) {
          dp[hi][wi] ^= dp[hi][wi];
          continue;
        }
        dp[hi][wi] = std::min(std::min(dp[hi-1][wi-1], dp[hi][wi-1]), dp[hi-1][wi]) + 1;
        chmax(resArea, dp[hi][wi] * dp[hi][wi]);
      }
    }

    return resArea;
  }
};

template <class Type, size_t width, size_t height>
class GetLargestRectArea {
public:
  void dumpArray(std::array< std::array<Type, width>, height > dp) {
    for(size_t hi=0; hi<dp.size(); ++hi){
      for(size_t wi=0; wi<dp[hi].size(); ++wi) {
        std::cerr << dp[hi][wi] << " ";
      }
      std::cerr << std::endl;
    }
  }
  
  size_t getLargestRectArea(std::array< std::array<Type, width>, height > matrix, Type searchElem) {
    std::array< std::array< size_t, width + 1 >, height> heightCnt;
    for(size_t hi=0; hi<height; ++hi){
      heightCnt[hi].fill(1);
    }
    for(size_t wi=0; wi<width; ++wi){
      for(size_t hi=0; hi<height; ++hi){
        if (matrix[hi][wi] != searchElem) {
          heightCnt[hi][wi] = 0;
          continue;
        }
        if (hi>0)
          heightCnt[hi][wi] = matrix[hi][wi] == matrix[hi-1][wi] ? (heightCnt[hi-1][wi] + 1) : 1;
      }
    }

    size_t resArea = 0;
    for(size_t hi=0; hi<height; ++hi){
      chmax(resArea, getLargestRectAreaInHist(heightCnt[hi])); 
    }

    return resArea;
  }
  size_t getLargestRectAreaInHist(std::array< Type, width + 1 > heightCnt) {
    // height, xPos
    std::stack< std::pair<size_t, size_t> > st;
    size_t resArea = 0;
    heightCnt[width] ^= heightCnt[width];
  
    for (size_t wi=0; wi<=width; ++wi) {
      std::pair< size_t, size_t > currentRect = std::make_pair(heightCnt[wi], wi);
      if (st.empty()) {
        st.push(currentRect);
      } else if (st.top().first < currentRect.first) {
        st.push(currentRect);
      } else if (st.top().first > currentRect.first) {
        size_t target = wi;
        while (!st.empty() && st.top().first >= currentRect.first) {
          auto stackTop = st.top(); st.pop();
          chmax(resArea, (stackTop.first) * (wi - stackTop.second));
          target = stackTop.second;
        }
        currentRect.second = target;
        st.push(currentRect);
      }
    }
    return resArea;
  }
};
