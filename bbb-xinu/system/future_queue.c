/* queue.c - enqueue, dequeue */

#include <future_queue.h>


/*------------------------------------------------------------------------
 *  enqueue  -  Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
pid32	f_enqueue(
	  pid32		pid,	/* ID of process to insert	*/
	  queue* q		/* ID of queue to use		*/
	  
	  
	)
{

	if(q->count == QUEUE_SIZE){
		return (pid32)SYSERR;
	}

	q->rear = (q->rear + 1)%QUEUE_SIZE;
	q->parray[q->rear] = pid;
	q->count++;
	return pid;
}


/*------------------------------------------------------------------------
 *  dequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	f_dequeue(
	  queue* q	/* ID of queue to use		*/
	  
	)
{
	if(q->count == 0){
		return (pid32)SYSERR;
	}
	pid32 pid;
	pid = q->parray[q->front];
	q->front = (q->front + 1)%QUEUE_SIZE;
	q->count--;
	return pid;
}

int	q_isempty(
	  queue* q	/* ID of queue to use		*/
	  
	)
{
	if(q->count == 0){
		return 1;
	}
	return 0;
}
