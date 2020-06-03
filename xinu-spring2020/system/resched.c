/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio); /* Commented for 4.2 */
//		rinsert(currpid, readylist, ptold->prprio); /* Commented for 4.2 */
//		rinsert(currpid, readylist, ptold->prvgrosscpu); /* Added for 4.2 */
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;

	/* QUANTUM is fixed to 30 msec for 4.4 in kernel.h */
	preempt = QUANTUM;		/* Reset time slice for process	*/

	uint32 currentgrosscpu; /* For 3.3, Akash, declaring currentgrosscpu */
	uint32 prgrosscpu; /* For 3.3, Akash, declaring prgrosscpu */
	
	uint32 prvgrosscpu; /* For 4.3, Akash, declaring prvgrosscpu */

	uint64 currentgrosscputick; /* For 3.5, Akash L, declaring currentgrosscputick */

	uint64 currentticks; /* For 3.5, Akash L, declaring currentticks */
	
	ptnew->prgrosscpu = clktimemilli - currentgrosscpu; /* For 3.3, Akash L */
	
	ptnew->prvgrosscpu = clktimemilli - currentgrosscpu; /* For 4.3, Akash L */

	asm volatile ( "rdtsc" : "=A"(currentticks) );

	ptnew->prgrosscputick = currentticks - currentgrosscputick;

	if (clktimemilli == currentgrosscpu) { /* For 3.3, Akash L */
		prgrosscpu = prgrosscpu + 1;
	}	

	if (clktimemilli == currentgrosscpu) { /* For 4.3, Akash L */
		prvgrosscpu = prvgrosscpu + 1;
	}
	
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	currentgrosscpu = clktimemilli; /* For 3.3, track gross cpu time */
	
	asm volatile ( "rdtsc" : "=A"(currentticks) );

	currentgrosscputick = currentticks;

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
