/* kill.c - kill */


#include <newmem.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	killme(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	int32	i;			/* Index into descriptors	*/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		
		restore(mask);
		return SYSERR;
	}
	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	//freestk(prptr->prstkbase, prptr->prstklen);  ----- No call made to free the stack memory
	

         if(maxusedflag==1)
	{
	char *sp_val;	
	sp_val = sp;
	int counter=0;
	
	
	for(i=0;i<stksize;i++)
	{
		if(*sp_val != 'c')
                {
		counter++;
                 }
		sp_val= sp_val-1; 

		
	}
	printf("Max stack space used:%d\n",counter);
       }
	
	
	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);

	return OK;
}
