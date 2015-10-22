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
    //NOT FINISHED
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

void graph::dfs()
{
    this->unmarkAll();
    this->dfsRec(this->first);
    for(node* m:this->listOfNodes) //for each unreached node we dfs it (yes the above line is usless
        this->dfsRec(m);
}

void graph::dfsRec(node* n)
{
    if(!n->isMarkedNode())
    {
        n->markNode();
        cout << "DFS : I'm " << n->uint_name << endl;
        for(node* m:n->edgesList)
                this->dfsRec(m);
    }
}

vector<vector<unsigned int>> graph::tarjan()
{
    int scc_id=0; //will be used to identify in wich strongly cinnected component the node belong
    this->unmarkAll();
    int tick =0;
    stack<node*> st;
    //this->tarjanRec(this->first,tick,st,scc_id);
    for(node* p : this->listOfNodes) //we search the node we did not traverse
        if(p->number<0)
            this->tarjanRec(p,tick,st,scc_id);

    /*Show the set of level*/


    /*******retrivieng the reduced graph****************/
    //will be refactored one day
    //first we need to count how many scc we have (COSTLY)
    int scc_max=0,i,j;
    for(node* n : this->listOfNodes)
        if(n->scc_mark > scc_max )
            scc_max=n->scc_mark;

    //now we have the count of scc but beware scc_id begin at 0 and therefore scc_mark also start at 0 so we correct this
    scc_max++;
    //we now have the size of the matrix, we can build it
    vector<vector<unsigned int>> matrix; //array<> is also a solution i think
    matrix.resize(scc_max);
    for (i=0; i<scc_max; ++i)
        matrix[i].resize(scc_max);
    for (j=0; j<scc_max; ++j)
        for (i=0; i<scc_max; ++i)
            matrix[i][j]=0;
    //now we calculate the new adj matrix
    for(node* n : this->listOfNodes)
    {
        for (node* m : n->edgesList)
        {
            if(n->scc_mark!=m->scc_mark)
                matrix[m->scc_mark][n->scc_mark]++; //matrix[i][j] i is the column so in a adjancecny matrix it's our target while j represent the point of departure
            //we use ++ because we can have seveeral path between scc (strongly connected componenet)
        }
    }

    cout << "Tarjan : reduced matrix is : \n";
    for (j=0; j<scc_max; ++j)
    {
        for (i=0; i<scc_max; ++i)
        {
            cout << matrix[i][j];
            cout << " ";
        }
        cout << endl;
    }
    return matrix;
}

void graph::tarjanRec(node* n, int &tick, stack<node*> &st,int &scc_id) //to ensure the unicity of the stack and the id we use ref and pointer
{
    n->number=tick; //the "time" of discovery
    n->numberA=tick; //the lowest time reachable
    tick++; //each tick refer to the tick of visit
    st.push(n);
    n->inStack=true;

    for(node* m:n->edgesList) //for each connected node of n
    {
        if(m->number==-1) //if m is not defined
        {
            this->tarjanRec(m,tick,st,scc_id);
            n->numberA = min(n->numberA,m->numberA); //on propage la valeur
        }
        else if (m->inStack) //if in the stack then update the value
        {
            n->numberA = min(n->numberA, m->number);
        }
    }
    if(n->numberA==n->number) //then n is a root
    {
        node* o;
        do
        {
          o=st.top();
          st.pop(); //on depile la stack car si numa=num on a trouvé un scc
          o->inStack=false;
          o->scc_mark=scc_id;
        }while(n->uint_name != o->uint_name);
        scc_id++; //when the scc is retrivied we update for a new scc
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

graph::~graph()
{
    while(!this->listOfNodes.empty())
    {
        delete this->listOfNodes.front();
        this->listOfNodes.pop_front();
    }
}
