// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <chrono>
#include <random>

// --- Global Random Number Generator ---
std::default_random_engine generator;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		// --- Initialize Random Number Generator ---
		generator = std::default_random_engine(
			std::chrono::system_clock::now().time_since_epoch().count());

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

