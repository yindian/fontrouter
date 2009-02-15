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
#include "CSettings.hpp"
#include "FontRouter.hpp"

TInt MIniParser::ParseL(RFs& aFs, const TDesC &aDirPath, const TDesC &aFileName)
{
	// Seek file.
	TFindFile FindFile(aFs);
	TInt ret = FindFile.FindByDir(aFileName, aDirPath);
	if (KErrNone != ret)
	{
		__dbgprint(level_info, "Configuration file (%S) not found, use default settings.", & aFileName);
		return ret;			// KErrNotFound only.
	}

	// Open file.
	RFile file;
	ret = file.Open(aFs, FindFile.File(), EFileShareReadersOnly | EFileRead);
	if (KErrNone != ret)
	{
		__dbgprint(level_error, "Failed to open file %S", &aFileName);
	}

	// Read file
	TFileText fileText;
	fileText.Set(file);
	TInt errCode;
	TInt lineNo = 0;
	//TBuf<KLineBufferSize> lineBuf;
	HBufC* heapBuf = HBufC::NewLC(KLineBufferSize);
	TPtr lineBuf = heapBuf->Des();
	TInt section = NULL;
	while ((errCode = fileText.Read(lineBuf)) != KErrEof)
	{
		lineNo ++;
		if (errCode == KErrTooBig)
		{
			__dbgprint(level_error, "Line %d is too long to parse.");
			continue;
		}
		if (errCode != KErrNone)
		{
			__dbgprint(level_error, "Error %d when reading file %S", errCode, &aFileName);
			break;
		}
		section = ParseLineL(section, lineNo, lineBuf);
	}
	CleanupStack::PopAndDestroy(heapBuf);
	file.Close();

	// Bubble error code.
	if (KErrEof == errCode) errCode = KErrNone;
	return errCode;
}

TInt MIniParser::ParseLineL(TInt aSection, TInt aLineNo, TDes& aLine)
{
	aLine.Trim();
	if (0 == aLine.Length()) return aSection;					// Empty line
	if (';' == aLine[0]) return aSection;						// Comment line

	if (aLine.Length() > 2 && '[' == aLine[0] && ']' == aLine[aLine.Length() - 1])  // Group line
	{
		aLine.Copy(aLine.Mid(1, aLine.Length() - 2));
		aLine.Trim();
		return ParseLineSection(aLine);
	}

	// Common line
	TInt posEqual = aLine.Locate('=');
	if (KErrNotFound == posEqual)
		(void) ParseLineAbnormalL(aSection, aLineNo, aLine);
	else
		(void) ParseLineNormalL(aSection, aLineNo, aLine.Mid(0, posEqual), aLine.Mid(posEqual + 1));

	return aSection;
}

TInt MIniParser::ParseLineAbnormalL(TInt aSection, TInt aLineNo, const TDesC& aLine)
{
	aSection = aSection;
	__dbgprint(level_error, "Failed to parse line %d: %S", aLineNo, &aLine);
	return KErrNotSupported;
}

