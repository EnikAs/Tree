#include "tree.h"

FILE* log_file = fopen("logfile.txt", "w");

int VisitPrintFile(const Node* node, FILE* treefile)
{
    if (!node)
        return 0; // TODO Errors
    fprintf(treefile, "{");

    fprintf(treefile, "%s", node->data);
    if (node->left)
        VisitPrintFile(node->left, treefile);

    if (node->right)    
        VisitPrintFile(node->right, treefile);

    fprintf(treefile, "}");
    return 0;
}

int VisitDumpPrint(const Node* node)
{
    if (!node)
        return 0; // TODO Errors

    fprintf(log_file, "%d [label =\"%s\"];\n", node, node->data);
    if (node->left)
    {
        fprintf(log_file, "%d -> %d ;\n", node, node->left);
        VisitDumpPrint(node->left);    
    }

    if (node->right)
    {
        fprintf(log_file, "%d -> %d ;\n", node, node->right);
        VisitDumpPrint(node->right);
    }

    return 0;
}

int TreeDump (Node* node)
{
    fprintf(log_file, "digraph tree {\n");

    VisitDumpPrint(node);

    fprintf(log_file, "\n}");
    
    fclose(log_file);

    system ("\"C:/Program Files/Graphviz/bin/dot.exe\" -Tpng logfile.txt -o graph.png");
    
}

int SetNode (Node* node, telem_t value, Node* leftptr, Node* rightptr)
{
    node->data = (telem_t) calloc(strlen(value), sizeof(char));
    if (node->data == NULL)
    {
        assert(0 && "Calloc in SetNode ERROR!");
    }
    strcpy(node->data, value);
    node->left = leftptr;
    node->right = rightptr;
    return 0;
}

Tree* TreeReadFile (FILE* treefile)
{
    char* buffer = NULL;
    int buf_pos = 0;
    int buf_size = scanf_file_size(treefile);
    buffer = (char*) calloc(buf_size, sizeof(char));
    fread(buffer, sizeof(char), buf_size, treefile);
    Tree* tree = (Tree*) calloc(1, sizeof(Tree));
    Node* tmp_peak = (Node*) calloc(1, sizeof(Node));

    tree->peak = tmp_peak;
    buf_pos = 1;
    char tmp_str[MAX_STR_SIZE] = "";
    int tmp_str_elem = 0;
    while (buffer[buf_pos] <= 'z' && buffer[buf_pos] >= 'a' || buffer[buf_pos] == ' ')
    {
        tmp_str[tmp_str_elem] = buffer[buf_pos];
        tmp_str_elem += 1;
        buf_pos += 1;
    }
    tmp_peak->data = (char*) calloc(strlen(tmp_str), sizeof(char));
    strcpy(tmp_peak->data, tmp_str);
    TreeReadNode (buffer, tree->peak, &buf_pos);

    return tree;
}

int TreeReadNode (const char* buffer, Node* main_node, int* buf_pos)
{
    if (buffer[*buf_pos] == '{')
    {
        Node* tmp_left_node = (Node*) calloc(1, sizeof(Node));
        main_node->left = tmp_left_node;
        *buf_pos += 1;
        char tmp_str[MAX_STR_SIZE] = "";
        int tmp_str_elem = 0;
        while (buffer[*buf_pos] <= 'z' && buffer[*buf_pos] >= 'a' || buffer[*buf_pos] == ' ')
        {
            tmp_str[tmp_str_elem] = buffer[*buf_pos];
            tmp_str_elem += 1;
            *buf_pos += 1;
        }
        tmp_left_node->data = (char*) calloc(strlen(tmp_str), sizeof(char));
        strcpy(tmp_left_node->data, tmp_str);
        if (buffer[*buf_pos] == '{')
            TreeReadNode(buffer, tmp_left_node, buf_pos);
    }
    if (buffer[*buf_pos] == '}')
    {
        if (buffer[*buf_pos + 1] == '}')
            return 0;
        else
            *buf_pos += 1;
    }
    if (buffer[*buf_pos] == '{')
    {
        Node* tmp_right_node = (Node*) calloc(1, sizeof(Node));
        main_node->right = tmp_right_node;
        *buf_pos += 1;
        char tmp_str1[MAX_STR_SIZE] = "";
        int tmp_str_elem1 = 0;
        while (buffer[*buf_pos] <= 'z' && buffer[*buf_pos] >= 'a' || buffer[*buf_pos] == ' ')
        {
            tmp_str1[tmp_str_elem1] = buffer[*buf_pos];
            tmp_str_elem1 += 1;
            *buf_pos += 1;
        }
        tmp_right_node->data = (char*) calloc(strlen(tmp_str1), sizeof(char));
        strcpy(tmp_right_node->data, tmp_str1);
        if (buffer[*buf_pos] == '{')
            TreeReadNode(buffer, tmp_right_node, buf_pos);
    }
    if (buffer[*buf_pos] == '}')
    {
        if (buffer[*buf_pos + 1] == '}')
        {
            *buf_pos += 1;
            return 0;
        }
        else
            assert(0 && "ETO NEVEDOMOYA HUIRGA");
    }

    return 0;// END
}

size_t scanf_file_size (FILE* input_file)
{
    struct stat file;
    if ( fstat(fileno(input_file), &file ) == -1 )
    {
        printf("FILE READING ERROR");
        return EOF;
    }

    return file.st_size;
}
