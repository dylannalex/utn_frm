#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int total_mails_per_thread = 100000000;
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
    pthread_t p1, p2;

    pthread_create(&p1, NULL, &routine, NULL);
    pthread_create(&p2, NULL, &routine, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Number of mails to be sent:    %d\n", total_mails_per_thread * 2);
    printf("Number of mails actually sent: %d\n", mails);
    return 0;
}