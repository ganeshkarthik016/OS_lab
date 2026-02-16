 #include <stdio.h>

int fork[5] = {1, 1, 1, 1, 1};
int room = 4;

void wait(int *S)
{
    while (*S <= 0);
    (*S)--;
}

void signal(int *S)
{
    (*S)++;
}

void philosopher(int i)
{
    printf("Philosopher %d is THINKING\n", i + 1);

    wait(&room);
    wait(&fork[i]);
    wait(&fork[(i + 1) % 5]);

    printf("Philosopher %d is EATING\n", i + 1);

    signal(&fork[i]);
    signal(&fork[(i + 1) % 5]);

    signal(&room);
}

int main()
{
    int i;
    for (i = 0; i < 5; i++)
        philosopher(i);
    return 0;
}