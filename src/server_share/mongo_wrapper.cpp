// Ryzom - MMORPG Framework <http://dev.ryzom.com/projects/ryzom/>
// Copyright (C) 2010  Winch Gate Property Limited
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "stdpch.h"

#include "mongo_wrapper.h"


using namespace std;
using namespace NLMISC;
using namespace NLNET;

CVariable<string> MongoPassword("mongo", "MongoPassword", "Set the password to access mongo", string(""), 0, true);

DBClientConnection CMongo::conn(true);
string CMongo::dbname;


void CMongo::init() {
	if (IService::getInstance()->getShardId() == 301) {
	    dbname = "megacorp_dev";
	} else {
		dbname = "megacorp_live";
	}

    try {
		bool res;
		string errmsg;

        res = conn.connect("ryzom.com:22110", errmsg);
		if(!res) nlerror("mongo: init failed, cannot connect '%s'", errmsg.c_str());
		else nlinfo("mongo: connection ok");

        res = conn.auth(dbname, "megacorp", MongoPassword.get(), errmsg);
		if(!res) nlerror("mongo: init failed, cannot auth '%s'", errmsg.c_str());
		else nlinfo("mongo: auth ok");
    } catch(DBException& e) {
        nlerror("mongo: init failed, caught DBException '%s'", e.toString().c_str());
    }
}

void CMongo::insert(const string &collection, const string &json) {
	nlinfo("mongo: try to insert into '%s': '%s'", collection.c_str(), json.c_str());

	try {
		conn.insert(dbname+"."+collection, fromjson(json));
		string e = conn.getLastError();
		if(!e.empty()) nlwarning("mongo: insert failed '%s'", e.c_str());
	} catch(DBException& e) {
		nlwarning("mongo: insert failed, caught DBException '%s'", e.toString().c_str());
	}
}

auto_ptr<DBClientCursor> CMongo::query(const string &collection, const string &json) {
//	nlinfo("mongo: try to query in '%s': '%s'", collection.c_str(), json.c_str());

    try {
		return conn.query(dbname+"."+collection, json);
    } catch(DBException& e) {
		nlwarning("mongo: query failed, caught DBException '%s'", e.toString().c_str());
		return auto_ptr<DBClientCursor>(0);
    }
}

void CMongo::update(const string &collection, const string &jsonQuery, const string &jsonObj, bool upsert, bool multi) {
	nlinfo("mongo: try to update in '%s' '%s': '%s'", collection.c_str(), jsonQuery.c_str(), jsonObj.c_str());

    try {
		conn.update(dbname+"."+collection, jsonQuery, fromjson(jsonObj), upsert, multi);
    } catch(DBException& e) {
		nlwarning("mongo: update failed, caught DBException '%s'", e.toString().c_str());
    }
}
