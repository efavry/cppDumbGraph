#include "graph.h"

using namespace std;

int main()
{
    graph *testG = new graph();
    node *a= new node(1);
    node *b= new node(2);
    testG->addNode(a);
    testG->addNode(b);
    testG->connectNode(a,b); //from a to b
    delete testG;
    return 0;
}

