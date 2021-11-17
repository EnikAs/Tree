#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include <iostream>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cassert>
#include <sys\stat.h>

typedef char* telem_t;

const int MAX_STR_SIZE = 1000;

#define PRINT_LINE printf("I'm at line %d at function %s\n", __LINE__, __func__);

struct Node
{
    Node* left = NULL;
    Node* right = NULL;
    telem_t data = NULL;
};

struct Tree
{
    Node* peak = NULL;

};

int VisitPrintFile(const Node* node, FILE* treefile);

int VisitDumpPrint(const Node* node);

int TreeDump (Node* node);

int SetNode (Node* node, telem_t value, Node* leftptr, Node* rightptr);

Tree* TreeReadFile (FILE* treefile);

int TreeReadNode (const char* buffer, Node* main_node, int* buf_pos);

size_t scanf_file_size (FILE* input_file);

#endif