#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "pqueue.h"
#include <time.h>
#include <stdlib.h>

char *filename = "queue.dat";
pqueue *qu = NULL;
int itemId = 0;

typedef struct item item;
struct item {
	int id;
};


int isValid(int k){
    
    for (pqueue *curr = qu; curr != NULL; curr = curr->next){
        if(((item*)(curr->data))->id == k){
           return 1;
        }
    }

    return 0;
}
void
print_process(void *data) {
	item *pr = (item *)data;
	printf("%d", pr->id);
}

item* produce() {
	int time = rand() % 5 + 1;
	item *it = (item *)malloc(sizeof(item));
	
	sleep(time);
	it->id = itemId;
	itemId += 1;
	return it;
}

void consume(item *it) {
	int time = rand() % 5 + 1;
	//sleep(time);
	free(it);
}


void producer(pid_t childPid) {

        int randK = rand()%5;
        qinsert(&qu, produce(), randK);  
        printf("Produced product %d \n", randK);
        if (qu == NULL)
            printf("queue is null! \n");

    
}
void
consumer() {
}

int
main(int argc, char **argv) {
	pid_t pid;
	srand(time(NULL)); 


    int order [] = {1, 2, 3, 4};
    qserialize(qu, sizeof(item), filename);
    
    pid = fork();

    //producer
    if(pid == 0){
        while(1){
            qunserialize(&qu, sizeof(item), filename);

            producer(pid);
        
            if (qu == NULL)
                printf("null po pierwszym watku \n");

            qserialize(qu, sizeof(item), filename);
        }
    }
    else{

        while(1){
            //waiting for producer thread 
            //waitpid(pid , NULL , 0);
            qunserialize(&qu, sizeof(item), filename);

          
                int randK = rand()%5;
                if(isValid(randK)){
                    qremove(&qu, randK);
                    printf("consuming product %d \n", randK);
                    sleep(2);
                    //qlist(qu, print_process);
                }
                else{
                    printf("no such product");
                      sleep(2);
                }
                //miss, waiting for producer
                //continue;
                //consume(qpop(&qu)->data);
                
            
            qserialize(qu, sizeof(item), filename);

        }
    }

	return 0;
}

