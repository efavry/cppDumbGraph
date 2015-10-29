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

    //for tarjan
    void tarjanRec(node* n, int &tick, stack<node*> &st,int &scc_id);
    int countNumberOfScc();
    void printSccContent(int);
    vector<vector<unsigned int>> calculateNewAdjacencyMatrix(int scc_max);
    void printReducedMatrix(vector<vector<unsigned int>> matrix, int scc_max);

    //for longest path
    bool topologicalSortRec(node *n, list<node *> &l_sorted); //rec fct for the topologicla sort
    void printTopologicalSort(list<node *> &l_sorted);
    list<unsigned int> reconstructFromEnd(node*);
    void printLongestPath(list<unsigned int>, int);
    int findMaximumDistance(node *end_of_longestpath);

    graph();
    graph(const graph&);
public:
    graph(vector<vector<unsigned int>>,int);
    void addNode(node *);
    void connectNode(node *,node *);
    void dfs();
    vector<vector<unsigned int>>  tarjan();
    void longestPath();
    //graph constructReverse();
    void unmarkAll();
    list<node *> dijkstra(node* startPoint, node* toFind); //return the ordered path from start node to end node

    node* getFirst(){return this->first;}

    ~graph();
}
;


#endif // GRAPH_H
