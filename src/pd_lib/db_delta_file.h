/** \file db_delta_file.h
 * <File description>
 *
 * $Id: db_delta_file.h,v 1.8 2004/09/27 17:42:37 legros Exp $
 */

#ifndef NL_DB_DELTA_FILE_H
#define NL_DB_DELTA_FILE_H

#include <nel/misc/types_nl.h>
#include <nel/misc/stream.h>
#include <nel/misc/path.h>

#include "pd_server_utils.h"

/**
 * <Class description>
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2003
 */
class CDBDeltaFile : public CMixedStreamFile
{
public:

	/// Constructor
	CDBDeltaFile();

	/// Destructor
	~CDBDeltaFile();


	/// Setup file name and path
	void				setup(const std::string& name, const std::string& path, uint32 rowSize, const CTimestamp& startTimestamp, const CTimestamp& endTimestamp);

	/// Setup file name and path
	void				setup(const std::string& filepath, uint32 rowSize, const CTimestamp& startTimestamp, const CTimestamp& endTimestamp);



	/// Write next row modification
	bool				write(uint32 index, const uint8* rowdata);

	/// Read next row modification
	bool				read(uint32& index, uint8* rowdata);



	/// Preload file
	bool				preload();

	/// Get Row Size
	uint32				getRowSize() const							{ return _Header.RowSize; }



	/// Set Delta Ids
	void				setDeltaIds(uint32 startId, uint32 endId)	{ _Header.StartDeltaId = startId; _Header.EndDeltaId = endId; }

	/// Get Delta Ids
	void				getDeltaIds(uint32& startId, uint32& endId)	{ startId = _Header.StartDeltaId; endId = _Header.EndDeltaId; }


	/**
	 * Get delta file name
	 */
	static std::string	getDeltaFileName(uint32 tableId, const CTimestamp& timestamp)
	{
		return NLMISC::toString("%04X_%s.%s", tableId, timestamp.toString().c_str(), getDeltaFileExt().c_str());
	}

	/**
	 * Get delta file name (hour truncated)
	 */
	static std::string	getHourDeltaFileName(uint32 tableId, const CTimestamp& timestamp)
	{
		//return NLMISC::toString("%04X_%s.%s", tableId, timestamp.truncToHours().c_str(), getDeltaFileExt().c_str());
		return NLMISC::toString("%04X_%s.%s", tableId, timestamp.toString().c_str(), getDeltaFileExt().c_str());
	}

	/**
	 * Get delta file name (minute truncated)
	 */
	static std::string	getMinuteDeltaFileName(uint32 tableId, const CTimestamp& timestamp)
	{
		//return NLMISC::toString("%04X_%s.%s", tableId, timestamp.truncToMinutes().c_str(), getDeltaFileExt().c_str());
		return NLMISC::toString("%04X_%s.%s", tableId, timestamp.toString().c_str(), getDeltaFileExt().c_str());
	}

	/**
	 * Is delta file name
	 */
	static bool			isDeltaFileName(const std::string& filename, uint32& tableId, CTimestamp& timestamp)
	{
		char	buffer[32];
		if (NLMISC::CFile::getExtension(filename) != getDeltaFileExt() ||
			sscanf(NLMISC::CFile::getFilenameWithoutExtension(filename).c_str(), "%4X_%s", &tableId, buffer) != 2)
			return false;
		timestamp.fromString(buffer);
		return true;
	}

	/**
	 * Get delta file name extension
	 */
	static std::string	getDeltaFileExt()					{ return "dbdelta"; }


	/**
	 * Concats a delta file to this one
	 */
	bool				concat(CDBDeltaFile& delta, const CTimestamp& starttime, const CTimestamp& endtime);


	/**
	 * Get Start Timestamp
	 */
	uint32				getStartTimestamp() const			{ return _Header.StartTimestamp; }

	/**
	 * Get End Timestamp
	 */
	uint32				getEndTimestamp() const				{ return _Header.EndTimestamp; }

	/**
	 * Get Row Header Size in byte (CTableBuffer needs it)
	 */
	static uint32		getRowHeaderSize()					{ return sizeof(uint32); }


	/**
	 * Invalid File exception
	 */
	class EInvalidFile : public NLMISC::Exception
	{
	public:

		EInvalidFile() : Exception("File not validated")	{ }

	};


private:

	class CDeltaHeader
	{
	public:

		CDeltaHeader()
		{
			RowSize = 0;
			FullRowSize = 0;
			StartTimestamp = 0;
			EndTimestamp = 0;
			StartDeltaId = 0;
			EndDeltaId = 0;
		}

		/// Row size, only declared size
		uint32				RowSize;

		/// Row Size, in byte (all headers included)
		uint32				FullRowSize;

		/// Start Timestamp
		uint32				StartTimestamp;

		/// End Timestamp
		uint32				EndTimestamp;

		/// Start Delta Id, used to check delta concatenation
		uint32				StartDeltaId;

		/// End Delta Id, used to check delta concatenation
		uint32				EndDeltaId;

		/// Is File Valid
		bool				IsValid;

		void				serial(NLMISC::IStream& s)
		{
			s.serialCheck((uint32)'DHdr');
			uint	version = s.serialVersion(0);

			s.serial(RowSize);
			s.serial(FullRowSize);

			s.serial(StartTimestamp);
			s.serial(EndTimestamp);

			s.serial(StartDeltaId);
			s.serial(EndDeltaId);

/*
			s.serial(IsValid);
			if (s.isReading())
			{
				if (!IsValid)
				{
				}
			}
*/
		}
	};

	/// File base name
	std::string			_Name;

	/// File path
	std::string			_Path;

	/// Header of the reference
	CDeltaHeader		_Header;


	/// Data start position
	uint32				_DataStart;


	/// Map of index position in file
	typedef CHashMap<uint32, uint32>	TIndexMap;
	TIndexMap			_IndexMap;


	/// Serial file header
	bool				serialHeader();

};


#endif // NL_DB_DELTA_FILE_H

/* End of db_delta_file.h */
