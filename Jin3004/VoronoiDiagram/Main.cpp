#include <Siv3D.hpp>
#include <random>
#include <array>

constexpr int WINDOW_X = 800;
constexpr int WINDOW_Y = 600;
constexpr int POINT_NUM = 40;//The number of plotted points.

struct Pos{
  int32 x, y;
  Pos& operator=(const Pos&) = default;
  Pos() = default;
};

void Main(){

  std::mt19937 mt{std::random_device{}()};
  std::uniform_int_distribution<int> dist_x{0, WINDOW_X}, dist_y{0, WINDOW_Y};
  //These will be used for generating random.

  std::array<Pos, POINT_NUM> points{};
  for(auto& p : points){
    p.x = dist_x(mt), p.y = dist_y(mt);
  }
  //Generate random points.

  while(System::Update()){
    for(const auto& p : points){
      Circle(p.x, p.y, 5).draw();
    }
  }

}