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

#include "DebugHelper.hpp"

_LIT(KSpecialLogPath, 		"C:\\");
_LIT(KSpecialLogFile, 		"FontRouterEx.log");
_LIT(KSpecialLogSection,	"[System Info]");
const TInt KSpecialLogInterval = 60;		// In minutes.
const TInt KSpecialLogLineBufferSize = 1024;

// Special log key text
#ifndef __wchar_t_defined
#ifndef __GCCXML__
typedef unsigned short int wchar_t;
#endif
#endif

const static wchar_t * const KSpecialLogKeyText[] =
{
	L"FontRouterVer",
	L"UserAgent",
	L"OSVer",
	L"UIVer",

	L"Manufacturer",
	L"ManufacturerHardwareRev",
	L"ManufacturerSoftwareRev",
	L"ManufacturerSoftwareBuild",
	L"Model",
	L"MachineUid",
	L"DeviceFamily",
	L"DeviceFamilyRev",
	L"CPU",
	L"CPUArch",
	L"CPUABI",
	L"CPUSpeed",
	L"DisplayXPixels",
	L"DisplayYPixels",
	L"DisplayXTwips",
	L"DisplayYTwips",
	L"LanguageIndex",
	L"SystemDrive",

	L"HeapSize",
	L"StackSize"
};

const TInt KNumSpecialLogKeys = ARRAY_DIM(KSpecialLogKeyText);


CSpecialLog::CSpecialLog() : iState(EInitializing), iLogSpecial(KNumSpecialLogKeys)
{
}

CSpecialLog::~CSpecialLog()
{
	// Need iLogSpecial.Reset() ?
}

TInt CSpecialLog::ConstructL(RFs & aFs)
{
	iFs = & aFs;

	if (iLogSpecial.Count() < KNumSpecialLogKeys)
		iLogSpecial.SetReserveL(KNumSpecialLogKeys);

	// Initialize entries with default value.
	RLogSpecial defaultEntry;
	iLogSpecial.AppendL(defaultEntry, KNumSpecialLogKeys);

	TInt result = ParseL(aFs, KSpecialLogPath, KSpecialLogFile);
	iState = ESaved;

	return result;
}

void CSpecialLog::SpecialLogL(TInt aKey, const TDesC & aValue)
{
	RLogSpecial & entry = iLogSpecial[aKey];
	if (ESpecialLogText == entry.iType && entry.iText)
	{
		if (entry.iText->Length() == aValue.Length() && 0 == entry.iText->Compare(aValue))
			return; // Same, ignore.
		// Reallocate for the value descriptor.
		delete entry.iText;
		entry.iText = NULL;
	}
	else
	{
		entry.iType = ESpecialLogText;
	}
	entry.iText = aValue.AllocL();
	UpdateL(EFalse);
}


void CSpecialLog::SpecialLogL(TInt aKey, TInt aValue)
{
	RLogSpecial & entry = iLogSpecial[aKey];
	if (ESpecialLogInt == entry.iType && aValue == entry.iInt)
		return; 	// Same, ignore.

	if (ESpecialLogText == entry.iType)
	{
		delete entry.iText;
		entry.iText = NULL;
		entry.iType = ESpecialLogInt;
	}
	entry.iInt = aValue;
	UpdateL(EFalse);
}


const TDesC & CSpecialLog::GetSpecialText(TInt aKey)
{
	RLogSpecial & entry = iLogSpecial[aKey];
	ASSERT_LOG(ESpecialLogText == entry.iType && entry.iText);
	return * entry.iText;
}


TInt CSpecialLog::UpdateL(TBool aForced)
{
	if (NULL == iFs)
		return KErrNotReady;

	if (EInitializing == iState)	// No need to flush during loading.
		return KErrNone;

	iState = EUnsaved;

	TTime now;
	TTimeIntervalMinutes diff;
	now.UniversalTime();

	// Check flush interval.
	if (!aForced && (now.MinutesFrom(iTimeLastSave, diff), diff < TTimeIntervalMinutes(KSpecialLogInterval)))
		return KErrNone;

	// Update time of last save.
	iTimeLastSave = now;

	return SaveL();
}


TInt CSpecialLog::SaveL(void)
{
	// Open file.
	TFileName filename;
	filename.Copy(KSpecialLogPath);
	filename.Append(KSpecialLogFile);
	RFile file;
	TInt result = file.Replace(* iFs, filename, EFileWrite);
	if (KErrNone != result)
	{
		return result;
	}

	// Write file
	TFileText fileText;
	fileText.Set(file);
	HBufC* buffer = HBufC::NewLC(KSpecialLogLineBufferSize);
	TPtr line = buffer->Des();

	line.Copy(KSpecialLogSection);					// Write section header.
	fileText.Write(line);

	for (TInt i = 0; i < iLogSpecial.Count(); i ++)	// Write all special log entries.
	{
		const RLogSpecial & entry = iLogSpecial[i];
		// Write key (text if defined, otherwise index)
		if (i < KNumSpecialLogKeys)
			line.Copy((const TUint16 *) KSpecialLogKeyText[i]);	// TODO: Fix the cast.
		else
			line.Num(i);

		line.Append(_L("="));
		// Write value.
		if (ESpecialLogInt == entry.iType)
			line.AppendNum(entry.iInt);
		else
			line.Append(* entry.iText);

		result = fileText.Write(line);
		if (result != KErrNone)
			break;
	}
	CleanupStack::PopAndDestroy(buffer);
	file.Close();

	if (KErrEof == result) result = KErrNone;

	iState = ESaved;

	// Bubble result of TFileText::Write().
	return result;
}


TInt CSpecialLog::ParseLineNormalL(TInt /*aSection*/, TInt /*aLineNo*/, const TDesC & aKey, const TDesC & aValue)
{
	TInt index;

	for (index = 0; index < KNumSpecialLogKeys; index ++)
	{
		TPtrC text((const TUint16 *) KSpecialLogKeyText[index]);
		if (0 == aKey.CompareF(text))
		{
			if (0 == aValue.Length())	// Value is empty, treat as tag, eg. "Key="
			{
				SpecialLogL(index);
				return 0;
			}
			TChar first = aValue[0];
			TInt intValue;
			TLex lex(aValue);

			if (first >= '0' && first <= '9' && KErrNone != lex.Val(intValue))	// Integer
			{
				SpecialLogL(index, intValue);
			}
			else																// Text
			{
				TInt textLength = aValue.Length();
				// Remove quote marks if present.
				if ('"' == first && '"' == aValue[textLength - 1] && textLength > 2)
				{
					SpecialLogL(index, aValue.Mid(1, textLength - 2));
				}
				else
				{
					SpecialLogL(index, aValue);
				}
			}

			return 0;
		}
	}

	return 0;
}

