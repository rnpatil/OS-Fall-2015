#include <newmem.h>
#include<string.h>

int n;
pid32 pid;
sid32 consumed,produced;
struct memblk* memptr;
char *sp,*newsp;
uint32 stksize;
int flagger =0;
int maxusedflag=0;

shellcmd xsh_newmem(int nargs, char *args[])
{
	int counter = 10;             //local varible to hold count
	struct	procent	*prptr;		/* pointer to proc. table entry */
	

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
	{
	printf("Use: %s Command\n", args[0]);
	printf("Description: FUTURE IMPLEMENTATION PART 2 \n");
	printf("\t--help\t To implement the producer-consumer problem with the use of FUTURES with queue implementations\n");
	return 0;
	}
	
	if(nargs==2 && strcmp(args[1], "-f") == 0)
	{
	flagger=1;
	}
	else if(nargs==2 && strcmp(args[1], "-s") == 0)
	{
	flagger=2;
	}
	else if(nargs==2 && strcmp(args[1], "-t") == 0)
	{
	flagger=3;
	}
	if(flagger==1)
	{
          flagger=0;
	  printf("Before everything:\n");
          printfreelist();
          
	}

	if(flagger==2)
	{
	flagger=0;
	printf("Before everything:\n");
        printfreelist();

	pid = newcreate(testprocess, 1024,20,"testprocess");

        prptr = &proctab[pid];
	sp = prptr->prstkptr;
        stksize= prptr->prstklen;
	resume(pid);
	

        printf("After process creation:\n");
        printfreelist();
	
	
	int i = (int) getmem(sizeof(int));

        printf("After calling getmem:\n");
        printfreelist();
	
	
	}
	//Question3
	if(flagger==3)
	{
        maxusedflag=1;
        flagger=0;
        pid = newcreate(testprocess, 1024,20,"testprocess");
        prptr = &proctab[pid];
	sp = prptr->prstkptr;
	stksize= prptr->prstklen;
	char* sp_val;	
	sp_val = sp;

	//printf("\nSp initial value=%d\n",sp);
	
	int i;
	for(i=0;i<stksize;i++)
	{
		*sp_val = 'c';
		sp_val= sp_val-1; 
	}
	
	resume(pid);


	}

	
	  return 0; 

}

void printfreelist()
{
memptr = memlist.mnext;
	while(memptr != NULL)
        {
          
	    printf("Address of free-block: %d\n",memptr);
            printf("Length of free-block: %d\n\n",memptr->mlength);
            memptr = memptr->mnext;
           
        }
}
