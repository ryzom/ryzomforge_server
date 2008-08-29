/**	/file handy_commands.h
 *
 *	Handy utility commands
 *
 *	This header file needs to be included by any file in a NeL service project in order for 
 *  the handy utility NLMISC_COMMAND commands to be available in the service.
 *
 *	$id$
 */


#ifndef HANDY_COMMANDS_H
#define HANDY_COMMANDS_H


//-------------------------------------------------------------------------------------------------
// fake variable to force a link to the handy_commands module
//-------------------------------------------------------------------------------------------------

static struct CHandyCommandIncluderClass
{
	CHandyCommandIncluderClass();
}
IncludeHandyCommand;


//-------------------------------------------------------------------------------------------------
#endif
