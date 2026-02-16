#include <stdio.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;

void producer()
{
    static int item = 1;

    if (count == BUFFER_SIZE)
    {
        printf("Buffer full, Producer waiting...\n");
        return;
    }

    buffer[in] = item;
    printf("Producer produced: %d\n", item);
    item++;

    in = (in + 1) % BUFFER_SIZE;
    count++;
}

void consumer()
{
    int item;

    if (count == 0)
    {
        printf("Buffer empty, Consumer waiting...\n");
        return;
    }

    item = buffer[out];
    printf("Consumer consumed: %d\n", item);

    out = (out + 1) % BUFFER_SIZE;
    count--;
}

int main()
{
    int i;

    for (i = 0; i < 10; i++)
    {
        producer();
        consumer();
    }

    return 0;
}