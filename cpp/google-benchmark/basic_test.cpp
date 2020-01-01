#include <benchmark/benchmark.h>


static void BM_LoopHundred(benchmark::State& state) {
  for (auto _ : state) {
    volatile int k = 0;
    for (int i = 0; i < 100; ++i) k *= k;
  }
}
BENCHMARK(BM_LoopHundred);

static void BM_LoopThousand(benchmark::State& state) {
  for (auto _ : state) {
    volatile int k = 0;
    for (int i = 0; i < 1000; ++i) k *= k;
  }
}
BENCHMARK(BM_LoopThousand);

static void BM_LoopMillion(benchmark::State& state) {
  for (auto _ : state) {
    volatile int k = 0;
    for (int i = 0; i < 1000000; ++i) k *= k;
  }
}
BENCHMARK(BM_LoopMillion);


BENCHMARK_MAIN();
