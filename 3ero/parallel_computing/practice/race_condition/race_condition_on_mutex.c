#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int total_mails_per_thread = 10000000;
int mutex = 0;
int mails = 0;

void *routine()
{
    int i;
    for (i = 0; i < total_mails_per_thread; i++)
    {
        while (mutex)
        {
        }
        mutex = 1;
        mails++;
        mutex = 0;
    }
}

int main(int argc, char *argv[])
{
    int i;
    int number_of_threads = 10;
    pthread_t p[number_of_threads];

    for (i = 0; i < number_of_threads; i++)
    {
        pthread_create(&p[i], NULL, &routine, NULL);
    }
    for (i = 0; i < number_of_threads; i++)
    {
        pthread_join(p[i], NULL);
    }

    printf("Number of mails to be sent:    %d\n", total_mails_per_thread * number_of_threads);
    printf("Number of mails actually sent: %d\n", mails);
    return 0;
}