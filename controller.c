#include <stdlib.h>
#include <pthread.h>
#include "GPIOutils.c"
#include "UI/tuningUtils.c"

void interruptCom(void)
{
	runComBool = 0;
}

void main( int argc, char* argv[]){
	pthread_t com_thread_id;
	pthread_create(&com_thread_id, NULL, runCommunication, NULL);
	runUI(argc,argv);
	interruptCom();
    pthread_join(com_thread_id, NULL);
};
