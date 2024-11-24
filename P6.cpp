#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int estimate(const std::vector<int>& spots) {
  size_t n = spots.size();
  std::vector<bool> diag1(2 * n - 1, false);
  std::vector<bool> diag2(2 * n - 1, false);
  int s = 0;
  for (int i = 0; i < n; i++) {
    size_t d1 = i + spots[i];
    size_t d2 = i - spots[i] + (n - 1);
    if (!diag1[d1] && !diag2[d2]) {
      s += 1;
      diag1[d1] = true;
      diag2[d2] = true;
    }
  }
  return s;
}

std::vector<int> Solve(int n) {
  std::vector<int> spots(n);
  for (int i = 0; i < n; ++i) {
    spots[i] = i;
  }
  std::random_device rand_dev;
  std::mt19937 generator(45);
  std::uniform_int_distribution<> distr(0, n - 1);
  std::shuffle(spots.begin(), spots.end(), generator);

  double energy = estimate(spots);
  double Ti = 1;
  for (int i = 0; i < 1000000; ++i) {
    Ti *= 0.99;

    std::vector<int> new_spots = spots;
    std::swap(new_spots[rand() % n], new_spots[rand() % n]);
    double new_energy = estimate(new_spots);
    double dE = new_energy - energy;

    if (new_energy > energy || distr(generator) < std::exp(dE / Ti)) {
      spots = new_spots;
      energy = new_energy;
    }
  }
  return spots;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> answer = Solve(n);
  for (int i = 0; i < answer.size(); ++i) {
    std::cout << answer[i] + 1<< " ";
  }
}