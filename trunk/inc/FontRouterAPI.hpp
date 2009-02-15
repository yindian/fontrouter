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

#ifndef __FONTROUTERAPI_INCLUDED__
#define __FONTROUTERAPI_INCLUDED__

_LIT(KAPIFontName,		"[FontRouter.Interface]");

class CRouterFontFile;

//////////////////////////////////////////////////////////////////////////
class CFontRouterAPI : public COpenFont
{
public:
	static CFontRouterAPI * NewL( RHeap* aHeap,
		COpenFontSessionCacheList* aSessionCacheList, CRouterFontFile* aFontFile );
	void RasterizeL(TInt aCmdCode, TOpenFontGlyphData* aData);
	enum TResult
	{
		ESuccess = 0,
		EFailure,
		EUnknown
	};
	struct SReplyInfo
	{
		TInt16 iAckSN;		// Equal to ReqSN, for verification on the reply information,
							//  because of the cache mechanism.
		TInt16 iResult;		// Command result, enum TResult.
		TInt iSize;			// Information size
		TUint8 iBuffer[1];	// Information buffer (is actually of size iSize).
	};
	enum TCmdCode
	{
		ENull = 0,
		EGetVersion,
		ERuntimeLoad,
		EReloadConfig,
		ELoadFreeType,
		ELogOn,
		ELogOff,
		ELoadFontFile,
		EUnloadFontFile,
		EGetFontInfo,
	};

private:
	CFontRouterAPI(	RHeap* aHeap,
					COpenFontSessionCacheList* aSessionCacheList,
					COpenFontFile* aFontFile,
					TInt aFaceIndex );
	//CRouterFontRasterizer * iRasterizer;
};

#endif // __FONTROUTERAPI_INCLUDED__
