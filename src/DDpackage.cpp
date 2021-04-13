/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#include "DDpackage.hpp"

#include <cstdlib>
#include <iomanip>

namespace dd {
    void Package::printInformation() {
        std::cout << "\n  compiled: " << __DATE__ << " " << __TIME__
                  << "\n  Complex size: " << sizeof(Complex) << " bytes (aligned " << alignof(Complex) << " bytes)"
                  << "\n  ComplexValue size: " << sizeof(ComplexValue) << " bytes (aligned " << alignof(ComplexValue) << " bytes)"
                  << "\n  ComplexNumbers size: " << sizeof(ComplexNumbers) << " bytes (aligned " << alignof(ComplexNumbers) << " bytes)"
                  << "\n  vEdge size: " << sizeof(vEdge) << " bytes (aligned " << alignof(vEdge) << " bytes)"
                  << "\n  vNode size: " << sizeof(vNode) << " bytes (aligned " << alignof(vNode) << " bytes)"
                  << "\n  mEdge size: " << sizeof(mEdge) << " bytes (aligned " << alignof(mEdge) << " bytes)"
                  << "\n  mNode size: " << sizeof(mNode) << " bytes (aligned " << alignof(mNode) << " bytes)"
                  << "\n  CT Vector Add size: " << sizeof(decltype(vectorAdd)::Entry) << " bytes (aligned " << alignof(decltype(vectorAdd)::Entry) << " bytes)"
                  << "\n  CT Matrix Add size: " << sizeof(decltype(matrixAdd)::Entry) << " bytes (aligned " << alignof(decltype(matrixAdd)::Entry) << " bytes)"
                  << "\n  CT Matrix Transpose size: " << sizeof(decltype(matrixTranspose)::Entry) << " bytes (aligned " << alignof(decltype(matrixTranspose)::Entry) << " bytes)"
                  << "\n  CT Conjugate Matrix Transpose size: " << sizeof(decltype(conjugateMatrixTranspose)::Entry) << " bytes (aligned " << alignof(decltype(conjugateMatrixTranspose)::Entry) << " bytes)"
                  << "\n  CT Matrix Multiplication size: " << sizeof(decltype(matrixMultiplication)::Entry) << " bytes (aligned " << alignof(decltype(matrixMultiplication)::Entry) << " bytes)"
                  << "\n  CT Matrix Vector Multiplication size: " << sizeof(decltype(matrixVectorMultiplication)::Entry) << " bytes (aligned " << alignof(decltype(matrixVectorMultiplication)::Entry) << " bytes)"
                  << "\n  CT Vector Inner Product size: " << sizeof(decltype(vectorInnerProduct)::Entry) << " bytes (aligned " << alignof(decltype(vectorInnerProduct)::Entry) << " bytes)"
                  << "\n  CT Vector Kronecker size: " << sizeof(decltype(vectorKronecker)::Entry) << " bytes (aligned " << alignof(decltype(vectorKronecker)::Entry) << " bytes)"
                  << "\n  CT Matrix Kronecker size: " << sizeof(decltype(matrixKronecker)::Entry) << " bytes (aligned " << alignof(decltype(matrixKronecker)::Entry) << " bytes)"
                  << "\n  ToffoliTable::Entry size: " << sizeof(ToffoliTable<mEdge>::Entry) << " bytes (aligned " << alignof(ToffoliTable<mEdge>::Entry) << " bytes)"
                  << "\n  Package size: " << sizeof(Package) << " bytes (aligned " << alignof(Package) << " bytes)"
                  << "\n"
                  << std::flush;
    }

    void Package::statistics() {
        std::cout << "DD statistics:" << std::endl
                  << "[vUniqueTable] ";
        vUniqueTable.printStatistics();
        std::cout << "[mUniqueTable] ";
        mUniqueTable.printStatistics();
        std::cout << "[CT Vector Add] ";
        vectorAdd.printStatistics();
        std::cout << "[CT Matrix Add] ";
        matrixAdd.printStatistics();
        std::cout << "[CT Matrix Transpose] ";
        matrixTranspose.printStatistics();
        std::cout << "[CT Conjugate Matrix Transpose] ";
        conjugateMatrixTranspose.printStatistics();
        std::cout << "[CT Matrix Multiplication] ";
        matrixMultiplication.printStatistics();
        std::cout << "[CT Matrix Vector Multiplication] ";
        matrixVectorMultiplication.printStatistics();
        std::cout << "[CT Inner Product] ";
        vectorInnerProduct.printStatistics();
        std::cout << "[CT Vector Kronecker] ";
        vectorKronecker.printStatistics();
        std::cout << "[CT Matrix Kronecker] ";
        matrixKronecker.printStatistics();
        std::cout << "[Toffoli Table] ";
        toffoliTable.printStatistics();
        std::cout << "[Operation Table] ";
        noiseOperationTable.printStatistics();
    }

