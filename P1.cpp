#include <iostream>
#include <vector>

void Sink(std::vector<int>& ganmens, int k, int n) {
  while (2 * k + 1 < n) {
    int j = 2 * k + 1;
    if (j < n - 1 && ganmens[j] < ganmens[j + 1]) {
      j += 1;
    }
    if (ganmens[k] >= ganmens[j]) {
      break;
    }
    std::swap(ganmens[k], ganmens[j]);
    k = j;
  }
}

void BuildMaxHeap(std::vector<int>& ganmens) {
  int n = ganmens.size();
  for (int i = n / 2 - 1; i >= 0; --i) {
    Sink(ganmens, i, n);
  }
}

void HeapSort(std::vector<int>& ganmens) {
  int n = ganmens.size();
  BuildMaxHeap(ganmens);

  while (n > 1) {
    std::swap(ganmens[0], ganmens[n - 1]);
    n -= 1;
    Sink(ganmens, 0, n);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> ganmens(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> ganmens[i];
  }
  HeapSort(ganmens);
  for (int i = 0; i < n; ++i) {
    std::cout << ganmens[i] << " ";
  }
  return 0;
}
