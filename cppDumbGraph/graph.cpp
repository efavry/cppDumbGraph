#include "graph.h"

graph::graph(vector<vector<unsigned int>> matrix, int size)
{
    int i,j;
    node* temp[size]; //used temporary to construct the graph declared as an array of node pointers
    cout << "Creating graph from matrix \n";
    //first we create the nodes:
    for(i=0;i<size;++i)
    {
        temp[i]=new node(i);
        this->addNode(temp[i]);
    }
    for(i=0;i<size;++i)
        for(j=0;j<size;++j)
            if(matrix[i][j]>0) //then we have a edge
                this->connectNode(temp[j],temp[i]);
    cout << "end of creation of the graph\n";
    this->first=temp[0];
    this->unmarkAll();
}
void graph::addNode(node *n)
{
    cout << "Adding node \n";
    this->listOfNodes.push_back(n);
}

void graph::connectNode(node *from,node *to)
{//can be used later on to use edges defined by a class
    cout << "Connecting " << from->uint_name << "to" << to->uint_name << endl;
    from->addNeighbor(to);
}


void graph::unmarkAll()
{
    for(node* n : this->listOfNodes)
    {
        n->unmarkNode();
    }
}




list<node *> graph::dijkstra(node* startPoint, node* toFind) //as oposed to A* this algorithm always find with the lowest weight
{
    //the fact that our arc are not weighted simplify some things here
 //first we set all node to a weight of infinity
    for(node* n : this->listOfNodes)
        n->int_weightOfPath=INT_MAX;
    //excepted the startPoint
    startPoint->int_weightOfPath=0;
    //we mark the start point;
    startPoint->markNode();
    //cleaning the graph from the operatin we've just done
    this->unmarkAll();
    //this->cleanWeight TODO
    //this->cleanPredecessor TODO


}
/*
DFS (graphe G, sommet s)
{
  Marquer(s);
  POUR CHAQUE élément s_fils de Voisins(s) FAIRE
     SI NonMarqué(s_fils) ALORS
       DFS(G,s_fils);
     FIN-SI
  FIN-POUR
}*/

void graph::dfs(node* n)
{
    n->markNode();
    cout << "DFS : I'm " << n->uint_name << endl;
        for(node* m:n->edgesList)
        {
            if(!m->isMarkedNode())
            {
                this->dfs(m);
            }
        }
}

void graph::dijkstraRec(node* startPoint, node* toFind)
{
    //we look from the start point all the neigbours and for each of this neigbours we mark the weight we meet but (here the cost will always be one)
    for(node* y: startPoint->edgesList)
    {
        if(!y->isMarkedNode()) //if not marked then we mark, we set the predeccesors and the weight
        {
            y->markNode();
            y->predecessor=startPoint;
            y->int_weightOfPath=startPoint->int_weightOfPath+1/*weight of arc*/; //because our arc are not weighted, each arc have a weight of one
        }
    }

    //then we search the one in the edges list that must be elected
    for(node* y: startPoint->edgesList)
    {
        if(!y->isMarkedNode()) //if not marked then we mark, we set the predeccesors and the weight
        {
            y->markNode();
            y->predecessor=startPoint;
            y->int_weightOfPath=startPoint->int_weightOfPath+1/*weight of arc*/; //because our arc are not weighted, each arc have a weight of one
        }
    }
}

/*
list<node *> graph::detphFirstSearch(node* toFind)
{
    //TODO
}
*/
void graph::detphFirstSearchBegin(node* toFind)
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
            this->detphFirstSearchRec(y,open);
}

graph::~graph()
{
    while(!this->listOfNodes.empty())
    {
        delete this->listOfNodes.front();
        this->listOfNodes.pop_front();
    }
}