    Package::vEdge Package::normalize(const Package::vEdge& e, bool cached) {
        auto argmax = -1;

        auto zero = std::array{CN::equalsZero(e.p->e[0].w), CN::equalsZero(e.p->e[1].w)};

        for (auto i = 0U; i < RADIX; i++) {
            // make sure to release cached numbers approximately zero, but not exactly zero
            if (zero[i] && e.p->e[i].w != CN::ZERO) {
                cn.releaseCached(e.p->e[i].w);
                e.p->e[i] = vEdge::zero;
            }
        }

        fp sum = 0.;
        fp div = 0.;
        for (auto i = 0U; i < RADIX; ++i) {
            if (e.p->e[i].p == nullptr || zero[i]) {
                continue;
            }

            if (argmax == -1) {
                argmax = static_cast<decltype(argmax)>(i);
                div    = ComplexNumbers::mag2(e.p->e[i].w);
                sum    = div;
            } else {
                sum += ComplexNumbers::mag2(e.p->e[i].w);
            }
        }

        // all equal to zero
        if (argmax == -1) {
            if (!cached && !e.isTerminal()) {
                // If it is not a cached computation, the node has to be put back into the chain
                vUniqueTable.returnNode(e.p);
            }
            return vEdge::zero;
        }

        sum = std::sqrt(sum / div);

        auto  r   = e;
        auto& max = r.p->e[argmax];
        if (cached && max.w != CN::ONE) {
            r.w = max.w;
            r.w.r->val *= sum;
            r.w.i->val *= sum;
        } else {
            r.w = cn.lookup(ComplexNumbers::val(max.w.r) * sum, ComplexNumbers::val(max.w.i) * sum);
            if (CN::equalsZero(r.w)) {
                return vEdge::zero;
            }
        }
        max.w = cn.lookup(static_cast<fp>(1.0) / sum, 0.);
        if (max.w == CN::ZERO)
            max = vEdge::zero;

        auto  argmin = (argmax + 1) % 2;
        auto& min    = r.p->e[argmin];
        if (!zero[argmin]) {
            if (cached) {
                cn.releaseCached(min.w);
                CN::div(min.w, min.w, r.w);
                min.w = cn.lookup(min.w);
                if (min.w == CN::ZERO) {
                    min = vEdge::zero;
                }
            } else {
                auto c = cn.getTempCachedComplex();
                CN::div(c, min.w, r.w);
                min.w = cn.lookup(c);
                if (min.w == CN::ZERO) {
                    min = vEdge::zero;
                }
            }
        }

        return r;
    }

    Package::vEdge Package::makeZeroState(QubitCount n) {
        assert(n <= nqubits);

        auto f = vEdge::one;
        for (std::size_t p = 0; p < n; p++) {
            f = makeDDNode(static_cast<Qubit>(p), std::array{f, vEdge::zero});
        }
        return f;
    }

    Package::vEdge Package::makeBasisState(QubitCount n, const std::vector<bool>& state) {
        assert(n <= nqubits);

        auto f = vEdge::one;
        for (std::size_t p = 0; p < n; ++p) {
            if (state[p] == 0) {
                f = makeDDNode(static_cast<Qubit>(p), std::array{f, vEdge::zero});
            } else {
                f = makeDDNode(static_cast<Qubit>(p), std::array{vEdge::zero, f});
            }
        }
        return f;
    }

    Package::vEdge Package::makeBasisState(QubitCount n, const std::vector<BasisStates>& state) {
        assert(n <= nqubits);

        if (state.size() < n) {
            throw std::invalid_argument("Insufficient qubit states provided. Requested " + std::to_string(n) + ", but received " + std::to_string(state.size()));
        }

        auto f = vEdge::one;
        for (std::size_t p = 0; p < n; ++p) {
            switch (state[p]) {
                case BasisStates::zero:
                    f = makeDDNode(static_cast<Qubit>(p), std::array{f, vEdge::zero});
                    break;
                case BasisStates::one:
                    f = makeDDNode(static_cast<Qubit>(p), std::array{vEdge::zero, f});
                    break;
                case BasisStates::plus:
                    f = makeDDNode(static_cast<Qubit>(p), std::array<vEdge, RADIX>{{{f.p, cn.lookup(dd::SQRT2_2, 0)}, {f.p, cn.lookup(dd::SQRT2_2, 0)}}});
                    break;
                case BasisStates::minus:
                    f = makeDDNode(static_cast<Qubit>(p), std::array<vEdge, RADIX>{{{f.p, cn.lookup(dd::SQRT2_2, 0)}, {f.p, cn.lookup(-dd::SQRT2_2, 0)}}});
                    break;
                case BasisStates::right:
                    f = makeDDNode(static_cast<Qubit>(p), std::array<vEdge, RADIX>{{{f.p, cn.lookup(dd::SQRT2_2, 0)}, {f.p, cn.lookup(0, dd::SQRT2_2)}}});
                    break;
                case BasisStates::left:
                    f = makeDDNode(static_cast<Qubit>(p), std::array<vEdge, RADIX>{{{f.p, cn.lookup(dd::SQRT2_2, 0)}, {f.p, cn.lookup(0, -dd::SQRT2_2)}}});
                    break;
            }
        }
        return f;
    }

    Package::mEdge Package::normalize(const Package::mEdge& e, bool cached) {
        auto argmax = -1;

        auto zero = std::array{CN::equalsZero(e.p->e[0].w),
                               CN::equalsZero(e.p->e[1].w),
                               CN::equalsZero(e.p->e[2].w),
                               CN::equalsZero(e.p->e[3].w)};

        for (auto i = 0U; i < NEDGE; i++) {
            // make sure to release cached numbers approximately zero, but not exactly zero
            if (zero[i] && e.p->e[i].w != CN::ZERO) {
                cn.releaseCached(e.p->e[i].w);
                e.p->e[i] = mEdge::zero;
            }
        }

        fp   max  = 0;
        auto maxc = CN::ONE;
        // determine max amplitude
        for (auto i = 0U; i < NEDGE; ++i) {
            if (zero[i]) continue;
            if (argmax == -1) {
                argmax = static_cast<decltype(argmax)>(i);
                max    = ComplexNumbers::mag2(e.p->e[i].w);
                maxc   = e.p->e[i].w;
            } else {
                auto mag = ComplexNumbers::mag2(e.p->e[i].w);
                if (mag - max > CN::TOLERANCE) {
                    argmax = static_cast<decltype(argmax)>(i);
                    max    = mag;
                    maxc   = e.p->e[i].w;
                }
            }
        }

        // all equal to zero
        if (argmax == -1) {
            if (!cached && !e.isTerminal()) {
                // If it is not a cached computation, the node has to be put back into the chain
                mUniqueTable.returnNode(e.p);
            }
            return mEdge::zero;
        }

        auto r = e;
        // divide each entry by max
        for (auto i = 0U; i < NEDGE; ++i) {
            if (static_cast<decltype(argmax)>(i) == argmax) {
                if (cached) {
                    if (r.w == CN::ONE)
                        r.w = maxc;
                    else
                        CN::mul(r.w, r.w, maxc);
                } else {
                    if (r.w == CN::ONE) {
                        r.w = maxc;
                    } else {
                        auto c = cn.getTempCachedComplex();
                        CN::mul(c, r.w, maxc);
                        r.w = cn.lookup(c);
                    }
                }
                r.p->e[i].w = CN::ONE;
            } else {
                if (zero[i]) {
                    if (cached && r.p->e[i].w != ComplexNumbers::ZERO)
                        cn.releaseCached(r.p->e[i].w);
                    r.p->e[i] = mEdge::zero;
                    continue;
                }
                if (cached && !zero[i] && r.p->e[i].w != ComplexNumbers::ONE) {
                    cn.releaseCached(r.p->e[i].w);
                }
                if (CN::equalsOne(r.p->e[i].w))
                    r.p->e[i].w = ComplexNumbers::ONE;
                auto c = cn.getTempCachedComplex();
                CN::div(c, r.p->e[i].w, maxc);
                r.p->e[i].w = cn.lookup(c);
            }
        }
        return r;
    }

