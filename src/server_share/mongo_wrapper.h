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

#ifndef MONGODB_WRAPPER_H
#define MONGODB_WRAPPER_H

#include <mongo/client/dbclient.h>

using namespace mongo;
using namespace bson;

class CMongo {
public:
	static void init();
	static void insert(const std::string &collection, const std::string &json);
	static std::auto_ptr<DBClientCursor> query(const std::string &collection, const std::string &json);
	static void update(const std::string &collection, const std::string &jsonQuery, const std::string &jsonObj, bool upsert=false, bool multi=false);
	static std::string quote(const std::string &s);

private:
    static DBClientConnection conn;
	static std::string dbname;
};

#endif //  MONGODB_WRAPPER_H