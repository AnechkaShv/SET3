#include <iostream>
#include <vector>
#include <random>
#include <bitset>

std::vector<int> hex2bin(char c) {
  int num;
  if (c <= '9') {
    num = c - '0';
  } else {
    num = c - 'A' + 10;
  }
  std::vector<int> res(4);
  std::bitset<4> bin_num(num);
  int j = 0;
  for (int i = 3; i >= 0; --i) {
    res[j] = bin_num[i];
    j += 1;
  }
  return res;
}


std::vector<std::vector<int>> UnpackMatrix(int n) {
  std::vector<std::vector<int>> result(n, std::vector<int>(n));
  for (int l = 0; l < n; ++l) {
    int j = 0;
    for (int i = 0; i < (n+3)/4; ++i) {
      char c;
      std::cin >> c;
      auto res = hex2bin(c);
      for (int k = 0; k < res.size() && k + 4 * i < n; ++k) {
        result[l][j] = res[k];
        j += 1;
      }
    }
  }
  return result;
}

std::vector<int> GenerateVector(int n) {
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<> distr(0, 1);
  std::vector<int> vect(n);
  for (int i = 0; i < n; ++i) {
    vect[i] = distr(generator);
  }
  return vect;
}

std::vector<int> Multiply(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vector) {
  int n = matrix.size();
  std::vector<int> res(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      res[i] = (res[i] + matrix[i][j] * vector[j]) % 2;
    }
  }
  return res;
}

int check(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {

  auto vector = GenerateVector(A.size());
  auto Br = Multiply(B, vector);
  auto X = Multiply(A, Br);
  auto Y = Multiply(C, vector);
  return X == Y;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;

  auto A = UnpackMatrix(n);
  auto B = UnpackMatrix(n);
  auto C = UnpackMatrix(n);
  bool flag = true;
  for (int i = 0; i < 10; ++i) {
    flag = check(A, B, C);
    if (!flag){
      break;
    }
  }
  if (flag) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}
