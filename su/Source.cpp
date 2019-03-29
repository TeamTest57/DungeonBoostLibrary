#include"Source.h"
#include<iostream>

int main() {
    int a[32][32] = {{0}};

    matrixInit(a);

    createStar(a, 32, 32, 15, 15, 11, 1);

    output(a);

    return 0;

}

template<typename Matrix>
void createStar(Matrix& matrix, size_t x, size_t y, size_t star_x, size_t star_y, size_t star_r, size_t value){
    constexpr size_t stars = 5;
    constexpr double angle = 360.0 / (double)stars;
    constexpr double PI = 3.141592653589793;
    size_t vertex[stars][2] = {0};

    vertex[0][0] = star_x;
    vertex[0][1] = star_y - star_r;



    for (size_t i = 1; i < stars; ++i) {
        std::cout << "ang:" << angle * i << std::endl;
        double degree = (double)(i * angle * PI) / 180.0;
        std::cout << "ƒÆ:" <<degree << std::endl;

        auto cx = (vertex[i - 1][0] - star_x);
        std::cout << "cx:" <<cx << std::endl;
        auto cy = (vertex[i - 1][1] - star_y);
        std::cout << "cy:" << cy << std::endl;

        vertex[i][0] = 
              (size_t)((cx * std::cos(degree)))
            - (size_t)((cy * std::sin(degree)));
        vertex[i][1] = 
              (size_t)((cx * std::cos(degree)))
            + (size_t)((cy * std::sin(degree)));
    }

    for (auto&& i : vertex) {
        std::cout << i[0] << ":" << i[1] << std::endl;
        //matrix[i[0]][i[1]] = value;
    }
    
}

template<typename Matrix>
void output(Matrix& matrix) {
    for (auto&& row : matrix) {
        for (auto&& i : row) {
            std::cout << i;
        }
        std::cout << std::endl;
    }
}

template<typename Matrix>
void matrixInit(Matrix& matrix) {
    for (auto& row : matrix) {
        for (auto& i : row) {
            i = 0;
        }
    }
}

