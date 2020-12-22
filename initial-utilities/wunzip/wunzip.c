#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }
    int n = 0;
    char c = '\0';
    for (size_t i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp != NULL)
        {
            while (true)
            {
                fread(&n, sizeof(int), 1, fp);
                if (ferror(fp) || feof(fp))
                {
                    break;
                }

                fread(&c, sizeof(char), 1, fp);
                if (ferror(fp) || feof(fp))
                {
                    break;
                }

                for (size_t j = 0; j < (int)n; j++)
                {
                    fprintf(stdout, "%c", c);
                }
            }
            fclose(fp);
        }
    }
    return 0;
}
