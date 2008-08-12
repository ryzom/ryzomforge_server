#ifndef  DMS_COMLUAMODULE_H
#define  DMS_COMLUAMODULE_H

#include "nel/misc/types_nl.h"


extern "C"
{
//	#include "lua_loadlib.h"

// interface_v3 file, replaced with:
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}





#include <map>
#include <string>

namespace R2
{
	class CObject;
	class CDynamicMapClient;

	class CComLuaModule
	{
		public:
		/** Build the communication module
		  * \param luaState NULL If the lua environment should be built by this object
		  *        If the lua state is provided externally, then it won't be deleted by this object
		  */

		CComLuaModule(CDynamicMapClient* client, lua_State *luaState = NULL);
		
		void doFile(const std::string& filename);

		bool runLuaScript(const std::string& filename, std::string& errorMsg);

		CObject* translateFeatures(CObject* hlScenario, std::string& errorMsg) const;
		
		void loadFeatures();
		
		static CComLuaModule* getInstance(lua_State* state);
		
		void callTranslateFeatures(CObject* scenario);


		//Edition
		static sint luaAddPaletteElement(lua_State* state);

		static sint luaGetPropertyValue(lua_State* state);
		static sint luaPrint(lua_State* state);
	
		static sint luaGetPaletteElement(lua_State* state);

		static sint luaRequestTranslateFeatures(lua_State* state);
		
		static sint luaNewComponent(lua_State* state);

		static sint luaNewGhostComponent(lua_State* state);

		static sint luaRegisterGenerator(lua_State* state);

		static sint luaShow(lua_State* state);

		static sint luaRequestInsertNode(lua_State* state);

		static sint luaRequestInsertGhostNode(lua_State* state);

		static sint luaRequestSetNode(lua_State* state);

		static sint luaRequestEraseNode(lua_State* state);

		static sint luaRequestMoveNode(lua_State* state);

		static sint luaRequestUpdateRtScenario(lua_State* state);

	
		//Admin
		static sint luaRequestGoLive(lua_State* state);

		static sint luaRequestCreatePrimitives(lua_State* state);

		static sint luaRequestStopLive(lua_State* state);

		static sint luaRequestStartAct(lua_State* state);

		static sint luaRequestStopAct(lua_State* state);

		static sint luaRequestMapConnection(lua_State* state);
		
		static sint luaRequestReconnection(lua_State* state);

		static sint luaRequestCreateScenario(lua_State* state);

		static sint luaRequestListAdventure(lua_State* state);

		static sint luaRequestSetWeather(lua_State* state);

	

		static void setObjectToLua(lua_State* state, CObject* object);
		
		static CObject* getObjectFromLua(lua_State* state, sint idx=-1);

		bool load(const std::string& filename);

		CObject* loadLocal(const std::string& filename);
		
		static sint luaUpdateScenario(lua_State* state);
		
		static sint luaLoad(lua_State* state);
		static sint luaSave(lua_State* state);
		static sint luaDoFile2(lua_State* state);
		static sint luaTalkAs(lua_State* state);
		static sint luaStopTalkAs(lua_State* state);
		static sint luaRequestTpPosition(lua_State* state);
		static sint luaRequestDespawnEntity(lua_State* state);
		static sint luaRequestDespawnGrp(lua_State* state);
		static sint luaRequestIdList(lua_State* state);
		static sint luaRequestStringTable(lua_State* state);
		static sint luaRequestSetStringValue(lua_State* state);
		static sint luaRequestStringValue(lua_State* state);
		static sint luaGetScenarioObj(lua_State* state);
		static sint luaGetNamespace(lua_State* state);
		static sint luaGetIslandsLocation(lua_State* state);

	
		//static sint luaGetPropertyList(lua_State* state);
		~CComLuaModule();
	private:
		lua_State* _LuaState;
		bool	   _LuaOwnerShip;
		
		CDynamicMapClient* _Client;
	
		static std::map<lua_State*, CComLuaModule*> _Instance;
	
		// register the com lib into lua
		void initLuaLib();

		
		static sint requestInsertNode(lua_State* state, bool ghost);


	};



} // namespace DMS
#endif // DMS_COMLUAMODULE_H
