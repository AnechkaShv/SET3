#include <iostream>
#include <vector>
#include <queue>
#include <valarray>

int GetMaxLength(std::vector<int>& nums) {
  size_t max_length = 0;
  for (int & i : nums) {
    max_length = std::max(max_length, std::to_string(i).length());
  }
  return max_length;
}

void RadixSort(std::vector<int>& nums) {
  std::vector<std::queue<int>> queues(514);
  int max_length = GetMaxLength(nums);
  for (int i = 0; i < max_length; ++i) {
    for (int j = 0; j < nums.size(); ++j) {
      int digit = (nums[j] / int(std::pow(256, i))) % 256;
      queues[digit+256].push(nums[j]);
    }
    int l = 0;
    for (int j = 0; j < 514; ++j) {
      while(!queues[j].empty()) {
        nums[l] = queues[j].front();
        queues[j].pop();
        l += 1;
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
  RadixSort(nums);
  for (int num : nums) {
    std::cout << num << " ";
  }
}