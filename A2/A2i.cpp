#include <iostream>
#include <vector>


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

void merge(std::vector<int>& nums, int left, int mid, int right) {

  std::vector<int> left_sorted(mid - left + 1);
  std::vector<int> right_sorted(right - mid);

  for (int i = 0; i < left_sorted.size(); i++)
    left_sorted[i] = nums[left + i];
  for (int i = 0; i < right_sorted.size(); i++)
    right_sorted[i] = nums[mid + 1 + i];

  int i = 0;
  int j = 0;
  size_t k = left;
  while (i < left_sorted.size() && j < right_sorted.size()) {
    if (left_sorted[i] <= right_sorted[j]) {
      nums[k] = left_sorted[i];
      i++;
    } else {
      nums[k] = right_sorted[j];
      j++;
    }
    k++;
  }

  while (i < left_sorted.size()) {
    nums[k] = left_sorted[i];
    i++;
    k++;
  }

  while (j < right_sorted.size()) {
    nums[k] = right_sorted[j];
    j++;
    k++;
  }
}

void mergeSort(std::vector<int>& nums, int left, int right) {
  if (left < right) {
    if (right - left <= 500) {
      insertionSort(nums, left, right);
      return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
  }
}

//int main() {
//  int n;
//  std::cin >> n;
//  std::vector<int> nums(n);
//  for (int i = 0; i < n; ++i) {
//    std::cin >> nums[i];
//  }
//  mergeSort(nums, 0, n - 1);
//  for (int i = 0; i < n; ++i) {
//    std::cout << nums[i] << " ";
//  }
//}