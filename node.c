#include <stdio.h>
#include <stdlib.h>
#include "path.h"
#include "node.h"
#include <string.h>
#include "common.h"

NODE* create_node (char* name)
{
    NODE* n = (NODE*) malloc (sizeof (NODE));
    n->parent = NULL;
    n->child = NULL;
    n->next = NULL;
    n->type = NONE;
    n->level = 0;
    strcpy (n->name, name);
    return n;
}

void append_child (NODE* parent, NODE* child)
{
   RET_ON_NULL (parent, ); 
   RET_ON_NULL (child, ); 
   if (parent->child == NULL)
   {
       parent->child = child;
       return;
   }

   NODE* p_child = parent->child;
   NODE* priv = NULL;
   while (p_child != NULL)
   {
       priv = p_child;
       p_child = p_child->next;
   }
   priv->next = child;
}

void get_full_path (NODE* leaf_node, char* fullpath, int path_len)
{
    char path [path_len];
    NODE* n = leaf_node;
    int is_first = 1;
    while (n)
    {
        char p [path_len];
        if (is_first == 1)
            sprintf (p, "%s", n->name);
        else
            sprintf (p, "%s/%s", n->name, path);
        strcpy (path, p);
        is_first = 0;
        n = n->parent;
    }
    path [strlen(path)] = '\0';
    strcpy (fullpath, path);
}

void dump_node (NODE* node)
{
    NODE* n = node;
    while (n != NULL)
    {
        char* space = NULL;
        space = (char*) malloc ((n->level) * 4);
        RET_ON_NULL (space, );
        int i = 0;
        for (i = 0; i < n->level * 4; ++i)
        {
            space [i] = ' ';
        }
        space [n->level * 4] = '\0';
        char fullpath [2048] = {};
        get_full_path (n, fullpath, sizeof (fullpath));
        LOG ("%s[%s]%s -> ", space, (n->type == D) ? "D" : "F", n->name);
        LOG_RED ("%s\n", fullpath);
        free (space);
        if (n->child != NULL)
        {
            dump_node (n->child);
        }
        n = n->next;
    }
}
