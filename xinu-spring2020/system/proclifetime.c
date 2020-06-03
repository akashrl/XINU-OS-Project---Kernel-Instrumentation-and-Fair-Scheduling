/* proclifetime.c - proclifetime */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  proclifetime  -  Return the scheduling priority of a process
 *------------------------------------------------------------------------
 */
uint32	proclifetime(
	  pid32		pid		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	uint32	bday;			/* birthday of process		*/
	uint32	lifetime;		/* lifetime of process		*/
	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	bday = proctab[pid].prbirth;
	lifetime = clktimemilli - bday;
	restore(mask);
	return lifetime;
}
