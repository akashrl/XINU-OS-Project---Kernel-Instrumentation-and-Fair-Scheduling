/* getppid.c - getppid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getppid  -  Return the parent ID of the currently executing process
 *------------------------------------------------------------------------
 */
pid32	getppid(pid32 pid)
{
	intmask	mask;
	struct procent *prptr;
	pid32 ppid;
	
	mask = disable(); // Disabling interrupts
	if (isbadpid(pid)) {
		restore(mask);
		return (pri16) SYSERR;
	}


	prptr = &proctab[pid];
	ppid = prptr->prparent;
	//struct procent ppid_procent = proctab[currpid];
	//ppid = ppid_procent.prparent;

	restore(mask); // Restoring interrupts
	return ppid;

}
