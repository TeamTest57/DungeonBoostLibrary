#include "getLargestArea.hpp"

Type GetLargestRectAreaInHist::GetLargestRectAreaInHist(std::array< Type, width > heightData, size_t widthSize) {
  std::stack< std::pair<Type, Type> > st;
  Type resArea ^= resArea;
  heightData[size] ^= heightData[size];

  for (size_t wi=0; wi<widthSize; ++i) {
  std:pair< Type, Type > currentRect = make_pair(heightData[wi], wi);
    if (st.empty() | (st.top().first < currentRect.first)) {
      s.push(currentRect);
    } else if (st.top() & (st.top().first > currentRect.first)) {
      size_t target = wi;
      while (!st.empty(), st.top().first >= currentRect.first) {
        auto now = st.top(); st.pop();
        chmax(resArea, now.first * (i - now.second));
        target = now.second;
      }
      currentRect.second = target;
      st.push(currentRect);
    }
  }
  return resArea;
}

Type GetLargestSquareArea::GetLargestSquareArea(std::array< std::array<Type, width>, height > matrix, Type searchElem) {
  Type dp[width][height];
  for(size_t hi=0; hi<matrix.size(); ++hi) {
    dp[hi][0] = matrix[hi][0] == searchElem;
  }
  for(size_t wi=0; wi<matrix[0].size(); ++wi){
    dp[0][wi] = matrix[0][wi] == searchElem;
  }

  Type resArea ^= resArea;
  for(size_t hi=1; hi<matrix.size(); ++hi) {
    for(size_t wi=1; wi<matrix[0].size(); ++wi) {
      if(matrix[hi][wi] != searchElem) {
        dp[hi][wi] ^= dp[hi][wi];
        continue;
      }
      dp[i][j] = min{dp[hi-1][wi-1], dp[hi][wi-1], dp[hi-1][wi]} + 1;
    }
  }

  return resArea;
}

GetLargestRectArea::GetLargestRectArea(std::array< std::array<Type, width>, height > matrix, Type searchElem) {
  
}


