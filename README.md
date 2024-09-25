# PalAnticheat
화이트햇 스쿨 2기 기본 프로젝트

일단, 핵에 대한 전혀 불법적인 행동을 하지 않았으며 게임회사에 대한 어떤 불법적인 행동 혹은 윤리적으로 어긋난 행동을 하지 않았음을 선업합니다.


개요 : 언리얼엔진에 대한 이해와 분석 및 이를 이용한 Palworld 게임 핵에 대한 안티치트 & 안티디버깅 제작
1. 마이크로소프트의 Detour 라이브러리를 다운로드합니다. https://github.com/microsoft/Detours
2. sln 프로젝트 파일에서 소스.cpp 에서 4번째 줄에 경로를 detours.h 로 설정합니다. ex) `#include "C:/Users/Desktop/Detours/include/detours.h"`
3. sln 프로젝트 파일에서 소스.cpp 에서 10번째 줄에 경로를 detours.lib 로 설정합니다. ex) `#pragma comment(lib, "C:/Users/하태구/Desktop/Detours/lib.X64/detours.lib")`
   
구현내용 : Window GUI 정보를 바탕으로 한 안티디버깅 , SPY++ 를 이용한 안티디버깅 , 마이크로소프트 Detour를 이용한 안티치트 ( DLL injection Blocker )
구현범위 : INTERNAL 핵 BLOCK ( DLL Injection )
필요한 Dependency : 마이크로소프트의 Detour 라이브러리가 필요함
상세내용 : Anticheat2.dll - 메인 dll으로 이 dll을 Palworld 게임에 dll injection을 하면 된다. ( 당연하지만 게임 핵이 먼저 dll injection을 진행하기 전에 주입을 해야한다. )
한계점 : 이 Dll 자체는 dll injection을 통해 미리 주입을 해야한다는 점과 유저레벨 안티치트라서 권한적인 한계가 분명이 존재한다.
후속연구 : 따라서 이러한 한계점을 해결하기 위해서 커널 레벨 안티치트를 제작하려고 한다.

팀 : WhiteGang
제작기간 : 2024-06 ~ 2024-08
