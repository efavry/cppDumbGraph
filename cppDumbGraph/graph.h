#ifndef GRAPH_H
#define GRAPH_H

#include <includecentral.h>
#include <node.h>
class graph
{
private:
    node* first; //the first node where we will start our search
    list<node *> listOfNodes; //will usefull for unmark or things like that
    void detphFirstSearchBegin(node* tofind);
    void detphFirstSearchRec(node* w, list<node*>*open);
public:
    graph();
    graph(const graph&);
    void addNode(int value);
    void connectNode(node *,node *);
    graph constructReverse();
    void unmarkAll();
    list<node *> (node* startPoint, node* tofind); //return the ordered path from start node to end node
    list<node *> detphFirstSearch(node* tofind); //return the ordered path from start node to end node

    ~graph();
}
;


#endif // GRAPH_H
