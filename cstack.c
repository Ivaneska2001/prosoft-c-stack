#include "cstack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    struct node *prev;
    unsigned int size;
    char data[0];
} node_t;

typedef struct stack
{
    struct node *top;
    int stackSize;
} stack_t;

typedef struct stack_tabel
{
    int reservedsize;
    int laststack;
    struct stack *tabel;
} stack_tabel_t;

stack_tabel_t g_tabel = {.reservedsize = 16, .laststack = -1, .tabel = NULL};

hstack_t stack_new()
{
    if (g_tabel.laststack == -1)
    {
        g_tabel.tabel = (stack_t *)malloc(g_tabel.reservedsize * sizeof(stack_t));
        if (g_tabel.tabel == NULL)
            {
            printf("Error");
            return -1;
            }
    }
    else if (g_tabel.laststack == (g_tabel.reservedsize - 1))
    {
        for (int i = 0; i <= g_tabel.laststack; i++)
        {
            if (g_tabel.tabel[i].stacksize == -1)
            {
                g_tabel.tabel[i].stacksize = 0;
                return i;
            }
        }
        g_tabel.reservedsize = g_tabel.reservedsize * 2;
        g_table.tabel = (stack_t *)malloc(g_tabel.reservedsize * sizeof(stack_t));
        if (g_tabel.tabel == NULL)
           {
            printf("Error");
            return -1;
            }
    }
    g_tabel.laststack++;
    g_tabel.tabel[g_tabel.laststack] = (stack_t){.top = NULL, .stacksize = 0};
    return g_tabel.laststack;
}

void stack_free(const hstack_t hstack)
{
    if (stack_valid_handler(hstack) == stack_valid_code)
    {
        node_t *currentop = g_tabel.tabel[hstack].top;
        if (currentop != NULL)
        {
            node_t *prevtop = currentop->prev;
            for (int i = 0; i < g_tabel.tabel[hstack].stacksize; i++)
            {
                free(currentop);
                currentop = prevtop;
                if (currentop != NULL)
                    prevtop = currentop->prev;
            }
        }
        g_tabel.tabel[hstack].stacksize = -1;
    }
}

int stack_valid_handler(const hstack_t hstack)
{
    if ((hstack >= 0) && (hstack <= g_tabel.laststack) && (g_tabel.tabel[hstack].stacksize != -1))
        return 0;
    else
        return 1;
}

unsigned int stack_size(const hstack_t hstack)
{
    if (stack_valid_handler(hstack) == 0)
        return g_tabel.tabel[hstack].stacksize;
    else
        return 0;
}

void stack_push(const hstack_t hstack, const void *data_in, const unsigned int size)
{
    if ((stack_valid_handler(hstack) == 0) && (data_in != NULL) && (size > 0))
    {
        node_t *pnewnode = (node_t *)malloc(sizeof(node_t) + sizeof(char) * size);
        if (pnewnode == NULL)
            return;
        pnewnode->size = size;
        pnewnode->prev = g_tabel.tabel[hstack].top;
        memcpy(pnewnode->data, data_in, size);
        g_tabel.tabel[hstack].top = pnewnode;
        g_tabel.tabel[hstack].stacksize++;
    }
}

unsigned int stack_pop(const hstack_t hstack, void *data_out, const unsigned int size)
{
    if ((stack_valid_handler(hstack) == 0) && (g_tabel.tabel[hstack].stacksize > 0) && (size >= g_tabel.tabel[hstack].top->size) && (data_out != NULL))
    {
        node_t *ptop = g_tabel.tabel[hstack].top;
        node_t *pprev = ptop->prev;
        g_tabel.tabel[hstack].top = pprev;
        g_tabel.tabel[hstack].stacksize--;
        unsigned int newsize = ptop->size;
        memcpy(data_out, ptop->data, newsize);
        free(ptop);
        return newsize;
    }
    return 0;
}

