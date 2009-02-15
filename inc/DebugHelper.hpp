/*
   Copyright 2007 oasisfeng
   http://fontrouter.oasisfeng.com/

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef __DEBUGHELPER_INCLUDED__
#define __DEBUGHELPER_INCLUDED__


#include <e32std.h>
#include <flogger.h>	// RFileLogger
#include <badesca.h>	// CDesCArray
#include <utf.h>		// CnvUtfConverter
#include "CSettings.hpp"

#pragma warning(disable : 4127)

_LIT(KLogFolder,			"FontRouter");
_LIT(KLogFilename,			"FontRouter.log");
_LIT(KLogFilenameSpecial,	"FontRouterEx.log");


//////////////////////////////////////////////////////////////////////////
// Common
//

#ifdef __WINS__x
#define __USER_BREAKPOINT asm("int $3");
#else
#define __USER_BREAKPOINT
#endif

#define ASSERT_LOG(cond) \
	do { \
		if (!(cond)) { \
			__dbgprint_simple(level_fatal, "ASSERT: " #cond); \
			__USER_BREAKPOINT \
		} \
	} while(0)

#define ASSERT_RET(cond, retval) \
	do { \
		if (!(cond)) { \
			__dbgprint_simple(level_fatal, "ASSERT: " #cond); \
			__USER_BREAKPOINT \
			return retval; \
		} \
	} while(0)

#define ASSERT_LEAVE(cond, reason) \
	do { \
		if (!(cond)) { \
			__dbgprint_simple(level_fatal, "ASSERT: " #cond); \
			__USER_BREAKPOINT \
			User::Leave(reason); \
		} \
	} while(0)

#define RET_VOID

#define ARRAY_DIM(array) (sizeof(array) / sizeof((array)[0]))

// PLEASE SYNCHRONIZE "KSpecialLogKeyText"
enum TSpecialLogKey
{
	EFontRouterVer,
	EUserAgent,
	EOSVer,
	EUIVer,

	// From class HALData
	EManufacturer,
	EManufacturerHardwareRev,
	EManufacturerSoftwareRev,
	EManufacturerSoftwareBuild,
	EModel,
	EMachineUid,
	EDeviceFamily,
	EDeviceFamilyRev,
	ECPU,
	ECPUArch,
	ECPUABI,
	ECPUSpeed,
	EDisplayXPixels,
	EDisplayYPixels,
	EDisplayXTwips,
	EDisplayYTwips,
	ELanguageIndex,
	ESystemDrive,
	// End of HALData

	EHeapSize,
	EStackSize
};


enum TLogLevel
{
	level_always = 0,
	level_fatal = 1,
	level_error = 2,
	level_warning = 3,
	level_info = 4,
	level_debug = 5,
	level_never = 6	// For fake debug log.
};

class RDebugHelper
{
public:
	RDebugHelper()
	{
		// Set default log level.
#ifdef _DEBUG
		iLogLevel = level_debug;
#else
		iLogLevel = level_warning;
#endif
	}
	void InitializeSpecialLog(const CDesCArrayFlat & aKeyText);
	inline void SetLogLevel(TInt aLogLevel) { iLogLevel = aLogLevel; }
	inline TInt LogLevel() { return iLogLevel; }
	inline static void Log(const TDesC& aText)
		{ RFileLogger::Write(KLogFolder, KLogFilename, EFileLoggingModeAppend, aText); }
	inline static void LogFormat(TRefByValue<const TDesC> aFmt, ...)
	{
		VA_LIST aList;
		VA_START(aList, aFmt);
		RFileLogger::WriteFormat(KLogFolder, KLogFilename, EFileLoggingModeAppend, aFmt, aList);
		VA_END(aList);
	}
	inline static void LogFormat(TRefByValue<const TDesC16> aFmt, VA_LIST& aList)
		{ RFileLogger::WriteFormat(KLogFolder, KLogFilename, EFileLoggingModeAppend, aFmt, aList); }

private:
	TInt iLogLevel;
};

#ifdef __GNUC__
#define __dbgprint(level, fmt, va...) \
	do {_LIT(KFmt ## __LINE__, fmt); RDebugHelper::LogFormat(KFmt ## __LINE__ , ## va);} while(0)
#define __dbgprint_simple(level, text) \
	do {_LIT(KText ## __LINE__, text); RDebugHelper::LogFormat(KText ## __LINE__);} while(0)
#define __dbgprint_des(level, des) RDebugHelper::Log(des)

#define dbgprint(level, fmt...) \
	do {if (Debug().LogLevel() >= level) __dbgprint(level, fmt);} while(0)
#define dbgprint_simple(level, text) \
	do {if (Debug().LogLevel() >= level) __dbgprint_simple(level, text);} while(0)
#define dbgprint_des(level, des) \
	do {if (Debug().LogLevel() >= level) __dbgprint_des(des);} while(0)
#else
	#ifdef __WINS__
	inline void __dbgprint(TLogLevel /*aLogLevel*/, const char * aFormat, ...)
	{
		VA_LIST vaList;

		VA_START(vaList, aFormat);
		TBuf<200> format;
		const TPtrC8 from((const TUint8 *) aFormat);
		CnvUtfConverter::ConvertToUnicodeFromUtf8(format, from);
		RDebugHelper::LogFormat(format, vaList);
		VA_END(vaList);
	}
	#define dbgprint __dbgprint
	inline void __dbgprint_simple(TLogLevel /*aLogLevel*/, const char * aText)
	{
		TBuf<200> text;
		const TPtrC8 from((const TUint8 *) aText);
		CnvUtfConverter::ConvertToUnicodeFromUtf8(text, from);
		RDebugHelper::LogFormat(text);
	}
	inline void __dbgprint_des(TLogLevel /*aLogLevel*/, const TDesC aDes)
	{
		RDebugHelper::Log(aDes);
	}
	#endif