    Package::mEdge Package::makeGateDD(const std::array<ComplexValue, NEDGE>& mat, QubitCount n, const std::set<Control>& controls, Qubit target) {
        assert(n <= nqubits);

        std::array<mEdge, NEDGE> em{};
        auto                     it = controls.begin();
        for (auto i = 0U; i < NEDGE; ++i) {
            if (mat[i].r == 0 && mat[i].i == 0) {
                em[i] = mEdge::zero;
            } else {
                em[i] = mEdge::terminal(cn.lookup(mat[i]));
            }
        }

        //process lines below target
        Qubit z = 0;
        for (; z < target; z++) {
            for (auto i1 = 0U; i1 < RADIX; i1++) {
                for (auto i2 = 0U; i2 < RADIX; i2++) {
                    auto i = i1 * RADIX + i2;
                    if (it != controls.end() && it->qubit == z) {
                        if (it->type == Control::Type::neg) { // neg. control
                            em[i] = makeDDNode(z, std::array{em[i], mEdge::zero, mEdge::zero, (i1 == i2) ? makeIdent(z) : mEdge::zero});
                        } else { // pos. control
                            em[i] = makeDDNode(z, std::array{(i1 == i2) ? makeIdent(z) : mEdge::zero, mEdge::zero, mEdge::zero, em[i]});
                        }
                    } else { // not connected
                        em[i] = makeDDNode(z, std::array{em[i], mEdge::zero, mEdge::zero, em[i]});
                    }
                }
            }
            if (it != controls.end() && it->qubit == z) {
                ++it;
            }
        }

        // target line
        auto e = makeDDNode(z, em);

        //process lines above target
        for (; z < static_cast<Qubit>(n - 1); z++) {
            auto q = static_cast<Qubit>(z + 1);
            if (it != controls.end() && it->qubit == q) {
                if (it->type == Control::Type::neg) { // neg. control
                    e = makeDDNode(q, std::array{e, mEdge::zero, mEdge::zero, makeIdent(q)});
                } else { // pos. control
                    e = makeDDNode(q, std::array{makeIdent(q), mEdge::zero, mEdge::zero, e});
                }
                ++it;
            } else { // not connected
                e = makeDDNode(q, std::array{e, mEdge::zero, mEdge::zero, e});
            }
        }
        return e;
    }

    void Package::checkSpecialMatrices(Package::mNode* p) {
        if (p->v == -1)
            return;

        p->ident = false; // assume not identity
        p->symm  = false; // assume symmetric

        // check if matrix is symmetric
        if (!p->e[0].p->symm || !p->e[3].p->symm) return;
        if (transpose(p->e[1]) != p->e[2]) return;
        p->symm = true;

        // check if matrix resembles identity
        if (!(p->e[0].p->ident) || (p->e[1].w) != CN::ZERO || (p->e[2].w) != CN::ZERO || (p->e[0].w) != CN::ONE ||
            (p->e[3].w) != CN::ONE || !(p->e[3].p->ident))
            return;
        p->ident = true;
    }

    void Package::garbageCollect(bool force) {
        [[maybe_unused]] auto vCollect = vUniqueTable.garbageCollect(force);
        [[maybe_unused]] auto mCollect = mUniqueTable.garbageCollect(force);
        [[maybe_unused]] auto cCollect = cn.garbageCollect(force);

        // IMPORTANT clear all compute tables
        clearComputeTables();
    }

    void Package::clearComputeTables() {
        vectorAdd.clear();
        matrixAdd.clear();
        matrixTranspose.clear();
        conjugateMatrixTranspose.clear();
        matrixMultiplication.clear();
        matrixVectorMultiplication.clear();
        vectorInnerProduct.clear();
        vectorKronecker.clear();
        matrixKronecker.clear();

        toffoliTable.clear();

        clearIdentityTable();

        noiseOperationTable.clear();
    }

    Package::mEdge Package::transpose(const Package::mEdge& a) {
        if (a.p == nullptr || a.isTerminal() || a.p->symm) {
            return a;
        }

        // check in compute table
        auto r = matrixTranspose.lookup(a);
        if (r.p != nullptr) {
            return r;
        }

        std::array<mEdge, NEDGE> e{};
        // transpose sub-matrices and rearrange as required
        for (auto i = 0U; i < RADIX; ++i) {
            for (auto j = 0U; j < RADIX; ++j) {
                e[RADIX * i + j] = transpose(a.p->e[RADIX * j + i]);
            }
        }
        // create new top node
        r = makeDDNode(a.p->v, e);
        // adjust top weight
        auto c = cn.getTempCachedComplex();
        CN::mul(c, r.w, a.w);
        r.w = cn.lookup(c);

        // put in compute table
        matrixTranspose.insert(a, r);
        return r;
    }

