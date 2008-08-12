/** \file ags_time.h
 *
 * $Id: ags_timer.h,v 1.4 2004/03/01 19:18:37 lecroart Exp $
 */



#include "nel/misc/types_nl.h"

namespace AGS_TEST
{
	class CAGSTimer
	{
		private:
			uint32 _start;
			uint32 _dt;
		public:
			CAGSTimer(uint32 dt = 0);
			void set(uint32 dt);
			void add(uint32 dt);
			bool test();
	};
}

