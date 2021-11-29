#ifndef   __PC_h__
#define   __PC_h__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
 
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <errno.h> 

#define SHM_SIZE 1024
#define sm_k 1111
#define se_k 1112



union semun {
	int val;
};

static int P(char x[],int semid){
	//printf("into P %s\n",x);
	
	struct sembuf se_op;
	if  (strcmp(x,"mutex")==0)
		se_op.sem_num = 0;
	if  (strcmp(x,"freebuffer")==0)
		se_op.sem_num = 1;
	if  (strcmp(x,"loadedbuffer")==0)
		se_op.sem_num = 2;
	//printf("cur sem index %d\n",se_op.sem_num);
	se_op.sem_op = -1;
	se_op.sem_flg = 0;
	if (semop(semid, &se_op, 1) == -1){ 
		perror("semop");
		exit(1); 
    	}
    	
    	//printf("got %s \n",x);

}

static int V(char x[],int semid){
	//printf("into V %s\n",x);
	
	struct sembuf se_op;
	if  (strcmp(x,"mutex")==0)
		se_op.sem_num = 0;
	if  (strcmp(x,"freebuffer")==0)
		se_op.sem_num = 1;
	if  (strcmp(x,"loadedbuffer")==0)
		se_op.sem_num = 2;
	
	//printf("cur sem index %d\n",se_op.sem_num);
	se_op.sem_op = 1;
	se_op.sem_flg = 0;
	if (semop(semid, &se_op, 1) == -1){ 
		perror("semop");
		exit(1); 
    	}
    	
    	//printf("drop %s \n",x);

}

struct _buffer{
	int p1,p2,p3;
	int cur;
};

typedef struct _buffer buffer;
typedef struct _buffer* buffer_pointer; 




#endif
