#include <iostream>
#include <vector>
#include <valarray>
#include <random>

void sink(std::vector<int>& nums, int k, int n) {
  while (2 * k + 1 < n) {
    int j = 2 * k + 1;
    if (j < n - 1 && nums[j] < nums[j + 1]) {
      j += 1;
    }
    if (nums[k] >= nums[j]) {
      break;
    }
    std::swap(nums[k], nums[j]);
    k = j;
  }
}

void buildMaxHeap(std::vector<int>& nums, int left, int right) {
  int n = right;
  for (int i = left + n / 2 - 1; i >= left; --i) {
    sink(nums, i, n);
  }
}

void heapSort(std::vector<int>& nums, int left, int right) {
  int n = right;
  buildMaxHeap(nums, left, right);

  while (n > left + 1) {
    std::swap(nums[left], nums[right - 1]);
    n -= 1;
    sink(nums, left, n);
  }
}

void insertionSort(std::vector<int>& nums, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    int key = nums[i];
    int j = i - 1;
    while (j >= left && nums[j] > key) {
      nums[j + 1] = nums[j];
      j -= 1;
    }
    nums[j + 1] = key;
  }
}

int partition(std::vector<int>& nums, int left, int right) {
  int pivot = nums[right];
  int i = left - 1;
  for (int j = left; j <= right - 1; ++j) {
    if (nums[j] <= pivot) {
      i += 1;
      std::swap(nums[i], nums[j]);
    }
  }
  std::swap(nums[i + 1], nums[right]);
  return i + 1;
}

void quickSort(std::vector<int>& nums, int left, int right, int depth = 0) {
  if (left < right) {
    if (right - left < 15) {
      insertionSort(nums, left, right);
      return;
    }

    if (depth >= 2 * std::log2(nums.size())) {
      make_heap(nums.begin() + left, nums.begin() + right + 1);
      sort_heap(nums.begin() + left, nums.begin() + right + 1);
      return;
    }

    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1, depth + 1);
    quickSort(nums, pivot + 1, right, depth + 1);
  }
}

//int main() {
//  int n;
//  std::cin >> n;
//  std::vector<int> nums(n);
//  for (int i = 0; i < n; ++i) {
//    std::cin >> nums[i];
//  }
//  quickSort(nums, 0, n - 1);
//  for (int i = 0; i < n; ++i) {
//    std::cout << nums[i] << " ";
//  }
//}