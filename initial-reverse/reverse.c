#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

typedef struct node
{
    char *line;
    struct node *next;
} Node;

typedef Node *Head;

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

void insert(Head *head, Node *node)
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
        (*head) = node;
    }
}

void show(Head head, FILE *stream)
{
    if (head == NULL || stream == NULL)
    {
        return;
    }
    Node *p = head;
    while (p != NULL)
    {
        fprintf(stream, "%s", p->line);
        p = p->next;
    }
}

void clear(Head *node)
{
    while (*node != NULL)
    {
        if ((*node)->line != NULL)
        {
            free((*node)->line);
            (*node)->line = NULL;
        }
        (*node) = (*node)->next;
    }
}

bool is_same_file(const char *file1, const char *file2)
{
    char *p1 = strrchr(file1, '/');
    char *p2 = strrchr(file2, '/');
    if (p1 == NULL)
    {
        p1 = (char *)file1;
    }
    if (p2 == NULL)
    {
        p2 = (char *)file2;
    }
    if (strcmp(p1 + 1, p2 + 1) == 0)
    {
        return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    Head head = NULL;
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
            node = create(line);
            insert(&head, node);
            line = NULL;
            n = 0;
        }
        show(head, stdout);
        clear(&head);
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
        if (is_same_file(argv[1], argv[2]))
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }

        if ((fin = fopen(argv[1], "r")) != NULL)
        {
            while ((ret = getline(&line, &n, fin)) != -1)
            {
                node = create(line);
                insert(&head, node);
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
                fprintf(stderr, "Bad argument\n");
                clear(&head);
                fclose(fin);
                exit(1);
            }
            else
            {
                if ((fout = fopen(argv[2], "w+")) != NULL)
                {
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