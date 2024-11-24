#include <iostream>
#include <vector>

void CountingSort(std::vector<long long>& stars) {
  size_t n = stars.size();
  std::vector<long long> buckets(2000002, 0);
  for (long long star : stars) {
    buckets[star + 1000001] += 1;
  }
  long long j = 0;
  for (long long i = 0; i < 2000002; ++i) {
    for (long long k = 0; k < buckets[i]; ++k) {
      stars[j] = i - 1000001;
      j += 1;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  long long n;
  std::cin >> n;
  std::vector<long long> stars(n);
  for (long long i = 0; i < n; ++i) {
    std::cin >> stars[i];
  }
  CountingSort(stars);
  for (long long i = 0; i < n; ++i) {
    std::cout << stars[i] << " ";
  }
}