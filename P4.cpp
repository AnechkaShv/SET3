
#include <iostream>
#include <vector>

struct Fraction {
  int numerator;
  int denominator;
  bool operator<=(const Fraction& other) const {
    return numerator * other.denominator <= denominator * other.numerator;
  }
};

void merge(std::vector<Fraction>& intervals, int left, int mid, int right) {
  std::vector<Fraction> left_sorted(mid - left + 1);
  std::vector<Fraction> right_sorted(right - mid);

  for (int i = 0; i < left_sorted.size(); i++)
    left_sorted[i] = intervals[left + i];
  for (int i = 0; i < right_sorted.size(); i++)
    right_sorted[i] = intervals[mid + 1 + i];

  int i = 0;
  int j = 0;
  size_t k = left;
  while (i < left_sorted.size() && j < right_sorted.size()) {
    if (left_sorted[i] <= right_sorted[j]) {
      intervals[k] = left_sorted[i];
      i++;
    } else {
      intervals[k] = right_sorted[j];
      j++;
    }
    k++;
  }

  while (i < left_sorted.size()) {
    intervals[k] = left_sorted[i];
    i++;
    k++;
  }

  while (j < right_sorted.size()) {
    intervals[k] = right_sorted[j];
    j++;
    k++;
  }
}

void mergeSort(std::vector<Fraction>& intervals, int left, int right) {
  if (left < right) {

    int mid = left + (right - left) / 2;

    mergeSort(intervals, left, mid);
    mergeSort(intervals, mid + 1, right);
    merge(intervals, left, mid, right);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<Fraction> nums(n);
  for (int i = 0; i < n; ++i) {
    std::string str;
    std::cin >> str;
    int j = 0;
    while (str[j] != '/') {
      j += 1;
    }
    nums[i].numerator = std::stoi(str.substr(0, j));
    nums[i].denominator = std::stoi(str.substr(j + 1));
  }
  mergeSort(nums, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    std::cout << nums[i].numerator << "/" << nums[i].denominator << (i == n - 1 ? "" :" ");
  }
}