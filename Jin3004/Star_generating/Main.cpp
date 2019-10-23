#include <Siv3D.hpp>
#include <array>
#include <tuple>

constexpr double pi = 3.141592;
constexpr size_t scale = 8;

constexpr double toRadian(size_t angle){
  return (double)(angle * pi / 180);
}

struct Line{
  double x[2], y[2];
  double inclination;
  double section;
  Line() = default;
};

template <typename Matrix>
void createStar(Matrix &matrix, size_t x, size_t y, size_t star_x, size_t star_y, size_t star_r, double theta, size_t value)
{

  std::array<::Line, 5> lines;
  {
  
    std::array<std::tuple<double, double>, 5> vertex;
    for (size_t i = 0; i < 5; ++i)
    {
      double rad = theta + toRadian(i * (360 / 5) + 270);
      double tmp_x = std::round(star_r * std::cos(rad) + star_x), tmp_y = std::round(star_r * std::sin(rad) + star_y);
      vertex[i] = {tmp_x, tmp_y};
    } //Calculate the positions of every vertexes.

    auto make_line = [&](size_t fir, size_t sec) {
      static size_t index = 0;
      ::Line &line = lines[index];
      std::tie(line.x[0], line.y[0]) = vertex[fir];
      std::tie(line.x[1], line.y[1]) = vertex[sec];
      line.inclination = (line.y[1] - line.y[0]) / (line.x[1] - line.x[0]);
      line.section = line.y[0] - line.inclination * line.x[0];
      index++;
    };

    for (size_t i = 0; i < 3; ++i){
      if(i < 2){
        make_line(i, i + 2);
        make_line(i, i + 3);
      }else{
        make_line(i, i + 2);
      }
    }
  }//Set each line.

  for (size_t i = 0; i < 5; ++i){
    ::Line &line = lines[i];
    for (size_t x = std::round(std::min(line.x[0], line.x[1])), prev = -1; x <= std::round(std::max(line.x[0], line.x[1])); ++x){
      y = std::round(line.inclination * x + line.section);
      matrix[y][x] += value;
      if(prev != -1){
        if(y < prev - 1 || prev + 1 < y){
          bool flag = (prev < y);
          for (size_t i = (flag ? std::min(prev + 1, y - 1) : std::min(prev - 1, y + 1)); i <= (flag ? std::max(prev + 1, y - 1) : std::max(prev - 1, y + 1)); ++i)
          {
            matrix[i][x] += value;
          }
        }
      }
      prev = y;
    }
  }
}

void Main()
{

  constexpr size_t HEIGHT = 64, WIDTH = 64;
  Window::Resize(WIDTH * scale, HEIGHT * scale); //Change the window size into the matrix size.
  Scene::SetBackground(Palette::White);

  std::array<std::array<int32_t, WIDTH>, HEIGHT> matrix; //matrix[y][x]
  for(auto& mat : matrix)for(auto& m : mat)m = 0;//Initialize all the elements as zero.

  createStar(matrix, WIDTH, HEIGHT, 31, 31, 25, 1.0, 1);

  s3d::Color colors[3] = {Palette::White, Palette::Black, Palette::Red};

  while (System::Update())
  {
    for (size_t x = 0; x < WIDTH; ++x){
      s3d::Line(x * scale, 0, x * scale, HEIGHT * scale).draw(Palette::Black);
    }
    for (size_t y = 0; y < HEIGHT; ++y){
      s3d::Line(0, y * scale, WIDTH * scale, y * scale).draw(Palette::Black);
    }
    //Draw a grid.

    for (size_t i = 0; i < WIDTH; ++i)
    {
      for (size_t j = 0; j < HEIGHT; ++j)
      {
        if(matrix[j][i] >= 1)Rect(i * scale, j * scale, scale, scale).draw(colors[matrix[j][i]]);
      }
      }
  };
}