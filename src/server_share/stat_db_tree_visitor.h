/** \file stat_db_tree_visitor.h
 * 
 *
 * $Id: stat_db_tree_visitor.h,v 1.1 2005/08/04 18:27:14 guignot Exp $
 */



#ifndef RY_STAT_DB_TREE_VISITOR_H
#define RY_STAT_DB_TREE_VISITOR_H


class CStatDBBranch;
class CStatDBValueLeaf;
class CStatDBTableLeaf;

/**
 * SDB node visitor (visitor design pattern).
 *
 * \author Sébastien 'kxu' Guignot
 * \author Nevrax France
 * \date 2005 July
 */
class CStatDBNodeVisitor
{
public:
	virtual void visitBranch(CStatDBBranch * branch, const std::string & path) {}
	virtual void visitValueLeaf(CStatDBValueLeaf * valueLeaf, const std::string & path) {}
	virtual void visitTableLeaf(CStatDBTableLeaf * tableLeaf, const std::string & path) {}

protected:
	CStatDBNodeVisitor() {}
};


#endif // RY_STAT_DB_TREE_VISITOR_H