    Package::mEdge Package::conjugateTranspose(const Package::mEdge& a) {
        if (a.p == nullptr)
            return a;
        if (a.isTerminal()) { // terminal case
            auto r = a;
            r.w    = CN::conj(a.w);
            return r;
        }

        // check if in compute table
        auto r = conjugateMatrixTranspose.lookup(a);
        if (r.p != nullptr) {
            return r;
        }

        std::array<mEdge, NEDGE> e{};
        // conjugate transpose submatrices and rearrange as required
        for (auto i = 0U; i < RADIX; ++i) {
            for (auto j = 0U; j < RADIX; ++j) {
                e[RADIX * i + j] = conjugateTranspose(a.p->e[RADIX * j + i]);
            }
        }
        // create new top node
        r = makeDDNode(a.p->v, e);

        auto c = cn.getTempCachedComplex();
        // adjust top weight including conjugate
        CN::mul(c, r.w, CN::conj(a.w));
        r.w = cn.lookup(c);

        // put it in the compute table
        conjugateMatrixTranspose.insert(a, r);
        return r;
    }

    Package::vEdge Package::multiply2(const Package::mEdge& x, const Package::vEdge& y, Qubit var) {
        if (x.p == nullptr) return {nullptr, CN::ZERO};
        if (y.p == nullptr) return y;

        if (x.w == CN::ZERO || y.w == CN::ZERO) {
            return vEdge::zero;
        }

        if (var == -1) {
            return vEdge::terminal(cn.mulCached(x.w, y.w));
        }

        auto xCopy = x;
        xCopy.w    = CN::ONE;
        auto yCopy = y;
        yCopy.w    = CN::ONE;

        auto r = matrixVectorMultiplication.lookup(xCopy, yCopy);
        if (r.p != nullptr) {
            if (CN::equalsZero(r.w)) {
                return vEdge::zero;
            } else {
                auto e = vEdge{r.p, cn.getCachedComplex(r.w)};
                CN::mul(e.w, e.w, x.w);
                CN::mul(e.w, e.w, y.w);
                if (CN::equalsZero(e.w)) {
                    cn.releaseCached(e.w);
                    return vEdge::zero;
                }
                return e;
            }
        }

        vEdge e{};
        if (x.p->v == var && x.p->v == y.p->v) {
            if (x.p->ident) {
                e = yCopy;
                matrixVectorMultiplication.insert(xCopy, yCopy, {e.p, e.w});
                e.w = cn.mulCached(x.w, y.w);
                if (CN::equalsZero(e.w)) {
                    cn.releaseCached(e.w);
                    return vEdge::zero;
                }
                return e;
            }
        }

        std::array<vEdge, RADIX> edge{};
        for (auto i = 0U; i < RADIX; i++) {
            edge[i] = vEdge::zero;
            for (auto k = 0U; k < RADIX; k++) {
                mEdge e1{};
                if (!x.isTerminal() && x.p->v == var) {
                    e1 = x.p->e[RADIX * i + k];
                } else {
                    e1 = xCopy;
                }
                vEdge e2{};
                if (!y.isTerminal() && y.p->v == var) {
                    e2 = y.p->e[k];
                } else {
                    e2 = yCopy;
                }

                auto m = multiply2(e1, e2, static_cast<Qubit>(var - 1));

                if (k == 0 || edge[i].w == CN::ZERO) {
                    edge[i] = m;
                } else if (m.w != CN::ZERO) {
                    auto old_e = edge[i];
                    edge[i]    = add2(edge[i], m);
                    cn.releaseCached(old_e.w);
                    cn.releaseCached(m.w);
                }
            }
        }
        e = makeDDNode(var, edge, true);

        matrixVectorMultiplication.insert(xCopy, yCopy, {e.p, e.w});

        if (e.w != CN::ZERO && (x.w != CN::ONE || y.w != CN::ONE)) {
            if (e.w == CN::ONE) {
                e.w = cn.mulCached(x.w, y.w);
            } else {
                CN::mul(e.w, e.w, x.w);
                CN::mul(e.w, e.w, y.w);
            }
            if (CN::equalsZero(e.w)) {
                cn.releaseCached(e.w);
                return vEdge::zero;
            }
        }
        return e;
    }

