// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the AI_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// AI_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef AI_EXPORTS
#define AI_API __declspec(dllexport)
#else
#define AI_API __declspec(dllimport)
#endif

// This class is exported from the dll
class AI_API Cai {
public:
	Cai(void);
	// TODO: add your methods here.
};

extern AI_API int nai;

AI_API int fnai(void);
