/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#include "DDpackage.h"

#include <benchmark/benchmark.h>
#include <chrono>
#include <memory>

static void QubitRange(benchmark::internal::Benchmark* b) {
    b->Unit(benchmark::kMicrosecond)->RangeMultiplier(2)->Range(16, 128);
}

///
/// Test class creation
///
/// At the moment packages are allocated with a fixed maximum number of qubits (=128)
/// In the future, the maximum number of qubits can be set at construction time
/// until then, each creation should take equally long
///

static void BM_DDNodeCreation(benchmark::State& state) {
    for (auto _: state) {
        auto node = dd::Node{};
        benchmark::DoNotOptimize(node);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_DDNodeCreation)->Unit(benchmark::kNanosecond);

static void BM_ComplexNumbersCreation(benchmark::State& state) {
    for (auto _: state) {
        auto cn = dd::ComplexNumbers();
        benchmark::DoNotOptimize(cn);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_ComplexNumbersCreation)->Unit(benchmark::kMicrosecond);

static void BM_PackageCreation(benchmark::State& state) {
    [[maybe_unused]] unsigned short nqubits = state.range(0);
    for (auto _: state) {
        auto dd = std::make_unique<dd::Package>();
        benchmark::DoNotOptimize(dd);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_PackageCreation)->Unit(benchmark::kMillisecond)->RangeMultiplier(2)->Range(16, 128);

///
/// Test creation of identity matrix
///

static void BM_MakeIdentCached(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    for (auto _: state) {
        benchmark::DoNotOptimize(dd->makeIdent(nqubits));
    }
}
BENCHMARK(BM_MakeIdentCached)->Unit(benchmark::kNanosecond)->RangeMultiplier(2)->Range(16, 128);

static void BM_MakeIdent(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Imat    = std::array<dd::ComplexValue, 4>{{{1., 0.}, {0., 0.}, {0., 0.}, {1., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(-1);
        line[0] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Imat, nqubits, line));
    }
}
BENCHMARK(BM_MakeIdent)->Apply(QubitRange);

///
/// Test makeGateDD
///

static void BM_MakeSingleQubitGateDD_TargetTop(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(-1);
        line[nqubits - 1] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeSingleQubitGateDD_TargetTop)->Apply(QubitRange);

static void BM_MakeSingleQubitGateDD_TargetMiddle(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(-1);
        line[nqubits / 2] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeSingleQubitGateDD_TargetMiddle)->Apply(QubitRange);

static void BM_MakeSingleQubitGateDD_TargetBottom(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(-1);
        line[0] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeSingleQubitGateDD_TargetBottom)->Apply(QubitRange);

static void BM_MakeControlledQubitGateDD_ControlBottom_TargetTop(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(-1);
        line[0]           = 1;
        line[nqubits - 1] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeControlledQubitGateDD_ControlBottom_TargetTop)->Apply(QubitRange);

static void BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(-1);
        line[0]           = 1;
        line[nqubits / 2] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle)->Apply(QubitRange);

static void BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(-1);
        line[nqubits - 1] = 1;
        line[nqubits / 2] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle)->Apply(QubitRange);

static void BM_MakeControlledQubitGateDD_ControlTop_TargetBottom(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(-1);
        line[nqubits - 1] = 1;
        line[0]           = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeControlledQubitGateDD_ControlTop_TargetBottom)->Apply(QubitRange);

static void BM_MakeFullControlledToffoliDD_TargetTop(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(1);
        line[nqubits - 1] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeFullControlledToffoliDD_TargetTop)->Apply(QubitRange);

static void BM_MakeFullControlledToffoliDD_TargetMiddle(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(1);
        line[nqubits / 2] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeFullControlledToffoliDD_TargetMiddle)->Apply(QubitRange);

static void BM_MakeFullControlledToffoliDD_TargetBottom(benchmark::State& state) {
    unsigned short nqubits = state.range(0);
    auto           dd      = std::make_unique<dd::Package>();
    auto           Xmat    = std::array<dd::ComplexValue, 4>{{{0., 0.}, {1., 0.}, {1., 0.}, {0., 0.}}};
    auto           line    = std::array<short, dd::MAXN>{};
    for (auto _: state) {
        line.fill(1);
        line[0] = 2;
        benchmark::DoNotOptimize(dd->makeGateDD(Xmat, nqubits, line));
    }
}
BENCHMARK(BM_MakeFullControlledToffoliDD_TargetBottom)->Apply(QubitRange);
