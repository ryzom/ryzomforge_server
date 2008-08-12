/** \file ec_event_chat_module.h
 *
 * $id$
 *
 */

#ifndef EC_EVENT_CHAT_MODULE_H
#define EC_EVENT_CHAT_MODULE_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "gus_module_manager.h"
#include "gus_text.h"
#include "ec_types.h"


//-----------------------------------------------------------------------------
// EC namespace
//-----------------------------------------------------------------------------

namespace EC
{
	//-----------------------------------------------------------------------------
	// class CEventChatModule
	//-----------------------------------------------------------------------------

	class CEventChatModule: public GUS::IModule
	{
	public:
		// IModule specialisation implementation
		bool initialiseModule(const NLMISC::CSString& rawArgs);
		NLMISC::CSString getState() const;
		NLMISC::CSString getName() const;
		NLMISC::CSString getParameters() const;
		void displayModule() const;

		// management of the set of faction channels
		bool addFactionChannel(const NLMISC::CSString& channelName,const NLMISC::CSString& channelTitle);
		bool removeFactionChannel(const NLMISC::CSString& name);

		// a set of accessors for the faction channels
		uint32 getNumFactionChannels() const;
		CFactionChannel* getFactionChannel(uint32 idx);
		CFactionChannel* getFactionChannelByName(const NLMISC::CSString& name,bool addIfNotExist=false);

		// a set of accessors that englobes the ctrl channel, faction channels, and the factions' party channels
		uint32 getNumChannels() const;
		IChannel* getChannel(uint32 idx);
		IChannel* getChannelByName(const NLMISC::CSString& name);

		// accessors for the module's prepared texts
		typedef std::set<NLMISC::CSString> TTextFlags;
		GUS::CText& getPreparedText();
		TTextFlags& getPreparedTextFlags();

	public:
		// remaining public interface
		CEventChatModule();

	private:
		TCtrlChannelPtr		_CtrlChannel;
		typedef std::vector<TFactionChannelPtr>	TFactionChannels;
		TFactionChannels	_FactionChannels;
		GUS::CText			_PreparedText;
		TTextFlags			_PreparedTextFlags;
	};
}


//-----------------------------------------------------------------------------
#endif
