/* procgrosscpumicro.c - procgrosscpumicro */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  procgrosscpumicro  -  gets process gross cpu usage time in microsecs
 *------------------------------------------------------------------------
 */

uint32	procgrosscpumicro(
	  pid32		pid		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	uint64	grosscpumicro;		/* Process gross cpu time to return	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	grosscpumicro = proctab[pid].prgrosscputick;
	grosscpumicro = (grosscpumicro * 2.5) / 1000; /* Converting ticks into microsecs */
	restore(mask);
	return grosscpumicro;
}
