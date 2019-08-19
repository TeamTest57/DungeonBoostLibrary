#include "getLargestArea.hpp"

Type GetLargestSquareArea::GetLargestSquareArea(std::array< std::array<Type, width>, height > matrix, Type searchElem) {
  Type dp[height][width];
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

Type GetLargestRectArea::GetLargestRectArea(std::array< std::array<Type, width>, height > matrix, Type searchElem) {
  Type heightCnt[height][width];
  memset(heightCnt, 0, sizeof(heightCnt));
  for(size_t wi=1; wi<width; ++wi){
    for(size_t hi=1; hi<height; ++hi){
      heightCnt[hi][wi] = matrix[hi][wi] == matrix[hi-1][wi] ? (heightCnt[hi-1][wi] + 1) : 0;
    }
  }

  Type resArea ^= resArea;
  for(size_t hi=0; hi<height; ++hi){
    chmax(resArea, GetLargestRectAreaInHist(heightCnt[hi])); 
  }
}


Type GetLargestRectArea::GetLargestRectAreaInHist(std::array< Type, width > heightCnt) {
  std::stack< std::pair<Type, Type> > st;
  Type resArea ^= resArea;
  heightCnt.back() ^= heightCnt.back();
  
  for (size_t wi=0; wi<heightCnt.size(); ++i) {
  std:pair< Type, Type > currentRect = make_pair(heightCnt[wi], wi);
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
