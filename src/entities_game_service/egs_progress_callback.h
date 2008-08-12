/** \file egs_progress_callback.h
 * <File description>
 *
 * $Id: egs_progress_callback.h,v 1.6 2004/12/08 13:26:42 besson Exp $
 */



#ifndef RY_EGS_PROGRESS_CALLBACK_H
#define RY_EGS_PROGRESS_CALLBACK_H

#include "nel/misc/progress_callback.h"

/**
 * class used to handle database progess callbacks
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2002
 */
class CEGSProgressCallback : public NLMISC::IProgressCallback
{
public:
	CEGSProgressCallback():IProgressCallback() {}
	virtual void progress (float progressValue) {};
	virtual ~CEGSProgressCallback() {}

};


#endif // RY_EGS_PROGRESS_CALLBACK_H

/* End of egs_progress_callback.h */

