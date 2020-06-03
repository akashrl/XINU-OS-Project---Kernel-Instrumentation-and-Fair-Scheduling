/* gettmslice.c - gettmslice */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  gettmslice  -  Find timeslice for the current process
 *------------------------------------------------------------------------
 */
uint32	gettmslice(void)
{

	return(preempt);

}
