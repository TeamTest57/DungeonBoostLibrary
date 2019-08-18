#include "getLargestArea.hpp"

GetLargestRectAreaInHist::GetLargestRectAreaInHist(std::array< Type, width > heightData, size_t widthSize) {
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



