#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

int main() {
  std::ofstream out("diffWide.txt");
  std::ofstream out2("SquareWide.txt");
  const double s_real = (0.25 * M_PI + 1.25 * std::asin(0.8) - 1);

  std::cout << s_real;
  double x1, y1, r1, x2, y2, r2, x3, y3, r3;
  x1 = 1; y1 = 1; r1 = 1;
  x2 = 1.5; y2 = 2; r2 = std::sqrt(5)/2;
  x3 = 2; y3 = 1.5; r3 = std::sqrt(5)/2;

  double bottom = std::min(y1 - r1, std::min(y2 - r2, y3 - r3));
  double top = std::max(y1 + r1, std::min(y2 + r2, y3 + r3));
  double left = std::min(x1 - r1, std::min(x2 - r2, x3 - r3));
  double right = std::max(x1 + r1, std::min(x2 + r2, x3 + r3));
  double S_rec = (right - left) * (top - bottom);

  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_real_distribution<> distr_x(left, right);
  std::uniform_real_distribution<> distr_y(bottom, top);

  for (int j = 100; j <= 100000; j += 500) {
    int N = j;
    int M = 0;
    for (int i = 0; i < j; ++i) {

      double x = distr_x(generator);
      double y = distr_y(generator);

      if (pow(x1 - x, 2) + pow(y1 - y, 2) <= pow(r1, 2) &&
          pow(x2 - x, 2) + pow(y2 - y, 2) <= pow(r2, 2) &&
          pow(x3 - x, 2) + pow(y3 - y, 2) <= pow(r3, 2)) {
        M += 1;
      }
    }
    double S = (static_cast<double>(M) / N) * S_rec;
    out << N << ", " << 100 * (S - s_real) / s_real << "\n";
    out2 << N << ", " << S << "\n";
  }

  out = std::ofstream ("diffNarrow.txt");
  out2 = std::ofstream ("SquareNarrow.txt");


  bottom = 0.87;
  top = 2.1;
  left = 0.87;
  right = 2;
  S_rec = (right - left) * (top - bottom);

  distr_x = std::uniform_real_distribution<>(left, right);
  distr_y = std::uniform_real_distribution<>(bottom, top);

  for (int j = 100; j <= 100000; j += 500) {
    int N = j;
    int M = 0;
    for (int i = 0; i < j; ++i) {

      double x = distr_x(generator);
      double y = distr_y(generator);

      if (pow(x1 - x, 2) + pow(y1 - y, 2) <= pow(r1, 2) &&
          pow(x2 - x, 2) + pow(y2 - y, 2) <= pow(r2, 2) &&
          pow(x3 - x, 2) + pow(y3 - y, 2) <= pow(r3, 2)) {
        M += 1;
      }
    }
    double S = (static_cast<double>(M) / N) * S_rec;
    out << N << ", " << 100 * (S - s_real) / s_real << "\n";
    out2 << N << ", " << S << "\n";
  }
}

