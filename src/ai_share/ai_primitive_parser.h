/** \file ai_primitive_parser.h
 *
 * $id$
 *
 */


#ifndef R2_AIPRIMITIVEPARSER_H
#define R2_AIPRIMITIVEPARSER_H

//nel 
#include "nel/misc/types_nl.h"
#include "nel/misc/debug.h"
#include "nel/misc/singleton.h"
#include "nel/ligo/ligo_config.h"

//game_share
class CPersistentDataRecord;

namespace R2
{
	
class CAIPrimitiveParser : public NLMISC::CSingleton<CAIPrimitiveParser>
{

public:
	static void init(CPersistentDataRecord* pdr);	
	static void release();	

	void clear();
	void readFile(const std::string &fileName);
	void writeFile(const std::string &fileName);
	void display();
	void serial(NLMISC::IStream &stream);

};

}
#endif