#endif


//////////////////////////////////////////////////
// Special logging: permanent information,
//	always overwrite the previous value but never duplicate.
//
// Text key / value pair,		eg. UISpec = "S60v2 FP1".
// Integer key / value pair,	eg. StackSize = 8192.
// Tag, 				eg. HasRasterizeFault.

#define KMaxNumLogSpecialKeys	1000


class CSpecialLog : public CBase, private MIniParser
{
public:
	CSpecialLog();
	~CSpecialLog();
	TInt ConstructL(RFs & aFs);
	// Setter
	void SpecialLogL(TInt aKey, const TDesC & aValue);
	void SpecialLogL(TInt aKey, TInt aValue);
	inline void SpecialLogL(TInt aKey) { SpecialLogL(aKey, 1); }
	// Getter
	const TDesC & GetSpecialText(TInt aKey);
	TInt GetSpecialInt(TInt aKey);
	// Helper
	inline void IncSpecialL(TInt aKey)
	{
		RLogSpecial & entry = iLogSpecial[aKey];
		ASSERT_RET(ESpecialLogInt == entry.iType, RET_VOID);
		entry.iInt ++;
		UpdateL(EFalse);
	}
	void FlushL(void) { if (EUnsaved == iState) SaveL(); }

private:
	enum TSpecialLogType
	{
		ESpecialLogInt,
		ESpecialLogText
	};
	enum TLogSpecialState
	{
		EInitializing,
		ESaved,
		EUnsaved
	};
	TInt UpdateL(TBool aForced);
	TInt SaveL(void);

	// Implementation for MIniParser
	TInt ParseLineSection(const TDesC & /*aSectionName*/) { return 0; }
	TInt ParseLineNormalL(TInt /*aSection*/, TInt /*aLineNo*/, const TDesC & aKey, const TDesC & aValue);
	class RLogSpecial
	{
	public:
		inline RLogSpecial() : iType(ESpecialLogInt), iInt(0) {}
		inline ~RLogSpecial() { if (ESpecialLogInt == iType) delete iText;}
		TSpecialLogType iType;
		union
		{
			TInt iInt;
			HBufC * iText;
		};
	};

	RFs * iFs;
	TLogSpecialState iState;
	TTime iTimeLastSave;			// Time when last save.
	CArrayFixFlat<RLogSpecial> iLogSpecial;
};

//////////////////////////////////////////////////////////////////////////


#endif //__DEBUGHELPER_INCLUDED__
