#include <stdlib.h>
#include <pthread.h>
#include "GPIOutils.c"

void interruptCom(void)
{
	runComBool = 0;
}

void main(){
	pthread_t com_thread_id;
	pthread_create(&com_thread_id, NULL, runCommunication, NULL);
	delay(1000);
	interruptCom();
	pthread_join(com_thread_id, NULL);
	//runCommunication();
};
