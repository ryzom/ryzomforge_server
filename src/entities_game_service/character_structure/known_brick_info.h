/** \known_brick_info.h
 * 
 *
 * $Id: known_brick_info.h,v 1.5 2004/12/09 14:17:28 besson Exp $
 */



#ifndef RY_KNOWN_BRICK_INFO_H
#define RY_KNOWN_BRICK_INFO_H

// ---------------------------------------------------------------------------
class CStaticGameBrick;

// ---------------------------------------------------------------------------
struct CKnownBrickInfo
{
	const CStaticGameBrick*	Form;
	uint32					LatencyEndDate;
	bool					OldLatentState;
	
	CKnownBrickInfo( const CStaticGameBrick *form = NULL ) : Form(form)
	{		
		LatencyEndDate = 0;
		OldLatentState = false;
	}
	
	/// Serialisation
	void serial(class NLMISC::IStream &f) throw(NLMISC::EStream)
	{
		//		f.serial( LatencyEndDate );
		//		f.serial( OldLatentState );
		// nothing to serial here, the date are no longer meaningful, all bricks are available when the character connects to the game
		// and the Form is set while setting the databse in the setDatabase() method
	}
};

#endif // RY_KNOWN_BRICK_INFO_H
/* known_brick_info.h */
