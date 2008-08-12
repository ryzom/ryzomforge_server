/** file patchman_tester.h
 *
 */

#ifndef PATCHMAN_TESTER_H
#define PATCHMAN_TESTER_H

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------

// nel
#include "nel/misc/sstring.h"


//-----------------------------------------------------------------------------
// namespace PATCHMAN
//-----------------------------------------------------------------------------

namespace PATCHMAN
{
	//-----------------------------------------------------------------------------
	// class CPatchmanTester
	//-----------------------------------------------------------------------------

	class CPatchmanTester
	{
	public:
		// this is a singleton so it has a getInstance() method to get to the singleton instance
		static CPatchmanTester& getInstance();

		// public interface...

		// clear everything
		virtual void clear() =0;

		// clear loaded script(s) but leave state intact
		virtual void clearScript() =0;

		// clear state variables but leave scripts intact
		virtual void clearState() =0;

		// load a script file
		virtual void loadScript(const NLMISC::CSString& fileName) =0;

		// set a state variable
		virtual void set(const NLMISC::CSString& variableName,const NLMISC::CSString& value) =0;
		virtual void set(const NLMISC::CSString& variableName,sint32 value) =0;

		// trigger an event
		virtual void trigger(const NLMISC::CSString& eventName) =0;

		// debug routine - display internal state info
		virtual void dump(NLMISC::CLog& log) =0;

		// debugging routine - displays the syntax help for the patchtest script files
		virtual void help(NLMISC::CLog& log) =0;
	};

} // end of namespace

#endif