    Package::mEdge Package::multiply2(const Package::mEdge& x, const Package::mEdge& y, Qubit var) {
        if (x.p == nullptr) return x;
        if (y.p == nullptr) return y;

        if (x.w == CN::ZERO || y.w == CN::ZERO) {
            return mEdge::zero;
        }

        if (var == -1) {
            return mEdge::terminal(cn.mulCached(x.w, y.w));
        }

        auto xCopy = x;
        xCopy.w    = CN::ONE;
        auto yCopy = y;
        yCopy.w    = CN::ONE;

        auto r = matrixMultiplication.lookup(xCopy, yCopy);
        if (r.p != nullptr) {
            if (CN::equalsZero(r.w)) {
                return mEdge::zero;
            } else {
                auto e = mEdge{r.p, cn.getCachedComplex(r.w)};
                CN::mul(e.w, e.w, x.w);
                CN::mul(e.w, e.w, y.w);
                if (CN::equalsZero(e.w)) {
                    cn.releaseCached(e.w);
                    return mEdge::zero;
                }
                return e;
            }
        }

        mEdge e{};
        if (x.p->v == var && x.p->v == y.p->v) {
            if (x.p->ident) {
                if (y.p->ident) {
                    e = makeIdent(0, var);
                } else {
                    e = yCopy;
                }
                matrixMultiplication.insert(xCopy, yCopy, {e.p, e.w});
                e.w = cn.mulCached(x.w, y.w);
                if (CN::equalsZero(e.w)) {
                    cn.releaseCached(e.w);
                    return mEdge::zero;
                }
                return e;
            }
            if (y.p->ident) {
                e = xCopy;
                matrixMultiplication.insert(xCopy, yCopy, {e.p, e.w});
                e.w = cn.mulCached(x.w, y.w);

                if (CN::equalsZero(e.w)) {
                    cn.releaseCached(e.w);
                    return mEdge::zero;
                }
                return e;
            }
        }

        std::array<mEdge, NEDGE> edge{};
        mEdge                    e1{}, e2{};
        for (auto i = 0U; i < NEDGE; i += RADIX) {
            for (auto j = 0U; j < RADIX; j++) {
                edge[i + j] = mEdge::zero;
                for (auto k = 0U; k < RADIX; k++) {
                    if (!x.isTerminal() && x.p->v == var) {
                        e1 = x.p->e[i + k];
                    } else {
                        e1 = xCopy;
                    }
                    if (!y.isTerminal() && y.p->v == var) {
                        e2 = y.p->e[j + RADIX * k];
                    } else {
                        e2 = yCopy;
                    }

                    auto m = multiply2(e1, e2, static_cast<Qubit>(var - 1));

                    if (k == 0 || edge[i + j].w == CN::ZERO) {
                        edge[i + j] = m;
                    } else if (m.w != CN::ZERO) {
                        auto old_e  = edge[i + j];
                        edge[i + j] = add2(edge[i + j], m);
                        cn.releaseCached(old_e.w);
                        cn.releaseCached(m.w);
                    }
                }
            }
        }
        e = makeDDNode(var, edge, true);

        matrixMultiplication.insert(xCopy, yCopy, {e.p, e.w});

        if (e.w != CN::ZERO && (x.w != CN::ONE || y.w != CN::ONE)) {
            if (e.w == CN::ONE) {
                e.w = cn.mulCached(x.w, y.w);
            } else {
                CN::mul(e.w, e.w, x.w);
                CN::mul(e.w, e.w, y.w);
            }
            if (CN::equalsZero(e.w)) {
                cn.releaseCached(e.w);
                return mEdge::zero;
            }
        }
        return e;
    }

    ComplexValue Package::innerProduct(const Package::vEdge& x, const Package::vEdge& y) {
        if (x.p == nullptr || y.p == nullptr || CN::equalsZero(x.w) || CN::equalsZero(y.w)) { // the 0 case
            return {0, 0};
        }

        [[maybe_unused]] const auto before = cn.cacheCount;

        auto w = x.p->v;
        if (y.p->v > w) {
            w = y.p->v;
        }
        const ComplexValue ip = innerProduct(x, y, static_cast<Qubit>(w + 1));

        [[maybe_unused]] const auto after = cn.cacheCount;
        assert(after == before);

        return ip;
    }

    fp Package::fidelity(const Package::vEdge& x, const Package::vEdge& y) {
        const auto fid = innerProduct(x, y);
        return fid.r * fid.r + fid.i * fid.i;
    }

    ComplexValue Package::innerProduct(const Package::vEdge& x, const Package::vEdge& y, Qubit var) {
        if (x.p == nullptr || y.p == nullptr || CN::equalsZero(x.w) || CN::equalsZero(y.w)) { // the 0 case
            return {0.0, 0.0};
        }

        if (var == 0) {
            auto c = cn.getTempCachedComplex();
            CN::mul(c, x.w, y.w);
            return {c.r->val, c.i->val};
        }

        auto xCopy = x;
        xCopy.w    = CN::ONE;
        auto yCopy = y;
        yCopy.w    = CN::ONE;

        auto r = vectorInnerProduct.lookup(xCopy, yCopy);
        if (r.p != nullptr) {
            auto c = cn.getTempCachedComplex(r.w);
            CN::mul(c, c, x.w);
            CN::mul(c, c, y.w);
            return {CN::val(c.r), CN::val(c.i)};
        }

        auto w = static_cast<Qubit>(var - 1);

        ComplexValue sum{0.0, 0.0};
        for (auto i = 0U; i < RADIX; i++) {
            vEdge e1{};
            if (!x.isTerminal() && x.p->v == w) {
                e1 = x.p->e[i];
            } else {
                e1 = xCopy;
            }
            vEdge e2{};
            if (!y.isTerminal() && y.p->v == w) {
                e2   = y.p->e[i];
                e2.w = CN::conj(e2.w);
            } else {
                e2 = yCopy;
            }
            auto cv = innerProduct(e1, e2, w);
            sum.r += cv.r;
            sum.i += cv.i;
        }
        r.p = vNode::terminal;
        r.w = sum;

        vectorInnerProduct.insert(xCopy, yCopy, r);
        auto c = cn.getTempCachedComplex(sum);
        CN::mul(c, c, x.w);
        CN::mul(c, c, y.w);
        return {CN::val(c.r), CN::val(c.i)};
    }

    Package::mEdge Package::extend(const Package::mEdge& e, Qubit h, Qubit l) {
        auto f = (l > 0) ? kronecker(e, makeIdent(l)) : e;
        auto g = (h > 0) ? kronecker(makeIdent(h), f) : f;
        return g;
    }

    Package::mEdge Package::partialTrace(const Package::mEdge& a, const std::vector<bool>& eliminate) {
        [[maybe_unused]] const auto before = cn.cacheCount;
        const auto                  result = trace(a, eliminate);
        [[maybe_unused]] const auto after  = cn.cacheCount;
        assert(before == after);
        return result;
    }

    ComplexValue Package::trace(const Package::mEdge& a) {
        auto                        eliminate = std::vector<bool>(nqubits, true);
        [[maybe_unused]] const auto before    = cn.cacheCount;
        const auto                  res       = partialTrace(a, eliminate);
        [[maybe_unused]] const auto after     = cn.cacheCount;
        assert(before == after);
        return {ComplexNumbers::val(res.w.r), ComplexNumbers::val(res.w.i)};
    }

