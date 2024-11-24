#include <iostream>
#include <random>

int main() {
  double x1, y1, r1, x2, y2, r2, x3, y3, r3;
  std::cin >> x1 >> y1 >> r1;
  std::cin >> x2 >> y2 >> r2;
  std::cin >> x3 >> y3 >> r3;

  double bottom = std::min(y1 - r1, std::min(y2 - r2, y3 - r3));
  double top = std::max(y1 + r1, std::min(y2 + r2, y3 + r3));
  double left = std::min(x1 - r1, std::min(x2 - r2, x3 - r3));
  double right = std::max(x1 + r1, std::min(x2 + r2, x3 + r3));
  double S_rec = (right - left) * (top - bottom);

  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_real_distribution<> distr_x(left, right);
  std::uniform_real_distribution<> distr_y(bottom, top);

  int N = 220000;
  int M = 0;
  for (int i = 0; i < 220000; ++i) {

    double x = distr_x(generator);
    double y = distr_y(generator);

    if (pow(x1 - x, 2) + pow(y1 - y, 2) <= pow(r1, 2) &&
    pow(x2 - x, 2) + pow(y2 - y, 2) <= pow(r2, 2) &&
    pow(x3 - x, 2) + pow(y3 - y, 2) <= pow(r3, 2)) {
      M += 1;
    }
  }
  std::cout << (static_cast<double>(M) / N) * S_rec;
}