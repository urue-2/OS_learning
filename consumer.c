#include "pc.h"
;

int main(int argc , char *argv[]){
	printf("in consumer\n");
	
	key_t key,se_key;
	int shmid,semid;
	
	buffer_pointer data;
	

	
	// sephmore
	se_key = se_k;
	if ((semid = semget(se_key, 3, 0666 | IPC_CREAT)) == -1) {
		perror("semget");
		exit(1); 
	}

	
	// shared memory	
	key = sm_k;


	if ((shmid = shmget(key,SHM_SIZE,0644 | IPC_CREAT)) == -1){
	
		perror("shmget");
		exit(1);
	}
	
	data = (buffer_pointer)shmat(shmid ,(void *)0,0); 
	if ( data == (buffer_pointer)-1){
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}



	
	for (int i =0 ;i<4;i++){
	sleep(rand()%6);

	
	P("loadedbuffer",semid);
    	P("mutex",semid);
    	
    	int *tp = data;
	for (int i =0 ;i < sizeof(buffer)/sizeof(int);i++){
		if((*tp)!=0){
		*tp = 0 ;
		break;
		}
		tp++;
		
	}
	printf("after consume buffer now is  %d  %d  %d ,  %d  products	have been produced \n\n",data->p1,data->p2,data->p3,data->cur);
	
	V("mutex",semid);
	V("freebuffer",semid);
	}	
	
	
}
