#include <dirent.h>
#include <unistd.h>  
#include <sys/stat.h>
#include "path.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include "node.h"

static NODE* root_node;

static int create_folder_tree (NODE* parent, char* path)
{  
    DIR *dp = NULL;  
    struct dirent *entry = NULL;  
    struct stat statbuf;  

    LOG ("enter new path = %s\n", path);
    if ((dp = opendir(path)) == NULL) {  
        LOG ("Can`t open directory %s\n", path);  
        return ;  
    }  

    NODE* entry_node = create_node (path);
    entry_node->type = D;
    if (parent != NULL)
    {
        entry_node->level = parent->level + 1;
        entry_node->parent = parent;
        append_child (parent, entry_node);
    }
    else
        root_node = entry_node;

    chdir(path);  

    while ((entry = readdir(dp)) != NULL) 
    {
        lstat(entry->d_name, &statbuf);  
        if (S_ISDIR(statbuf.st_mode)) 
        {
            if (strcmp(entry->d_name, ".") == 0 ||   
                    strcmp(entry->d_name, "..") == 0 )    
                continue;     
            LOG ("dir = %s\n", entry->d_name);

            create_folder_tree (entry_node, entry->d_name);
        } 
        else  
        {
            NODE* entry_child_node = create_node (entry->d_name);
            entry_child_node->level = entry_node->level + 1;
            entry_child_node->parent = entry_node;
            entry_child_node->type = F;
            append_child (entry_node, entry_child_node);
            LOG ("file = %s\n", entry->d_name);
        }
    }  
    LOG ("Leaving path %s\n", path);
    chdir("..");  
    closedir(dp);     
}  

int create_tree (char* path)
{
    create_folder_tree (NULL, path);
    dump_node (root_node);
}

