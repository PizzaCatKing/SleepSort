
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <time.h>
pthread_mutex_t counter_mutex;

struct SleepInsertArgs {
	unsigned int volatile *counter;
	unsigned int **targetArray;
	const unsigned int *value;
};

void *sleepInsert(void *vargp) 
{
	struct SleepInsertArgs *args = (struct SleepInsertArgs *) vargp;
	struct timespec tim, tim2;

	tim.tv_sec = 0;
	tim.tv_nsec = 1000000 * *args->value;
	nanosleep(&tim, &tim2);
	
	pthread_mutex_lock (&counter_mutex);
	  
	(*args->targetArray)[*args->counter] = *args->value;	
	//printf("Done: %d %d %d\n", *args->value, (*args->targetArray)[*args->counter], *args->counter);
	*args->counter = ++*args->counter;
	
	pthread_mutex_unlock (&counter_mutex);
	pthread_exit(NULL);
} 


unsigned int* sleepSort(const unsigned int* input_array, const int input_array_size) {
	unsigned int volatile *counter = (unsigned int *) malloc(sizeof (unsigned int));
	*counter = 0;
	unsigned int *output_array = (unsigned int *) malloc(input_array_size * sizeof(unsigned int));
	pthread_t *thread_ids = (pthread_t *) malloc(input_array_size * sizeof(pthread_t));
	struct SleepInsertArgs *sleep_insert_args = (struct SleepInsertArgs *) malloc(input_array_size * sizeof(struct SleepInsertArgs));
	pthread_mutex_init(&counter_mutex, NULL);
	
	for (int i = 0; i < input_array_size; i++){		
		sleep_insert_args[i].counter = counter;
		sleep_insert_args[i].targetArray = &output_array;
		sleep_insert_args[i].value = &input_array[i];
		
		pthread_create(&thread_ids[i], NULL, sleepInsert, (void *)&sleep_insert_args[i]); 
	}

	for (int j = 0; j < input_array_size; j++){
		pthread_join(thread_ids[j], NULL);
	}
	
	
	free(thread_ids);
	free(sleep_insert_args);
	return output_array;
}

int main() 
{
	const int ARRAY_SIZE = 100;
	const unsigned int MAX_VALUE = 20;
	unsigned int *values = (unsigned int *)malloc(ARRAY_SIZE * sizeof(unsigned int));
	
	for(int i =0; i< ARRAY_SIZE; i++){
		values[i] = rand() % MAX_VALUE;
		printf("%d", values[i]);	
		if(ARRAY_SIZE -1 > i){
			printf(", ");
		}
		else{
			printf("\n");
		}
	}
	unsigned int *sortedValues = sleepSort(values, ARRAY_SIZE);
	
	for(int i =0; i< ARRAY_SIZE; i++){
		printf("%d", sortedValues[i]);
		if(ARRAY_SIZE -1 > i){
			printf(", ");
		}
		else{
			printf("\n");
		}
	}
	
	free(values);
	free(sortedValues);
	return 0;
}

