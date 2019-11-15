#include <Siv3D.hpp>
#include <array>

// star_x, star_y <- 0-indexed
template<typename Matrix>
constexpr void createStar(Matrix& matrix, size_t width, size_t height, size_t star_x, size_t star_y, size_t star_r, double theta, size_t value){

  // First, calculate each vertex.
  struct Pos{
    size_t x, y;
    Pos() = default;
  };

  std::array<Pos, 5> vertexes;

  constexpr auto toRadian = [=](double angle) -> double{
    constexpr double pi = 3.141592;
    return angle * pi / 180;
  };

  constexpr auto Abs = [=](size_t n) -> size_t{
    return n > 0 ? n : -n;
  };

  for(size_t i = 0; i < 5; ++i){
    const double rad = toRadian(72 * i + 270) + theta;
    const size_t ver_x = std::round((double)(star_x + std::cos(rad) * star_r)), ver_y = std::round((double)(star_y + std::sin(rad) * star_r));
    vertexes[i] = {ver_x, ver_y};
  }

  //Second, caluculate each line and assign each element which is on the line with `value`.
  std::array<std::pair<int8_t, int8_t>, 5> lines = {std::make_pair(0, 2), std::make_pair(0, 3), std::make_pair(1, 3), std::make_pair(1, 4), std::make_pair(2, 4)};
  
  for(const auto& l : lines){

    double rate = (vertexes[l.second].y - vertexes[l.first].y) / (vertexes[l.second].x - vertexes[l.first].x);
    double section = vertexes[l.first].y - vertexes[l.first].x * rate;

    size_t begin_x = 0, end_x = 0;
    if(std::round(vertexes[l.first].x) > std::round(vertexes[l.second].x)){
      begin_x = std::round(vertexes[l.second].x);
      end_x = std::round(vertexes[l.first].x);
    }else{
      begin_x = std::round(vertexes[l.first].x);
      end_x = std::round(vertexes[l.second].x);
    }

    size_t pre_y{};

    for(size_t x = begin_x; x <= end_x; ++x){
      size_t new_y = std::round(x * rate + section);
      matrix[new_y][x] = value;

      if(x != begin_x && Abs(pre_y - new_y) >= 1){
        for(size_t i = std::min<size_t>(pre_y, new_y) + 1; i <= std::max<size_t>(pre_y, new_y) - 1; ++i){
          matrix[i][x] = value;
        }
      }

      pre_y = new_y;

    }

  }

}

void Main(){

  constexpr size_t WIDTH = 64, HEIGHT = 64;
  constexpr size_t scale = 8;
  Window::Resize(WIDTH * scale, HEIGHT * scale);
  Scene::SetBackground(Palette::White);

  std::array<std::array<size_t, WIDTH>, HEIGHT> matrix;
  for(auto& m1 : matrix)for(auto& m2 : m1){
    m2 = 0;
  }

  createStar(matrix, WIDTH, HEIGHT, 31, 31, 25, 0.0, 1);

  while(System::Update()){

    for(size_t y = 0; y < HEIGHT; ++y){
      Line(0, y * scale, WIDTH * scale, y * scale).draw(Palette::Black);
    }
    for(size_t x = 0; x < WIDTH; ++x){
      Line(x * scale, 0, x * scale, HEIGHT * scale).draw(Palette::Black);
    }

    for(size_t y = 0; y < HEIGHT; ++y)for(size_t x = 0; x < WIDTH; ++x){
      if(matrix[y][x] == 1)Rect(x * scale, y * scale, scale, scale).draw(Palette::Black);
    }

  }

}