//#include <iostream>
//#include <vector>
//#include <queue>
//#include <stack>
//
//std::string ToBinary(int n) {
//  std::stack<int> num;
//  std::string str;
//  if (n == 0) {
//    return "0";
//  }
//  while (n > 0) {
//    num.push(n % 2);
//    n /= 2;
//  }
//  while (!num.empty()) {
//    str += std::to_string(num.top());
//    num.pop();
//  }
//  return str;
//}
//
//std::pair<std::vector<std::string>, int> ToBinary(std::vector<std::pair<int, int>>& nums) {
//  std::vector<std::string> res(nums.size());
//  size_t max = 0;
//  for (int i = 0; i < nums.size(); ++i) {
//    std::string str;
//    int integer = nums[i].first / nums[i].second;
//    str += ToBinary(integer);
//    int num = nums[i].first - integer * nums[i].second;
//    int den = nums[i].second;
//    int counter = 0;
//    while (counter < 14) {
//      if (num % den != 0) {
//        num *= 2;
//        str += std::to_string(num / den);
//        num %= den;
//      } else {
//        str += "0";
//      }
//      counter += 1;
//    }
//    res[i] = str;
//    max = std::max(max, str.length());
//  }
//  return {res, max};
//}
//
//void RadixSort(std::vector<std::pair<int, int>>& nums) {
//  int n = nums.size();
//  std::vector<std::pair<int, int>> res(n);
//  auto binary = ToBinary(nums);
//  auto bin_nums = binary.first;
//  int max = binary.second;
//  std::vector<std::string> second(n);
//  int left = 0;
//  int right = n - 1;
//  int border = right;
//  std::vector<int> indexes(n);
//  std::vector<int> new_indexes(n);
//  for (int i = 0; i < n; ++i) {
//    indexes[i] = i;
//  }
//  for (int j = 0; j < max; ++j) {
//    left = 0;
//    right = n - 1;
//    int i = 0;
//    for (; i <= border; ++i) {
//      if (j >= bin_nums[i].length() || bin_nums[i][bin_nums[i].length() - j - 1] == '0') {
//        new_indexes[left] = indexes[i];
//        second[left] = bin_nums[i];
//        left += 1;
//      } else {
//        new_indexes[right] = indexes[i];
//        second[right] = bin_nums[i];
//        right -= 1;
//      }
//    }
//    for (int k = n-1; k > border; --k) {
//      if (j >= bin_nums[k].length() || bin_nums[k][bin_nums[k].length() - j - 1] == '0') {
//        new_indexes[left] = indexes[k];
//        second[left] = bin_nums[k];
//        left += 1;
//      } else {
//        new_indexes[right] = indexes[k];
//        second[right] = bin_nums[k];
//        right -= 1;
//      }
//    }
//    border = right;
//    auto tmp = std::move(second);
//    second = std::move(bin_nums);
//    bin_nums = std::move(tmp);
//    auto t = std::move(indexes);
//    indexes = std::move(new_indexes);
//    new_indexes = std::move(t);
//  }
//  for (int i = 0; i <= border; ++i) {
//    res[i] = nums[indexes[i]];
//  }
//  for (int i = 1; i < n - border; ++i) {
//    res[border + i] = nums[indexes[n - i]];
//  }
//  nums = std::move(res);
//}
//
//int main() {
//  int n;
//  std::cin >> n;
//  std::vector<std::pair<int, int>> nums(n);
//  for (int i = 0; i < n; ++i) {
//    std::string str;
//    std::cin >> str;
//    int j = 0;
//    while (str[j] != '/') {
//      j += 1;
//    }
//    nums[i].first = std::atoi(str.substr(0, j).c_str());
//    nums[i].second = std::atoi(str.substr(j + 1, str.length() - j).c_str());
//  }
//  RadixSort(nums);
//  for (int i = 0; i < n; ++i) {
//    std::cout << nums[i].first << "/" << nums[i].second << " ";
//  }
//}
//
//

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