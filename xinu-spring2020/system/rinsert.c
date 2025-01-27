/* rinsert.c - rinsert */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  rinsert  -  Insert a process into a queue in descending key order
 *------------------------------------------------------------------------
 */
status	rinsert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Key for the inserted process	*/
	)
{
	qid16	curr;			/* Runs through items in a queue*/
	qid16	prev;			/* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	curr = firstid(q);

	/* For 4.2 and 4.3: */

	/* The following conditions check:
	   1) If process being passed in is the NULL Process
	   2) If the process being passed in is a NEW process
	   3) If the process being passed in is an EXISTING process
	*/

	/* If process is a NEW process (with a CPU usage value prvgrosscpu == 0) */
	if (key == 0) {

		/* If process is the NULL Process (must have PID == 0) */
		if (pid == 0) {	/* This is the null process we are inserting into the ready list */
			
			/* If it is NULL Process, we simply insert it as the first process
			   in the ready list */

			prev = queuetab[curr].qprev;    /* Get index of previous node   */
        		queuetab[pid].qnext = curr;
        		queuetab[pid].qprev = prev;
        		queuetab[pid].qkey = key;
        		queuetab[prev].qnext = pid;
        		queuetab[curr].qprev = pid;
        		return OK;
		}

		/* If process is NOT the null process, but it is a new process,
		   we iterate through the ready list queue until we reach the element
		   right before the null process (which should be the last proc in ready list)
		   and then insert the new process right before the null process in the ready list */
		while (queuetab[curr].qnext != 0) { /* While the next element does not have a PID==0 */
			curr = queuetab[curr].qnext;	/* Keep iterating to the next process in the ready list */		}
			kprintf("rinsert.c - stuck in while loop\n");
		/* Insertion commands */
		/* These happen when we want to insert a new process into the ready list based on our current pointer */
		prev = queuetab[curr].qprev;    /* Get index of previous node   */
        	queuetab[pid].qnext = curr;
        	queuetab[pid].qprev = prev;
        	queuetab[pid].qkey = key;
        	queuetab[prev].qnext = pid;
        	queuetab[curr].qprev = pid;
        	return OK;
	}

	
	else {	/* else if it is a new process with a CPU usage of >0, or in other words, it is an already existing process */	
		while (queuetab[curr].qkey <= key) { /* Here key is the value for priority. We switch the >= sign to a <= */
			curr = queuetab[curr].qnext;	/* We switch the signs so that rinsert() inserts processes in ascending */
							/* order of priority */
		}
	}

	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	return OK;
}
