#include <stdio.h>

#define BUF_LEN 256

int main(int argc, char const *argv[])
{
    char buffer[BUF_LEN] = {0};
    if (argc < 2)
    {
        return 0;
    }
    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            return 1;
        }
        while (fgets(buffer, BUF_LEN, fp) != NULL)
        {
            printf("%s", buffer);
        }
        fclose(fp);
    }
    return 0;
}
