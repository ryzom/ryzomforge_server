/* \file character.h
 * database string updater
 *	Contains a class that manage the 'TEXT' property in the client/server database
 *	system.
 *
 * $Id: db_string_updater.h,v 1.4 2007/03/09 09:56:51 boucher Exp $
 */


#include "nel/misc/types_nl.h"

#include "nel/misc/singleton.h"
#include "nel/misc/string_mapper.h"
#include "nel/net/message.h"
#include "cdb_synchronised.h"


class CDBStringUpdater : public NLMISC::CSingleton<CDBStringUpdater>
{

	typedef uint32				TIOSStringId;
	typedef NLMISC::TStringId	TLocalStringId;

	// Identifier for one string mapped into one data container
	struct TBDStringLeaf
	{
		CCDBSynchronised		*ClientDB;
		ICDBStructNode			*Node;

		TBDStringLeaf()
			:	ClientDB(NULL),
				Node(NULL)
		{}

		TBDStringLeaf(CCDBSynchronised *clientDB, ICDBStructNode *node)
			: ClientDB(clientDB), Node(node)
		{}

		bool operator ==(const TBDStringLeaf &other) const
		{
			return ClientDB == other.ClientDB && Node == other.Node;
		}
	};

	// hasher for the identifier
	struct THashDBStringLeaf
	{
		size_t operator()(const TBDStringLeaf &stringLeaf) const
		{
			return ((size_t)stringLeaf.ClientDB>>4) ^ ((size_t)stringLeaf.Node>>4);
		}
	};

	// info for each string leaf
	struct TStringLeafInfo
	{
		TLocalStringId	LocalStringId;
		bool			ForceSending;
	};

	typedef CHashMap<TBDStringLeaf, TStringLeafInfo, THashDBStringLeaf> TStringLeafs;

	// All the string leaf with non empty string
	TStringLeafs			_StringLeafs;


	typedef std::map<TLocalStringId, TIOSStringId>	TMappedIOSStrings;

	// The local table of already mapped IOS id
	TMappedIOSStrings		_MappedIOSStrings;

	bool		_IOSIsUp;



private:
	void	storeAStringInIOS(const ucstring &str);

	void	storeStringResult(NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId);
public:

	CDBStringUpdater();

	void onIOSUp();
	void onIOSDown();

	void onClientDatabaseDeleted(CCDBSynchronised *clientDB);
	void setStringLeaf(CCDBSynchronised *clientDB, ICDBStructNode *node, const std::string &str, bool forceSending);
	void setStringLeaf(CCDBSynchronised *clientDB, ICDBStructNode *node, const ucstring &str, bool forceSending);
	ucstring getUcstringLeaf(CCDBSynchronised *clientDB, ICDBStructNode *node) const;
	const std::string &getStringLeaf(CCDBSynchronised *clientDB, ICDBStructNode *node) const;

	static void	cbStoreStringResult(NLNET::CMessage& msgin, const std::string &serviceName, NLNET::TServiceId serviceId);
};



