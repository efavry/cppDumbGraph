#include "graph.h"

graph::graph()
{
}

graph::graph(const graph&)
{

}
void graph::addNode(int value)
{
    node * n = new node(value);
    this->listOfNodes.push_back(n);
}

void graph::connectNode(node *from,node *to)
{
    from->addNeighbor(to);
}
/*
graph graph::constructReverse() //TODO
{

}
*/
void graph::unmarkAll()
{
    for(node* n : this->listOfNodes)
    {
        n->unmarkNode();
    }
}

list<node *> graph::detphFirstSearch(node* tofind)
{

}

void graph::detphFirstSearchBegin(node* tofind)
{
    list<node *> open; //open = unvisited node
    this->unmarkAll();
    node* temp;
    for(node* n : this->listOfNodes)
    {
        open.push_back(n);
    }

    while(!open.empty()) //if open is not empty : ie of there is unvisited node
    {
        temp=open.back();
        open.pop_back();
        temp->markNode(); //more easy like this we avoid traversal of list two time
        for(node* w : temp->edgesList) //for each unmarked neigbor w
        {
            open.remove(w);
            if(!w->isMarkedNode())
                this->detphFirstSearchRec(w,&open);

        }
    }


}
void graph::detphFirstSearchRec(node* w, list<node*>*open)
{
    w->markNode();
    open->remove(w);
    for(node* y : w->edgesList)
        if(!y->isMarkedNode())  // for each unmarked neigbor do
            this->detphFirstSearchRec(y);
}

graph::~graph()
{
    while(!this->listOfNodes.empty())
    {
        delete this->listOfNodes.front();
        this->listOfNodes.pop_front();
    }
}
