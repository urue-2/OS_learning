#include "pc.h"
#define STR_SIZE 50

#define post ".exe"
#define compre "./"
;

// p consumer / producer
void call_file(char x[]){

	char* path = (char *) malloc(strlen(x) + strlen(post)); 
	strcat(path,x);
	strcat(path,post);
	
	char* command = (char *) malloc(strlen(compre) + strlen(path)); 
	strcat(command,compre);
	strcat(command,path);
	
  	execl(path,command,NULL);
	  	
}


int main(int argc , char *argv[])
{
	
	key_t shared_memory_key,se_key;
	int shared_memory_id,semid;
	
	buffer_pointer data;
	
	
	
	
	// establish shared memory 
	shared_memory_key = sm_k;
	
	if ((shared_memory_id =  shmget(shared_memory_key,SHM_SIZE,0644 | IPC_CREAT)) == -1){
	
		perror("shmget");
		exit(1);
	}
	
	data = (buffer_pointer)shmat(shared_memory_id ,(void *)0,0); 
	if ( data == (buffer_pointer)-1){
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	
	
	
	
	
	data->p1=0;
	data->p2=0;
	data->p3=0;	
	data->cur = 0;
	
	
	// establish sephmore
	
	se_key = se_k;
	
	if ((semid = semget(se_key, 3, 0666 | IPC_CREAT)) == -1) {
		perror("semget");
		exit(1); 
	}
	
	
	
	union semun mutex,freebuffer,loadedbuffer;
	mutex.val = 1;
	freebuffer.val = 3;
	loadedbuffer.val = 0;
	
	if (semctl(semid,0,SETVAL,mutex.val) == -1) {
		perror("semctl");
		exit(1); 
    	}
    	if (semctl(semid,1,SETVAL,freebuffer.val ) == -1) {
		perror("semctl");
		exit(1); 
    	}
    	if (semctl(semid,2,SETVAL,loadedbuffer.val) == -1) {
		perror("semctl");
		exit(1); 
    	}
	
	
	
	
	if (fork()==0){
	// producer *2
		fork();
		call_file("producer");
	
	}
	
	
	else{
	// consumer *3
		if(fork()==0){
			fork();
			call_file("consumer");
		}
		else{
			call_file("consumer");
		}
	
	
	}

 
}
