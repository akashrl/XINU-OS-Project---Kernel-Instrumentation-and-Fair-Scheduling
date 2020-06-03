/* wgetprio.c - wgetprio */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wgetprio  -  Return the scheduling priority of a process
 *------------------------------------------------------------------------
 */
syscall	wgetprio(
	  pid32		pid		/* Process ID			*/
	)
{
	int callnum = 5;
	uint32 prio;
    	asm ("movl $5, %%eax;"
		"movl %1, %%ebx;"
        	"int $33;"
         	"movl %%eax, %0;"
         	: "=r" ( prio )        /* output */
        	: "r" ( pid )
         	: "%eax", "%ebx"         /* clobbered register */
         	);





/*
	intmask	mask;			// Saved interrupt mask		
	uint32	prio;			// Priority to return		

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	prio = proctab[pid].prprio;
	restore(mask);
*/
	return prio;
}
