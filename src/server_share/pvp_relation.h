/** \file pvp_relation.h
 *
 * $Id: pvp_relation.h,v 1.1 2005/09/30 15:27:33 coutelas Exp $
 */

#ifndef RY_PVP_RELATION_H
#define RY_PVP_RELATION_H

#include <string>

namespace PVP_RELATION
{
	enum TPVPRelation
	{
		Neutral,
		NeutralPVP,
		Ally,
		Ennemy,
		Unknown
	};

	TPVPRelation fromString(const std::string & str);
	const std::string & toString(TPVPRelation relation);

} // namespace PVP_RELATION

#endif // RY_PVP_RELATION_H
