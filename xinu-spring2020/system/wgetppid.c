/* wgetppid.c - wgetppid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wgetppid  -  Return the ID of the parent process
 *------------------------------------------------------------------------
 */
pid32	wgetppid(pid)
{
	pid32 pidnum;

	asm ("movl $6, %%eax;"
	 "movl %1, %%ebx;"
         "int $33;"
         "movl %%eax, %0;"
	 
         : "=r" ( pidnum )        /* output */
         : "r" ( pid )         /* input */
         : "%eax", "%ebx"         /* clobbered register */
         );

	return (pidnum);
	
	
}
/*
        int callnum = 5;
        uint32 prio;
        asm ("movl $5, %%eax;"
                "movl %1, %%ebx;"
                "int $33;"
                "movl %%eax, %0;"
                : "=r" ( prio )        // output 
                : "r" ( pid )
                : "%eax", "%ebx"         // clobbered register 
                );  
*/

