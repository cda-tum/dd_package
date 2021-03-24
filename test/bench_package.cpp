/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#include "DDpackage.h"

#include <benchmark/benchmark.h>
#include <memory>

///
/// Test DD Package creation
///
/// At the moment packages are allocated with a fixed maximum number of qubits (=128)
/// In the future, the maximum number of qubits can be set at construction time
/// until then, each creation should take equally long
///

static void BM_PackageCreation(benchmark::State& state) {
    for (auto _: state) {
        [[maybe_unused]] unsigned short nqubits = state.range(0);
        auto                            dd      = std::make_unique<dd::Package>();
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
BENCHMARK(BM_MakeIdent)->Unit(benchmark::kMicrosecond)->RangeMultiplier(2)->Range(16, 128);

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
BENCHMARK(BM_MakeSingleQubitGateDD_TargetTop)->Unit(benchmark::kMicrosecond)->RangeMultiplier(2)->Range(16, 128);

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
BENCHMARK(BM_MakeSingleQubitGateDD_TargetMiddle)->Unit(benchmark::kMicrosecond)->RangeMultiplier(2)->Range(16, 128);

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
BENCHMARK(BM_MakeSingleQubitGateDD_TargetBottom)->Unit(benchmark::kMicrosecond)->RangeMultiplier(2)->Range(16, 128);

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
BENCHMARK(BM_MakeControlledQubitGateDD_ControlBottom_TargetTop)->Unit(benchmark::kMicrosecond)->RangeMultiplier(2)->Range(16, 128);

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
BENCHMARK(BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle)->Unit(benchmark::kMicrosecond)->RangeMultiplier(2)->Range(16, 128);

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
BENCHMARK(BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle)->Unit(benchmark::kMicrosecond)->RangeMultiplier(2)->Range(16, 128);

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
BENCHMARK(BM_MakeControlledQubitGateDD_ControlTop_TargetBottom)->Unit(benchmark::kMicrosecond)->RangeMultiplier(2)->Range(16, 128);
