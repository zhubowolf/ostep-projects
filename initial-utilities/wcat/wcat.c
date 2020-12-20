#include <stdio.h>
// #include <errno.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        // printf("usage: wcat [file1] [file2]...");
        return 0;
    }
    for (int i = 1; i < argc; i++)
    {
        int c;
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            return 1;
        }
        while ((c = fgetc(fp)) != EOF)
        {
            printf("%c", c);
        }
        fclose(fp);
    }
    return 0;
}
