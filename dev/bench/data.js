window.BENCHMARK_DATA = {
  "lastUpdate": 1617106340263,
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
      }
    ]
  }
}