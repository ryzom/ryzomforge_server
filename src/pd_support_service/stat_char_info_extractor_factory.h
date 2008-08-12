/** \file stats_char_info_extractor_factory.h
 *
 * Part of STAT Module for GUS (general utilities service)
 *
 * $Id: stat_char_info_extractor_factory.h,v 1.2 2007/05/09 15:33:12 boucher Exp $
 */

#ifndef STAT_CHAR_INFO_EXTRACTOR_FACTORY_H
#define STAT_CHAR_INFO_EXTRACTOR_FACTORY_H


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "nel/misc/smart_ptr.h"
#include "nel/misc/sstring.h"


//-------------------------------------------------------------------------------------------------
// forward class declarations
//-------------------------------------------------------------------------------------------------

class CCharacterScanJob;
class CStatsScanCharacter;
class ICharInfoExtractorBuilder;


//-------------------------------------------------------------------------------------------------
// class ICharInfoExtractor
//-------------------------------------------------------------------------------------------------

class ICharInfoExtractor: public NLMISC::CRefCount
{
public:
	virtual ~ICharInfoExtractor() {}
	virtual std::string toString() const=0;
	virtual const ICharInfoExtractorBuilder* getBuilder() const=0;
	virtual void execute(CCharacterScanJob* job,const CStatsScanCharacter* c)=0;
};


//-------------------------------------------------------------------------------------------------
// class ICharInfoExtractorBuilder
//-------------------------------------------------------------------------------------------------

class ICharInfoExtractorBuilder: public NLMISC::CRefCount
{
public:
	virtual const char* getName() const=0;
	virtual const char* getDescription() const=0;
	virtual const char* getFields() const=0;
	virtual ICharInfoExtractor* build(const std::string& rawArgs) const=0;
};


//-------------------------------------------------------------------------------------------------
// class CCharInfoExtractorFactory
//-------------------------------------------------------------------------------------------------

class CCharInfoExtractorFactory
{
public:
	static CCharInfoExtractorFactory* getInstance();

public:
	// register an info extractor instance
	void registerInfoExtractor(NLMISC::CSmartPtr<ICharInfoExtractorBuilder> infoExtractor);

	// display the set of names and descriptions of info extractor instances
	void displayInfoExtractorList(NLMISC::CLog* log=NLMISC::InfoLog);

	// basic accessors for getting hold of the registered info extractors
	uint32 getInfoExtractorBuilderCount();
	ICharInfoExtractorBuilder* getInfoExtractorBuilder(uint32 idx);

	// the all important build method
	ICharInfoExtractor* build(const NLMISC::CSString& cmdLine);

private:
	// this is a singleton so ctor is private
	CCharInfoExtractorFactory() {}

	typedef std::vector<NLMISC::CSmartPtr<ICharInfoExtractorBuilder> > TInfoExtractors;
	TInfoExtractors _InfoExtractors;
};


//-------------------------------------------------------------------------------------------------
// class CInfoExtractorRegisterer
//-------------------------------------------------------------------------------------------------

template <class C>
class CInfoExtractorRegisterer
{
public:
	CInfoExtractorRegisterer()
	{
		CCharInfoExtractorFactory::getInstance()->registerInfoExtractor(new C);
	}
};


//-------------------------------------------------------------------------------------------------
// MACRO INFO_EXTRACTOR()
//-------------------------------------------------------------------------------------------------

#define INFO_EXTRACTOR(name,description,fields)\
class CInfoExtractor_##name: public ICharInfoExtractor\
{\
public:\
	CInfoExtractor_##name(const std::string& rawArgs,const ICharInfoExtractorBuilder *builder) {_RawArgs=rawArgs;_Builder=builder;}\
	virtual std::string toString() const {return std::string(#name)+" "+_RawArgs;}\
	virtual const ICharInfoExtractorBuilder* getBuilder() const {return _Builder;}\
	virtual void execute(CCharacterScanJob* job,const CStatsScanCharacter* c);\
private:\
	NLMISC::CSString _RawArgs;\
	const ICharInfoExtractorBuilder *_Builder;\
};\
class CInfoExtractorBuilder_##name: public ICharInfoExtractorBuilder\
{\
public:\
	virtual const char* getName() const			{return #name;}\
	virtual const char* getDescription() const	{return description;}\
	virtual const char* getFields() const		{return fields;}\
	virtual ICharInfoExtractor* build(const std::string& rawArgs) const {return new CInfoExtractor_##name(rawArgs,this);}\
};\
CInfoExtractorRegisterer<CInfoExtractorBuilder_##name> __Registerer_CInfoExtractor_##name;\
void CInfoExtractor_##name::execute(CCharacterScanJob* job,const CStatsScanCharacter* c)


//-------------------------------------------------------------------------------------------------
#endif
