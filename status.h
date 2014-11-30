/********************************************************************
 *
 * $Id: status.h 1957 2014-06-12 06:21:22Z phil $
 *
 ********************************************************************
 */
/**
 * Minimal system for error handling.
 *
 * Each value of the "status" enum is associated with an error message.
 * Every function (but some of those returning pointers) should return a
 * status. In the case of non-void functions, the former return value has 
 * to be placed in the parameter list (by address)
 *
 ********************************************************************/

#ifndef __STATUS_H
#define __STATUS_H

typedef enum {
	OK,
	ERROPEN,
	ERRACCESS,
	ERRCLOSE,
	ERRALLOC,
	ERRDATE,
	ERRFULL,
	ERREMPTY,
	ERRABSENT,
	ERREXIST,
    INDER,
	
	UNKNOWN,
	ENDER
	} status;

/** get message associated with the given status value (O(1)).
 * @param s the status value
 * @return the associated message
 */
extern char* message(status s);


#endif
