#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_milisec()
{
    srand(time(NULL));
    return rand() % 1000 + 1;
}

void type_one_process(int instance)
{
    int sleep_time = random_milisec();
    usleep(sleep_time);
    printf("[TYPE 1] instance n°%d\tsleep time: %d\n", instance, sleep_time);
}

void type_two_process(int instance)
{
    int sleep_time = random_milisec();
    usleep(sleep_time);
    printf("[TYPE 2] instance n°%d\tsleep time: %d\n", instance, sleep_time);
}

int get_number_of_processes(int process_type)
{
    int n;
    printf("Enter number of Type %d processes: ", process_type);
    scanf("%d", &n);
    return n;
}

int main(int argc, char **argv)
{
    int n = get_number_of_processes(1);
    int m = get_number_of_processes(2);
    int status = 0;
    int id = -1;
    int i;

    // Type 1 processes
    for (i = 0; i < n; i++)
    {
        if (id = fork() == 0)
        {
            type_one_process(i + 1);
            return 0;
        }
    }

    // Type 2 processes
    for (i = 0; i < m; i++)
    {
        if (fork() == 0)
        {
            type_two_process(i + 1);
            return 0;
        }
    }

    while ((wait(&status)) > 0)
        ;
    return 0;
}
