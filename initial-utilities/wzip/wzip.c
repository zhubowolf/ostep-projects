#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }
    int n = 0;
    char new = '\0', old = '\0';
    for (size_t i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp != NULL)
        {
            while ((new = fgetc(fp)) != EOF)
            {
                if (old != new)
                {
                    if (old != '\0')
                    {
                        fwrite(&n, sizeof(int), 1, stdout);
                        fwrite(&old, sizeof(char), 1, stdout);
                    }
                    old = new;
                    n = 1;
                }
                else
                {
                    n++;
                }
            }
            fclose(fp);
        }
    }
    if (old != '\0')
    {
        fwrite(&n, sizeof(int), 1, stdout);
        fwrite(&old, sizeof(char), 1, stdout);
    }
    return 0;
}
