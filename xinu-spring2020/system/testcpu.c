/* testcpu.c - testcpu (x86) */

#include <xinu.h>

uint32  clktimemilli;

void testcpu(void) {

	int x, y;
	x = 0;
	y = clktimemilli;
	while(clktimemilli - y < 8000) // until wall clock time of 8 sec is reached do
		x++;
//	kprintf("cpu: %d %d %d %d\n", currpid, x, proctab[currpid].prgrosscpu, procgrosscpumicro(currpid));
	kprintf("This is front testcpu\n");
}
