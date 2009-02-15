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

#ifndef __CSETTINGS_INCLUDED__
#define __CSETTINGS_INCLUDED__

#include <e32std.h>
#include <f32file.h>

class MIniParser
{
public:
	virtual ~MIniParser() {}
	TInt ParseL(RFs& aFs, const TDesC &aDirPath, const TDesC &aFileName);
	// Default action: deliver to ParseLineSection() or ParseLineNormalL()
	TInt ParseLineL(TInt aSection, TInt aLineNo, TDes& aLine);
	// Line enclosed by "[...]",
	virtual TInt ParseLineSection(const TDesC& aSectionName) = 0;
	// Line with "=" mark, aKey and aValue may be empty descriptor.
	virtual TInt ParseLineNormalL(TInt aSection, TInt aLineNo, const TDesC& aKey, const TDesC& aValue) = 0;
	virtual TInt ParseLineAbnormalL(TInt aSection, TInt aLineNo, const TDesC& aLine);  // Default: log only.

	// Helper functions for parsing.

	// If return value is EFalse, aBoolean is left unaltered.
	inline TBool GetBool(const TDesC& aString, TBool& aBoolean)
	{
		if (1 != aString.Length()) return EFalse;

		if ('0' == aString[0]) aBoolean = EFalse;
		else if ('1' == aString[0]) aBoolean = ETrue;
		else return EFalse;

		return ETrue;
	}
	// If return value is not KErrNone, aInteger is left unaltered.
	inline TBool GetInt(const TDesC& aString, TInt& aInteger)
	{
		if (0 == aString.Length()) return EFalse;

		TInt integer;
		TLex lex(aString);
		if (KErrNone != lex.Val(integer)) return EFalse;

		aInteger = integer;
		return ETrue;
	}
	inline TBool GetInt16(const TDesC& aString, TInt16& aInteger)
	{
		if (0 == aString.Length()) return EFalse;

		TInt16 integer;
		TLex lex(aString);
		if (KErrNone != lex.Val(integer)) return EFalse;

		aInteger = integer;
		return ETrue;
	}
};

#endif //__CSETTINGS_INCLUDED__
