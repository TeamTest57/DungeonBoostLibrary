#include <Siv3D.hpp>
#include <array>
#include <vector>
#include <tuple>
#include <queue>

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
void createStar(Matrix &matrix, size_t x, size_t y, size_t star_x, size_t star_y, size_t star_r, double theta, size_t value){

  std::array<::Line, 5> lines;
  //Matrix cnt;
  //for(size_t i = 0; i < x; ++i)for(size_t j = 0; j < y; ++j){
  //  matrix[y][x] = 0;
  //}
  //^Initialized all the elements by zero.

  int8_t dx[] = {0, 1, 1, 1, 0, -1, -1, -1}, dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

  std::vector<std::vector<int8_t>> states(y, std::vector<int8_t>(x, 0b00000));

  {

    std::array<std::tuple<double, double>, 5> vertex;
    for (size_t i = 0; i < 5; ++i){
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
      if (i < 2)
      {
        make_line(i, i + 2);
        make_line(i, i + 3);
      }
      else
      {
        make_line(i, i + 2);
      }
    }
  } //Set each line.

  for (size_t i = 0; i < 5; ++i){

    ::Line &line = lines[i];
    for (size_t x = std::round(std::min(line.x[0], line.x[1])), prev = -1; x <= std::round(std::max(line.x[0], line.x[1])); ++x){

      y = std::round(line.inclination * x + line.section);
      states[y][x] |= (1 << i);
      //maybe go well

      if (prev != -1){
        if (y < prev - 1 || prev + 1 < y){
          bool flag = (prev < y);
          for (size_t j = (flag ? std::min(prev + 1, y - 1) : std::min(prev - 1, y + 1)); j <= (flag ? std::max(prev + 1, y - 1) : std::max(prev - 1, y + 1)); ++j){
            states[j][x] |= (1 << i);
            //maybe go well
          }
        }
      }
      prev = y;
    }
  }

  for (size_t i = 0; i < 5; ++i){

    int8_t cur_state = states[std::round(lines[i].y[0])][std::round(lines[i].x[0])], next_state;
    size_t cur_x = std::round(lines[i].x[0]), cur_y = std::round(lines[i].y[0]), next_x, next_y;

    bool flag = false;//Whether the current pos is inside the star.

    while (cur_state & (1 << i)){
      
      for (size_t j = 0; j < 8; ++j){

        next_x = cur_x + dx[j], next_y = cur_y + dy[j], next_state = states[next_y][next_x];

        if (next_state & (1 << i)){//If i-th flag is true, check whether the other flags are true.
          for(int k = i + 1; k < 5; ++k){
            if(next_state & (1 << k))flag = ~flag;
          }
        }
      }
      //Check the point is the crossed point.

      if(!flag)matrix[next_y][next_x] = value;

      cur_x = next_x, cur_y = next_y, cur_state = next_state;
      //Update variable `state`.

    }
  }

  //std::queue<std::pair<size_t, size_t>> q;
  //q.push(std::make_pair(star_y, star_x));
  //while (!q.empty())
  //{
  //  //auto [cur_y, cur_x] = q.front(); q.pop();
  //  size_t cur_y = q.front().first, cur_x = q.front().second;
  //  q.pop();
  //  for (size_t i = 0; i < 8; ++i)
  //  {
  //    size_t next_y = cur_y + dy[i], next_x = cur_x + dx[i];
  //    if (matrix[next_y][next_x] == 1)
  //      continue;
  //    matrix[next_y][next_x] = value;
  //    q.push(std::make_pair(next_y, next_x));
  //  }
  //}

  //}//Run BFS.
}

void Main()
{

  constexpr size_t HEIGHT = 64, WIDTH = 64;
  Window::Resize(WIDTH * scale, HEIGHT * scale); //Change the window size into the matrix size.
  Scene::SetBackground(Palette::White);

  std::array<std::array<int32_t, WIDTH>, HEIGHT> matrix; //matrix[y][x]
  for (auto &mat : matrix)
    for (auto &m : mat)
      m = 0; //Initialize all the elements as zero.

  createStar(matrix, WIDTH, HEIGHT, 31, 31, 25, 1.0, 1);

  s3d::Color colors[3] = {Palette::White, Palette::Black, Palette::Red};

  while (System::Update())
  {
    for (size_t x = 0; x < WIDTH; ++x)
    {
      s3d::Line(x * scale, 0, x * scale, HEIGHT * scale).draw(Palette::Black);
    }
    for (size_t y = 0; y < HEIGHT; ++y)
    {
      s3d::Line(0, y * scale, WIDTH * scale, y * scale).draw(Palette::Black);
    }
    //Draw a grid.

    for (size_t i = 0; i < WIDTH; ++i)
    {
      for (size_t j = 0; j < HEIGHT; ++j)
      {
        if (matrix[j][i] >= 1)
          Rect(i * scale, j * scale, scale, scale).draw(matrix[j][i] ? Palette::Black : Palette::White);
      }
    }
  };
}