/** \file gus_text.h
 *
 * $id$
 *
 */

#ifndef GUS_TEXT_H
#define GUS_TEXT_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/displayer.h"
#include "gus_client_manager.h"


//-----------------------------------------------------------------------------
// GUS namespace
//-----------------------------------------------------------------------------

namespace GUS
{
	//-----------------------------------------------------------------------------
	// class CLangText
	//-----------------------------------------------------------------------------
	// the text set for a given language

	class CLangText
	{
	public:
		CLangText(const NLMISC::CSString& languageCode);
		const NLMISC::CSString& getLanguageCode() const;

		const ucstring& get(const NLMISC::CSString& tokenName) const;
		void set(const NLMISC::CSString& tokenName,const ucstring& txt);
		void set(const NLMISC::CSString& tokenName,const NLMISC::CSString& txt);

		void display() const;

		void getTokenNameSet(std::set<NLMISC::CSString>& result,bool clearResultFirst=true);

	private:
		NLMISC::CSString _Code;
		typedef std::map<NLMISC::CSString,ucstring> TTexts;
		TTexts _Texts;
	};


	//-----------------------------------------------------------------------------
	// class CTextSet
	//-----------------------------------------------------------------------------
		
	class CText
	{
	public:
		// read a file of text strings
		bool read(const NLMISC::CSString& fileName);

		// set the active language
		void setLanguage(const NLMISC::CSString& languageCode);
		// lookup a string trying the active lagugage first, and otherwise the default string set
		const ucstring& get(const NLMISC::CSString& tokenName) const;
		
		// lookup a string for a given language
		const ucstring& get(const NLMISC::CSString& languageCode,const NLMISC::CSString& tokenName) const;
		// set a string for a given language
		void set(const NLMISC::CSString& languageCode,const NLMISC::CSString& tokenName,const ucstring& txt);
		// set a string for the default string set
		void set(const NLMISC::CSString& tokenName,const ucstring& txt);

		// display a little info on the set of languages loaded
		void display() const;

		// get hold of the set of token names
		void getTokenNameSet(std::set<NLMISC::CSString>& result);

	private:
		NLMISC::CSString _ActiveLanguage;
		typedef std::vector<CLangText> TLangTexts;
		TLangTexts _LangTexts;
	};

}


//-----------------------------------------------------------------------------
#endif
