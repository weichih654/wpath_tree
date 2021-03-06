#include <stdio.h>
#include <stdlib.h>
#include "path.h"
#include "node.h"
#include <string.h>
#include "common.h"

NODE* create_node (char* name)
{
    NODE* n = (NODE*) malloc (sizeof (NODE));
    RET_ON_NULL (n, NULL);
    int name_len = strlen (name);
    n->parent = NULL;
    n->child = NULL;
    n->next = NULL;
    n->type = NONE;
    n->level = 0;
    n->name = (char*) malloc (name_len + 1);
    RET_ON_NULL (n->name, NULL);
    strcpy (n->name, name);
    n->name[name_len] = '\0';
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

static void free_node (NODE* node)
{
    RET_ON_NULL (node, );
    FREE (node->name);
    FREE (node);
}

void free_tree (NODE* node)
{
    RET_ON_NULL (node, );
    NODE* n = node;
    while (n != NULL)
    {
        if (n->child != NULL)
        {
            free_tree (n->child);
            n->child = NULL;
        }
        NODE* _n = n;
        n = n->next;
        free_node (_n);
        _n = NULL;
    }
}

static int show_line (NODE* node, int check_level)
{
    NODE* n = node;
    while (n)
    {
        if (n->level == check_level + 1)
        {
            if (n->next != NULL)
                return 1; 
        }
        n = n->parent;
    }
    return 0;
}

void dump_node (NODE* node)
{
    NODE* n = node;
    int space_count = 4;
    while (n != NULL)
    {
        char space[MAX_PATH_LENGTH] = {};
        int i = 0;
        for (i = 0; i < n->level * space_count; ++i)
        {
            if (i % space_count == 0) // "|" or "├" or "└"
            {
                if (i == (n->level - 1) * space_count && n->next == NULL)
                {
                    strcat (space, "└");
                }
                else if (i == (n->level - 1) * space_count && n->next != NULL)
                {
                    strcat (space, "├");
                }
                else if (show_line (n, i / space_count))
                    strcat (space, "|");
                else
                    strcat (space, " ");
            }
            else // " " or "─"
            {
                if (i > (n->level - 1) * space_count && i < n->level * space_count - 1)
                {
                    strcat (space, "─");
                }
                else
                    strcat (space, " ");
            }
        }
        printf ("%s%s\n", space, n->name);
        if (n->child != NULL)
        {
            dump_node (n->child);
        }
        n = n->next;
    }
}
