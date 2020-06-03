/*  main.c  - main */

#include <xinu.h>
  
//void sndch(char);

//void testcpu();
//void testipo();

process main(void)
{
       // kprintf("hello\n");
       // recvclr();

        
	// resume( create(sndch, 1024, 25, "send A", 1, 'A') );
	
	// resume( create(sndch, 1024, 20, "send A", 1, 'A') );
	
	// resume( create(sndch, 1024, 0, "send A", 1, 'A') ); // testing that priority is zero returns SYSERR
        
        // resume( create(sndch, 1024, 10, "send A", 1, 'A') );
	// resume( create(sndch, 1024, 10, "send B", 1, 'B') );
	kprintf("%d\n", clktimemilli);
	kprintf("Calling testcpu:\n");
//        resume( create(testcpu, 1024, 10, "test 1", 0));
//        resume( create(testcpu, 1024, 10, "test 2", 0));
//        resume( create(testcpu, 1024, 10, "test 3", 0));
//        resume( create(testcpu, 1024, 10, "test 4", 0));
        
	//resume( create(sndch, 1024, 15, "send B", 1, 'B') );
	
	//pid32 pid = getpid();
	//pid32 ppid = getppid(pid);
	//kprintf("Here is parent PID: ");
	//kprintf("%d\n", ppid);

	pid32 pid = wgetpid();
	// The following are testing getpid getprio using int wrapper
	kprintf("Here is current PID from wrapper function using interrupt: ");
	kprintf("%d\n", pid);
	
        kprintf("****** The following are the outputs from section 3 ******\n\n");    
        uint32 birthday = procbirth(pid);
        uint32 lifetime = proclifetime(pid);
        kprintf("3.2 - From main, birthday in milliseconds: %d\n\n", birthday);
        kprintf("3.2 - From main, proc lifetime in milliseconds: %d\n\n", lifetime);

        uint32 processgrosscpu = procgrosscpu(pid);
        kprintf("3.3 - From main, Process Gross CPU in milliseconds: %d\n\n", processgrosscpu);

        uint32 processgrosscpumicro = procgrosscpumicro(pid);
        kprintf("3.5 - From main, Process Gross CPU in microseconds: %d\n\n", processgrosscpumicro);
    
        kprintf("****** End of outputs from section 3 ******\n\n");



	uint32 prio = wgetprio(pid);
	//uint32 prio = getprio(pid);
	kprintf("Here is current PID priority from  wrapper function using interrupt: ");
	kprintf("%d\n", prio);
	

	pid32 ppid = wgetppid(pid);
	kprintf("Here is the PPID from wrapper function using interrupt: ");
	kprintf("%d\n", ppid);
	
}

void    sndch(char  ch) /* The character to emit continuously */
{

	uint32 tmslice;
	
//	while ( 1 ) {
		tmslice = gettmslice();
		kprintf("%c", ch);
		kprintf("The remaining timeslice: ");
		kprintf("%d\n", tmslice);
		
//	}
}


