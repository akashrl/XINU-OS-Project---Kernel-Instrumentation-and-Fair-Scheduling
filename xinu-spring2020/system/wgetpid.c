/* wgetpid.c - wgetpid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wgetpid  -  Return the ID of the currently executing process
 *------------------------------------------------------------------------
 */
pid32	wgetpid(void)
{
	int callnum = 4;
	pid32 pidnum;
	
	asm ("movl %1, %%eax;"
         "int $33;"
         "movl %%eax, %0;"
         : "=r" ( pidnum )        /* output */
         : "r" ( callnum )         /* input */
         : "%eax"         /* clobbered register */
         );

	return (pidnum);
	
	
}
