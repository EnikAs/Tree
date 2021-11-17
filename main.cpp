#include "tree.h"

int main()
{
    /*
    Tree tree = {};
    Node a = {};
    Node b = {};
    Node c = {};
    Node d = {};
    Node e = {};
    Node f = {};
    Node g = {};
    char aa[] = "animal";
    char bb[] = "bboba";
    char cc[] = "cboba";
    char dd[] = "dboba";
    char ee[] = "eboba";
    char ff[] = "fboba";
    char gg[] = "gboba";
    SetNode(&a, aa, &b, &c);
    SetNode(&b, bb, &d, &e);
    SetNode(&c, cc, &f, &g);
    SetNode(&d, dd, NULL, NULL);
    SetNode(&e, ee, NULL, NULL);
    SetNode(&f, ff, NULL, NULL);
    SetNode(&g, gg, NULL, NULL);
    tree.peak = &a;

    FILE* treefile = fopen("tree.txt", "w");
    VisitPrintFile(tree.peak, treefile);
    fclose(treefile);*/
    FILE* treefile = fopen("tree.txt", "r");
    Tree tree1 = *(TreeReadFile(treefile));
    FILE* treefile1 = fopen("tree1.txt", "w");
    VisitPrintFile(tree1.peak, treefile1);
    TreeDump(tree1.peak);

}