#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *ptr = NULL;
    size_t n = 0;
    if (argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }
    else if (argc == 2)
    {
        while (getline(&ptr, &n, stdin) != -1)
        {
            if (strstr(ptr, argv[1]) != NULL)
            {
                printf("%s", ptr);
            }
        }
        free(ptr);
        return 0;
    }

    for (int i = 2; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wgrep: cannot open file\n");
            return 1;
        }
        while (getline(&ptr, &n, fp) != -1)
        {
            if (strstr(ptr, argv[1]) != NULL)
            {
                printf("%s", ptr);
            }
        }
        free(ptr);
        fclose(fp);
    }
    return 0;
}
