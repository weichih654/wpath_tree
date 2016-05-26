#ifndef NODE_HEADER
#define NODE_HEADER
#define MAX_PATH_LENGTH 4096
typedef enum {
    NONE = 0,
    D,
    F,
} TYPE;

typedef struct node
{
    char* name;
    struct node* parent;
    struct node* child;
    struct node* next;
    int level;
    TYPE type;
} NODE;

NODE* create_node (char* name);
void dump_node (NODE* node);
#endif //NODE_HEADER
