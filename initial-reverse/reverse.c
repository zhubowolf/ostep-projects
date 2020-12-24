#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct node
{
    char *line;
    struct node *next;
} Node;

Node *create(char *line)
{
    Node *node = NULL;
    if (line == NULL)
    {
        return node;
    }
    node = malloc(sizeof(Node));
    if (node == NULL)
    {
        fprintf(stderr, "malloc failed");
        exit(1);
    }
    node->line = line;
    node->next = NULL;
    return node;
}

void insert(Node **head, Node *node)
{
    if (node == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = node;
    }
    else
    {
        node->next = *head;
        (*head)->next = node;
    }
}

void show(Node *head, FILE *stream)
{
    if (head == NULL || stream == NULL)
    {
        return;
    }
    Node *p = head;
    // fprintf(stream, "in output\n");
    while (p != NULL)
    {
        // fprintf(stream, "in output\n");
        fprintf(stream, "%s", p->line);
        p = p->next;
    }
}

void clear(Node **node)
{
    if (*node == NULL)
    {
        return;
    }
    if ((*node)->line != NULL)
    {
        free((*node)->line);
        (*node)->line = NULL;
    }
    clear(&((*node)->next));
    (*node)->next = NULL;
    *node = NULL;
}

int main(int argc, char const *argv[])
{
    Node *head = NULL;
    Node *node = NULL;
    char *line = NULL;
    size_t n = 0;
    int ret = 0;
    FILE *fin = NULL;
    FILE *fout = NULL;
    if (argc == 1)
    {
        while ((ret = getline(&line, &n, stdin)) != -1)
        {
            fprintf(stdout, "%s", line);
        }
    }
    else if (argc == 2)
    {
        if ((fin = fopen(argv[1], "r")) != NULL)
        {
            while ((ret = getline(&line, &n, fin)) != -1)
            {
                insert(&head, create(line));
            }
            if (ferror(fin))
            {
                fprintf(stderr, "malloc failed");
                fclose(fin);
                clear(&head);
                exit(1);
            }
            fclose(fin);
            show(head, stdout);
            clear(&head);
        }
        else
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }
    else if (argc == 3)
    {
        char *p1 = strrchr(argv[1], '/');
        char *p2 = strrchr(argv[2], '/');
        if (p1 == NULL)
        {
            p1 = (char *)argv[1];
        }
        if (p2 == NULL)
        {
            p2 = (char *)argv[2];
        }
        if (strcmp(p1 + 1, p2 + 1) == 0)
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        if ((fin = fopen(argv[1], "r")) != NULL)
        {
            while ((ret = getline(&line, &n, fin)) != -1)
            {
                node = create(line);
                // fprintf(stderr, "in main\n");
                // fprintf(stderr, "%s", line);
                insert(&head, node);
                // show(head, stderr);
                // fprintf(stderr, "in main\n");
                line = NULL;
                n = 0;
            }
            if (errno == ENOMEM)
            {
                fprintf(stderr, "malloc failed");
                clear(&head);
                fclose(fin);
                exit(1);
            }
            else if (errno == EINVAL)
            {
                fprintf(stderr, "%s\n", argv[1]);
                fprintf(stderr, "%s\n", argv[2]);
                fprintf(stderr, "%s\n", p1 + 1);
                fprintf(stderr, "%s\n", p2 + 1);
                fprintf(stderr, "%s\n", line);
                fprintf(stderr, "%s\n", head == NULL ? "NULL" : "not NULL");
                fprintf(stderr, "Bad argument\n");
                clear(&head);
                fclose(fin);
                exit(1);
            }
            else
            {
                if ((fout = fopen(argv[2], "w+")) != NULL)
                {
                    fprintf(stderr, "fout opened\n");
                    show(head, fout);
                    clear(&head);
                    fclose(fout);
                    fclose(fin);
                }
                else
                {
                    fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
                    clear(&head);
                    fclose(fin);
                    exit(1);
                }
            }
        }
        else
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }
    else
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    return 0;
}