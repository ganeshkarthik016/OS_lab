#include <stdio.h>

int readcount = 0;
int writer = 0;   // 0 = free, 1 = writing

void reader(int id)
{
    if (writer)
    {
        printf("Reader %d waiting (writer active)\n", id);
        return;
    }

    readcount++;
    printf("Reader %d is reading\n", id);

    readcount--;
    printf("Reader %d finished reading\n", id);
}

void writer_func()
{
    if (readcount > 0 || writer)
    {
        printf("Writer waiting\n");
        return;
    }

    writer = 1;
    printf("Writer is writing\n");

    writer = 0;
    printf("Writer finished writing\n");
}

int main()
{
    reader(1);
    reader(2);
    writer_func();
    reader(3);
    writer_func();

    return 0;
}