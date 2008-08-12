/** \file world_map_link.h
 *
 * $Id: world_map_link.h,v 1.2 2004/03/01 19:19:20 lecroart Exp $
 */



#ifndef _WORLD_MAP_LINK_
#define	_WORLD_MAP_LINK_

#include "ai_share/ai_entity_physical_list_link.h"

//------------------------------------------------------------------
// linkage to dynamic world map
template	<class	T>
class	CWorldMapLink
{
public:	
	CWorldMapLink	()	{}
	virtual ~CWorldMapLink() {}

	inline	bool	isLinkedToWorldMap() const	
	{
		return	!_matrixListLink.unlinked();
	}
	
	//	link the entity to its type Matrix.
	inline	void	linkEntityToMatrix	(const CAIVectorMirror&	pos, CAIEntityMatrix<T>&	matrix);
	inline	void	linkEntityToMatrix	(const CAIVector&		pos, CAIEntityMatrix<T>&	matrix);
	
	inline	void	linkToWorldMap		(T *entity, const	CAIVectorMirror	&pos, CAIEntityMatrix<T>&	matrix);
	inline	void	linkToWorldMap		(T *entity, const	CAIVector		&pos, CAIEntityMatrix<T>&	matrix);
	
	inline	void	unlinkFromWorldMap()
	{
		_matrixListLink.unlink();
	}
	
protected:
	inline	void	linkEntityToMatrix	(const CAICoord& x, const CAICoord& y, CAIEntityMatrix<T>&	matrix);
private:
	CEntityListLink<T>	_matrixListLink;	// link for the entity matrix used for vision systems
};

#endif
