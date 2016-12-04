#include <utils/ThreatUtils.h>
#include <stddef.h>
#include <pthread.h>

void ThreatUtils::startThreath(void *(*function)(void*), void* data) {
	pthread_t thread_id = (pthread_t) 0;
	pthread_attr_t attr;

	(void) pthread_attr_init(&attr);
	(void) pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread_id, &attr, function, data);
	pthread_attr_destroy(&attr);
}
