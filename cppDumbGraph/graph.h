#ifndef GRAPH_H
#define GRAPH_H

#include <includecentral.h>
#include <node.h>
class graph //in fact it is a digraph
{
private:
    node* first; //the first node where we will start our search
    list<node *> listOfNodes; //will usefull for unmark or things like that
    void dfsRec(node* n);
    void dijkstraRec(node* startPoint, node* toFind);
    void tarjanRec(node* n, int &tick, stack<node*> &st,int &scc_id);
    graph();
    graph(const graph&);
public:
    graph(vector<vector<unsigned int>>,int);
    void dfs();
    vector<vector<unsigned int>>  tarjan();
    void addNode(node *);
    void connectNode(node *,node *);
    graph constructReverse();
    void unmarkAll();
    list<node *> dijkstra(node* startPoint, node* toFind); //return the ordered path from start node to end node

    node* getFirst()
    {
        return this->first;
    }

    ~graph();
}
;


#endif // GRAPH_H
