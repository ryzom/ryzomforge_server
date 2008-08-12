/** file patchman_constants.h
 *
 *
 */

#ifndef PATCHMAN_CONSTANTS_H
#define PATCHMAN_CONSTANTS_H

namespace PATCHMAN
{
	/*
		Note that the contants in this file are 'static', meaning that they
		will be instantiated in every .o file independently, this is the price
		to pay for typed constants in C++ :(
	*/

	/*
		The following conatants are used in module manifests to identify
		modules that fit different criteria.
	*/

//	static const char* ManifestEntryIsServerPatchRepository="isServerPatchRepository";
//	static const char* ManifestEntryIsServerPatchManager="isServerPatchManager";
	static const char* ManifestEntryIsAdministered="isAdministered";
	static const char* ManifestEntryIsAdministrator="isAdministrator";
	static const char* ManifestEntryIsFileRepository="isFileRepository";
	static const char* ManifestEntryIsFileReceiver="isFileReceiver";
	static const char* ManifestEntryIsTerminal="isTerminal";

}

#endif