    Package::mEdge Package::trace(const Package::mEdge& a, const std::vector<bool>& eliminate, std::size_t alreadyEliminated) {
        auto v = a.p->v;

        if (CN::equalsZero(a.w)) return mEdge::zero;

        if (std::none_of(eliminate.begin(), eliminate.end(), [](bool v) { return v; })) return a;

        // Base case
        if (v == -1) {
            if (a.isTerminal()) return a;
            throw std::runtime_error("Expected terminal node in trace.");
        }

        if (eliminate[v]) {
            auto elims = alreadyEliminated + 1;
            auto r     = mEdge::zero;

            auto t0 = trace(a.p->e[0], eliminate, elims);
            r       = add2(r, t0);
            auto r1 = r;

            auto t1 = trace(a.p->e[3], eliminate, elims);
            r       = add2(r, t1);
            auto r2 = r;

            if (r.w == CN::ONE) {
                r.w = a.w;
            } else {
                auto c = cn.getTempCachedComplex();
                CN::mul(c, r.w, a.w);
                r.w = cn.lookup(c); // better safe than sorry. this may result in complex values with magnitude > 1 in the complex table
            }

            if (r1.w != CN::ZERO) {
                cn.releaseCached(r1.w);
            }

            if (r2.w != CN::ZERO) {
                cn.releaseCached(r2.w);
            }

            return r;
        } else {
            auto                     adjustedV = static_cast<Qubit>(a.p->v - (std::count(eliminate.begin(), eliminate.end(), true) - alreadyEliminated));
            std::array<mEdge, NEDGE> edge{};
            std::transform(a.p->e.cbegin(),
                           a.p->e.cend(),
                           edge.begin(),
                           [&](const mEdge& e) -> mEdge { return trace(e, eliminate, alreadyEliminated); });
            auto r = makeDDNode(adjustedV, edge);

            if (r.w == CN::ONE) {
                r.w = a.w;
            } else {
                auto c = cn.getTempCachedComplex();
                CN::mul(c, r.w, a.w);
                r.w = cn.lookup(c);
            }
            return r;
        }
    }

    Package::mEdge Package::makeIdent(Qubit leastSignificantQubit, Qubit mostSignificantQubit) {
        if (mostSignificantQubit < 0)
            return mEdge::one;

        if (leastSignificantQubit == 0 && IdTable[mostSignificantQubit].p != nullptr) {
            return IdTable[mostSignificantQubit];
        }
        if (mostSignificantQubit >= 1 && (IdTable[mostSignificantQubit - 1]).p != nullptr) {
            IdTable[mostSignificantQubit] = makeDDNode(mostSignificantQubit,
                                                       std::array{IdTable[mostSignificantQubit - 1],
                                                                  mEdge::zero,
                                                                  mEdge::zero,
                                                                  IdTable[mostSignificantQubit - 1]});
            return IdTable[mostSignificantQubit];
        }

        auto e = makeDDNode(leastSignificantQubit, std::array{mEdge::one, mEdge::zero, mEdge::zero, mEdge::one});
        for (std::size_t k = leastSignificantQubit + 1; k <= std::make_unsigned_t<Qubit>(mostSignificantQubit); k++) {
            e = makeDDNode(static_cast<Qubit>(k), std::array{e, mEdge::zero, mEdge::zero, e});
        }
        if (leastSignificantQubit == 0)
            IdTable[mostSignificantQubit] = e;
        return e;
    }

    Package::mEdge Package::reduceAncillae(Package::mEdge& e, const std::vector<bool>& ancillary, bool regular) {
        // return if no more garbage left
        if (std::none_of(ancillary.begin(), ancillary.end(), [](bool v) { return v; }) || e.p == nullptr) return e;
        Qubit lowerbound = 0;
        for (auto i = 0U; i < ancillary.size(); ++i) {
            if (ancillary[i]) {
                lowerbound = static_cast<Qubit>(i);
                break;
            }
        }
        if (e.p->v < lowerbound) return e;
        return reduceAncillaeRecursion(e, ancillary, lowerbound, regular);
    }

    Package::vEdge Package::reduceGarbage(Package::vEdge& e, const std::vector<bool>& garbage) {
        // return if no more garbage left
        if (std::none_of(garbage.begin(), garbage.end(), [](bool v) { return v; }) || e.p == nullptr) return e;
        Qubit lowerbound = 0;
        for (auto i = 0U; i < garbage.size(); ++i) {
            if (garbage[i]) {
                lowerbound = static_cast<Qubit>(i);
                break;
            }
        }
        if (e.p->v < lowerbound) return e;
        return reduceGarbageRecursion(e, garbage, lowerbound);
    }

    Package::mEdge Package::reduceGarbage(Package::mEdge& e, const std::vector<bool>& garbage, bool regular) {
        // return if no more garbage left
        if (std::none_of(garbage.begin(), garbage.end(), [](bool v) { return v; }) || e.p == nullptr) return e;
        Qubit lowerbound = 0;
        for (auto i = 0U; i < garbage.size(); ++i) {
            if (garbage[i]) {
                lowerbound = static_cast<Qubit>(i);
                break;
            }
        }
        if (e.p->v < lowerbound) return e;
        return reduceGarbageRecursion(e, garbage, lowerbound, regular);
    }

