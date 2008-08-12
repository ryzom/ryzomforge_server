/** \file ai_id.h
  
 * $Id: ai_spawn_commands.h,v 1.5 2004/11/23 21:58:00 boucher Exp $
 */



#include "nel/misc/types_nl.h"
#include "nel/misc/debug.h"

#include <string>


//class CAISpawnCtrl
//{
//public:
//	static bool spawn		(const std::string &name, int	aiInstance=-1)		{ nlassert(_instance!=NULL); return _instance->_spawn(aiInstance, name); }
//	static bool spawnMap	(const std::string &name, int	aiInstance=-1)	{ nlassert(_instance!=NULL); return _instance->_spawnMap(aiInstance, name); }
//	static bool spawnMgr	(const std::string &name, int	aiInstance=-1)	{ nlassert(_instance!=NULL); return _instance->_spawnMgr(aiInstance, name); }
//	static bool spawnGrp	(const std::string &name, int	aiInstance=-1)	{ nlassert(_instance!=NULL); return _instance->_spawnGrp(aiInstance, name); }
//	static bool spawnAll	(int	aiInstance=-1)		{ nlassert(_instance!=NULL); return _instance->_spawnAll(aiInstance); }
//
//	static bool despawn		(const std::string &name, int	aiInstance=-1)	{ nlassert(_instance!=NULL); return _instance->_despawn(aiInstance, name); }
//	static bool despawnMap	(const std::string &name, int	aiInstance=-1)	{ nlassert(_instance!=NULL); return _instance->_despawnMap(aiInstance, name); }
//	static bool despawnMgr	(const std::string &name, int	aiInstance=-1)	{ nlassert(_instance!=NULL); return _instance->_despawnMgr(aiInstance, name); }
//	static bool despawnGrp	(const std::string &name, int	aiInstance=-1)	{ nlassert(_instance!=NULL); return _instance->_despawnGrp(aiInstance, name); }
//	static bool despawnAll	(int	aiInstance=-1)		{ nlassert(_instance!=NULL); return _instance->_despawnAll(aiInstance); }
//
//protected:
//	virtual bool _spawn		(int	aiInstance, const std::string &name)=0;
//	virtual bool _spawnMap	(int	aiInstance, const std::string &name)=0;
//	virtual bool _spawnMgr	(int	aiInstance, const std::string &name)=0;
//	virtual bool _spawnGrp	(int	aiInstance, const std::string &name)=0;
//	virtual bool _spawnAll	(int	aiInstance)=0;
//
//	virtual bool _despawn		(int	aiInstance, const std::string &name)=0;
//	virtual bool _despawnMap	(int	aiInstance, const std::string &name)=0;
//	virtual bool _despawnMgr	(int	aiInstance, const std::string &name)=0;
//	virtual bool _despawnGrp	(int	aiInstance, const std::string &name)=0;
//	virtual bool _despawnAll	(int	aiInstance)=0;
//
//	static CAISpawnCtrl *_instance;
//};
