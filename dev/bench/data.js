window.BENCHMARK_DATA = {
  "lastUpdate": 1617296490048,
  "repoUrl": "https://github.com/iic-jku/dd_package",
  "entries": {
    "Benchmark": [
      {
        "commit": {
          "author": {
            "name": "iic-jku",
            "username": "iic-jku"
          },
          "committer": {
            "name": "iic-jku",
            "username": "iic-jku"
          },
          "id": "4c498bf1a68645a25a2c55bf7081d34670ee94b9",
          "message": "[WIP] Google Benchmark for JKQ Tools",
          "timestamp": "2021-03-24T12:48:45Z",
          "url": "https://github.com/iic-jku/dd_package/pull/6/commits/4c498bf1a68645a25a2c55bf7081d34670ee94b9"
        },
        "date": 1616774869641,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_DDVectorNodeCreation",
            "value": 9.928836516607497,
            "unit": "ns/iter",
            "extra": "iterations: 68285401\ncpu: 9.873666627512375 ns\nthreads: 1"
          },
          {
            "name": "BM_DDMatrixNodeCreation",
            "value": 9.942417619444997,
            "unit": "ns/iter",
            "extra": "iterations: 70835557\ncpu: 9.941584690298969 ns\nthreads: 1"
          },
          {
            "name": "BM_ComplexNumbersCreation",
            "value": 27.24759676089116,
            "unit": "us/iter",
            "extra": "iterations: 26674\ncpu: 27.24566233035916 us\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/2",
            "value": 12.696540280701715,
            "unit": "ms/iter",
            "extra": "iterations: 57\ncpu: 12.690064842105263 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/4",
            "value": 12.008730372881338,
            "unit": "ms/iter",
            "extra": "iterations: 59\ncpu: 11.890837152542375 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/8",
            "value": 11.816498311475709,
            "unit": "ms/iter",
            "extra": "iterations: 61\ncpu: 11.805975344262292 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/16",
            "value": 11.705241789473432,
            "unit": "ms/iter",
            "extra": "iterations: 57\ncpu: 11.699148807017549 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/32",
            "value": 12.62423735714283,
            "unit": "ms/iter",
            "extra": "iterations: 56\ncpu: 12.611410589285722 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/64",
            "value": 13.10021964285722,
            "unit": "ms/iter",
            "extra": "iterations: 56\ncpu: 13.095650017857142 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/128",
            "value": 12.968134454545385,
            "unit": "ms/iter",
            "extra": "iterations: 55\ncpu: 12.960487163636374 ms\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/2",
            "value": 7.585769921754784,
            "unit": "ns/iter",
            "extra": "iterations: 90561287\ncpu: 7.585203454540127 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/4",
            "value": 7.59803806211972,
            "unit": "ns/iter",
            "extra": "iterations: 85786814\ncpu: 7.597603263363996 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/8",
            "value": 7.7785621412262165,
            "unit": "ns/iter",
            "extra": "iterations: 90683301\ncpu: 7.7713877111729746 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/16",
            "value": 7.796456355219376,
            "unit": "ns/iter",
            "extra": "iterations: 93180615\ncpu: 7.795884337101646 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/32",
            "value": 7.675466736017291,
            "unit": "ns/iter",
            "extra": "iterations: 92076888\ncpu: 7.675073586327114 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/64",
            "value": 7.58767217382289,
            "unit": "ns/iter",
            "extra": "iterations: 93075923\ncpu: 7.587531439253086 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/128",
            "value": 7.792896328996361,
            "unit": "ns/iter",
            "extra": "iterations: 91429741\ncpu: 7.792338523632038 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/2",
            "value": 0.19880853902904036,
            "unit": "us/iter",
            "extra": "iterations: 3526771\ncpu: 0.19879892712058714 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/4",
            "value": 0.3773528449230448,
            "unit": "us/iter",
            "extra": "iterations: 1863952\ncpu: 0.3772921684678571 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/8",
            "value": 0.7282783559362969,
            "unit": "us/iter",
            "extra": "iterations: 958503\ncpu: 0.7282702192898745 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/16",
            "value": 1.332794162545348,
            "unit": "us/iter",
            "extra": "iterations: 524715\ncpu: 1.3327135454484809 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/32",
            "value": 2.7229856916603046,
            "unit": "us/iter",
            "extra": "iterations: 257612\ncpu: 2.7228816553576727 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/64",
            "value": 5.3688954006838525,
            "unit": "us/iter",
            "extra": "iterations: 123127\ncpu: 5.368586784377114 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/128",
            "value": 11.270934593749491,
            "unit": "us/iter",
            "extra": "iterations: 62043\ncpu: 11.270812114178874 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/2",
            "value": 0.3623126973497986,
            "unit": "us/iter",
            "extra": "iterations: 1920448\ncpu: 0.3622957221439999 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/4",
            "value": 0.8747294010920715,
            "unit": "us/iter",
            "extra": "iterations: 802494\ncpu: 0.8746958818383695 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/8",
            "value": 1.9502342029098474,
            "unit": "us/iter",
            "extra": "iterations: 358642\ncpu: 1.950071645261843 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/16",
            "value": 3.8053346154725185,
            "unit": "us/iter",
            "extra": "iterations: 174968\ncpu: 3.8050488489323615 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/32",
            "value": 7.795423377025419,
            "unit": "us/iter",
            "extra": "iterations: 90482\ncpu: 7.794592272496171 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/64",
            "value": 15.760790538402096,
            "unit": "us/iter",
            "extra": "iterations: 44242\ncpu: 15.757153745309864 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/128",
            "value": 32.50349102337958,
            "unit": "us/iter",
            "extra": "iterations: 22113\ncpu: 32.49999081987976 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/2",
            "value": 0.3619534528602596,
            "unit": "us/iter",
            "extra": "iterations: 1840199\ncpu: 0.3619263367711861 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/4",
            "value": 0.7256166721197352,
            "unit": "us/iter",
            "extra": "iterations: 898578\ncpu: 0.7255347649285872 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/8",
            "value": 1.477733014557031,
            "unit": "us/iter",
            "extra": "iterations: 485607\ncpu: 1.4775983398097625 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/16",
            "value": 2.6949518948128497,
            "unit": "us/iter",
            "extra": "iterations: 258891\ncpu: 2.694680348100164 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/32",
            "value": 5.377442029424779,
            "unit": "us/iter",
            "extra": "iterations: 131998\ncpu: 5.377374611736518 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/64",
            "value": 10.451213794263444,
            "unit": "us/iter",
            "extra": "iterations: 65404\ncpu: 10.450681716714643 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/128",
            "value": 22.31814995670501,
            "unit": "us/iter",
            "extra": "iterations: 32336\ncpu: 22.317429366650178 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/2",
            "value": 0.2000827900938319,
            "unit": "us/iter",
            "extra": "iterations: 3546318\ncpu: 0.20006296671646526 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/4",
            "value": 0.38869767443146874,
            "unit": "us/iter",
            "extra": "iterations: 1808504\ncpu: 0.38867826667787314 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/8",
            "value": 0.7521012714298669,
            "unit": "us/iter",
            "extra": "iterations: 950426\ncpu: 0.7520063666187586 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/16",
            "value": 1.3794369844850753,
            "unit": "us/iter",
            "extra": "iterations: 505320\ncpu: 1.3793022203751975 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/32",
            "value": 2.813626026282075,
            "unit": "us/iter",
            "extra": "iterations: 257970\ncpu: 2.8133601077644648 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/64",
            "value": 5.46732172140519,
            "unit": "us/iter",
            "extra": "iterations: 130986\ncpu: 5.465124540027172 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/128",
            "value": 11.263209264827184,
            "unit": "us/iter",
            "extra": "iterations: 59537\ncpu: 11.262507163612543 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/2",
            "value": 0.5488889138073473,
            "unit": "us/iter",
            "extra": "iterations: 1288648\ncpu: 0.5488647799864683 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/4",
            "value": 1.1788933204035064,
            "unit": "us/iter",
            "extra": "iterations: 586757\ncpu: 1.178732095228512 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/8",
            "value": 2.5560344120319454,
            "unit": "us/iter",
            "extra": "iterations: 269615\ncpu: 2.5559984310962074 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/16",
            "value": 5.4573040516421605,
            "unit": "us/iter",
            "extra": "iterations: 134464\ncpu: 5.456970876963347 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/32",
            "value": 11.074493890734017,
            "unit": "us/iter",
            "extra": "iterations: 65638\ncpu: 11.073546253694518 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/64",
            "value": 22.426951856074965,
            "unit": "us/iter",
            "extra": "iterations: 31572\ncpu: 22.425086278981365 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/128",
            "value": 45.63978255594499,
            "unit": "us/iter",
            "extra": "iterations: 14836\ncpu: 45.638434483688364 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/2",
            "value": 0.5603726794921361,
            "unit": "us/iter",
            "extra": "iterations: 1260877\ncpu: 0.5603518217875343 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/4",
            "value": 0.9193576390552353,
            "unit": "us/iter",
            "extra": "iterations: 772301\ncpu: 0.9192865527818845 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/8",
            "value": 1.8196643937302366,
            "unit": "us/iter",
            "extra": "iterations: 383938\ncpu: 1.819513067213966 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/16",
            "value": 3.5055970680798207,
            "unit": "us/iter",
            "extra": "iterations: 197959\ncpu: 3.505543526689868 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/32",
            "value": 7.064555949836765,
            "unit": "us/iter",
            "extra": "iterations: 99196\ncpu: 7.06390572200492 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/64",
            "value": 13.976248792609226,
            "unit": "us/iter",
            "extra": "iterations: 49901\ncpu: 13.975002304563064 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/128",
            "value": 29.413758124106504,
            "unit": "us/iter",
            "extra": "iterations: 23818\ncpu: 29.41015165001255 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/2",
            "value": 0.36837504181793246,
            "unit": "us/iter",
            "extra": "iterations: 1933979\ncpu: 0.36766433658276715 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/4",
            "value": 0.7102639557036294,
            "unit": "us/iter",
            "extra": "iterations: 981570\ncpu: 0.7102356337296365 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/8",
            "value": 1.3801916088774864,
            "unit": "us/iter",
            "extra": "iterations: 497931\ncpu: 1.3801171005621198 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/16",
            "value": 2.696935134601575,
            "unit": "us/iter",
            "extra": "iterations: 263407\ncpu: 2.696784037629983 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/32",
            "value": 5.437386761479677,
            "unit": "us/iter",
            "extra": "iterations: 134018\ncpu: 5.436997254100158 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/64",
            "value": 11.067187292593065,
            "unit": "us/iter",
            "extra": "iterations: 63884\ncpu: 11.066345141193377 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/128",
            "value": 23.217419911943445,
            "unit": "us/iter",
            "extra": "iterations: 29299\ncpu: 23.21470647462373 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/2",
            "value": 0.23641138458288316,
            "unit": "us/iter",
            "extra": "iterations: 2944403\ncpu: 0.23639644097632234 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/4",
            "value": 0.37240643390889905,
            "unit": "us/iter",
            "extra": "iterations: 1834468\ncpu: 0.3723992928740107 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/8",
            "value": 0.7262549397684688,
            "unit": "us/iter",
            "extra": "iterations: 970339\ncpu: 0.7262019675597793 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/16",
            "value": 1.3909018000881161,
            "unit": "us/iter",
            "extra": "iterations: 478921\ncpu: 1.3908435462216064 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/32",
            "value": 2.730549313464092,
            "unit": "us/iter",
            "extra": "iterations: 259564\ncpu: 2.7304129270623143 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/64",
            "value": 5.47582874080935,
            "unit": "us/iter",
            "extra": "iterations: 120776\ncpu: 5.475459470424573 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/128",
            "value": 11.330475856296921,
            "unit": "us/iter",
            "extra": "iterations: 62128\ncpu: 11.329645312902311 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/2",
            "value": 0.5512482776513493,
            "unit": "us/iter",
            "extra": "iterations: 1314339\ncpu: 0.5511960841152892 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/4",
            "value": 1.1632274598208188,
            "unit": "us/iter",
            "extra": "iterations: 603733\ncpu: 1.1631260905068925 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/8",
            "value": 2.3789519883215715,
            "unit": "us/iter",
            "extra": "iterations: 295928\ncpu: 2.378746532940485 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/16",
            "value": 5.192460518652226,
            "unit": "us/iter",
            "extra": "iterations: 137356\ncpu: 5.192140175893321 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/32",
            "value": 10.048488265524277,
            "unit": "us/iter",
            "extra": "iterations: 70050\ncpu: 10.047611763026419 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/64",
            "value": 20.580661449003735,
            "unit": "us/iter",
            "extra": "iterations: 34051\ncpu: 20.579231241373357 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/128",
            "value": 42.81094530205485,
            "unit": "us/iter",
            "extra": "iterations: 16454\ncpu: 42.80775464932567 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/2",
            "value": 0.5402632246995155,
            "unit": "us/iter",
            "extra": "iterations: 1314907\ncpu: 0.5401689975032369 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/4",
            "value": 0.9143534095948412,
            "unit": "us/iter",
            "extra": "iterations: 726098\ncpu: 0.9142502554751476 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/8",
            "value": 1.708907579833559,
            "unit": "us/iter",
            "extra": "iterations: 388465\ncpu: 1.7087049850051055 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/16",
            "value": 3.36646973974663,
            "unit": "us/iter",
            "extra": "iterations: 211102\ncpu: 3.366077033850974 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/32",
            "value": 6.710519132300607,
            "unit": "us/iter",
            "extra": "iterations: 104875\ncpu: 6.710025201430272 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/64",
            "value": 13.629080976814212,
            "unit": "us/iter",
            "extra": "iterations: 51064\ncpu: 13.627355710481018 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/128",
            "value": 27.968542285805068,
            "unit": "us/iter",
            "extra": "iterations: 25304\ncpu: 27.966416100220922 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/2",
            "value": 0.22921105057541175,
            "unit": "us/iter",
            "extra": "iterations: 3034756\ncpu: 0.22918805037373682 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/4",
            "value": 0.3961606065390776,
            "unit": "us/iter",
            "extra": "iterations: 1760744\ncpu: 0.3961311877251936 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/8",
            "value": 0.7513516139610973,
            "unit": "us/iter",
            "extra": "iterations: 926974\ncpu: 0.7512269071192954 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/16",
            "value": 1.4677841550138893,
            "unit": "us/iter",
            "extra": "iterations: 476138\ncpu: 1.4676098358039047 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/32",
            "value": 2.9610453270312136,
            "unit": "us/iter",
            "extra": "iterations: 235268\ncpu: 2.9607205867350963 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/64",
            "value": 5.972786962206039,
            "unit": "us/iter",
            "extra": "iterations: 117796\ncpu: 5.972299670617016 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/128",
            "value": 12.549834137019666,
            "unit": "us/iter",
            "extra": "iterations: 55992\ncpu: 12.548548239034185 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/2",
            "value": 373.78309044943643,
            "unit": "us/iter",
            "extra": "iterations: 1780\ncpu: 373.75415786516794 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/4",
            "value": 373.57077684093065,
            "unit": "us/iter",
            "extra": "iterations: 1779\ncpu: 373.53868071951257 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/8",
            "value": 380.8507466014275,
            "unit": "us/iter",
            "extra": "iterations: 1839\ncpu: 380.83117074497136 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/16",
            "value": 377.8783902702639,
            "unit": "us/iter",
            "extra": "iterations: 1850\ncpu: 377.86666054053916 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/32",
            "value": 387.49796400884856,
            "unit": "us/iter",
            "extra": "iterations: 1806\ncpu: 387.4480193798486 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/64",
            "value": 393.73266180758804,
            "unit": "us/iter",
            "extra": "iterations: 1715\ncpu: 393.70484839649504 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/128",
            "value": 451.88626658551715,
            "unit": "us/iter",
            "extra": "iterations: 1643\ncpu: 451.8432361533776 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/2",
            "value": 370.03530303031863,
            "unit": "us/iter",
            "extra": "iterations: 1881\ncpu: 370.02339447103094 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/4",
            "value": 367.580309660585,
            "unit": "us/iter",
            "extra": "iterations: 1915\ncpu: 367.573051174931 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/8",
            "value": 367.8440694517067,
            "unit": "us/iter",
            "extra": "iterations: 1915\ncpu: 367.8045399477791 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/16",
            "value": 371.3034031385275,
            "unit": "us/iter",
            "extra": "iterations: 1848\ncpu: 371.26790530303003 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/32",
            "value": 384.93636423840803,
            "unit": "us/iter",
            "extra": "iterations: 1812\ncpu: 384.89160706401367 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/64",
            "value": 408.6944077181341,
            "unit": "us/iter",
            "extra": "iterations: 1788\ncpu: 408.68842281879284 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/128",
            "value": 426.5543813349701,
            "unit": "us/iter",
            "extra": "iterations: 1618\ncpu: 426.5103145859048 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/2",
            "value": 373.11777863435265,
            "unit": "us/iter",
            "extra": "iterations: 1816\ncpu: 373.0765346916305 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/4",
            "value": 371.61455620985475,
            "unit": "us/iter",
            "extra": "iterations: 1868\ncpu: 371.58709368308297 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/8",
            "value": 376.71428413864237,
            "unit": "us/iter",
            "extra": "iterations: 1904\ncpu: 376.66691018907613 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/16",
            "value": 375.84760986301137,
            "unit": "us/iter",
            "extra": "iterations: 1825\ncpu: 375.840980821916 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/32",
            "value": 384.8294799358106,
            "unit": "us/iter",
            "extra": "iterations: 1869\ncpu: 384.8234874264305 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/64",
            "value": 399.03527808989435,
            "unit": "us/iter",
            "extra": "iterations: 1780\ncpu: 398.99213258426914 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/128",
            "value": 433.4149035532979,
            "unit": "us/iter",
            "extra": "iterations: 1576\ncpu: 433.38273350253473 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/2",
            "value": 367.76781429316156,
            "unit": "us/iter",
            "extra": "iterations: 1917\ncpu: 367.5917584767834 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/4",
            "value": 370.27543216342127,
            "unit": "us/iter",
            "extra": "iterations: 1909\ncpu: 370.2218968046111 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/8",
            "value": 380.18115929201906,
            "unit": "us/iter",
            "extra": "iterations: 1921\ncpu: 380.1671561686635 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/16",
            "value": 374.6338883277354,
            "unit": "us/iter",
            "extra": "iterations: 1782\ncpu: 374.58893883276704 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/32",
            "value": 381.3436876042335,
            "unit": "us/iter",
            "extra": "iterations: 1799\ncpu: 381.32095330739503 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/64",
            "value": 404.1787578822187,
            "unit": "us/iter",
            "extra": "iterations: 1681\ncpu: 404.1102266508004 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/128",
            "value": 433.1666264984295,
            "unit": "us/iter",
            "extra": "iterations: 1585\ncpu: 433.1468788643579 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/2",
            "value": 376.20799637118347,
            "unit": "us/iter",
            "extra": "iterations: 1929\ncpu: 376.2034339035727 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/4",
            "value": 362.4139020217839,
            "unit": "us/iter",
            "extra": "iterations: 1929\ncpu: 362.36895645411903 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/8",
            "value": 380.4396238821912,
            "unit": "us/iter",
            "extra": "iterations: 1901\ncpu: 380.40816675434 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/16",
            "value": 370.8865932656541,
            "unit": "us/iter",
            "extra": "iterations: 1871\ncpu: 370.84597274185666 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/32",
            "value": 386.09244420248405,
            "unit": "us/iter",
            "extra": "iterations: 1837\ncpu: 386.06315732172146 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/64",
            "value": 403.38095394359914,
            "unit": "us/iter",
            "extra": "iterations: 1737\ncpu: 403.3676551525679 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/128",
            "value": 432.0940689433032,
            "unit": "us/iter",
            "extra": "iterations: 1552\ncpu: 432.0523150773074 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/2",
            "value": 373.0568088627873,
            "unit": "us/iter",
            "extra": "iterations: 1873\ncpu: 373.0339578216677 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/4",
            "value": 367.02272132904716,
            "unit": "us/iter",
            "extra": "iterations: 1866\ncpu: 366.9766870310749 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/8",
            "value": 376.2009249592274,
            "unit": "us/iter",
            "extra": "iterations: 1839\ncpu: 376.16992985317705 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/16",
            "value": 382.1472303894621,
            "unit": "us/iter",
            "extra": "iterations: 1823\ncpu: 382.1421294569497 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/32",
            "value": 397.59422266287487,
            "unit": "us/iter",
            "extra": "iterations: 1765\ncpu: 397.54555410765715 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/64",
            "value": 434.20012566136387,
            "unit": "us/iter",
            "extra": "iterations: 1512\ncpu: 434.1379563492011 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/128",
            "value": 503.05474900000036,
            "unit": "us/iter",
            "extra": "iterations: 1000\ncpu: 503.02074999999036 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/2",
            "value": 372.7686481381343,
            "unit": "us/iter",
            "extra": "iterations: 1853\ncpu: 372.7408019427972 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/4",
            "value": 371.0927913708056,
            "unit": "us/iter",
            "extra": "iterations: 1831\ncpu: 371.0472976515518 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/8",
            "value": 390.1679651029594,
            "unit": "us/iter",
            "extra": "iterations: 1748\ncpu: 390.13426887872595 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/16",
            "value": 463.56954447437965,
            "unit": "us/iter",
            "extra": "iterations: 1484\ncpu: 463.55188948787065 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/32",
            "value": 745.0896610348468,
            "unit": "us/iter",
            "extra": "iterations: 947\ncpu: 745.037814149953 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/64",
            "value": 1906.6672330622991,
            "unit": "us/iter",
            "extra": "iterations: 369\ncpu: 1906.2989403794395 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/128",
            "value": 6385.54355555559,
            "unit": "us/iter",
            "extra": "iterations: 108\ncpu: 6385.013935184984 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/2",
            "value": 367.6647463389,
            "unit": "us/iter",
            "extra": "iterations: 1912\ncpu: 367.62029027196263 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/4",
            "value": 371.79515015808556,
            "unit": "us/iter",
            "extra": "iterations: 1898\ncpu: 371.76501369862626 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/8",
            "value": 407.04997586393864,
            "unit": "us/iter",
            "extra": "iterations: 1823\ncpu: 407.0352194185433 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/16",
            "value": 456.12645921645674,
            "unit": "us/iter",
            "extra": "iterations: 1557\ncpu: 456.07783943479797 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/32",
            "value": 696.0608929961021,
            "unit": "us/iter",
            "extra": "iterations: 1028\ncpu: 696.0122548637909 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/64",
            "value": 1625.8900731131926,
            "unit": "us/iter",
            "extra": "iterations: 424\ncpu: 1625.7964386792503 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/128",
            "value": 5945.967221311519,
            "unit": "us/iter",
            "extra": "iterations: 122\ncpu: 5945.709836065375 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/2",
            "value": 369.35936241969523,
            "unit": "us/iter",
            "extra": "iterations: 1868\ncpu: 369.3405728051486 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/4",
            "value": 364.4606882352963,
            "unit": "us/iter",
            "extra": "iterations: 1870\ncpu: 364.437372727276 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/8",
            "value": 362.75903985316893,
            "unit": "us/iter",
            "extra": "iterations: 1907\ncpu: 362.7116360775971 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/16",
            "value": 388.6800177580485,
            "unit": "us/iter",
            "extra": "iterations: 1802\ncpu: 388.6362330743765 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/32",
            "value": 384.9983597972993,
            "unit": "us/iter",
            "extra": "iterations: 1776\ncpu: 384.95894594594546 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/64",
            "value": 404.73401308306677,
            "unit": "us/iter",
            "extra": "iterations: 1758\ncpu: 404.7071643913489 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/128",
            "value": 444.19961703471944,
            "unit": "us/iter",
            "extra": "iterations: 1585\ncpu: 444.1579135646712 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/2",
            "value": 362.51867947367157,
            "unit": "us/iter",
            "extra": "iterations: 1900\ncpu: 362.48441631577657 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/4",
            "value": 379.9030872446246,
            "unit": "us/iter",
            "extra": "iterations: 1811\ncpu: 379.85074047486876 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/8",
            "value": 394.27919092420376,
            "unit": "us/iter",
            "extra": "iterations: 1807\ncpu: 394.2556712783627 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/16",
            "value": 452.76882727274347,
            "unit": "us/iter",
            "extra": "iterations: 1540\ncpu: 452.73798246752267 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/32",
            "value": 721.1758793970084,
            "unit": "us/iter",
            "extra": "iterations: 995\ncpu: 721.1661296482256 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/64",
            "value": 1772.1155288220182,
            "unit": "us/iter",
            "extra": "iterations: 399\ncpu: 1772.081944862189 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/128",
            "value": 6078.948227722961,
            "unit": "us/iter",
            "extra": "iterations: 101\ncpu: 6078.207623762457 us\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "lukas.burgholzer@jku.at",
            "name": "Lukas Burgholzer",
            "username": "burgholzer"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "6bc27c71e6b302a2345c8d83c21b783cc0a9c654",
          "message": "Google Benchmark for JKQ Tools (#6)\n\n✅ add multiple benchmarks for core package functionality\r\n\r\n♻️ changing maximum reference count to maximum supported by type\r\n♻️ restructure function order and/or visibility in package\r\n♻️ rewrote package reset functionality\r\n\r\n✨ provide const access methods for compute and unique tables\r\n\r\n💥 Add constexpr/inline definitions for gate matrices (moved from JKQ QFR)\r\n💥 move global SQRT_2 and PI constants to dd::ComplexNumbers class\r\n\r\n⬆️ googletest",
          "timestamp": "2021-03-26T17:30:38+01:00",
          "tree_id": "a88152eb5b464dd3df2e3763eba00c9e8bd03120",
          "url": "https://github.com/iic-jku/dd_package/commit/6bc27c71e6b302a2345c8d83c21b783cc0a9c654"
        },
        "date": 1616776841045,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_DDVectorNodeCreation",
            "value": 5.710120321102154,
            "unit": "ns/iter",
            "extra": "iterations: 127708438\ncpu: 5.707888557841418 ns\nthreads: 1"
          },
          {
            "name": "BM_DDMatrixNodeCreation",
            "value": 5.6351496191715045,
            "unit": "ns/iter",
            "extra": "iterations: 123103843\ncpu: 5.634334177528478 ns\nthreads: 1"
          },
          {
            "name": "BM_ComplexNumbersCreation",
            "value": 24.4471951737693,
            "unit": "us/iter",
            "extra": "iterations: 31536\ncpu: 24.446282914764083 us\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/2",
            "value": 14.160446579999757,
            "unit": "ms/iter",
            "extra": "iterations: 50\ncpu: 14.157616179999996 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/4",
            "value": 14.36495938775507,
            "unit": "ms/iter",
            "extra": "iterations: 49\ncpu: 14.340179591836728 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/8",
            "value": 14.362372106382795,
            "unit": "ms/iter",
            "extra": "iterations: 47\ncpu: 14.361666319148936 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/16",
            "value": 14.415117306122497,
            "unit": "ms/iter",
            "extra": "iterations: 49\ncpu: 14.391709224489787 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/32",
            "value": 13.941910760000269,
            "unit": "ms/iter",
            "extra": "iterations: 50\ncpu: 13.93291756 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/64",
            "value": 13.856258396226343,
            "unit": "ms/iter",
            "extra": "iterations: 53\ncpu: 13.851871150943403 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/128",
            "value": 14.326219744680564,
            "unit": "ms/iter",
            "extra": "iterations: 47\ncpu: 14.312933425531916 ms\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/2",
            "value": 6.4481236771095105,
            "unit": "ns/iter",
            "extra": "iterations: 112822559\ncpu: 6.44776136481711 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/4",
            "value": 6.27158662432337,
            "unit": "ns/iter",
            "extra": "iterations: 103723142\ncpu: 6.271283731455013 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/8",
            "value": 6.559069110540253,
            "unit": "ns/iter",
            "extra": "iterations: 106235170\ncpu: 6.5588315715031 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/16",
            "value": 6.437308770523469,
            "unit": "ns/iter",
            "extra": "iterations: 99816267\ncpu: 6.436311898941266 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/32",
            "value": 6.436785487952099,
            "unit": "ns/iter",
            "extra": "iterations: 109547488\ncpu: 6.436452819438457 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/64",
            "value": 6.959034991905826,
            "unit": "ns/iter",
            "extra": "iterations: 100754844\ncpu: 6.958649164302205 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/128",
            "value": 6.709230060021483,
            "unit": "ns/iter",
            "extra": "iterations: 105035720\ncpu: 6.709086823035059 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/2",
            "value": 0.17407347983610447,
            "unit": "us/iter",
            "extra": "iterations: 4009617\ncpu: 0.17406405948498305 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/4",
            "value": 0.3460373722826636,
            "unit": "us/iter",
            "extra": "iterations: 2084486\ncpu: 0.3460062183195276 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/8",
            "value": 0.6395532498845146,
            "unit": "us/iter",
            "extra": "iterations: 1058453\ncpu: 0.6394544500322623 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/16",
            "value": 1.2433512498554045,
            "unit": "us/iter",
            "extra": "iterations: 553344\ncpu: 1.2433076946709436 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/32",
            "value": 2.46148503607923,
            "unit": "us/iter",
            "extra": "iterations: 279940\ncpu: 2.4612499464170994 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/64",
            "value": 5.007631280000169,
            "unit": "us/iter",
            "extra": "iterations: 100000\ncpu: 5.007404320000006 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/128",
            "value": 10.074534383364423,
            "unit": "us/iter",
            "extra": "iterations: 67998\ncpu: 10.073617474043347 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/2",
            "value": 0.3430167640325138,
            "unit": "us/iter",
            "extra": "iterations: 1987350\ncpu: 0.3430087599064083 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/4",
            "value": 0.841829438312544,
            "unit": "us/iter",
            "extra": "iterations: 857719\ncpu: 0.8405562451105789 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/8",
            "value": 1.801782675369377,
            "unit": "us/iter",
            "extra": "iterations: 389307\ncpu: 1.801625341953787 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/16",
            "value": 3.7132912434354433,
            "unit": "us/iter",
            "extra": "iterations: 182229\ncpu: 3.7129381602269627 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/32",
            "value": 7.268934142759649,
            "unit": "us/iter",
            "extra": "iterations: 93976\ncpu: 7.2685218779262915 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/64",
            "value": 14.404752899793381,
            "unit": "us/iter",
            "extra": "iterations: 44917\ncpu: 14.404244428612737 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/128",
            "value": 29.86007451693963,
            "unit": "us/iter",
            "extra": "iterations: 23082\ncpu: 29.85900974785544 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/2",
            "value": 0.3379770216411346,
            "unit": "us/iter",
            "extra": "iterations: 2031085\ncpu: 0.33795407183845066 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/4",
            "value": 0.6748748737212638,
            "unit": "us/iter",
            "extra": "iterations: 1033428\ncpu: 0.6748497708597051 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/8",
            "value": 1.2903450712450504,
            "unit": "us/iter",
            "extra": "iterations: 530844\ncpu: 1.2902033139679492 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/16",
            "value": 2.6114228813652933,
            "unit": "us/iter",
            "extra": "iterations: 272003\ncpu: 2.6113294522486914 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/32",
            "value": 5.34390777863938,
            "unit": "us/iter",
            "extra": "iterations: 136682\ncpu: 5.343559400652572 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/64",
            "value": 10.407602298077654,
            "unit": "us/iter",
            "extra": "iterations: 65446\ncpu: 10.40717660361216 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/128",
            "value": 20.889080026918638,
            "unit": "us/iter",
            "extra": "iterations: 35663\ncpu: 20.887906513753766 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/2",
            "value": 0.18041042350482195,
            "unit": "us/iter",
            "extra": "iterations: 3754668\ncpu: 0.1803967434670642 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/4",
            "value": 0.33599561484508383,
            "unit": "us/iter",
            "extra": "iterations: 2122616\ncpu: 0.33597391426428314 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/8",
            "value": 0.6103441978095432,
            "unit": "us/iter",
            "extra": "iterations: 953321\ncpu: 0.6103279420048429 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/16",
            "value": 1.2122087950724065,
            "unit": "us/iter",
            "extra": "iterations: 591604\ncpu: 1.2121195225184325 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/32",
            "value": 2.4156794323940276,
            "unit": "us/iter",
            "extra": "iterations: 302111\ncpu: 2.4155970620070013 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/64",
            "value": 4.903514657833272,
            "unit": "us/iter",
            "extra": "iterations: 132830\ncpu: 4.9029473612888435 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/128",
            "value": 9.077865535680726,
            "unit": "us/iter",
            "extra": "iterations: 69379\ncpu: 9.077236642211615 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/2",
            "value": 0.4371428549081261,
            "unit": "us/iter",
            "extra": "iterations: 1662071\ncpu: 0.4371129368119632 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/4",
            "value": 1.1074807791736727,
            "unit": "us/iter",
            "extra": "iterations: 667271\ncpu: 1.1074171183821786 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/8",
            "value": 2.389035976914139,
            "unit": "us/iter",
            "extra": "iterations: 303389\ncpu: 2.388912926968343 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/16",
            "value": 5.054280103299436,
            "unit": "us/iter",
            "extra": "iterations: 129720\ncpu: 5.053798196114706 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/32",
            "value": 9.341443590536526,
            "unit": "us/iter",
            "extra": "iterations: 67923\ncpu: 9.34119109874417 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/64",
            "value": 20.672843826632956,
            "unit": "us/iter",
            "extra": "iterations: 35070\ncpu: 20.671210749928832 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/128",
            "value": 41.85006533513918,
            "unit": "us/iter",
            "extra": "iterations: 17724\ncpu: 41.848012468968534 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/2",
            "value": 0.46380063586734555,
            "unit": "us/iter",
            "extra": "iterations: 1561961\ncpu: 0.46378448245506754 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/4",
            "value": 0.8100574723071164,
            "unit": "us/iter",
            "extra": "iterations: 837760\ncpu: 0.8099815197670016 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/8",
            "value": 1.6203566311316904,
            "unit": "us/iter",
            "extra": "iterations: 449041\ncpu: 1.6202629180854347 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/16",
            "value": 3.0521904711468855,
            "unit": "us/iter",
            "extra": "iterations: 226596\ncpu: 3.0519333748168567 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/32",
            "value": 6.227769106386778,
            "unit": "us/iter",
            "extra": "iterations: 116885\ncpu: 6.227503067117221 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/64",
            "value": 13.352346059582697,
            "unit": "us/iter",
            "extra": "iterations: 55083\ncpu: 13.35136631991711 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/128",
            "value": 28.213348455560237,
            "unit": "us/iter",
            "extra": "iterations: 25349\ncpu: 28.21045630991369 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/2",
            "value": 0.35989977727940425,
            "unit": "us/iter",
            "extra": "iterations: 1939650\ncpu: 0.35987205939215816 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/4",
            "value": 0.7104904467120281,
            "unit": "us/iter",
            "extra": "iterations: 1023993\ncpu: 0.710461997298812 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/8",
            "value": 1.358790643361707,
            "unit": "us/iter",
            "extra": "iterations: 538655\ncpu: 1.3586637588066528 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/16",
            "value": 2.6129502589754456,
            "unit": "us/iter",
            "extra": "iterations: 281880\ncpu: 2.6128130871292634 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/32",
            "value": 5.105029000000059,
            "unit": "us/iter",
            "extra": "iterations: 100000\ncpu: 5.104228789999965 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/64",
            "value": 10.454535287610458,
            "unit": "us/iter",
            "extra": "iterations: 72320\ncpu: 10.454309858960178 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/128",
            "value": 19.82724063380079,
            "unit": "us/iter",
            "extra": "iterations: 35153\ncpu: 19.825668876055996 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/2",
            "value": 0.19486256935278573,
            "unit": "us/iter",
            "extra": "iterations: 3732006\ncpu: 0.19485134000320425 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/4",
            "value": 0.3574003148330419,
            "unit": "us/iter",
            "extra": "iterations: 1964851\ncpu: 0.35736370238761017 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/8",
            "value": 0.6404553308449022,
            "unit": "us/iter",
            "extra": "iterations: 1011078\ncpu: 0.6404000433200954 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/16",
            "value": 1.2347593890150883,
            "unit": "us/iter",
            "extra": "iterations: 595563\ncpu: 1.234655311025039 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/32",
            "value": 2.52991190347124,
            "unit": "us/iter",
            "extra": "iterations: 298854\ncpu: 2.529763322558843 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/64",
            "value": 4.840306226834518,
            "unit": "us/iter",
            "extra": "iterations: 134900\ncpu: 4.839912972572273 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/128",
            "value": 10.410833565890155,
            "unit": "us/iter",
            "extra": "iterations: 69517\ncpu: 10.410553260353593 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/2",
            "value": 0.4523856965808691,
            "unit": "us/iter",
            "extra": "iterations: 1544372\ncpu: 0.45234248225168516 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/4",
            "value": 1.0525134304008605,
            "unit": "us/iter",
            "extra": "iterations: 676711\ncpu: 1.042404453304291 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/8",
            "value": 2.2100035699128826,
            "unit": "us/iter",
            "extra": "iterations: 320456\ncpu: 2.20981670182489 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/16",
            "value": 4.8281258821519,
            "unit": "us/iter",
            "extra": "iterations: 146375\ncpu: 4.827952942783947 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/32",
            "value": 9.686857349218569,
            "unit": "us/iter",
            "extra": "iterations: 75457\ncpu: 9.669136952171392 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/64",
            "value": 20.26916071428572,
            "unit": "us/iter",
            "extra": "iterations: 33992\ncpu: 20.26835402447598 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/128",
            "value": 39.658993991072805,
            "unit": "us/iter",
            "extra": "iterations: 17474\ncpu: 39.65697081377995 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/2",
            "value": 0.45271734220193094,
            "unit": "us/iter",
            "extra": "iterations: 1523878\ncpu: 0.45267570304185284 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/4",
            "value": 0.8113772442822258,
            "unit": "us/iter",
            "extra": "iterations: 859072\ncpu: 0.8113478474446827 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/8",
            "value": 1.6160277704840922,
            "unit": "us/iter",
            "extra": "iterations: 434166\ncpu: 1.6158723345448702 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/16",
            "value": 3.270797144559535,
            "unit": "us/iter",
            "extra": "iterations: 219861\ncpu: 3.270634318956073 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/32",
            "value": 6.442132023593491,
            "unit": "us/iter",
            "extra": "iterations: 110200\ncpu: 6.441673702359394 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/64",
            "value": 12.641914580341258,
            "unit": "us/iter",
            "extra": "iterations: 57797\ncpu: 12.641279080228955 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/128",
            "value": 26.25903281179839,
            "unit": "us/iter",
            "extra": "iterations: 28953\ncpu: 26.25622353469421 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/2",
            "value": 0.1815592386794947,
            "unit": "us/iter",
            "extra": "iterations: 3505961\ncpu: 0.18154122792581015 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/4",
            "value": 0.3539083565328969,
            "unit": "us/iter",
            "extra": "iterations: 2024105\ncpu: 0.3538777113835494 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/8",
            "value": 0.6919144453678222,
            "unit": "us/iter",
            "extra": "iterations: 940966\ncpu: 0.6918728232476016 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/16",
            "value": 1.356675166882165,
            "unit": "us/iter",
            "extra": "iterations: 496458\ncpu: 1.3565400497121736 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/32",
            "value": 2.714568440972204,
            "unit": "us/iter",
            "extra": "iterations: 267391\ncpu: 2.714394583213359 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/64",
            "value": 5.367330725526272,
            "unit": "us/iter",
            "extra": "iterations: 133062\ncpu: 5.366790375914959 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/128",
            "value": 11.942306625991431,
            "unit": "us/iter",
            "extra": "iterations: 59659\ncpu: 11.941964280326449 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/2",
            "value": 322.1499593764859,
            "unit": "us/iter",
            "extra": "iterations: 2117\ncpu: 322.1144459140308 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/4",
            "value": 334.26842552183183,
            "unit": "us/iter",
            "extra": "iterations: 2108\ncpu: 334.25603889942903 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/8",
            "value": 328.9169634317833,
            "unit": "us/iter",
            "extra": "iterations: 2133\ncpu: 328.8895583684915 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/16",
            "value": 330.08475741874065,
            "unit": "us/iter",
            "extra": "iterations: 2123\ncpu: 330.070293923698 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/32",
            "value": 344.3457028092762,
            "unit": "us/iter",
            "extra": "iterations: 2029\ncpu: 344.3215032035512 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/64",
            "value": 359.02320515463,
            "unit": "us/iter",
            "extra": "iterations: 1940\ncpu: 359.00241855669697 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/128",
            "value": 386.05940809626964,
            "unit": "us/iter",
            "extra": "iterations: 1828\ncpu: 386.0290645514278 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/2",
            "value": 323.3508724202535,
            "unit": "us/iter",
            "extra": "iterations: 2132\ncpu: 323.3040628517829 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/4",
            "value": 332.06762148455147,
            "unit": "us/iter",
            "extra": "iterations: 2169\ncpu: 332.0540456431503 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/8",
            "value": 335.5658292794834,
            "unit": "us/iter",
            "extra": "iterations: 2179\ncpu: 335.5315507113385 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/16",
            "value": 328.8289653767788,
            "unit": "us/iter",
            "extra": "iterations: 1964\ncpu: 328.81266446028803 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/32",
            "value": 347.4602512537522,
            "unit": "us/iter",
            "extra": "iterations: 1994\ncpu: 347.4401188565697 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/64",
            "value": 350.5644289340168,
            "unit": "us/iter",
            "extra": "iterations: 1970\ncpu: 350.5436532994969 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/128",
            "value": 381.3769120699171,
            "unit": "us/iter",
            "extra": "iterations: 1831\ncpu: 381.35664117968463 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/2",
            "value": 315.3167659963488,
            "unit": "us/iter",
            "extra": "iterations: 2188\ncpu: 315.2792477148102 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/4",
            "value": 337.37503887467255,
            "unit": "us/iter",
            "extra": "iterations: 1955\ncpu: 337.3581790281386 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/8",
            "value": 334.2815841098619,
            "unit": "us/iter",
            "extra": "iterations: 2039\ncpu: 334.2572780774892 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/16",
            "value": 336.5524689849716,
            "unit": "us/iter",
            "extra": "iterations: 2128\ncpu: 336.539037593988 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/32",
            "value": 340.75558966863144,
            "unit": "us/iter",
            "extra": "iterations: 2052\ncpu: 340.73411793372117 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/64",
            "value": 368.46348157894226,
            "unit": "us/iter",
            "extra": "iterations: 1900\ncpu: 368.43316315789974 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/128",
            "value": 419.5881669412221,
            "unit": "us/iter",
            "extra": "iterations: 1821\ncpu: 419.5467336628287 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/2",
            "value": 335.09964451673346,
            "unit": "us/iter",
            "extra": "iterations: 2152\ncpu: 335.0662802044589 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/4",
            "value": 323.7956148648512,
            "unit": "us/iter",
            "extra": "iterations: 2072\ncpu: 323.78167374517596 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/8",
            "value": 330.8672906814863,
            "unit": "us/iter",
            "extra": "iterations: 2157\ncpu: 330.84285581826765 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/16",
            "value": 345.1378890600855,
            "unit": "us/iter",
            "extra": "iterations: 1947\ncpu: 345.09392449922893 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/32",
            "value": 344.98520553937766,
            "unit": "us/iter",
            "extra": "iterations: 2058\ncpu: 344.97646161321836 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/64",
            "value": 356.0672302016624,
            "unit": "us/iter",
            "extra": "iterations: 2033\ncpu: 356.0274840137735 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/128",
            "value": 389.753204656188,
            "unit": "us/iter",
            "extra": "iterations: 1847\ncpu: 389.73534001083164 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/2",
            "value": 329.18873873462644,
            "unit": "us/iter",
            "extra": "iterations: 2197\ncpu: 329.15015976331483 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/4",
            "value": 319.04409035865206,
            "unit": "us/iter",
            "extra": "iterations: 2147\ncpu: 319.031397764325 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/8",
            "value": 323.83646084478266,
            "unit": "us/iter",
            "extra": "iterations: 2107\ncpu: 323.8266264831452 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/16",
            "value": 342.32582032755283,
            "unit": "us/iter",
            "extra": "iterations: 2076\ncpu: 342.302202312137 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/32",
            "value": 344.6515295902951,
            "unit": "us/iter",
            "extra": "iterations: 1977\ncpu: 344.6338027314069 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/64",
            "value": 356.11269163671267,
            "unit": "us/iter",
            "extra": "iterations: 1949\ncpu: 356.0726269881885 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/128",
            "value": 386.41630328324754,
            "unit": "us/iter",
            "extra": "iterations: 1797\ncpu: 386.383866444082 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/2",
            "value": 339.4790270924166,
            "unit": "us/iter",
            "extra": "iterations: 2067\ncpu: 339.4594586357057 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/4",
            "value": 336.54615744275253,
            "unit": "us/iter",
            "extra": "iterations: 2096\ncpu: 336.53323807252076 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/8",
            "value": 343.74312463201085,
            "unit": "us/iter",
            "extra": "iterations: 2038\ncpu: 343.71676104023976 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/16",
            "value": 346.4653574706686,
            "unit": "us/iter",
            "extra": "iterations: 1961\ncpu: 346.42445283018975 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/32",
            "value": 348.7148644067921,
            "unit": "us/iter",
            "extra": "iterations: 1947\ncpu: 348.7032121212039 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/64",
            "value": 386.2805736040471,
            "unit": "us/iter",
            "extra": "iterations: 1773\ncpu: 386.2326395939223 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/128",
            "value": 448.5249992565169,
            "unit": "us/iter",
            "extra": "iterations: 1345\ncpu: 448.49912788104325 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/2",
            "value": 334.25482956684294,
            "unit": "us/iter",
            "extra": "iterations: 2124\ncpu: 334.2165362523533 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/4",
            "value": 337.747016973819,
            "unit": "us/iter",
            "extra": "iterations: 2062\ncpu: 337.4485436469493 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/8",
            "value": 350.67972420537376,
            "unit": "us/iter",
            "extra": "iterations: 2045\ncpu: 350.64026992665373 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/16",
            "value": 414.52024952976274,
            "unit": "us/iter",
            "extra": "iterations: 1595\ncpu: 414.48680062696474 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/32",
            "value": 668.103077071292,
            "unit": "us/iter",
            "extra": "iterations: 1038\ncpu: 668.0271666666606 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/64",
            "value": 1695.4877487684182,
            "unit": "us/iter",
            "extra": "iterations: 406\ncpu: 1695.3913596059494 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/128",
            "value": 5862.773528455238,
            "unit": "us/iter",
            "extra": "iterations: 123\ncpu: 5862.133959349573 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/2",
            "value": 325.7122461904839,
            "unit": "us/iter",
            "extra": "iterations: 2100\ncpu: 325.69800523809874 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/4",
            "value": 335.50888645038305,
            "unit": "us/iter",
            "extra": "iterations: 2096\ncpu: 335.2731226145023 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/8",
            "value": 349.8291819100667,
            "unit": "us/iter",
            "extra": "iterations: 1979\ncpu: 349.7945154118231 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/16",
            "value": 416.89787413394,
            "unit": "us/iter",
            "extra": "iterations: 1732\ncpu: 416.8688903002358 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/32",
            "value": 657.8844947368548,
            "unit": "us/iter",
            "extra": "iterations: 1045\ncpu: 657.8544736842279 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/64",
            "value": 1507.9472906724786,
            "unit": "us/iter",
            "extra": "iterations: 461\ncpu: 1507.922442516252 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/128",
            "value": 5355.212286885348,
            "unit": "us/iter",
            "extra": "iterations: 122\ncpu: 5354.958573770423 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/2",
            "value": 322.5542666362849,
            "unit": "us/iter",
            "extra": "iterations: 2194\ncpu: 322.5328518687399 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/4",
            "value": 327.43647307335607,
            "unit": "us/iter",
            "extra": "iterations: 2154\ncpu: 327.4215849582151 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/8",
            "value": 326.052414933836,
            "unit": "us/iter",
            "extra": "iterations: 2116\ncpu: 326.03248960302324 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/16",
            "value": 346.055746884009,
            "unit": "us/iter",
            "extra": "iterations: 2086\ncpu: 346.0198082454494 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/32",
            "value": 344.54271700878155,
            "unit": "us/iter",
            "extra": "iterations: 2046\ncpu: 344.5197429129993 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/64",
            "value": 352.97157560225077,
            "unit": "us/iter",
            "extra": "iterations: 1951\ncpu: 352.9308298308544 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/128",
            "value": 390.23957984083165,
            "unit": "us/iter",
            "extra": "iterations: 1885\ncpu: 390.2197198938898 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/2",
            "value": 332.17328907399553,
            "unit": "us/iter",
            "extra": "iterations: 2041\ncpu: 332.1531548260726 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/4",
            "value": 340.0178834059075,
            "unit": "us/iter",
            "extra": "iterations: 2067\ncpu: 339.9620464441221 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/8",
            "value": 355.8400200102634,
            "unit": "us/iter",
            "extra": "iterations: 1949\ncpu: 355.80179220112836 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/16",
            "value": 402.48323166473057,
            "unit": "us/iter",
            "extra": "iterations: 1718\ncpu: 402.434098952258 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/32",
            "value": 642.6912178571545,
            "unit": "us/iter",
            "extra": "iterations: 1120\ncpu: 642.6552205357134 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/64",
            "value": 1587.1863217592854,
            "unit": "us/iter",
            "extra": "iterations: 432\ncpu: 1587.01112037035 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/128",
            "value": 5624.345035398438,
            "unit": "us/iter",
            "extra": "iterations: 113\ncpu: 5624.175353982114 us\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "name": "iic-jku",
            "username": "iic-jku"
          },
          "committer": {
            "name": "iic-jku",
            "username": "iic-jku"
          },
          "id": "04cbca3f302eede858bdada942574347efdf862b",
          "message": "Remove line",
          "timestamp": "2021-03-26T16:30:42Z",
          "url": "https://github.com/iic-jku/dd_package/pull/7/commits/04cbca3f302eede858bdada942574347efdf862b"
        },
        "date": 1617106339746,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_DDVectorNodeCreation",
            "value": 9.951176591604813,
            "unit": "ns/iter",
            "extra": "iterations: 71604157\ncpu: 9.929788182549235 ns\nthreads: 1"
          },
          {
            "name": "BM_DDMatrixNodeCreation",
            "value": 9.733482920301304,
            "unit": "ns/iter",
            "extra": "iterations: 71956803\ncpu: 9.732259950459444 ns\nthreads: 1"
          },
          {
            "name": "BM_ComplexNumbersCreation",
            "value": 26.689976548620287,
            "unit": "us/iter",
            "extra": "iterations: 25329\ncpu: 26.683375379999205 us\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/2",
            "value": 11.192860283333061,
            "unit": "ms/iter",
            "extra": "iterations: 60\ncpu: 11.192080266666663 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/4",
            "value": 11.532528140844773,
            "unit": "ms/iter",
            "extra": "iterations: 71\ncpu: 11.171867577464784 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/8",
            "value": 10.752479603174907,
            "unit": "ms/iter",
            "extra": "iterations: 63\ncpu: 10.752127238095245 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/16",
            "value": 11.013347846153902,
            "unit": "ms/iter",
            "extra": "iterations: 65\ncpu: 11.005777061538453 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/32",
            "value": 11.00011609523808,
            "unit": "ms/iter",
            "extra": "iterations: 63\ncpu: 10.99184784126983 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/64",
            "value": 11.339172360655565,
            "unit": "ms/iter",
            "extra": "iterations: 61\ncpu: 11.338134655737708 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/128",
            "value": 10.460572584615262,
            "unit": "ms/iter",
            "extra": "iterations: 65\ncpu: 10.449678723076927 ms\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/2",
            "value": 7.196656064326407,
            "unit": "ns/iter",
            "extra": "iterations: 98428269\ncpu: 7.196167393739295 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/4",
            "value": 7.165627427744621,
            "unit": "ns/iter",
            "extra": "iterations: 98200710\ncpu: 7.165307674455712 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/8",
            "value": 7.299422939725052,
            "unit": "ns/iter",
            "extra": "iterations: 96560277\ncpu: 7.299097754245246 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/16",
            "value": 7.1177237676202605,
            "unit": "ns/iter",
            "extra": "iterations: 98636590\ncpu: 7.117319262557636 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/32",
            "value": 7.208876730428702,
            "unit": "ns/iter",
            "extra": "iterations: 98720470\ncpu: 7.208202088178861 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/64",
            "value": 7.193482430112847,
            "unit": "ns/iter",
            "extra": "iterations: 96455828\ncpu: 7.19300967485344 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/128",
            "value": 7.2081569346762455,
            "unit": "ns/iter",
            "extra": "iterations: 97099662\ncpu: 7.207436015585707 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/2",
            "value": 0.18653414970338283,
            "unit": "us/iter",
            "extra": "iterations: 3783415\ncpu: 0.18652780649228265 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/4",
            "value": 0.3726643711345948,
            "unit": "us/iter",
            "extra": "iterations: 1866234\ncpu: 0.37262814791714305 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/8",
            "value": 0.6881673304035856,
            "unit": "us/iter",
            "extra": "iterations: 946158\ncpu: 0.6881325581985271 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/16",
            "value": 1.3848465064896593,
            "unit": "us/iter",
            "extra": "iterations: 501487\ncpu: 1.3847468030078536 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/32",
            "value": 2.5782723663752702,
            "unit": "us/iter",
            "extra": "iterations: 272049\ncpu: 2.57813856694933 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/64",
            "value": 5.15943184240856,
            "unit": "us/iter",
            "extra": "iterations: 138840\ncpu: 5.158945671276296 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/128",
            "value": 10.800031680915406,
            "unit": "us/iter",
            "extra": "iterations: 66791\ncpu: 10.799447784881178 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/2",
            "value": 0.34015473553660375,
            "unit": "us/iter",
            "extra": "iterations: 2037541\ncpu: 0.3401262202821935 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/4",
            "value": 0.8118584293059028,
            "unit": "us/iter",
            "extra": "iterations: 854845\ncpu: 0.8118236849955237 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/8",
            "value": 1.7218286585543305,
            "unit": "us/iter",
            "extra": "iterations: 412212\ncpu: 1.7216195404306502 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/16",
            "value": 3.5424777296728718,
            "unit": "us/iter",
            "extra": "iterations: 199795\ncpu: 3.542340589103822 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/32",
            "value": 6.961327896260326,
            "unit": "us/iter",
            "extra": "iterations: 95701\ncpu: 6.960595406526581 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/64",
            "value": 14.030695293768275,
            "unit": "us/iter",
            "extra": "iterations: 50465\ncpu: 14.02960939264839 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/128",
            "value": 28.170349189146474,
            "unit": "us/iter",
            "extra": "iterations: 24912\ncpu: 28.167611512524143 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/2",
            "value": 0.33121761993428367,
            "unit": "us/iter",
            "extra": "iterations: 2088623\ncpu: 0.331201963686123 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/4",
            "value": 0.6727941783993676,
            "unit": "us/iter",
            "extra": "iterations: 1068950\ncpu: 0.6727354291594542 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/8",
            "value": 1.3061881897739245,
            "unit": "us/iter",
            "extra": "iterations: 532149\ncpu: 1.306121665172729 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/16",
            "value": 2.5721446049920433,
            "unit": "us/iter",
            "extra": "iterations: 267349\ncpu: 2.571914568597597 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/32",
            "value": 4.898939480125609,
            "unit": "us/iter",
            "extra": "iterations: 143804\ncpu: 4.898839343829098 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/64",
            "value": 9.733058560730653,
            "unit": "us/iter",
            "extra": "iterations: 70508\ncpu: 9.732210430022146 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/128",
            "value": 20.137726794850316,
            "unit": "us/iter",
            "extra": "iterations: 35574\ncpu: 20.136931270028708 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/2",
            "value": 0.19488147844424325,
            "unit": "us/iter",
            "extra": "iterations: 3697319\ncpu: 0.1948644931638312 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/4",
            "value": 0.3793995592277492,
            "unit": "us/iter",
            "extra": "iterations: 1844490\ncpu: 0.3793849210350803 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/8",
            "value": 0.7280401777677008,
            "unit": "us/iter",
            "extra": "iterations: 988706\ncpu: 0.7255440869176482 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/16",
            "value": 1.4175449397566868,
            "unit": "us/iter",
            "extra": "iterations: 492170\ncpu: 1.4174945506633894 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/32",
            "value": 2.6461817695167325,
            "unit": "us/iter",
            "extra": "iterations: 269000\ncpu: 2.645850914498135 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/64",
            "value": 5.249369776180081,
            "unit": "us/iter",
            "extra": "iterations: 135198\ncpu: 5.249256608825577 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/128",
            "value": 11.041204076007574,
            "unit": "us/iter",
            "extra": "iterations: 65309\ncpu: 11.040254742837897 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/2",
            "value": 0.33649114193470187,
            "unit": "us/iter",
            "extra": "iterations: 2086065\ncpu: 0.3364737407511279 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/4",
            "value": 0.820679224630174,
            "unit": "us/iter",
            "extra": "iterations: 863330\ncpu: 0.8206018498140972 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/8",
            "value": 1.7453965492295467,
            "unit": "us/iter",
            "extra": "iterations: 407793\ncpu: 1.74532739894996 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/16",
            "value": 3.558518642224253,
            "unit": "us/iter",
            "extra": "iterations: 194907\ncpu: 3.5581948980796176 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/32",
            "value": 6.936386284688241,
            "unit": "us/iter",
            "extra": "iterations: 101332\ncpu: 6.935910610665949 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/64",
            "value": 14.030353995861356,
            "unit": "us/iter",
            "extra": "iterations: 50252\ncpu: 14.029078424739325 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/128",
            "value": 28.31318968231536,
            "unit": "us/iter",
            "extra": "iterations: 24773\ncpu: 28.31219262907202 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/2",
            "value": 0.6835960190149363,
            "unit": "us/iter",
            "extra": "iterations: 1017939\ncpu: 0.6835316733124456 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/4",
            "value": 0.9311024563115491,
            "unit": "us/iter",
            "extra": "iterations: 737895\ncpu: 0.9310562437745247 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/8",
            "value": 1.7712626323744454,
            "unit": "us/iter",
            "extra": "iterations: 398302\ncpu: 1.7710856310036271 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/16",
            "value": 3.3361839165583715,
            "unit": "us/iter",
            "extra": "iterations: 209296\ncpu: 3.33605729684275 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/32",
            "value": 6.476666933230358,
            "unit": "us/iter",
            "extra": "iterations: 108792\ncpu: 6.475978463489989 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/64",
            "value": 13.024851495824638,
            "unit": "us/iter",
            "extra": "iterations: 54719\ncpu: 13.024372685904334 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/128",
            "value": 26.26209054603688,
            "unit": "us/iter",
            "extra": "iterations: 26793\ncpu: 26.25901511588867 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/2",
            "value": 0.3712637890553011,
            "unit": "us/iter",
            "extra": "iterations: 1941703\ncpu: 0.3682321719645075 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/4",
            "value": 0.6917686547088872,
            "unit": "us/iter",
            "extra": "iterations: 1014851\ncpu: 0.6916756361278676 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/8",
            "value": 1.379718061147877,
            "unit": "us/iter",
            "extra": "iterations: 527508\ncpu: 1.3796062145029102 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/16",
            "value": 2.5336432142568928,
            "unit": "us/iter",
            "extra": "iterations: 272822\ncpu: 2.5332898739837724 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/32",
            "value": 4.915815278059614,
            "unit": "us/iter",
            "extra": "iterations: 142793\ncpu: 4.915311051662189 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/64",
            "value": 9.93691634938541,
            "unit": "us/iter",
            "extra": "iterations: 71703\ncpu: 9.935947073344227 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/128",
            "value": 20.12209086634575,
            "unit": "us/iter",
            "extra": "iterations: 34028\ncpu: 20.117474080169373 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/2",
            "value": 0.28144594892684005,
            "unit": "us/iter",
            "extra": "iterations: 2448018\ncpu: 0.2814225013868348 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/4",
            "value": 0.3869444188689395,
            "unit": "us/iter",
            "extra": "iterations: 1822489\ncpu: 0.3859925338369657 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/8",
            "value": 0.7776852142840025,
            "unit": "us/iter",
            "extra": "iterations: 896054\ncpu: 0.7775793066042793 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/16",
            "value": 1.3815979605385884,
            "unit": "us/iter",
            "extra": "iterations: 515136\ncpu: 1.381434702680451 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/32",
            "value": 2.653528491722348,
            "unit": "us/iter",
            "extra": "iterations: 262392\ncpu: 2.6531546236165497 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/64",
            "value": 5.357432805496845,
            "unit": "us/iter",
            "extra": "iterations: 131417\ncpu: 5.357271486946142 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/128",
            "value": 10.831830078362765,
            "unit": "us/iter",
            "extra": "iterations: 65848\ncpu: 10.83084295650584 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/2",
            "value": 0.7018355561438498,
            "unit": "us/iter",
            "extra": "iterations: 1019880\ncpu: 0.7018022179079898 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/4",
            "value": 1.3106956507088556,
            "unit": "us/iter",
            "extra": "iterations: 534156\ncpu: 1.3105415758692376 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/8",
            "value": 2.6917327597177763,
            "unit": "us/iter",
            "extra": "iterations: 267194\ncpu: 2.691575192556764 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/16",
            "value": 5.411558006523351,
            "unit": "us/iter",
            "extra": "iterations: 130606\ncpu: 5.410763249774114 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/32",
            "value": 10.99457002464873,
            "unit": "us/iter",
            "extra": "iterations: 62478\ncpu: 10.994158679855222 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/64",
            "value": 21.87322002992278,
            "unit": "us/iter",
            "extra": "iterations: 32082\ncpu: 21.872780531138815 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/128",
            "value": 45.737105915343264,
            "unit": "us/iter",
            "extra": "iterations: 15333\ncpu: 45.73327104937129 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/2",
            "value": 0.6999958056196219,
            "unit": "us/iter",
            "extra": "iterations: 1014691\ncpu: 0.6999533296343368 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/4",
            "value": 1.0387621462488683,
            "unit": "us/iter",
            "extra": "iterations: 672224\ncpu: 1.038689997679336 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/8",
            "value": 1.951043435576018,
            "unit": "us/iter",
            "extra": "iterations: 360580\ncpu: 1.9508637251095362 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/16",
            "value": 3.623417954938191,
            "unit": "us/iter",
            "extra": "iterations: 189207\ncpu: 3.6232451283514826 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/32",
            "value": 7.200363826615744,
            "unit": "us/iter",
            "extra": "iterations: 97956\ncpu: 7.200213759238904 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/64",
            "value": 14.234016534737382,
            "unit": "us/iter",
            "extra": "iterations: 49774\ncpu: 14.233146602644004 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/128",
            "value": 28.822836743213813,
            "unit": "us/iter",
            "extra": "iterations: 23950\ncpu: 28.82092025052174 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/2",
            "value": 0.2894252151727879,
            "unit": "us/iter",
            "extra": "iterations: 2446987\ncpu: 0.2894105849356757 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/4",
            "value": 0.49891542254506954,
            "unit": "us/iter",
            "extra": "iterations: 1417198\ncpu: 0.49887576683003787 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/8",
            "value": 0.8771961542929473,
            "unit": "us/iter",
            "extra": "iterations: 791948\ncpu: 0.8771182438746136 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/16",
            "value": 1.6372253898484501,
            "unit": "us/iter",
            "extra": "iterations: 434079\ncpu: 1.6370263500422733 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/32",
            "value": 3.114198874634877,
            "unit": "us/iter",
            "extra": "iterations: 227304\ncpu: 3.1140488552775065 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/64",
            "value": 6.148823241882217,
            "unit": "us/iter",
            "extra": "iterations: 115180\ncpu: 6.148254566765088 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/128",
            "value": 12.676533879683019,
            "unit": "us/iter",
            "extra": "iterations: 55520\ncpu: 12.675878242075159 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/2",
            "value": 369.20077016341736,
            "unit": "us/iter",
            "extra": "iterations: 1897\ncpu: 369.1521671059521 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/4",
            "value": 379.8730416889338,
            "unit": "us/iter",
            "extra": "iterations: 1871\ncpu: 379.85631266702626 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/8",
            "value": 386.8642255225599,
            "unit": "us/iter",
            "extra": "iterations: 1818\ncpu: 386.8288569857033 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/16",
            "value": 388.6609966814054,
            "unit": "us/iter",
            "extra": "iterations: 1808\ncpu: 388.6550232300868 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/32",
            "value": 419.2121471291784,
            "unit": "us/iter",
            "extra": "iterations: 1672\ncpu: 419.1491088516777 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/64",
            "value": 466.7606801346821,
            "unit": "us/iter",
            "extra": "iterations: 1485\ncpu: 466.71468686868246 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/128",
            "value": 566.295020441526,
            "unit": "us/iter",
            "extra": "iterations: 1223\ncpu: 566.1772771872401 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/2",
            "value": 372.7934964682137,
            "unit": "us/iter",
            "extra": "iterations: 1982\ncpu: 372.7589354187699 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/4",
            "value": 367.90768485167507,
            "unit": "us/iter",
            "extra": "iterations: 1888\ncpu: 367.89412552966337 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/8",
            "value": 362.6466814928431,
            "unit": "us/iter",
            "extra": "iterations: 1956\ncpu: 362.61912525562553 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/16",
            "value": 378.3490576414766,
            "unit": "us/iter",
            "extra": "iterations: 1891\ncpu: 378.3051649920734 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/32",
            "value": 384.20052802199643,
            "unit": "us/iter",
            "extra": "iterations: 1820\ncpu: 384.1772318681377 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/64",
            "value": 399.40928144745715,
            "unit": "us/iter",
            "extra": "iterations: 1741\ncpu: 399.37413038483464 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/128",
            "value": 422.89036237981475,
            "unit": "us/iter",
            "extra": "iterations: 1664\ncpu: 422.8758792067351 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/2",
            "value": 366.9552997892674,
            "unit": "us/iter",
            "extra": "iterations: 1898\ncpu: 366.9107792413073 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/4",
            "value": 355.50890650405097,
            "unit": "us/iter",
            "extra": "iterations: 1968\ncpu: 355.5006250000048 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/8",
            "value": 357.5338476141672,
            "unit": "us/iter",
            "extra": "iterations: 1949\ncpu: 357.49808568496684 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/16",
            "value": 370.46240352697686,
            "unit": "us/iter",
            "extra": "iterations: 1928\ncpu: 370.4277043568486 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/32",
            "value": 383.66237208040843,
            "unit": "us/iter",
            "extra": "iterations: 1841\ncpu: 383.64173112438885 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/64",
            "value": 387.69542897089923,
            "unit": "us/iter",
            "extra": "iterations: 1788\ncpu: 387.6513573825498 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/128",
            "value": 408.53465593915104,
            "unit": "us/iter",
            "extra": "iterations: 1709\ncpu: 408.52687361030013 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/2",
            "value": 369.4783500784761,
            "unit": "us/iter",
            "extra": "iterations: 1911\ncpu: 369.45244740972964 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/4",
            "value": 373.4638372827805,
            "unit": "us/iter",
            "extra": "iterations: 1899\ncpu: 373.44214165349536 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/8",
            "value": 370.55411699313646,
            "unit": "us/iter",
            "extra": "iterations: 1889\ncpu: 370.5212424563252 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/16",
            "value": 363.87607931403323,
            "unit": "us/iter",
            "extra": "iterations: 1866\ncpu: 363.84065594855423 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/32",
            "value": 369.15752198954135,
            "unit": "us/iter",
            "extra": "iterations: 1910\ncpu: 369.1493020942429 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/64",
            "value": 393.2351678710497,
            "unit": "us/iter",
            "extra": "iterations: 1799\ncpu: 393.20220511395246 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/128",
            "value": 424.4486810877726,
            "unit": "us/iter",
            "extra": "iterations: 1618\ncpu: 424.4090636588351 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/2",
            "value": 370.16603823990744,
            "unit": "us/iter",
            "extra": "iterations: 1909\ncpu: 370.14471870089136 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/4",
            "value": 369.00577267759047,
            "unit": "us/iter",
            "extra": "iterations: 1830\ncpu: 368.9726579235012 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/8",
            "value": 375.1846256830484,
            "unit": "us/iter",
            "extra": "iterations: 1830\ncpu: 375.1746803278652 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/16",
            "value": 374.1028393144221,
            "unit": "us/iter",
            "extra": "iterations: 1867\ncpu: 374.0589185859699 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/32",
            "value": 385.2379489685083,
            "unit": "us/iter",
            "extra": "iterations: 1842\ncpu: 385.22681976113773 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/64",
            "value": 400.40784142773816,
            "unit": "us/iter",
            "extra": "iterations: 1709\ncpu: 400.3859572849666 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/128",
            "value": 422.07827250899265,
            "unit": "us/iter",
            "extra": "iterations: 1666\ncpu: 422.03217406962403 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/2",
            "value": 367.7045002647185,
            "unit": "us/iter",
            "extra": "iterations: 1889\ncpu: 367.67363737428184 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/4",
            "value": 372.80548270357036,
            "unit": "us/iter",
            "extra": "iterations: 1879\ncpu: 372.77307184671963 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/8",
            "value": 375.63815538290777,
            "unit": "us/iter",
            "extra": "iterations: 1802\ncpu: 375.6327164261905 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/16",
            "value": 373.3707698195692,
            "unit": "us/iter",
            "extra": "iterations: 1829\ncpu: 373.345510661577 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/32",
            "value": 393.6542852272528,
            "unit": "us/iter",
            "extra": "iterations: 1760\ncpu: 393.62922840910517 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/64",
            "value": 424.1588636085802,
            "unit": "us/iter",
            "extra": "iterations: 1635\ncpu: 424.1438177369925 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/128",
            "value": 476.45202859042274,
            "unit": "us/iter",
            "extra": "iterations: 1504\ncpu: 476.3937174202136 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/2",
            "value": 367.10704277517283,
            "unit": "us/iter",
            "extra": "iterations: 1917\ncpu: 367.0938977569191 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/4",
            "value": 361.76279597244064,
            "unit": "us/iter",
            "extra": "iterations: 1887\ncpu: 361.7546348701644 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/8",
            "value": 390.6396421223734,
            "unit": "us/iter",
            "extra": "iterations: 1847\ncpu: 390.5956247969781 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/16",
            "value": 459.4793722580356,
            "unit": "us/iter",
            "extra": "iterations: 1550\ncpu: 459.4683400000026 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/32",
            "value": 696.8738127530513,
            "unit": "us/iter",
            "extra": "iterations: 988\ncpu: 696.8254321862165 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/64",
            "value": 1691.9438444975447,
            "unit": "us/iter",
            "extra": "iterations: 418\ncpu: 1691.80173923446 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/128",
            "value": 5821.892733333319,
            "unit": "us/iter",
            "extra": "iterations: 120\ncpu: 5821.6802250001365 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/2",
            "value": 367.99137773152574,
            "unit": "us/iter",
            "extra": "iterations: 1922\ncpu: 367.9518881373556 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/4",
            "value": 371.12370270269037,
            "unit": "us/iter",
            "extra": "iterations: 1887\ncpu: 371.0930190779033 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/8",
            "value": 388.3209662797178,
            "unit": "us/iter",
            "extra": "iterations: 1809\ncpu: 388.31184521834956 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/16",
            "value": 442.2526468305181,
            "unit": "us/iter",
            "extra": "iterations: 1546\ncpu: 442.20284087969264 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/32",
            "value": 670.592314606767,
            "unit": "us/iter",
            "extra": "iterations: 1068\ncpu: 670.543063670434 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/64",
            "value": 1476.7063680851413,
            "unit": "us/iter",
            "extra": "iterations: 470\ncpu: 1476.5582808510235 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/128",
            "value": 4975.4984927535525,
            "unit": "us/iter",
            "extra": "iterations: 138\ncpu: 4975.177478260909 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/2",
            "value": 360.924818642351,
            "unit": "us/iter",
            "extra": "iterations: 1974\ncpu: 360.8869260385045 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/4",
            "value": 369.30825941423126,
            "unit": "us/iter",
            "extra": "iterations: 1912\ncpu: 369.29293514645184 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/8",
            "value": 371.2160254776836,
            "unit": "us/iter",
            "extra": "iterations: 1884\ncpu: 371.1741464968192 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/16",
            "value": 370.68899034333003,
            "unit": "us/iter",
            "extra": "iterations: 1864\ncpu: 370.6665654506462 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/32",
            "value": 371.8755520262733,
            "unit": "us/iter",
            "extra": "iterations: 1826\ncpu: 371.8514008762359 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/64",
            "value": 405.59967565949336,
            "unit": "us/iter",
            "extra": "iterations: 1668\ncpu: 405.56993944843845 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/128",
            "value": 431.6417615725804,
            "unit": "us/iter",
            "extra": "iterations: 1577\ncpu: 431.6132897907483 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/2",
            "value": 366.71615755968156,
            "unit": "us/iter",
            "extra": "iterations: 1885\ncpu: 366.6860779840763 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/4",
            "value": 383.77777801492965,
            "unit": "us/iter",
            "extra": "iterations: 1874\ncpu: 383.7665186766322 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/8",
            "value": 396.00579518747304,
            "unit": "us/iter",
            "extra": "iterations: 1787\ncpu: 395.9616989367672 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/16",
            "value": 442.7355275287984,
            "unit": "us/iter",
            "extra": "iterations: 1562\ncpu: 442.69826760563336 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/32",
            "value": 660.0143225806412,
            "unit": "us/iter",
            "extra": "iterations: 1054\ncpu: 659.9508500948658 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/64",
            "value": 1606.4651573033648,
            "unit": "us/iter",
            "extra": "iterations: 445\ncpu: 1606.3730224718813 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/128",
            "value": 5424.651167999855,
            "unit": "us/iter",
            "extra": "iterations: 125\ncpu: 5424.263167999925 us\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "lukas.burgholzer@jku.at",
            "name": "Lukas Burgholzer",
            "username": "burgholzer"
          },
          "committer": {
            "email": "lukas.burgholzer@jku.at",
            "name": "Lukas Burgholzer",
            "username": "burgholzer"
          },
          "distinct": true,
          "id": "17092ec00db72053a376698c886200ac8d397492",
          "message": "⚡ improved compute table reset",
          "timestamp": "2021-04-01T16:18:10+02:00",
          "tree_id": "9bdb42ef0ff3a0b6cfa07fbb43972d567c01db2d",
          "url": "https://github.com/iic-jku/dd_package/commit/17092ec00db72053a376698c886200ac8d397492"
        },
        "date": 1617289416870,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_DDVectorNodeCreation",
            "value": 11.291031524267208,
            "unit": "ns/iter",
            "extra": "iterations: 61775648\ncpu: 11.286045837997523 ns\nthreads: 1"
          },
          {
            "name": "BM_DDMatrixNodeCreation",
            "value": 11.247407551683459,
            "unit": "ns/iter",
            "extra": "iterations: 63068374\ncpu: 11.246511809548156 ns\nthreads: 1"
          },
          {
            "name": "BM_ComplexNumbersCreation",
            "value": 31.098914428036647,
            "unit": "us/iter",
            "extra": "iterations: 22484\ncpu: 31.09460496352964 us\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/2",
            "value": 15.427600953487822,
            "unit": "ms/iter",
            "extra": "iterations: 43\ncpu: 15.420794046511629 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/4",
            "value": 14.353013711110584,
            "unit": "ms/iter",
            "extra": "iterations: 45\ncpu: 14.343600355555559 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/8",
            "value": 13.920112351852536,
            "unit": "ms/iter",
            "extra": "iterations: 54\ncpu: 13.912049388888887 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/16",
            "value": 14.682363696428931,
            "unit": "ms/iter",
            "extra": "iterations: 56\ncpu: 14.679254821428575 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/32",
            "value": 15.849744444444191,
            "unit": "ms/iter",
            "extra": "iterations: 45\ncpu: 15.843531088888893 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/64",
            "value": 15.875082860464657,
            "unit": "ms/iter",
            "extra": "iterations: 43\ncpu: 15.873608511627904 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/128",
            "value": 16.249425093022626,
            "unit": "ms/iter",
            "extra": "iterations: 43\ncpu: 16.230741441860488 ms\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/2",
            "value": 7.640406182920048,
            "unit": "ns/iter",
            "extra": "iterations: 91117273\ncpu: 7.639631379222675 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/4",
            "value": 7.655179009894514,
            "unit": "ns/iter",
            "extra": "iterations: 91977011\ncpu: 7.654678906667238 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/8",
            "value": 7.638348994753167,
            "unit": "ns/iter",
            "extra": "iterations: 91921210\ncpu: 7.638036759959974 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/16",
            "value": 7.684948799535195,
            "unit": "ns/iter",
            "extra": "iterations: 91694480\ncpu: 7.684259575930863 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/32",
            "value": 7.957360792062136,
            "unit": "ns/iter",
            "extra": "iterations: 91669503\ncpu: 7.95675649076008 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/64",
            "value": 7.727260829565729,
            "unit": "ns/iter",
            "extra": "iterations: 83323928\ncpu: 7.726372777337143 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/128",
            "value": 7.868438593649591,
            "unit": "ns/iter",
            "extra": "iterations: 90937231\ncpu: 7.867434626418289 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/2",
            "value": 0.20660185495269906,
            "unit": "us/iter",
            "extra": "iterations: 3404076\ncpu: 0.2065855812267408 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/4",
            "value": 0.39885399649320585,
            "unit": "us/iter",
            "extra": "iterations: 1744054\ncpu: 0.3988390904180714 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/8",
            "value": 0.7400079572746209,
            "unit": "us/iter",
            "extra": "iterations: 977219\ncpu: 0.7399320305888455 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/16",
            "value": 1.4236252288843376,
            "unit": "us/iter",
            "extra": "iterations: 480592\ncpu: 1.4234525314611968 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/32",
            "value": 2.8330105348328716,
            "unit": "us/iter",
            "extra": "iterations: 245946\ncpu: 2.832777158400621 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/64",
            "value": 5.795460229342493,
            "unit": "us/iter",
            "extra": "iterations: 126274\ncpu: 5.795050825981604 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/128",
            "value": 11.73131847340635,
            "unit": "us/iter",
            "extra": "iterations: 61575\ncpu: 11.730511327649172 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/2",
            "value": 0.44158196537888894,
            "unit": "us/iter",
            "extra": "iterations: 1528316\ncpu: 0.44156299417136313 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/4",
            "value": 1.0536335938313819,
            "unit": "us/iter",
            "extra": "iterations: 652852\ncpu: 1.053522701929383 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/8",
            "value": 2.312757625308019,
            "unit": "us/iter",
            "extra": "iterations: 305168\ncpu: 2.312661619173701 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/16",
            "value": 4.683180773705829,
            "unit": "us/iter",
            "extra": "iterations: 151272\ncpu: 4.682768926172723 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/32",
            "value": 9.464416825146133,
            "unit": "us/iter",
            "extra": "iterations: 73616\ncpu: 9.464158701912606 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/64",
            "value": 19.118767680988714,
            "unit": "us/iter",
            "extra": "iterations: 35886\ncpu: 19.117349328428872 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/128",
            "value": 38.61311417084199,
            "unit": "us/iter",
            "extra": "iterations: 18157\ncpu: 38.611990582144564 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/2",
            "value": 0.4343482998418522,
            "unit": "us/iter",
            "extra": "iterations: 1597322\ncpu: 0.4343250158703111 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/4",
            "value": 0.8537645334919325,
            "unit": "us/iter",
            "extra": "iterations: 810404\ncpu: 0.8537028408053244 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/8",
            "value": 1.6289844807395129,
            "unit": "us/iter",
            "extra": "iterations: 427791\ncpu: 1.628897297979619 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/16",
            "value": 3.273483559649062,
            "unit": "us/iter",
            "extra": "iterations: 215628\ncpu: 3.2730708488693434 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/32",
            "value": 6.498290351308283,
            "unit": "us/iter",
            "extra": "iterations: 107797\ncpu: 6.4978469159624055 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/64",
            "value": 12.784626389321703,
            "unit": "us/iter",
            "extra": "iterations: 54613\ncpu: 12.782753154010937 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/128",
            "value": 25.408485328467744,
            "unit": "us/iter",
            "extra": "iterations: 27400\ncpu: 25.40607291970792 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/2",
            "value": 0.20551976153001184,
            "unit": "us/iter",
            "extra": "iterations: 3367300\ncpu: 0.20550060701452344 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/4",
            "value": 0.3991410945765287,
            "unit": "us/iter",
            "extra": "iterations: 1720300\ncpu: 0.39910400976573823 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/8",
            "value": 0.7608591214377043,
            "unit": "us/iter",
            "extra": "iterations: 922234\ncpu: 0.7606777206218818 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/16",
            "value": 1.4359028312812647,
            "unit": "us/iter",
            "extra": "iterations: 486988\ncpu: 1.4358356858896024 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/32",
            "value": 2.9008083543815832,
            "unit": "us/iter",
            "extra": "iterations: 244279\ncpu: 2.900503375238983 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/64",
            "value": 5.6305482281599675,
            "unit": "us/iter",
            "extra": "iterations: 126648\ncpu: 5.630296341039761 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/128",
            "value": 11.32686762852355,
            "unit": "us/iter",
            "extra": "iterations: 60300\ncpu: 11.325695207296855 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/2",
            "value": 0.6461706289614162,
            "unit": "us/iter",
            "extra": "iterations: 1056122\ncpu: 0.6461189341761698 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/4",
            "value": 1.3404586805504446,
            "unit": "us/iter",
            "extra": "iterations: 539528\ncpu: 1.3403092925668336 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/8",
            "value": 2.955594175081748,
            "unit": "us/iter",
            "extra": "iterations: 233411\ncpu: 2.9464190290945957 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/16",
            "value": 6.032552523655711,
            "unit": "us/iter",
            "extra": "iterations: 118261\ncpu: 6.028632888272549 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/32",
            "value": 12.404405339376298,
            "unit": "us/iter",
            "extra": "iterations: 56486\ncpu: 12.402725223949263 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/64",
            "value": 25.379184361138766,
            "unit": "us/iter",
            "extra": "iterations: 27956\ncpu: 25.37475930032917 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/128",
            "value": 57.5669762448964,
            "unit": "us/iter",
            "extra": "iterations: 12250\ncpu: 57.56073093877547 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/2",
            "value": 0.654779749736027,
            "unit": "us/iter",
            "extra": "iterations: 1088371\ncpu: 0.6517746742608901 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/4",
            "value": 1.0611987326621761,
            "unit": "us/iter",
            "extra": "iterations: 629982\ncpu: 1.0611671412834 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/8",
            "value": 2.065869954876355,
            "unit": "us/iter",
            "extra": "iterations: 335745\ncpu: 2.0658452664968867 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/16",
            "value": 4.016744235493883,
            "unit": "us/iter",
            "extra": "iterations: 175427\ncpu: 4.016209061318941 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/32",
            "value": 7.829204981035774,
            "unit": "us/iter",
            "extra": "iterations: 89379\ncpu: 7.828456483066451 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/64",
            "value": 15.787061016948519,
            "unit": "us/iter",
            "extra": "iterations: 44840\ncpu: 15.78533490187336 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/128",
            "value": 32.437575768682834,
            "unit": "us/iter",
            "extra": "iterations: 21823\ncpu: 32.43232456582511 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/2",
            "value": 0.4436068806572404,
            "unit": "us/iter",
            "extra": "iterations: 1602376\ncpu: 0.4435581392881581 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/4",
            "value": 0.8282943179703743,
            "unit": "us/iter",
            "extra": "iterations: 833065\ncpu: 0.8282120902930693 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/8",
            "value": 1.6241091270718107,
            "unit": "us/iter",
            "extra": "iterations: 429875\ncpu: 1.6239718755452115 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/16",
            "value": 3.2780306960677885,
            "unit": "us/iter",
            "extra": "iterations: 213643\ncpu: 3.277566838136501 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/32",
            "value": 6.34737272493974,
            "unit": "us/iter",
            "extra": "iterations: 105217\ncpu: 6.346922227396706 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/64",
            "value": 12.87962055401623,
            "unit": "us/iter",
            "extra": "iterations: 54150\ncpu: 12.878451542013043 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/128",
            "value": 26.67545850294015,
            "unit": "us/iter",
            "extra": "iterations: 26532\ncpu: 26.67294082617211 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/2",
            "value": 0.27140088032073933,
            "unit": "us/iter",
            "extra": "iterations: 2506132\ncpu: 0.2713722704949345 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/4",
            "value": 0.41389353824970215,
            "unit": "us/iter",
            "extra": "iterations: 1670600\ncpu: 0.4138738483179749 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/8",
            "value": 0.8267644445601942,
            "unit": "us/iter",
            "extra": "iterations: 844574\ncpu: 0.8267121116681242 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/16",
            "value": 1.6330930936243415,
            "unit": "us/iter",
            "extra": "iterations: 435250\ncpu: 1.6330083078690412 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/32",
            "value": 3.1131506294033353,
            "unit": "us/iter",
            "extra": "iterations: 226961\ncpu: 3.112917095888745 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/64",
            "value": 6.276702793555015,
            "unit": "us/iter",
            "extra": "iterations: 112151\ncpu: 6.276516437660005 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/128",
            "value": 13.43324496676056,
            "unit": "us/iter",
            "extra": "iterations: 52799\ncpu: 13.43242483759155 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/2",
            "value": 0.6469540025863788,
            "unit": "us/iter",
            "extra": "iterations: 1064799\ncpu: 0.6469014151966759 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/4",
            "value": 1.3039588909399666,
            "unit": "us/iter",
            "extra": "iterations: 533605\ncpu: 1.3038174023856368 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/8",
            "value": 2.841717392092836,
            "unit": "us/iter",
            "extra": "iterations: 248153\ncpu: 2.8416448481380234 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/16",
            "value": 5.8928744687221055,
            "unit": "us/iter",
            "extra": "iterations: 116935\ncpu: 5.892447718818185 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/32",
            "value": 12.339533261839893,
            "unit": "us/iter",
            "extra": "iterations: 58746\ncpu: 12.338239607803212 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/64",
            "value": 24.871114452647873,
            "unit": "us/iter",
            "extra": "iterations: 27898\ncpu: 24.860595311491622 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/128",
            "value": 50.64803977742485,
            "unit": "us/iter",
            "extra": "iterations: 13299\ncpu: 50.64046018497626 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/2",
            "value": 0.6505327538862343,
            "unit": "us/iter",
            "extra": "iterations: 1095412\ncpu: 0.6504780721774018 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/4",
            "value": 1.0391400505203938,
            "unit": "us/iter",
            "extra": "iterations: 685267\ncpu: 1.0390587683340902 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/8",
            "value": 2.0270802909265306,
            "unit": "us/iter",
            "extra": "iterations: 342492\ncpu: 2.0269048123752103 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/16",
            "value": 4.152043877266988,
            "unit": "us/iter",
            "extra": "iterations: 161815\ncpu: 4.1517503383493235 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/32",
            "value": 7.877457582653914,
            "unit": "us/iter",
            "extra": "iterations: 89197\ncpu: 7.87704501272471 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/64",
            "value": 15.92021141259808,
            "unit": "us/iter",
            "extra": "iterations: 44004\ncpu: 15.918841082628695 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/128",
            "value": 32.27816944538982,
            "unit": "us/iter",
            "extra": "iterations: 20573\ncpu: 32.27343022408056 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/2",
            "value": 0.26657164624010604,
            "unit": "us/iter",
            "extra": "iterations: 2511681\ncpu: 0.26654843389745614 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/4",
            "value": 0.44524218638742974,
            "unit": "us/iter",
            "extra": "iterations: 1558882\ncpu: 0.44520241365286517 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/8",
            "value": 0.8397376115560213,
            "unit": "us/iter",
            "extra": "iterations: 819655\ncpu: 0.8397030848344686 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/16",
            "value": 1.6121559592741104,
            "unit": "us/iter",
            "extra": "iterations: 416737\ncpu: 1.6120532566102792 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/32",
            "value": 3.300693739147495,
            "unit": "us/iter",
            "extra": "iterations: 213661\ncpu: 3.3005252526198143 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/64",
            "value": 6.481353273063545,
            "unit": "us/iter",
            "extra": "iterations: 106521\ncpu: 6.481044404389653 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/128",
            "value": 13.705828965844573,
            "unit": "us/iter",
            "extra": "iterations: 50563\ncpu: 13.705579771770031 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/2",
            "value": 67.16966644492582,
            "unit": "us/iter",
            "extra": "iterations: 10523\ncpu: 67.16366216858333 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/4",
            "value": 70.5518008018749,
            "unit": "us/iter",
            "extra": "iterations: 10226\ncpu: 70.54689331116747 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/8",
            "value": 77.72296877421789,
            "unit": "us/iter",
            "extra": "iterations: 9031\ncpu: 77.71766714649507 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/16",
            "value": 93.60113907014805,
            "unit": "us/iter",
            "extra": "iterations: 7356\ncpu: 93.59258917890003 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/32",
            "value": 120.39338240918235,
            "unit": "us/iter",
            "extra": "iterations: 5753\ncpu: 120.3734428993567 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/64",
            "value": 168.48644516908345,
            "unit": "us/iter",
            "extra": "iterations: 4140\ncpu: 168.46485048309304 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/128",
            "value": 287.5582538838985,
            "unit": "us/iter",
            "extra": "iterations: 2446\ncpu: 287.5194153720374 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/2",
            "value": 70.64335307539243,
            "unit": "us/iter",
            "extra": "iterations: 10080\ncpu: 70.63541656746044 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/4",
            "value": 70.77577471004679,
            "unit": "us/iter",
            "extra": "iterations: 9743\ncpu: 70.76885682028171 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/8",
            "value": 73.44609140673388,
            "unit": "us/iter",
            "extra": "iterations: 9682\ncpu: 73.44131935550368 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/16",
            "value": 75.66932171410555,
            "unit": "us/iter",
            "extra": "iterations: 9381\ncpu: 75.66847937320145 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/32",
            "value": 83.53875757216402,
            "unit": "us/iter",
            "extra": "iterations: 8419\ncpu: 83.52708171991814 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/64",
            "value": 99.2174760022612,
            "unit": "us/iter",
            "extra": "iterations: 7084\ncpu: 99.21006451157506 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/128",
            "value": 126.49439595960172,
            "unit": "us/iter",
            "extra": "iterations: 5445\ncpu: 126.48367033976105 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/2",
            "value": 70.10463701492347,
            "unit": "us/iter",
            "extra": "iterations: 10050\ncpu: 70.09866676616923 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/4",
            "value": 71.60479102956336,
            "unit": "us/iter",
            "extra": "iterations: 9810\ncpu: 71.59822599388298 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/8",
            "value": 72.29570503734898,
            "unit": "us/iter",
            "extra": "iterations: 10442\ncpu: 72.28744043286817 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/16",
            "value": 76.31369101604687,
            "unit": "us/iter",
            "extra": "iterations: 9350\ncpu: 76.30648267379644 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/32",
            "value": 84.34042303526299,
            "unit": "us/iter",
            "extra": "iterations: 8309\ncpu: 84.33566903357766 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/64",
            "value": 99.09779947916256,
            "unit": "us/iter",
            "extra": "iterations: 6912\ncpu: 99.09269227430599 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/128",
            "value": 124.22614787674028,
            "unit": "us/iter",
            "extra": "iterations: 5322\ncpu: 124.21927057497308 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/2",
            "value": 70.94398319912847,
            "unit": "us/iter",
            "extra": "iterations: 10059\ncpu: 70.93862461477144 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/4",
            "value": 70.34657508445034,
            "unit": "us/iter",
            "extra": "iterations: 9769\ncpu: 70.34046401883558 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/8",
            "value": 72.60919945640562,
            "unit": "us/iter",
            "extra": "iterations: 9566\ncpu: 72.60105571816851 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/16",
            "value": 76.52874318647032,
            "unit": "us/iter",
            "extra": "iterations: 9283\ncpu: 76.52284013788605 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/32",
            "value": 82.92179105355466,
            "unit": "us/iter",
            "extra": "iterations: 8495\ncpu: 82.9150223660985 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/64",
            "value": 97.37523943084015,
            "unit": "us/iter",
            "extra": "iterations: 7309\ncpu: 97.36999986318389 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/128",
            "value": 125.97589186276039,
            "unit": "us/iter",
            "extra": "iterations: 5567\ncpu: 125.96766283456238 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/2",
            "value": 71.76223473568352,
            "unit": "us/iter",
            "extra": "iterations: 10007\ncpu: 71.7511513940248 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/4",
            "value": 71.89021435950342,
            "unit": "us/iter",
            "extra": "iterations: 9680\ncpu: 71.88422272727283 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/8",
            "value": 73.57114799959831,
            "unit": "us/iter",
            "extra": "iterations: 9973\ncpu: 73.56508272335324 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/16",
            "value": 76.36442119684413,
            "unit": "us/iter",
            "extra": "iterations: 9124\ncpu: 76.35541166155203 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/32",
            "value": 84.29217126940468,
            "unit": "us/iter",
            "extra": "iterations: 8437\ncpu: 84.28267784757675 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/64",
            "value": 98.21492055024783,
            "unit": "us/iter",
            "extra": "iterations: 7124\ncpu: 98.2060211959587 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/128",
            "value": 130.02986422689548,
            "unit": "us/iter",
            "extra": "iterations: 5465\ncpu: 130.01678096980933 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/2",
            "value": 68.42176779780682,
            "unit": "us/iter",
            "extra": "iterations: 9931\ncpu: 68.42104279528671 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/4",
            "value": 72.71605639686946,
            "unit": "us/iter",
            "extra": "iterations: 9575\ncpu: 72.71180407310662 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/8",
            "value": 77.65499419791698,
            "unit": "us/iter",
            "extra": "iterations: 9307\ncpu: 77.64614548189641 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/16",
            "value": 86.06570836084664,
            "unit": "us/iter",
            "extra": "iterations: 7571\ncpu: 86.05561775194839 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/32",
            "value": 101.27997928687917,
            "unit": "us/iter",
            "extra": "iterations: 6759\ncpu: 101.26855688711481 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/64",
            "value": 135.66378962317316,
            "unit": "us/iter",
            "extra": "iterations: 5281\ncpu: 135.64877277031047 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/128",
            "value": 194.68697232022188,
            "unit": "us/iter",
            "extra": "iterations: 3685\ncpu: 194.67123446403986 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/2",
            "value": 71.57513641499384,
            "unit": "us/iter",
            "extra": "iterations: 9735\ncpu: 71.56870672829974 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/4",
            "value": 75.71151520158855,
            "unit": "us/iter",
            "extra": "iterations: 9078\ncpu: 75.70482881692051 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/8",
            "value": 94.84650927325895,
            "unit": "us/iter",
            "extra": "iterations: 7279\ncpu: 94.84302019508472 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/16",
            "value": 165.37789953596655,
            "unit": "us/iter",
            "extra": "iterations: 4310\ncpu: 165.36764338747344 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/32",
            "value": 458.2651682600375,
            "unit": "us/iter",
            "extra": "iterations: 1569\ncpu: 458.21749649458417 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/64",
            "value": 1558.5811367713577,
            "unit": "us/iter",
            "extra": "iterations: 446\ncpu: 1558.4078251121234 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/128",
            "value": 6138.582447618731,
            "unit": "us/iter",
            "extra": "iterations: 105\ncpu: 6081.589095238033 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/2",
            "value": 68.57067990407884,
            "unit": "us/iter",
            "extra": "iterations: 10425\ncpu: 68.5255105995195 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/4",
            "value": 76.42464953119683,
            "unit": "us/iter",
            "extra": "iterations: 9279\ncpu: 76.41627589179888 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/8",
            "value": 93.17627632570695,
            "unit": "us/iter",
            "extra": "iterations: 7958\ncpu: 93.17167705453623 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/16",
            "value": 154.74343439320188,
            "unit": "us/iter",
            "extra": "iterations: 4466\ncpu: 154.73311330048915 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/32",
            "value": 390.8845976948474,
            "unit": "us/iter",
            "extra": "iterations: 1822\ncpu: 390.8443144895758 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/64",
            "value": 1322.1715244618974,
            "unit": "us/iter",
            "extra": "iterations: 511\ncpu: 1322.1155557730374 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/128",
            "value": 5155.4359844961555,
            "unit": "us/iter",
            "extra": "iterations: 129\ncpu: 5154.804976744224 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/2",
            "value": 67.82362744159565,
            "unit": "us/iter",
            "extra": "iterations: 10444\ncpu: 67.81561336652716 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/4",
            "value": 70.46654501516336,
            "unit": "us/iter",
            "extra": "iterations: 10552\ncpu: 70.46086846095497 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/8",
            "value": 72.0601322073358,
            "unit": "us/iter",
            "extra": "iterations: 10302\ncpu: 72.05269685497878 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/16",
            "value": 76.75567162356789,
            "unit": "us/iter",
            "extra": "iterations: 9011\ncpu: 76.75435101542816 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/32",
            "value": 84.12719305389162,
            "unit": "us/iter",
            "extra": "iterations: 8350\ncpu: 84.09828275448912 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/64",
            "value": 100.37718363411156,
            "unit": "us/iter",
            "extra": "iterations: 7259\ncpu: 100.36959291913496 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/128",
            "value": 129.9623891762143,
            "unit": "us/iter",
            "extra": "iterations: 5414\ncpu: 129.94803768009277 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/2",
            "value": 70.39809091766955,
            "unit": "us/iter",
            "extra": "iterations: 10592\ncpu: 70.39509799848952 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/4",
            "value": 71.16024618440309,
            "unit": "us/iter",
            "extra": "iterations: 9566\ncpu: 71.15541689316146 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/8",
            "value": 90.76696564553986,
            "unit": "us/iter",
            "extra": "iterations: 8063\ncpu: 90.75962420935136 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/16",
            "value": 155.72038792720448,
            "unit": "us/iter",
            "extra": "iterations: 4506\ncpu: 155.6846138482049 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/32",
            "value": 412.2888748537867,
            "unit": "us/iter",
            "extra": "iterations: 1710\ncpu: 412.25999415204853 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/64",
            "value": 1434.6482704402601,
            "unit": "us/iter",
            "extra": "iterations: 477\ncpu: 1434.5340440251439 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/128",
            "value": 5624.132204917673,
            "unit": "us/iter",
            "extra": "iterations: 122\ncpu: 5623.642950819688 us\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "lukas.burgholzer@jku.at",
            "name": "Lukas Burgholzer",
            "username": "burgholzer"
          },
          "committer": {
            "email": "lukas.burgholzer@jku.at",
            "name": "Lukas Burgholzer",
            "username": "burgholzer"
          },
          "distinct": true,
          "id": "df9e633786b3812f4854ad4f9245d918bce728ed",
          "message": "🐛 Fix SWAP and GHZ benchmarks",
          "timestamp": "2021-04-01T16:15:49+02:00",
          "tree_id": "e1157be4935fa89e295b770b1a6761e6c614bf31",
          "url": "https://github.com/iic-jku/dd_package/commit/df9e633786b3812f4854ad4f9245d918bce728ed"
        },
        "date": 1617289921121,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_DDVectorNodeCreation",
            "value": 10.102711809092646,
            "unit": "ns/iter",
            "extra": "iterations: 67601477\ncpu: 10.092150812030336 ns\nthreads: 1"
          },
          {
            "name": "BM_DDMatrixNodeCreation",
            "value": 9.957732788666688,
            "unit": "ns/iter",
            "extra": "iterations: 70138552\ncpu: 9.957312463479427 ns\nthreads: 1"
          },
          {
            "name": "BM_ComplexNumbersCreation",
            "value": 26.783194608065536,
            "unit": "us/iter",
            "extra": "iterations: 26484\ncpu: 26.782985236369136 us\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/2",
            "value": 11.78903204918028,
            "unit": "ms/iter",
            "extra": "iterations: 61\ncpu: 11.775462721311479 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/4",
            "value": 11.603476433333526,
            "unit": "ms/iter",
            "extra": "iterations: 60\ncpu: 11.59947925 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/8",
            "value": 12.155323542372772,
            "unit": "ms/iter",
            "extra": "iterations: 59\ncpu: 12.143136067796624 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/16",
            "value": 12.105583392857357,
            "unit": "ms/iter",
            "extra": "iterations: 56\ncpu: 12.101958696428573 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/32",
            "value": 11.704536693548379,
            "unit": "ms/iter",
            "extra": "iterations: 62\ncpu: 11.700900564516129 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/64",
            "value": 11.09965830645185,
            "unit": "ms/iter",
            "extra": "iterations: 62\ncpu: 11.099288854838708 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/128",
            "value": 11.710666301587661,
            "unit": "ms/iter",
            "extra": "iterations: 63\ncpu: 11.70925079365078 ms\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/2",
            "value": 7.764129333600297,
            "unit": "ns/iter",
            "extra": "iterations: 92281263\ncpu: 7.763725871415516 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/4",
            "value": 7.628756131659832,
            "unit": "ns/iter",
            "extra": "iterations: 91240179\ncpu: 7.628464418071778 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/8",
            "value": 7.648507967046232,
            "unit": "ns/iter",
            "extra": "iterations: 90166038\ncpu: 7.647887234437433 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/16",
            "value": 7.607938668925954,
            "unit": "ns/iter",
            "extra": "iterations: 91722379\ncpu: 7.607676213893222 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/32",
            "value": 7.636804209133773,
            "unit": "ns/iter",
            "extra": "iterations: 92316191\ncpu: 7.636271160711135 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/64",
            "value": 7.724302201554,
            "unit": "ns/iter",
            "extra": "iterations: 92479498\ncpu: 7.723909811880676 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/128",
            "value": 7.672058776547922,
            "unit": "ns/iter",
            "extra": "iterations: 87675513\ncpu: 7.671651273942361 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/2",
            "value": 0.19385884723027771,
            "unit": "us/iter",
            "extra": "iterations: 3424049\ncpu: 0.19384812892572464 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/4",
            "value": 0.3904637046488471,
            "unit": "us/iter",
            "extra": "iterations: 1801002\ncpu: 0.3904372688092505 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/8",
            "value": 0.7203593022623163,
            "unit": "us/iter",
            "extra": "iterations: 974177\ncpu: 0.7203214990704949 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/16",
            "value": 1.3973667205816236,
            "unit": "us/iter",
            "extra": "iterations: 499552\ncpu: 1.3929617317116125 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/32",
            "value": 2.7380029730796385,
            "unit": "us/iter",
            "extra": "iterations: 245873\ncpu: 2.737877542471121 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/64",
            "value": 5.405047990883306,
            "unit": "us/iter",
            "extra": "iterations: 124607\ncpu: 5.404570080332565 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/128",
            "value": 11.003157048115945,
            "unit": "us/iter",
            "extra": "iterations: 63783\ncpu: 11.002465218004769 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/2",
            "value": 0.3620975191733913,
            "unit": "us/iter",
            "extra": "iterations: 1912024\ncpu: 0.3620768049982639 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/4",
            "value": 0.8884438109900257,
            "unit": "us/iter",
            "extra": "iterations: 796339\ncpu: 0.8884147002721211 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/8",
            "value": 1.8841015293581909,
            "unit": "us/iter",
            "extra": "iterations: 375517\ncpu: 1.884008100831652 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/16",
            "value": 3.822831182766109,
            "unit": "us/iter",
            "extra": "iterations: 181735\ncpu: 3.822658689850618 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/32",
            "value": 7.788743007379384,
            "unit": "us/iter",
            "extra": "iterations: 90524\ncpu: 7.787957293093534 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/64",
            "value": 15.485285068675372,
            "unit": "us/iter",
            "extra": "iterations: 45140\ncpu: 15.484470890562763 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/128",
            "value": 31.990688618143885,
            "unit": "us/iter",
            "extra": "iterations: 22079\ncpu: 31.98751505955883 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/2",
            "value": 0.37123687033959935,
            "unit": "us/iter",
            "extra": "iterations: 1899516\ncpu: 0.37122174911925027 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/4",
            "value": 0.7248714780040085,
            "unit": "us/iter",
            "extra": "iterations: 960038\ncpu: 0.7248230642953717 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/8",
            "value": 1.4000805719777196,
            "unit": "us/iter",
            "extra": "iterations: 500509\ncpu: 1.4000194082424093 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/16",
            "value": 2.6874164716494993,
            "unit": "us/iter",
            "extra": "iterations: 259379\ncpu: 2.6872025761530285 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/32",
            "value": 5.333830675622073,
            "unit": "us/iter",
            "extra": "iterations: 131316\ncpu: 5.33357817021537 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/64",
            "value": 10.569484133040035,
            "unit": "us/iter",
            "extra": "iterations: 66837\ncpu: 10.568942157786827 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/128",
            "value": 21.45157565628106,
            "unit": "us/iter",
            "extra": "iterations: 32608\ncpu: 21.450285819430714 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/2",
            "value": 0.19868742124192276,
            "unit": "us/iter",
            "extra": "iterations: 3523448\ncpu: 0.1986675330528504 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/4",
            "value": 0.39800811793904506,
            "unit": "us/iter",
            "extra": "iterations: 1775697\ncpu: 0.39799036209443606 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/8",
            "value": 0.7296298345110299,
            "unit": "us/iter",
            "extra": "iterations: 967859\ncpu: 0.7295907337742366 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/16",
            "value": 1.3967099779431118,
            "unit": "us/iter",
            "extra": "iterations: 500524\ncpu: 1.3966383749830165 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/32",
            "value": 2.758767163153634,
            "unit": "us/iter",
            "extra": "iterations: 253246\ncpu: 2.758576214431821 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/64",
            "value": 5.406923808237876,
            "unit": "us/iter",
            "extra": "iterations: 125906\ncpu: 5.40648358299053 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/128",
            "value": 11.068442576067847,
            "unit": "us/iter",
            "extra": "iterations: 63989\ncpu: 11.05654195252306 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/2",
            "value": 0.5574787647289882,
            "unit": "us/iter",
            "extra": "iterations: 1218939\ncpu: 0.5574489412513699 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/4",
            "value": 1.1885673002721115,
            "unit": "us/iter",
            "extra": "iterations: 590904\ncpu: 1.1884805789096045 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/8",
            "value": 2.608011956460908,
            "unit": "us/iter",
            "extra": "iterations: 267805\ncpu: 2.607909714157704 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/16",
            "value": 5.486520485238699,
            "unit": "us/iter",
            "extra": "iterations: 131729\ncpu: 5.465925513744085 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/32",
            "value": 11.029617245930298,
            "unit": "us/iter",
            "extra": "iterations: 63644\ncpu: 11.028750471371941 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/64",
            "value": 22.297015434554012,
            "unit": "us/iter",
            "extra": "iterations: 31423\ncpu: 22.295318524647502 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/128",
            "value": 46.44156393098602,
            "unit": "us/iter",
            "extra": "iterations: 15243\ncpu: 46.439773207373854 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/2",
            "value": 0.5545055734653281,
            "unit": "us/iter",
            "extra": "iterations: 1269946\ncpu: 0.5544683222751235 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/4",
            "value": 0.9295392899497995,
            "unit": "us/iter",
            "extra": "iterations: 751299\ncpu: 0.9294701031147379 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/8",
            "value": 1.8545304589552711,
            "unit": "us/iter",
            "extra": "iterations: 376638\ncpu: 1.8544127092858287 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/16",
            "value": 3.540327041061887,
            "unit": "us/iter",
            "extra": "iterations: 197385\ncpu: 3.5401990728778943 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/32",
            "value": 7.054438313499915,
            "unit": "us/iter",
            "extra": "iterations: 98571\ncpu: 7.053979963680995 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/64",
            "value": 14.254317134983525,
            "unit": "us/iter",
            "extra": "iterations: 49717\ncpu: 14.253156807530601 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/128",
            "value": 28.813099389204982,
            "unit": "us/iter",
            "extra": "iterations: 24067\ncpu: 28.810240121328007 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/2",
            "value": 0.3646635423818588,
            "unit": "us/iter",
            "extra": "iterations: 1931322\ncpu: 0.36465199070895293 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/4",
            "value": 0.705979955628543,
            "unit": "us/iter",
            "extra": "iterations: 971345\ncpu: 0.7059616058146138 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/8",
            "value": 1.4397593095549601,
            "unit": "us/iter",
            "extra": "iterations: 488960\ncpu: 1.4396609559064217 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/16",
            "value": 2.716289758774532,
            "unit": "us/iter",
            "extra": "iterations: 260213\ncpu: 2.716173334921785 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/32",
            "value": 5.329736780753458,
            "unit": "us/iter",
            "extra": "iterations: 132969\ncpu: 5.329273334386229 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/64",
            "value": 10.530772066498375,
            "unit": "us/iter",
            "extra": "iterations: 66107\ncpu: 10.530127581042803 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/128",
            "value": 21.21352729661191,
            "unit": "us/iter",
            "extra": "iterations: 32733\ncpu: 21.2116348944491 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/2",
            "value": 0.24342252542535106,
            "unit": "us/iter",
            "extra": "iterations: 2977835\ncpu: 0.24340350858929416 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/4",
            "value": 0.38864709147623294,
            "unit": "us/iter",
            "extra": "iterations: 1797888\ncpu: 0.38863975397799844 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/8",
            "value": 0.7551433070010329,
            "unit": "us/iter",
            "extra": "iterations: 957127\ncpu: 0.7550810446262647 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/16",
            "value": 1.410003611285487,
            "unit": "us/iter",
            "extra": "iterations: 490684\ncpu: 1.4099039748595952 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/32",
            "value": 2.737572252239606,
            "unit": "us/iter",
            "extra": "iterations: 256518\ncpu: 2.7374945150048275 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/64",
            "value": 5.607550758011912,
            "unit": "us/iter",
            "extra": "iterations: 125064\ncpu: 5.607119426853456 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/128",
            "value": 11.191934330813412,
            "unit": "us/iter",
            "extra": "iterations: 63226\ncpu: 11.19129125676149 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/2",
            "value": 0.5510448362665779,
            "unit": "us/iter",
            "extra": "iterations: 1106738\ncpu: 0.551001047221656 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/4",
            "value": 1.1092221461263316,
            "unit": "us/iter",
            "extra": "iterations: 630783\ncpu: 1.1091478115294835 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/8",
            "value": 2.397837275492427,
            "unit": "us/iter",
            "extra": "iterations: 276160\ncpu: 2.397580366454236 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/16",
            "value": 4.934699155095263,
            "unit": "us/iter",
            "extra": "iterations: 139424\ncpu: 4.934290323043379 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/32",
            "value": 10.254550284981342,
            "unit": "us/iter",
            "extra": "iterations: 70180\ncpu: 10.254071672841372 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/64",
            "value": 20.66851096865199,
            "unit": "us/iter",
            "extra": "iterations: 34006\ncpu: 20.667906310650785 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/128",
            "value": 41.940043676779894,
            "unit": "us/iter",
            "extra": "iterations: 16645\ncpu: 41.93576797837228 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/2",
            "value": 0.5467055067628157,
            "unit": "us/iter",
            "extra": "iterations: 1183236\ncpu: 0.5466607194169264 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/4",
            "value": 0.8887823772870893,
            "unit": "us/iter",
            "extra": "iterations: 792500\ncpu: 0.8887370624605713 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/8",
            "value": 1.737371143443455,
            "unit": "us/iter",
            "extra": "iterations: 401524\ncpu: 1.7372769498211753 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/16",
            "value": 3.384039756961057,
            "unit": "us/iter",
            "extra": "iterations: 209020\ncpu: 3.383704970816212 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/32",
            "value": 6.641284255182334,
            "unit": "us/iter",
            "extra": "iterations: 105838\ncpu: 6.640993584534858 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/64",
            "value": 13.56493773196676,
            "unit": "us/iter",
            "extra": "iterations: 52001\ncpu: 13.564454779715645 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/128",
            "value": 27.468069460795967,
            "unit": "us/iter",
            "extra": "iterations: 25482\ncpu: 27.466601797347536 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/2",
            "value": 0.23191425978230898,
            "unit": "us/iter",
            "extra": "iterations: 3051940\ncpu: 0.2318923743586013 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/4",
            "value": 0.39894836961919805,
            "unit": "us/iter",
            "extra": "iterations: 1761889\ncpu: 0.39892205468108377 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/8",
            "value": 0.7713757213549289,
            "unit": "us/iter",
            "extra": "iterations: 924129\ncpu: 0.7712932339532617 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/16",
            "value": 1.4521465789490413,
            "unit": "us/iter",
            "extra": "iterations: 475921\ncpu: 1.4520228588358268 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/32",
            "value": 2.9171096032274475,
            "unit": "us/iter",
            "extra": "iterations: 240440\ncpu: 2.9167949841956022 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/64",
            "value": 5.935248488260085,
            "unit": "us/iter",
            "extra": "iterations: 117249\ncpu: 5.934795631519133 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/128",
            "value": 12.317712371152071,
            "unit": "us/iter",
            "extra": "iterations: 57529\ncpu: 12.317011489857418 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/2",
            "value": 371.289100656458,
            "unit": "us/iter",
            "extra": "iterations: 1828\ncpu: 371.2550979212193 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/4",
            "value": 371.68710684647056,
            "unit": "us/iter",
            "extra": "iterations: 1928\ncpu: 371.6490254149446 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/8",
            "value": 381.27250477707,
            "unit": "us/iter",
            "extra": "iterations: 1884\ncpu: 381.2466852441672 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/16",
            "value": 388.4843144414126,
            "unit": "us/iter",
            "extra": "iterations: 1835\ncpu: 388.4765782016333 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/32",
            "value": 410.0239003476202,
            "unit": "us/iter",
            "extra": "iterations: 1726\ncpu: 410.0010208574744 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/64",
            "value": 461.88085329744393,
            "unit": "us/iter",
            "extra": "iterations: 1486\ncpu: 461.84791520861035 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/128",
            "value": 567.2505050590132,
            "unit": "us/iter",
            "extra": "iterations: 1186\ncpu: 567.1992200674553 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/2",
            "value": 361.1479641577135,
            "unit": "us/iter",
            "extra": "iterations: 1953\ncpu: 361.1139426523309 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/4",
            "value": 370.46283828045483,
            "unit": "us/iter",
            "extra": "iterations: 1954\ncpu: 370.423126919139 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/8",
            "value": 358.76545253505725,
            "unit": "us/iter",
            "extra": "iterations: 1854\ncpu: 358.746067961163 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/16",
            "value": 372.05476373057905,
            "unit": "us/iter",
            "extra": "iterations: 1930\ncpu: 372.03111813471895 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/32",
            "value": 380.72714610904046,
            "unit": "us/iter",
            "extra": "iterations: 1889\ncpu: 380.7064430915882 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/64",
            "value": 388.41755448354434,
            "unit": "us/iter",
            "extra": "iterations: 1762\ncpu: 388.3839676503956 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/128",
            "value": 426.62714242424323,
            "unit": "us/iter",
            "extra": "iterations: 1650\ncpu: 426.58411333333515 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/2",
            "value": 366.2504868488755,
            "unit": "us/iter",
            "extra": "iterations: 1939\ncpu: 366.2255915420378 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/4",
            "value": 365.5630015584523,
            "unit": "us/iter",
            "extra": "iterations: 1925\ncpu: 365.5350062337657 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/8",
            "value": 361.24341947368663,
            "unit": "us/iter",
            "extra": "iterations: 1900\ncpu: 361.2269036842077 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/16",
            "value": 376.3424579195075,
            "unit": "us/iter",
            "extra": "iterations: 1913\ncpu: 376.30597177208847 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/32",
            "value": 375.4977879429094,
            "unit": "us/iter",
            "extra": "iterations: 1891\ncpu: 375.46043469063926 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/64",
            "value": 391.17449692567703,
            "unit": "us/iter",
            "extra": "iterations: 1789\ncpu: 391.14353269983445 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/128",
            "value": 420.7254339622707,
            "unit": "us/iter",
            "extra": "iterations: 1643\ncpu: 420.6974923919699 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/2",
            "value": 366.74119958419885,
            "unit": "us/iter",
            "extra": "iterations: 1924\ncpu: 366.7249553014511 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/4",
            "value": 372.8850129198794,
            "unit": "us/iter",
            "extra": "iterations: 1935\ncpu: 372.85222170542977 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/8",
            "value": 378.2904130781348,
            "unit": "us/iter",
            "extra": "iterations: 1881\ncpu: 378.2522493354563 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/16",
            "value": 368.2844038147052,
            "unit": "us/iter",
            "extra": "iterations: 1835\ncpu: 368.2591215258817 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/32",
            "value": 382.163744959146,
            "unit": "us/iter",
            "extra": "iterations: 1835\ncpu: 382.1245934604925 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/64",
            "value": 391.46211405982615,
            "unit": "us/iter",
            "extra": "iterations: 1771\ncpu: 391.45429813664225 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/128",
            "value": 417.125804229621,
            "unit": "us/iter",
            "extra": "iterations: 1655\ncpu: 417.09623021148354 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/2",
            "value": 371.26094535238764,
            "unit": "us/iter",
            "extra": "iterations: 1958\ncpu: 371.22218181817874 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/4",
            "value": 363.1224356060632,
            "unit": "us/iter",
            "extra": "iterations: 1848\ncpu: 363.0915898268375 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/8",
            "value": 370.2977190775658,
            "unit": "us/iter",
            "extra": "iterations: 1908\ncpu: 370.26760849056933 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/16",
            "value": 366.9005075268935,
            "unit": "us/iter",
            "extra": "iterations: 1860\ncpu: 366.8846032258126 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/32",
            "value": 376.6239249074713,
            "unit": "us/iter",
            "extra": "iterations: 1891\ncpu: 376.61694077208085 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/64",
            "value": 392.3553947661663,
            "unit": "us/iter",
            "extra": "iterations: 1796\ncpu: 392.3198591314138 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/128",
            "value": 413.278999390999,
            "unit": "us/iter",
            "extra": "iterations: 1642\ncpu: 413.24346102313535 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/2",
            "value": 361.27729846938615,
            "unit": "us/iter",
            "extra": "iterations: 1960\ncpu: 361.241276020406 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/4",
            "value": 366.38935199585757,
            "unit": "us/iter",
            "extra": "iterations: 1929\ncpu: 366.37038206324775 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/8",
            "value": 373.6523482666902,
            "unit": "us/iter",
            "extra": "iterations: 1875\ncpu: 373.64407093333887 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/16",
            "value": 385.8176307439989,
            "unit": "us/iter",
            "extra": "iterations: 1828\ncpu: 385.782012035013 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/32",
            "value": 399.80349772468384,
            "unit": "us/iter",
            "extra": "iterations: 1758\ncpu: 399.7726888509649 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/64",
            "value": 422.6842797619058,
            "unit": "us/iter",
            "extra": "iterations: 1680\ncpu: 422.6505470238047 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/128",
            "value": 488.74963877264963,
            "unit": "us/iter",
            "extra": "iterations: 1434\ncpu: 488.74048396094963 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/2",
            "value": 369.94486896198396,
            "unit": "us/iter",
            "extra": "iterations: 1946\ncpu: 369.9283751284638 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/4",
            "value": 367.25549542272324,
            "unit": "us/iter",
            "extra": "iterations: 1857\ncpu: 367.21954173397614 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/8",
            "value": 398.5578728193486,
            "unit": "us/iter",
            "extra": "iterations: 1777\ncpu: 398.53006809228907 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/16",
            "value": 452.0502706270503,
            "unit": "us/iter",
            "extra": "iterations: 1515\ncpu: 452.00153861386667 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/32",
            "value": 725.0857289339683,
            "unit": "us/iter",
            "extra": "iterations: 985\ncpu: 725.0356040609048 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/64",
            "value": 1765.8690989846866,
            "unit": "us/iter",
            "extra": "iterations: 394\ncpu: 1765.6769873096423 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/128",
            "value": 6175.351572727033,
            "unit": "us/iter",
            "extra": "iterations: 110\ncpu: 6174.757245454481 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/2",
            "value": 370.40698615547336,
            "unit": "us/iter",
            "extra": "iterations: 1878\ncpu: 370.3670037273589 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/4",
            "value": 364.9603972972862,
            "unit": "us/iter",
            "extra": "iterations: 1850\ncpu: 364.9357637837855 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/8",
            "value": 392.770896571099,
            "unit": "us/iter",
            "extra": "iterations: 1779\ncpu: 392.75928442945616 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/16",
            "value": 445.9112461059092,
            "unit": "us/iter",
            "extra": "iterations: 1605\ncpu: 445.898854205606 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/32",
            "value": 672.1931728748675,
            "unit": "us/iter",
            "extra": "iterations: 1047\ncpu: 672.1702569245203 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/64",
            "value": 1572.1433377482715,
            "unit": "us/iter",
            "extra": "iterations: 453\ncpu: 1572.1269889625057 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/128",
            "value": 5107.066390977231,
            "unit": "us/iter",
            "extra": "iterations: 133\ncpu: 5106.605684210607 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/2",
            "value": 371.2096325107173,
            "unit": "us/iter",
            "extra": "iterations: 1864\ncpu: 371.19429023605437 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/4",
            "value": 366.44909302325345,
            "unit": "us/iter",
            "extra": "iterations: 1849\ncpu: 366.4367344510615 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/8",
            "value": 373.6813924336273,
            "unit": "us/iter",
            "extra": "iterations: 1771\ncpu: 373.64348955391176 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/16",
            "value": 368.0162727272835,
            "unit": "us/iter",
            "extra": "iterations: 1870\ncpu: 367.9860016042863 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/32",
            "value": 385.24840602741745,
            "unit": "us/iter",
            "extra": "iterations: 1825\ncpu: 385.18847780822347 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/64",
            "value": 387.8094435075829,
            "unit": "us/iter",
            "extra": "iterations: 1779\ncpu: 387.78806632940154 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/128",
            "value": 430.663304832717,
            "unit": "us/iter",
            "extra": "iterations: 1614\ncpu: 430.64554151177157 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/2",
            "value": 361.5919745157978,
            "unit": "us/iter",
            "extra": "iterations: 1962\ncpu: 361.5601452599302 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/4",
            "value": 368.13173347436083,
            "unit": "us/iter",
            "extra": "iterations: 1891\ncpu: 368.10328080379907 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/8",
            "value": 385.347236111089,
            "unit": "us/iter",
            "extra": "iterations: 1800\ncpu: 385.30916888888095 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/16",
            "value": 444.61998597833093,
            "unit": "us/iter",
            "extra": "iterations: 1569\ncpu: 444.57584703634126 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/32",
            "value": 697.1679090909171,
            "unit": "us/iter",
            "extra": "iterations: 1012\ncpu: 696.9403873517921 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/64",
            "value": 1655.5684033019058,
            "unit": "us/iter",
            "extra": "iterations: 424\ncpu: 1655.4489103773694 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/128",
            "value": 5598.9699666668,
            "unit": "us/iter",
            "extra": "iterations: 120\ncpu: 5598.391666666676 us\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "lukas.burgholzer@jku.at",
            "name": "Lukas Burgholzer",
            "username": "burgholzer"
          },
          "committer": {
            "email": "lukas.burgholzer@jku.at",
            "name": "Lukas Burgholzer",
            "username": "burgholzer"
          },
          "distinct": true,
          "id": "17092ec00db72053a376698c886200ac8d397492",
          "message": "⚡ improved compute table reset",
          "timestamp": "2021-04-01T16:18:10+02:00",
          "tree_id": "9bdb42ef0ff3a0b6cfa07fbb43972d567c01db2d",
          "url": "https://github.com/iic-jku/dd_package/commit/17092ec00db72053a376698c886200ac8d397492"
        },
        "date": 1617296488736,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_DDVectorNodeCreation",
            "value": 5.77230556912139,
            "unit": "ns/iter",
            "extra": "iterations: 120628563\ncpu: 5.771775661457561 ns\nthreads: 1"
          },
          {
            "name": "BM_DDMatrixNodeCreation",
            "value": 5.789015792230573,
            "unit": "ns/iter",
            "extra": "iterations: 121301420\ncpu: 5.787790959083579 ns\nthreads: 1"
          },
          {
            "name": "BM_ComplexNumbersCreation",
            "value": 15.939916586123147,
            "unit": "us/iter",
            "extra": "iterations: 34143\ncpu: 15.939670064142001 us\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/2",
            "value": 14.437463224489747,
            "unit": "ms/iter",
            "extra": "iterations: 49\ncpu: 14.433804673469389 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/4",
            "value": 14.41119185416658,
            "unit": "ms/iter",
            "extra": "iterations: 48\ncpu: 14.40445054166667 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/8",
            "value": 14.451676437500005,
            "unit": "ms/iter",
            "extra": "iterations: 48\ncpu: 14.44662179166667 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/16",
            "value": 14.548388250000007,
            "unit": "ms/iter",
            "extra": "iterations: 48\ncpu: 14.533620062499992 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/32",
            "value": 14.500832749999878,
            "unit": "ms/iter",
            "extra": "iterations: 48\ncpu: 14.492359812500004 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/64",
            "value": 14.403223645833426,
            "unit": "ms/iter",
            "extra": "iterations: 48\ncpu: 14.400212104166663 ms\nthreads: 1"
          },
          {
            "name": "BM_PackageCreation/128",
            "value": 14.395256374999832,
            "unit": "ms/iter",
            "extra": "iterations: 48\ncpu: 14.388735250000005 ms\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/2",
            "value": 7.167289778330447,
            "unit": "ns/iter",
            "extra": "iterations: 99055012\ncpu: 7.166552228573753 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/4",
            "value": 7.211423615916734,
            "unit": "ns/iter",
            "extra": "iterations: 96661198\ncpu: 7.210914859548906 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/8",
            "value": 7.219231554327013,
            "unit": "ns/iter",
            "extra": "iterations: 97567652\ncpu: 7.218811066602269 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/16",
            "value": 7.192321998317496,
            "unit": "ns/iter",
            "extra": "iterations: 96874295\ncpu: 7.191909443057101 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/32",
            "value": 7.19286669458174,
            "unit": "ns/iter",
            "extra": "iterations: 96664668\ncpu: 7.192519649475239 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/64",
            "value": 7.2196298912981005,
            "unit": "ns/iter",
            "extra": "iterations: 96306463\ncpu: 7.213620450374128 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdentCached/128",
            "value": 7.188114784832108,
            "unit": "ns/iter",
            "extra": "iterations: 96599244\ncpu: 7.18781057955277 ns\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/2",
            "value": 0.18949745293963907,
            "unit": "us/iter",
            "extra": "iterations: 3692492\ncpu: 0.1894870044403614 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/4",
            "value": 0.35772383148822,
            "unit": "us/iter",
            "extra": "iterations: 1960314\ncpu: 0.35769929052182486 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/8",
            "value": 0.6577177095704273,
            "unit": "us/iter",
            "extra": "iterations: 1056745\ncpu: 0.6576796568708624 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/16",
            "value": 1.2682720063817872,
            "unit": "us/iter",
            "extra": "iterations: 547807\ncpu: 1.268148366121646 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/32",
            "value": 2.529572633403694,
            "unit": "us/iter",
            "extra": "iterations: 278047\ncpu: 2.5294401593975153 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/64",
            "value": 5.025192244514412,
            "unit": "us/iter",
            "extra": "iterations: 139411\ncpu: 5.024875834761945 us\nthreads: 1"
          },
          {
            "name": "BM_MakeIdent/128",
            "value": 10.420622746742819,
            "unit": "us/iter",
            "extra": "iterations: 67236\ncpu: 10.4198391040514 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/2",
            "value": 0.3549712195693474,
            "unit": "us/iter",
            "extra": "iterations: 1963070\ncpu: 0.3549542802854716 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/4",
            "value": 0.8528764872541903,
            "unit": "us/iter",
            "extra": "iterations: 817446\ncpu: 0.852827160448518 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/8",
            "value": 1.8330867437652478,
            "unit": "us/iter",
            "extra": "iterations: 383578\ncpu: 1.832972438461017 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/16",
            "value": 3.7910362175759755,
            "unit": "us/iter",
            "extra": "iterations: 184855\ncpu: 3.790843098644894 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/32",
            "value": 7.62152291796902,
            "unit": "us/iter",
            "extra": "iterations: 91173\ncpu: 7.62112578285241 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/64",
            "value": 15.367797698018656,
            "unit": "us/iter",
            "extra": "iterations: 45526\ncpu: 15.366891073232875 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetTop/128",
            "value": 31.39420966873131,
            "unit": "us/iter",
            "extra": "iterations: 22278\ncpu: 31.391037615584903 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/2",
            "value": 0.35723243226704704,
            "unit": "us/iter",
            "extra": "iterations: 1961010\ncpu: 0.35720757874768516 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/4",
            "value": 0.6938561303661797,
            "unit": "us/iter",
            "extra": "iterations: 1012778\ncpu: 0.6938122806775004 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/8",
            "value": 1.3460752652385914,
            "unit": "us/iter",
            "extra": "iterations: 519815\ncpu: 1.3459777690139778 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/16",
            "value": 2.594716773011551,
            "unit": "us/iter",
            "extra": "iterations: 266899\ncpu: 2.5945851239607425 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/32",
            "value": 5.144050759579065,
            "unit": "us/iter",
            "extra": "iterations: 135009\ncpu: 5.143676162329893 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/64",
            "value": 10.286910922462452,
            "unit": "us/iter",
            "extra": "iterations: 67851\ncpu: 10.286457900399409 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetMiddle/128",
            "value": 20.963767619620878,
            "unit": "us/iter",
            "extra": "iterations: 33230\ncpu: 20.962631778513334 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/2",
            "value": 0.19071148263394092,
            "unit": "us/iter",
            "extra": "iterations: 3681664\ncpu: 0.19069932834718153 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/4",
            "value": 0.35452721226612594,
            "unit": "us/iter",
            "extra": "iterations: 1961891\ncpu: 0.3545080633939392 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/8",
            "value": 0.6592096411991821,
            "unit": "us/iter",
            "extra": "iterations: 1053147\ncpu: 0.6591462179543821 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/16",
            "value": 1.2792613678542373,
            "unit": "us/iter",
            "extra": "iterations: 546915\ncpu: 1.2791851677134503 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/32",
            "value": 2.5130648520264467,
            "unit": "us/iter",
            "extra": "iterations: 281672\ncpu: 2.512926780084655 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/64",
            "value": 5.0159145257125,
            "unit": "us/iter",
            "extra": "iterations: 142382\ncpu: 5.015818649829339 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSingleQubitGateDD_TargetBottom/128",
            "value": 10.32712081451968,
            "unit": "us/iter",
            "extra": "iterations: 68212\ncpu: 10.327006010672672 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/2",
            "value": 0.4733877515349017,
            "unit": "us/iter",
            "extra": "iterations: 1504662\ncpu: 0.47335922419785653 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/4",
            "value": 1.141487391562479,
            "unit": "us/iter",
            "extra": "iterations: 606340\ncpu: 1.1414665946498694 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/8",
            "value": 2.489771697622071,
            "unit": "us/iter",
            "extra": "iterations: 280457\ncpu: 2.486958924184456 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/16",
            "value": 5.200933561755892,
            "unit": "us/iter",
            "extra": "iterations: 134546\ncpu: 5.2008623296121534 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/32",
            "value": 10.65831730318022,
            "unit": "us/iter",
            "extra": "iterations: 66063\ncpu: 10.65795993218593 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/64",
            "value": 21.991838267304992,
            "unit": "us/iter",
            "extra": "iterations: 32158\ncpu: 21.989519932831534 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetTop/128",
            "value": 44.92654632917994,
            "unit": "us/iter",
            "extra": "iterations: 15487\ncpu: 44.92404203525526 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/2",
            "value": 0.47161567508273927,
            "unit": "us/iter",
            "extra": "iterations: 1487788\ncpu: 0.47154904260553204 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/4",
            "value": 0.8628431928478114,
            "unit": "us/iter",
            "extra": "iterations: 814746\ncpu: 0.8627990944417008 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/8",
            "value": 1.7797553356063391,
            "unit": "us/iter",
            "extra": "iterations: 389787\ncpu: 1.779658049139663 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/16",
            "value": 3.4015429420619725,
            "unit": "us/iter",
            "extra": "iterations: 207256\ncpu: 3.401362151156063 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/32",
            "value": 6.818443452908679,
            "unit": "us/iter",
            "extra": "iterations: 101526\ncpu: 6.818076867009403 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/64",
            "value": 13.394335036922222,
            "unit": "us/iter",
            "extra": "iterations: 51460\ncpu: 13.39355015546057 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlBottom_TargetMiddle/128",
            "value": 28.0343101042532,
            "unit": "us/iter",
            "extra": "iterations: 25227\ncpu: 28.03250069370115 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/2",
            "value": 0.35837199156779376,
            "unit": "us/iter",
            "extra": "iterations: 1952512\ncpu: 0.356353096933591 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/4",
            "value": 0.7070429513843327,
            "unit": "us/iter",
            "extra": "iterations: 992890\ncpu: 0.7069853800521708 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/8",
            "value": 1.3940824121044795,
            "unit": "us/iter",
            "extra": "iterations: 500509\ncpu: 1.3939860262252937 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/16",
            "value": 2.6147830174858715,
            "unit": "us/iter",
            "extra": "iterations: 266215\ncpu: 2.614635741787656 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/32",
            "value": 5.2000645312812726,
            "unit": "us/iter",
            "extra": "iterations: 134121\ncpu: 5.1997169272522665 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/64",
            "value": 10.219808661879323,
            "unit": "us/iter",
            "extra": "iterations: 68230\ncpu: 10.21924159460644 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetMiddle/128",
            "value": 20.956858124943498,
            "unit": "us/iter",
            "extra": "iterations: 33311\ncpu: 20.95579637357054 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/2",
            "value": 0.2036749852721471,
            "unit": "us/iter",
            "extra": "iterations: 3422088\ncpu: 0.20365369183960255 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/4",
            "value": 0.3543211981094914,
            "unit": "us/iter",
            "extra": "iterations: 1963293\ncpu: 0.3543006846150789 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/8",
            "value": 0.6729378878665377,
            "unit": "us/iter",
            "extra": "iterations: 1028221\ncpu: 0.6728901413217588 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/16",
            "value": 1.293660430444176,
            "unit": "us/iter",
            "extra": "iterations: 538467\ncpu: 1.2935884817453942 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/32",
            "value": 2.5440473019651137,
            "unit": "us/iter",
            "extra": "iterations: 276479\ncpu: 2.543896701015265 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/64",
            "value": 5.1186060860207245,
            "unit": "us/iter",
            "extra": "iterations: 134735\ncpu: 5.118312049578829 us\nthreads: 1"
          },
          {
            "name": "BM_MakeControlledQubitGateDD_ControlTop_TargetBottom/128",
            "value": 10.367277586078215,
            "unit": "us/iter",
            "extra": "iterations: 66945\ncpu: 10.36662119650461 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/2",
            "value": 0.4661725160923184,
            "unit": "us/iter",
            "extra": "iterations: 1497298\ncpu: 0.4661509038280987 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/4",
            "value": 1.0854450701901897,
            "unit": "us/iter",
            "extra": "iterations: 642611\ncpu: 1.085382940846027 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/8",
            "value": 2.314831003562794,
            "unit": "us/iter",
            "extra": "iterations: 300888\ncpu: 2.3147012709047936 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/16",
            "value": 4.816811296146312,
            "unit": "us/iter",
            "extra": "iterations: 145678\ncpu: 4.81670064114008 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/32",
            "value": 9.877969551281824,
            "unit": "us/iter",
            "extra": "iterations: 70512\ncpu: 9.877685415248362 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/64",
            "value": 20.39190837718965,
            "unit": "us/iter",
            "extra": "iterations: 34773\ncpu: 20.389003652258737 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetTop/128",
            "value": 42.49076005825588,
            "unit": "us/iter",
            "extra": "iterations: 16479\ncpu: 42.487464105831805 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/2",
            "value": 0.4720588700235278,
            "unit": "us/iter",
            "extra": "iterations: 1490385\ncpu: 0.47202232242004055 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/4",
            "value": 0.8469929181009435,
            "unit": "us/iter",
            "extra": "iterations: 825626\ncpu: 0.8469299913035803 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/8",
            "value": 1.682486181248606,
            "unit": "us/iter",
            "extra": "iterations: 416246\ncpu: 1.682385228927111 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/16",
            "value": 3.2756377732611144,
            "unit": "us/iter",
            "extra": "iterations: 213532\ncpu: 3.275434225315202 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/32",
            "value": 6.516565422477494,
            "unit": "us/iter",
            "extra": "iterations: 107272\ncpu: 6.516199772540834 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/64",
            "value": 13.404185704665679,
            "unit": "us/iter",
            "extra": "iterations: 51975\ncpu: 13.40314387686398 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetMiddle/128",
            "value": 27.569997561838612,
            "unit": "us/iter",
            "extra": "iterations: 25429\ncpu: 27.5681457391167 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/2",
            "value": 0.19969372999185953,
            "unit": "us/iter",
            "extra": "iterations: 3494828\ncpu: 0.19968086841469884 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/4",
            "value": 0.3809088014459895,
            "unit": "us/iter",
            "extra": "iterations: 1835687\ncpu: 0.38089003735385546 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/8",
            "value": 0.7275005441656677,
            "unit": "us/iter",
            "extra": "iterations: 962942\ncpu: 0.7274524218488725 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/16",
            "value": 1.4300089215439944,
            "unit": "us/iter",
            "extra": "iterations: 489153\ncpu: 1.4299427581963178 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/32",
            "value": 2.829470463861516,
            "unit": "us/iter",
            "extra": "iterations: 246884\ncpu: 2.8292299298456127 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/64",
            "value": 5.812399657505745,
            "unit": "us/iter",
            "extra": "iterations: 119710\ncpu: 5.812054941107693 us\nthreads: 1"
          },
          {
            "name": "BM_MakeFullControlledToffoliDD_TargetBottom/128",
            "value": 11.829213173407778,
            "unit": "us/iter",
            "extra": "iterations: 58694\ncpu: 11.828365011755979 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/2",
            "value": 39.022199854854435,
            "unit": "us/iter",
            "extra": "iterations: 17913\ncpu: 39.01943035784003 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/4",
            "value": 42.433784179628674,
            "unit": "us/iter",
            "extra": "iterations: 16523\ncpu: 42.41084766688839 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/8",
            "value": 48.76088490906655,
            "unit": "us/iter",
            "extra": "iterations: 14406\ncpu: 48.75800472025477 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/16",
            "value": 61.480478417900805,
            "unit": "us/iter",
            "extra": "iterations: 11352\ncpu: 61.47689711064161 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/32",
            "value": 87.1811944860279,
            "unit": "us/iter",
            "extra": "iterations: 8016\ncpu: 87.17995958083938 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/64",
            "value": 138.90207179896277,
            "unit": "us/iter",
            "extra": "iterations: 5014\ncpu: 138.89831591543762 us\nthreads: 1"
          },
          {
            "name": "BM_MakeSWAPDD/128",
            "value": 242.90365414057047,
            "unit": "us/iter",
            "extra": "iterations: 2874\ncpu: 242.89458420320332 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/2",
            "value": 37.43112342058956,
            "unit": "us/iter",
            "extra": "iterations: 18757\ncpu: 37.428988377672304 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/4",
            "value": 38.509224676397864,
            "unit": "us/iter",
            "extra": "iterations: 18155\ncpu: 38.507063288350906 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/8",
            "value": 40.43980366461733,
            "unit": "us/iter",
            "extra": "iterations: 17246\ncpu: 40.43715377478856 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/16",
            "value": 44.543110051496576,
            "unit": "us/iter",
            "extra": "iterations: 15729\ncpu: 44.54204558458901 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/32",
            "value": 52.63269797088434,
            "unit": "us/iter",
            "extra": "iterations: 13257\ncpu: 52.62894576450133 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/64",
            "value": 68.62843470588253,
            "unit": "us/iter",
            "extra": "iterations: 10200\ncpu: 68.62278764705849 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_X/128",
            "value": 99.65232853067091,
            "unit": "us/iter",
            "extra": "iterations: 7010\ncpu: 99.64535278173939 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/2",
            "value": 37.70483091995434,
            "unit": "us/iter",
            "extra": "iterations: 18577\ncpu: 37.69206621090616 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/4",
            "value": 38.558751190344545,
            "unit": "us/iter",
            "extra": "iterations: 18062\ncpu: 38.55783041745072 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/8",
            "value": 40.49450635113954,
            "unit": "us/iter",
            "extra": "iterations: 17241\ncpu: 40.49352781161169 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/16",
            "value": 44.65575456053128,
            "unit": "us/iter",
            "extra": "iterations: 15678\ncpu: 44.65298590381442 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/32",
            "value": 52.74938690566417,
            "unit": "us/iter",
            "extra": "iterations: 13166\ncpu: 52.74565950174662 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/64",
            "value": 68.79366627195613,
            "unit": "us/iter",
            "extra": "iterations: 10134\ncpu: 68.79298727057419 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_H/128",
            "value": 100.00853253253247,
            "unit": "us/iter",
            "extra": "iterations: 6993\ncpu: 100.0066227656237 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/2",
            "value": 37.32226311025827,
            "unit": "us/iter",
            "extra": "iterations: 18783\ncpu: 37.31986349358405 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/4",
            "value": 38.313857956411624,
            "unit": "us/iter",
            "extra": "iterations: 18262\ncpu: 38.311312835395796 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/8",
            "value": 40.32804309997144,
            "unit": "us/iter",
            "extra": "iterations: 17355\ncpu: 40.32494935177157 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/16",
            "value": 44.09992891740527,
            "unit": "us/iter",
            "extra": "iterations: 15897\ncpu: 44.09821953827739 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/32",
            "value": 51.35665392592475,
            "unit": "us/iter",
            "extra": "iterations: 13500\ncpu: 51.352669333334056 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/64",
            "value": 66.43211377473418,
            "unit": "us/iter",
            "extra": "iterations: 10512\ncpu: 66.42955821917806 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_T/128",
            "value": 94.31275091228498,
            "unit": "us/iter",
            "extra": "iterations: 7399\ncpu: 94.3073382889591 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/2",
            "value": 37.544354340006954,
            "unit": "us/iter",
            "extra": "iterations: 18629\ncpu: 37.542000000000115 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/4",
            "value": 38.84927767604397,
            "unit": "us/iter",
            "extra": "iterations: 18021\ncpu: 38.847828977304594 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/8",
            "value": 40.806810645366944,
            "unit": "us/iter",
            "extra": "iterations: 17153\ncpu: 40.80615787325839 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/16",
            "value": 44.89885121151664,
            "unit": "us/iter",
            "extra": "iterations: 15559\ncpu: 44.895843306125656 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/32",
            "value": 52.848611402111295,
            "unit": "us/iter",
            "extra": "iterations: 13173\ncpu: 52.844366962726056 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/64",
            "value": 70.20378907795875,
            "unit": "us/iter",
            "extra": "iterations: 10108\ncpu: 70.20212564305653 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlTop_TargetBottom/128",
            "value": 99.98437483898725,
            "unit": "us/iter",
            "extra": "iterations: 6987\ncpu: 99.98175840847405 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/2",
            "value": 38.068949804856665,
            "unit": "us/iter",
            "extra": "iterations: 18448\ncpu: 38.0664258456202 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/4",
            "value": 40.31762249065153,
            "unit": "us/iter",
            "extra": "iterations: 17385\ncpu: 40.31540310612574 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/8",
            "value": 44.12298418200154,
            "unit": "us/iter",
            "extra": "iterations: 15868\ncpu: 44.120349319385014 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/16",
            "value": 52.52546085061781,
            "unit": "us/iter",
            "extra": "iterations: 13308\ncpu: 52.521648782687556 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/32",
            "value": 69.59816756325844,
            "unit": "us/iter",
            "extra": "iterations: 10038\ncpu: 69.59294700139337 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/64",
            "value": 102.26057297772529,
            "unit": "us/iter",
            "extra": "iterations: 6824\ncpu: 102.25221307151577 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_CX_ControlBottom_TargetTop/128",
            "value": 167.60086974285184,
            "unit": "us/iter",
            "extra": "iterations: 4161\ncpu: 167.5892146118682 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/2",
            "value": 38.70311311466427,
            "unit": "us/iter",
            "extra": "iterations: 18079\ncpu: 38.699955860389515 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/4",
            "value": 43.623404230096746,
            "unit": "us/iter",
            "extra": "iterations: 16028\ncpu: 43.61995875967041 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/8",
            "value": 61.796117517020726,
            "unit": "us/iter",
            "extra": "iterations: 11309\ncpu: 61.79088274825415 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/16",
            "value": 130.9115794708207,
            "unit": "us/iter",
            "extra": "iterations: 5329\ncpu: 130.90382304372324 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/32",
            "value": 394.4755665914317,
            "unit": "us/iter",
            "extra": "iterations: 1772\ncpu: 394.4450750564322 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/64",
            "value": 1453.3037620041998,
            "unit": "us/iter",
            "extra": "iterations: 479\ncpu: 1453.2072922755306 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_HadamardLayer/128",
            "value": 5761.823642856965,
            "unit": "us/iter",
            "extra": "iterations: 112\ncpu: 5761.384241071405 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/2",
            "value": 38.712644995864714,
            "unit": "us/iter",
            "extra": "iterations: 18135\ncpu: 38.689768899917695 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/4",
            "value": 44.17805514546156,
            "unit": "us/iter",
            "extra": "iterations: 16121\ncpu: 44.176708206686996 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/8",
            "value": 59.70560881049682,
            "unit": "us/iter",
            "extra": "iterations: 11736\ncpu: 59.70021941036199 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/16",
            "value": 122.02272566835309,
            "unit": "us/iter",
            "extra": "iterations: 5723\ncpu: 122.01308334789664 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/32",
            "value": 354.3416023362006,
            "unit": "us/iter",
            "extra": "iterations: 1969\ncpu: 354.31171965464114 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/64",
            "value": 1265.0715729730134,
            "unit": "us/iter",
            "extra": "iterations: 555\ncpu: 1264.9348756756785 us\nthreads: 1"
          },
          {
            "name": "BM_MxV_GHZ/128",
            "value": 4995.11941353368,
            "unit": "us/iter",
            "extra": "iterations: 133\ncpu: 4994.814714285752 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/2",
            "value": 37.6263943707714,
            "unit": "us/iter",
            "extra": "iterations: 18475\ncpu: 37.623821163735016 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/4",
            "value": 38.930121365430644,
            "unit": "us/iter",
            "extra": "iterations: 17987\ncpu: 38.929536665369895 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/8",
            "value": 40.953327618490164,
            "unit": "us/iter",
            "extra": "iterations: 17090\ncpu: 40.949904973667955 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/16",
            "value": 44.59295723935899,
            "unit": "us/iter",
            "extra": "iterations: 15692\ncpu: 44.590135228141655 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/32",
            "value": 52.012391921151725,
            "unit": "us/iter",
            "extra": "iterations: 13393\ncpu: 52.00862555066026 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/64",
            "value": 67.43318812733041,
            "unit": "us/iter",
            "extra": "iterations: 10461\ncpu: 67.43229920657457 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_Bell/128",
            "value": 97.91839115646015,
            "unit": "us/iter",
            "extra": "iterations: 7056\ncpu: 97.9128208616779 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/2",
            "value": 37.52565825242781,
            "unit": "us/iter",
            "extra": "iterations: 18540\ncpu: 37.52248236246011 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/4",
            "value": 41.88451259143824,
            "unit": "us/iter",
            "extra": "iterations: 16678\ncpu: 41.88251001319212 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/8",
            "value": 58.05863942227276,
            "unit": "us/iter",
            "extra": "iterations: 11978\ncpu: 58.054025964267915 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/16",
            "value": 120.05198997233579,
            "unit": "us/iter",
            "extra": "iterations: 5784\ncpu: 120.04286358921213 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/32",
            "value": 363.6347541493796,
            "unit": "us/iter",
            "extra": "iterations: 1928\ncpu: 363.61385321575585 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/64",
            "value": 1329.103804971325,
            "unit": "us/iter",
            "extra": "iterations: 523\ncpu: 1328.994172084181 us\nthreads: 1"
          },
          {
            "name": "BM_MxM_GHZ/128",
            "value": 5251.8999679998615,
            "unit": "us/iter",
            "extra": "iterations: 125\ncpu: 5251.8276880000485 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}