    Package::mEdge Package::reduceAncillaeRecursion(Package::mEdge& e, const std::vector<bool>& ancillary, Qubit lowerbound, bool regular) {
        if (e.p->v < lowerbound) return e;

        auto f = e;

        std::array<mEdge, NEDGE> edges{};
        std::bitset<NEDGE>       handled{};
        for (auto i = 0U; i < NEDGE; ++i) {
            if (!handled.test(i)) {
                if (e.p->e[i].isTerminal()) {
                    edges[i] = e.p->e[i];
                } else {
                    edges[i] = reduceAncillaeRecursion(f.p->e[i], ancillary, lowerbound, regular);
                    for (auto j = i + 1; j < NEDGE; ++j) {
                        if (e.p->e[i].p == e.p->e[j].p) {
                            edges[j] = edges[i];
                            handled.set(j);
                        }
                    }
                }
                handled.set(i);
            }
        }
        f = makeDDNode(f.p->v, edges);

        // something to reduce for this qubit
        if (f.p->v >= 0 && ancillary[f.p->v]) {
            if (regular) {
                if (f.p->e[1].w != CN::ZERO || f.p->e[3].w != CN::ZERO) {
                    f = makeDDNode(f.p->v, std::array{f.p->e[0], mEdge::zero, f.p->e[2], mEdge::zero});
                }
            } else {
                if (f.p->e[2].w != CN::ZERO || f.p->e[3].w != CN::ZERO) {
                    f = makeDDNode(f.p->v, std::array{f.p->e[0], f.p->e[1], mEdge::zero, mEdge::zero});
                }
            }
        }

        auto c = cn.mulCached(f.w, e.w);
        f.w    = cn.lookup(c);
        cn.releaseCached(c);

        // increasing the ref count for safety. TODO: find out if this is necessary
        incRef(f);
        return f;
    }

    Package::vEdge Package::reduceGarbageRecursion(Package::vEdge& e, const std::vector<bool>& garbage, Qubit lowerbound) {
        if (e.p->v < lowerbound) return e;

        auto f = e;

        std::array<vEdge, RADIX> edges{};
        std::bitset<RADIX>       handled{};
        for (auto i = 0U; i < RADIX; ++i) {
            if (!handled.test(i)) {
                if (e.p->e[i].isTerminal()) {
                    edges[i] = e.p->e[i];
                } else {
                    edges[i] = reduceGarbageRecursion(f.p->e[i], garbage, lowerbound);
                    for (auto j = i + 1; j < RADIX; ++j) {
                        if (e.p->e[i].p == e.p->e[j].p) {
                            edges[j] = edges[i];
                            handled.set(j);
                        }
                    }
                }
                handled.set(i);
            }
        }
        f = makeDDNode(f.p->v, edges);

        // something to reduce for this qubit
        if (f.p->v >= 0 && garbage[f.p->v]) {
            if (f.p->e[1].w != CN::ZERO) {
                vEdge g{};
                if (f.p->e[0].w == CN::ZERO && f.p->e[1].w != CN::ZERO) {
                    g = f.p->e[1];
                } else if (f.p->e[1].w != CN::ZERO) {
                    g = add(f.p->e[0], f.p->e[1]);
                } else {
                    g = f.p->e[0];
                }
                f = makeDDNode(e.p->v, std::array{g, vEdge::zero});
            }
        }

        auto c = cn.mulCached(f.w, e.w);
        f.w    = cn.lookup(c);
        cn.releaseCached(c);

        // Quick-fix for normalization bug
        if (CN::mag2(f.w) > 1.0)
            f.w = CN::ONE;

        // increasing the ref count for safety. TODO: find out if this is necessary
        incRef(f);
        return f;
    }

    Package::mEdge Package::reduceGarbageRecursion(Package::mEdge& e, const std::vector<bool>& garbage, Qubit lowerbound, bool regular) {
        if (e.p->v < lowerbound) return e;

        auto f = e;

        std::array<mEdge, NEDGE> edges{};
        std::bitset<NEDGE>       handled{};
        for (auto i = 0U; i < NEDGE; ++i) {
            if (!handled.test(i)) {
                if (e.p->e[i].isTerminal()) {
                    edges[i] = e.p->e[i];
                } else {
                    edges[i] = reduceGarbageRecursion(f.p->e[i], garbage, lowerbound, regular);
                    for (auto j = i + 1; j < NEDGE; ++j) {
                        if (e.p->e[i].p == e.p->e[j].p) {
                            edges[j] = edges[i];
                            handled.set(j);
                        }
                    }
                }
                handled.set(i);
            }
        }
        f = makeDDNode(f.p->v, edges);

        // something to reduce for this qubit
        if (f.p->v >= 0 && garbage[f.p->v]) {
            if (regular) {
                if (f.p->e[2].w != CN::ZERO || f.p->e[3].w != CN::ZERO) {
                    mEdge g{};
                    if (f.p->e[0].w == CN::ZERO && f.p->e[2].w != CN::ZERO) {
                        g = f.p->e[2];
                    } else if (f.p->e[2].w != CN::ZERO) {
                        g = add(f.p->e[0], f.p->e[2]);
                    } else {
                        g = f.p->e[0];
                    }
                    mEdge h{};
                    if (f.p->e[1].w == CN::ZERO && f.p->e[3].w != CN::ZERO) {
                        h = f.p->e[3];
                    } else if (f.p->e[3].w != CN::ZERO) {
                        h = add(f.p->e[1], f.p->e[3]);
                    } else {
                        h = f.p->e[1];
                    }
                    f = makeDDNode(e.p->v, std::array{g, h, mEdge::zero, mEdge::zero});
                }
            } else {
                if (f.p->e[1].w != CN::ZERO || f.p->e[3].w != CN::ZERO) {
                    mEdge g{};
                    if (f.p->e[0].w == CN::ZERO && f.p->e[1].w != CN::ZERO) {
                        g = f.p->e[1];
                    } else if (f.p->e[1].w != CN::ZERO) {
                        g = add(f.p->e[0], f.p->e[1]);
                    } else {
                        g = f.p->e[0];
                    }
                    mEdge h{};
                    if (f.p->e[2].w == CN::ZERO && f.p->e[3].w != CN::ZERO) {
                        h = f.p->e[3];
                    } else if (f.p->e[3].w != CN::ZERO) {
                        h = add(f.p->e[2], f.p->e[3]);
                    } else {
                        h = f.p->e[2];
                    }
                    f = makeDDNode(e.p->v, std::array{g, mEdge::zero, h, mEdge::zero});
                }
            }
        }

        auto c = cn.mulCached(f.w, e.w);
        f.w    = cn.lookup(c);
        cn.releaseCached(c);

        // Quick-fix for normalization bug
        if (CN::mag2(f.w) > 1.0)
            f.w = CN::ONE;

        // increasing the ref count for safety. TODO: find out if this is necessary
        incRef(f);
        return f;
    }

