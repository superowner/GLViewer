// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MY3DBASE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MY3DBASE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

// This class is exported from the 3DBase.dll
class MY3DBASE_API CMy3DBase {
public:
	CMy3DBase(void);
	// TODO: add your methods here.
};

extern MY3DBASE_API int nMy3DBase;

MY3DBASE_API int fnMy3DBase(void);
