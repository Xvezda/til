#include <benchmark/benchmark.h>

#include <iostream>
#include <vector>


constexpr void const_test(std::vector<int>& ref, int n) {
  for (int i = 0; i < n; ++i) {
    ref.push_back(i);
  }
}

void test(std::vector<int>& ref, int n) {
  for (int i = 0; i < n; ++i) {
    ref.push_back(i);
  }
}

#if 0
int main(void) {
  int T;
  std::cin >> T;

  std::vector<int> res;

  test(res, T);

  for (int i = 0; i < T; ++i) {
    std::cout << "i: " << i << ", res[i]: " << res[i] << std::endl;
  }
  return 0;
}
#endif

static void BM_ConstExpr(benchmark::State& state) {
  std::vector<int> vec;
  for (auto _ : state)
    const_test(vec, 1000000);
}
BENCHMARK(BM_ConstExpr);

static void BM_NonConstExpr(benchmark::State& state) {
  std::vector<int> vec;
  for (auto _ : state)
    test(vec, 1000000);
}
BENCHMARK(BM_NonConstExpr);

BENCHMARK_MAIN();

