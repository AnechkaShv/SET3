#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "A2i.cpp"


class ArrayGenerator {
private:
  std::vector<std::vector<int>> randomArrays;
  std::vector<std::vector<int>> sortedArrays;
  std::vector<std::vector<int>> almostSortedArrays;
public:
  ArrayGenerator() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<> distr(1, 6000);
    randomArrays.emplace_back(10000);
    sortedArrays.emplace_back(10000);
    almostSortedArrays.emplace_back(10000);
    for (int i = 0; i < 10000; ++i) {
      randomArrays[0][i] = distr(generator);
      sortedArrays[0][i] = distr(generator);
      almostSortedArrays[0][i] = distr(generator);

    }
    std::stable_sort(sortedArrays[0].begin(), sortedArrays[0].end());
    for (int i = 0; i < sortedArrays[0].size() / 2; ++i) {
      std::swap(sortedArrays[0][i], sortedArrays[0][10000 - i - 1]);
    }
    int n = almostSortedArrays[0].size();

    std::stable_sort(almostSortedArrays[0].begin(), almostSortedArrays[0].end());
    for (int i = 0; i < n / 2; ++i) {
      std::swap(almostSortedArrays[0][i], almostSortedArrays[0][10000 - i - 1]);
    }

    for (int i = 0; i < 10; ++i) {
      std::swap(almostSortedArrays[0][distr(generator) % n], almostSortedArrays[0][distr(generator) % n]);
    }
    int k = 1;
    for (int i = 500; i < 10000; i += 100) {
      randomArrays.emplace_back(i);
      sortedArrays.emplace_back(i);
      almostSortedArrays.emplace_back(i);
      int start = distr(generator) % (10000 - i);
      for (int j = 0; j < i; ++j) {
        randomArrays[k][j] = randomArrays[0][start + j];
        sortedArrays[k][j] = sortedArrays[0][start + j];
        almostSortedArrays[k][j] = almostSortedArrays[0][start + j];
      }
      k += 1;
    }
    std::swap(randomArrays[0], randomArrays[randomArrays.size()]);
    std::swap(sortedArrays[0], sortedArrays[randomArrays.size()]);
    std::swap(almostSortedArrays[0], almostSortedArrays[randomArrays.size()]);

  }
  std::vector<std::vector<int>> getRandomArrays() {
    return randomArrays;
  }
  std::vector<std::vector<int>> getSortedArrays() {
    return sortedArrays;
  }
  std::vector<std::vector<int>> getAlmostSorted() {
    return almostSortedArrays;
  }
};

class SortTester {
public:
  long long Test(std::vector<int> A) {
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(A, 0, static_cast<int>(A.size() - 1));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    return msec;
  }
};

int main() {
  ArrayGenerator arrg = ArrayGenerator();
  auto random = arrg.getRandomArrays();
  auto sorted = arrg.getSortedArrays();
  auto almost = arrg.getAlmostSorted();
  SortTester sortTester = SortTester();
  std::vector<long long> res(almost.size());
  for (int j = 0; j < 10; ++j) {
    for (int i = 0; i < almost.size(); ++i) {
      res[i] += sortTester.Test(almost[i]);
    }
  }
  for (int i = 0; i < almost.size(); ++i) {
    res[i] /= 10;
    std::cout << res[i] << " ";
  }

}