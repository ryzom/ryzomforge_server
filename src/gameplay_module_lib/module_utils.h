/** \file module_utils.h
 * usefuls defines / macro for the module library DO NOT INCLUDE THIS FILE INCLUDE "gameplay_module.h"
 *
 * $Id: module_utils.h,v 1.4 2004/07/22 09:25:45 brigand Exp $
 */

#ifndef RY_MODULE_UTILS_H
#define RY_MODULE_UTILS_H

#include "nel/misc/types_nl.h"

// comment / uncomment that to have a debug version of the library
#define RY_MODULE_DEBUG


#ifdef RY_MODULE_DEBUG
	inline void MODULE_INFO(const char*,...) {}
	#define MODULE_AST nlassert
	#define MODULE_CAST static_cast
#else
	inline void MODULE_INFO(const char*,...) {}
	inline void MODULE_AST(const char*,...) {}
	#define MODULE_CAST dynamic_cast
#endif


#endif
