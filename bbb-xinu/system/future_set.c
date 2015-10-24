#include <future.h> 
/* if future does not have value set */
syscall future_set(future *f, int *i) {
	
	pid32 p_id;
	intmask	mask;
	mask=disable();
	
	if (f->state == FUTURE_EMPTY){
		
		f->value = i;
		f->state = FUTURE_VALID; 
		
		if(f->flag == FUTURE_EXCLUSIVE || f->flag == FUTURE_SHARED){
					
			restore(mask);
			return OK; 
		}else {
			p_id = f_enqueue(currpid, f->set_queue);
			if(p_id == (pid32) SYSERR){
				restore(mask);
				return SYSERR;
			}	
			suspend(currpid);
			f->value = i;	
			restore(mask);
			return OK; 
		}
	} 	

	if(f->state == FUTURE_WAITING){
		if(f->flag == FUTURE_EXCLUSIVE){
			f->value = i;			
			f->state=FUTURE_VALID;
			resume(f->pid);
			restore(mask);
			return OK;
		}else if(f->flag == FUTURE_SHARED){
			f->value = i;			
			f->state=FUTURE_VALID;
			
			while (!q_isempty(f->get_queue))
				resume(f_dequeue(f->get_queue));
			restore(mask);
			return OK;
		}
		else if(f->flag == FUTURE_QUEUE){
			if(!q_isempty(f->get_queue)){
				f->value = i;			
				
				resume(f_dequeue(f->get_queue));
			}else{
				p_id = f_enqueue(currpid, f->set_queue);
				if(p_id == (pid32) SYSERR){
					restore(mask);
					return SYSERR;
				}	
				suspend(currpid);
				f->value = i;	
			}
			
			restore(mask);
			return OK;
		}
	}
	restore(mask);
	return SYSERR;
}

