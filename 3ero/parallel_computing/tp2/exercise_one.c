#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int random_milisec()
{
    return rand()%1000 + 1;
}

void *type_one_thread(void *vargp)
{
    int instance = *((int *) vargp);
    int sleep_time = random_milisec();
    usleep(sleep_time);
	printf("[TYPE 1] instance n°%d\tsleep time: %d\n", instance, sleep_time);
    free(vargp);
}

void *type_two_thread(void *vargp)
{
    int instance = *((int *) vargp);
    int sleep_time = random_milisec();
    usleep(sleep_time);
	printf("[TYPE 2] instance n°%d\tsleep time: %d\n", instance, sleep_time);
    free(vargp);
}

int get_number_of_threads(int thread_type){
    int n;
    printf("Enter number of Type %d threads: ", thread_type);
    scanf("%d",&n);
    return n;
}


int main(int argc, char **argv)
{
    int n = get_number_of_threads(1);
    int m = get_number_of_threads(2);
    int i;

    // threads id:
    pthread_t type_one_thr[n];
    pthread_t type_two_thr[m];
    
    // Create threads
    for (i = 0; i < n; i++){
        int* instance = malloc(sizeof(int));
        *instance = i; 
        pthread_create(&type_one_thr[i], NULL, *type_one_thread, instance);
    }

    for (i = 0; i < m; i++){
        int* instance = malloc(sizeof(int));
        *instance = i; 
        pthread_create(&type_two_thr[i], NULL, *type_two_thread, instance);
    }

    // Join threads
    for (i = 0; i < n; i++){
        pthread_join(type_one_thr[i], NULL);
    }
    for (i = 0; i < m; i++){
        pthread_join(type_two_thr[i], NULL);
    }

    return 0;
}