    ComplexValue Package::getValueByPath(const Package::vEdge& e, std::size_t i) {
        if (e.isTerminal()) {
            return {CN::val(e.w.r), CN::val(e.w.i)};
        }
        return getValueByPath(e, CN::ONE, i);
    }

    ComplexValue Package::getValueByPath(const Package::vEdge& e, const Complex& amp, std::size_t i) {
        auto c = cn.mulCached(e.w, amp);

        if (e.isTerminal()) {
            cn.releaseCached(c);
            return {CN::val(c.r), CN::val(c.i)};
        }

        bool one = i & (1 << e.p->v);

        ComplexValue r{};
        if (!one && !CN::equalsZero(e.p->e[0].w)) {
            r = getValueByPath(e.p->e[0], c, i);
        } else if (one && !CN::equalsZero(e.p->e[1].w)) {
            r = getValueByPath(e.p->e[1], c, i);
        }
        cn.releaseCached(c);
        return r;
    }
    ComplexValue Package::getValueByPath(const Package::mEdge& e, std::size_t i, std::size_t j) {
        if (e.isTerminal()) {
            return {CN::val(e.w.r), CN::val(e.w.i)};
        }
        return getValueByPath(e, CN::ONE, i, j);
    }
    ComplexValue Package::getValueByPath(const Package::mEdge& e, const Complex& amp, std::size_t i, std::size_t j) {
        auto c = cn.mulCached(e.w, amp);

        if (e.isTerminal()) {
            cn.releaseCached(c);
            return {CN::val(c.r), CN::val(c.i)};
        }

        bool row = i & (1 << e.p->v);
        bool col = j & (1 << e.p->v);

        ComplexValue r{};
        if (!row && !col && !CN::equalsZero(e.p->e[0].w)) {
            r = getValueByPath(e.p->e[0], c, i, j);
        } else if (!row && col && !CN::equalsZero(e.p->e[1].w)) {
            r = getValueByPath(e.p->e[1], c, i, j);
        } else if (row && !col && !CN::equalsZero(e.p->e[2].w)) {
            r = getValueByPath(e.p->e[2], c, i, j);
        } else if (row && col && !CN::equalsZero(e.p->e[3].w)) {
            r = getValueByPath(e.p->e[3], c, i, j);
        }
        cn.releaseCached(c);
        return r;
    }

    CVec Package::getVector(const Package::vEdge& e) {
        std::size_t dim = 1 << (e.p->v + 1);
        // allocate resulting vector
        auto vec = CVec(dim, {0.0, 0.0});
        getVector(e, CN::ONE, 0, vec);
        return vec;
    }

    void Package::getVector(const Package::vEdge& e, const Complex& amp, std::size_t i, CVec& vec) {
        // calculate new accumulated amplitude
        auto c = cn.mulCached(e.w, amp);

        // base case
        if (e.isTerminal()) {
            vec.at(i) = {CN::val(c.r), CN::val(c.i)};
            cn.releaseCached(c);
            return;
        }

        std::size_t x = i | (1 << e.p->v);

        // recursive case
        if (!CN::equalsZero(e.p->e[0].w))
            getVector(e.p->e[0], c, i, vec);
        if (!CN::equalsZero(e.p->e[1].w))
            getVector(e.p->e[1], c, x, vec);
        cn.releaseCached(c);
    }

    void Package::printVector(const Package::vEdge& e) {
        unsigned long long element = 2u << e.p->v;
        for (unsigned long long i = 0; i < element; i++) {
            auto amplitude = getValueByPath(e, i);
            for (Qubit j = e.p->v; j >= 0; j--) {
                std::cout << ((i >> j) & 1u);
            }
            std::cout << ": " << amplitude << "\n";
        }
        std::cout << std::flush;
    }

    CMat Package::getMatrix(const Package::mEdge& e) {
        std::size_t dim = 1 << (e.p->v + 1);
        // allocate resulting matrix
        auto mat = CMat(dim, CVec(dim, {0.0, 0.0}));
        getMatrix(e, CN::ONE, 0, 0, mat);
        return mat;
    }

    void Package::getMatrix(const Package::mEdge& e, const Complex& amp, std::size_t i, std::size_t j, CMat& mat) {
        // calculate new accumulated amplitude
        auto c = cn.mulCached(e.w, amp);

        // base case
        if (e.isTerminal()) {
            mat.at(i).at(j) = {CN::val(c.r), CN::val(c.i)};
            cn.releaseCached(c);
            return;
        }

        std::size_t x = i | (1 << e.p->v);
        std::size_t y = j | (1 << e.p->v);

        // recursive case
        if (!CN::equalsZero(e.p->e[0].w))
            getMatrix(e.p->e[0], c, i, j, mat);
        if (!CN::equalsZero(e.p->e[1].w))
            getMatrix(e.p->e[1], c, i, y, mat);
        if (!CN::equalsZero(e.p->e[2].w))
            getMatrix(e.p->e[2], c, x, j, mat);
        if (!CN::equalsZero(e.p->e[3].w))
            getMatrix(e.p->e[3], c, x, y, mat);
        cn.releaseCached(c);
    }

} // namespace dd
