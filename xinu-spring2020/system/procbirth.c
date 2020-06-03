/* procbirth.c - procbirth */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  procbirth  -  Return the scheduling priority of a process
 *------------------------------------------------------------------------
 */
uint32	procbirth(
	  pid32		pid		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	uint32	bday;			/* Priority to return		*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	bday = proctab[pid].prbirth;
	restore(mask);
	return bday;
}
