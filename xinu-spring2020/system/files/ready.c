/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	insert(pid, readylist, prptr->prprio); /* Commented out for 4.2 */

	/* Added for 4.2 */
	/* New insert function rinsert() that uses cpu usage value prvgrosscpu */
	/* as a priority value instead of using prprio */
//	rinsert(pid, readylist, prptr->prvgrosscpu);

	resched();
	
	return OK;
}
