#include <time.h>
// Utilities for profiling code

#if ENABLE_PROFILING

    #define declareProfilingVariables(functionName) inline static clock_t functionName##Time = 0; inline static long functionName##CallCount = 0

    #define startProfile(functionName) \
[[maybe_unused]] clock_t functionName##Begin = clock();   \
Profile::functionName##CallCount++; \

    #define endProfile(functionName) Profile::functionName##Time += clock() - functionName##Begin;

    #define incrementCallCount(functionName) Profile::functionName##CallCount++;


#else

    #define incrementCallCount(functionName)

    #define declareProfilingVariables(functionName)

    #define startProfile(functionName)

    #define endProfile(functionName)
#endif

namespace dd {
    struct Profile {
        declareProfilingVariables(groupIntersect);
        declareProfilingVariables(cosetIntersectModP);
        declareProfilingVariables(cosetIntersectPauli);
        declareProfilingVariables(constructStabilizer);
        declareProfilingVariables(recoverPhase);
        declareProfilingVariables(gramSchmidt);
        declareProfilingVariables(gaussianElimination);
        declareProfilingVariables(normalizeLIMDD);
        declareProfilingVariables(makeDDNode);
        declareProfilingVariables(add);
        declareProfilingVariables(multiply2);
        declareProfilingVariables(applyPauli);
        declareProfilingVariables(applyHadamard);
        declareProfilingVariables(applyPhase);
        declareProfilingVariables(applyControlledPauli);
        declareProfilingVariables(applyProjection);
        declareProfilingVariables(getVector);
        inline static size_t intersectionMemoizationHits = 0;
    };

}