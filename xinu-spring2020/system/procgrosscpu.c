/* procgrosscpu.c - procgrosscpu */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  procgrosscpu  -  gets process gross cpu usage time
 *------------------------------------------------------------------------
 */

uint32	procgrosscpu(
	  pid32		pid		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	uint32	grosscpu;		/* Process gross cpu time to return	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	grosscpu = proctab[pid].prgrosscpu;
	restore(mask);
	return grosscpu;
}
