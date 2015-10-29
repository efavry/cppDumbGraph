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
    this->listOfNodes.push_back(n);
}

void graph::connectNode(node *from,node *to)
{//can be used later on to use edges defined by a class
    cout << "Connecting " << from->uint_name << "to" << to->uint_name << endl;
    from->addNeighbor(to);
    //to->addParent(from);
}


void graph::unmarkAll()
{
    for(node* n : this->listOfNodes)
        n->unmarkNode();
}





void graph::dfs()
{
    this->unmarkAll();
    this->dfsRec(this->first);
    for(node* m:this->listOfNodes) //for each unreached node we dfs it (yes the above line is usless)
        this->dfsRec(m);
}

void graph::dfsRec(node* n)
{
    if(!n->isMarkedNode())
    {
        n->markNode();
        cout << "DFS : I'm " << n->uint_name << endl;
        for(node* m:n->l_successors)
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
        if(p->int_number<0)
            this->tarjanRec(p,tick,st,scc_id);

    /*******retrivieng the reduced graph****************/
    //will be refactored one day
    //first we need to count how many scc we have (COSTLY)
    int scc_max=0,i;
    for(node* n : this->listOfNodes)
        if(n->int_scc_mark  > scc_max )
            scc_max=n->int_scc_mark ;

    //now we have the count of scc but beware scc_id begin at 0 and therefore scc_mark also start at 0 so we correct this
    scc_max++;
    //we now have the size of the matrix, we can build it but before that we must a question :
    //we show a set of level
    for(i=0;i<scc_max;++i)
    {
      cout << "{";
      for(node *toShow : this->listOfNodes)
      {
          if(toShow->int_scc_mark  == i)
          {
            cout << toShow->uint_name;
            if(toShow != this->listOfNodes.back())
                cout << ",";
          }
      }
        cout << "}";
    }
    cout << endl;

    vector<vector<unsigned int>> matrix = this->calculateNewAdjacencyMatrix(scc_max);
    this->printReducedMatrix(matrix,scc_max);
    return matrix;
}

vector<vector<unsigned int>> graph::calculateNewAdjacencyMatrix(int scc_max)
{
    int i,j;
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
        for (node* m : n->l_successors)
        {
            if(n->int_scc_mark !=m->int_scc_mark ) //remove the self loop
                matrix[m->int_scc_mark ][n->int_scc_mark ]++; //matrix[i][j] i is the column so in a adjancecny matrix it's our target while j represent the point of departure
            //we use ++ because we can have seveeral path between scc (strongly connected componenet)
        }
    }
    return matrix;
}

void graph::printReducedMatrix(vector<vector<unsigned int>> matrix, int scc_max)
{
    int j=0,i=0;
    cout << "Tarjan : reduced matrix is (beware the loop to the self scc is not noted): \n";
    for (j=0; j<scc_max; ++j)
    {
        for (i=0; i<scc_max; ++i)
        {
            cout << matrix[i][j];
            cout << " ";
        }
        cout << endl;
    }
}
void graph::tarjanRec(node* n, int &tick, stack<node*> &st,int &scc_id) //to ensure the unicity of the stack and the id we use ref and pointer
{
    n->int_number=tick; //the "time" of discovery
    n->int_numberA=tick; //the lowest time reachable
    tick++; //each tick refer to the tick of visit
    st.push(n);
    n->b_inStack=true;

    for(node* m:n->l_successors) //for each connected node of n
    {
        if(m->int_number==-1) //if m is not defined
        {
            this->tarjanRec(m,tick,st,scc_id);
            n->int_numberA = min(n->int_numberA,m->int_numberA); //on propage la valeur
        }
        else if (m->b_inStack) //if in the stack then update the value
        {
            n->int_numberA = min(n->int_numberA, m->int_number);
        }
    }
    if(n->int_numberA==n->int_number) //then n is a root
    {
        node* o;
        do
        {
          o=st.top();
          st.pop(); //on depile la stack car si numa=num on a trouvé un scc
          o->b_inStack=false;
          o->int_scc_mark =scc_id;
        }while(n->uint_name != o->uint_name);
        scc_id++; //when the scc is retrivied we update for a new scc
    }

}

void graph::longestPath() //BEWARE MUST BE DONE ON A ACYCLIC DI-GRAPH
{
    this->unmarkAll();
    //because we have a dag we can do a topological sort and search with it
    //tarjan made an easy to implement algorithm to do the topological sort
    list<node *> l_sorted; //will store the sorted node
    bool unmarked_node_exist=true;
    node* elected_node=this->first; //when we find an unmarked node the pointer will be stored here for the next iteration of the while to be used for the call of traverse
    cout << "Topological Sort : Starting \n";
    while(unmarked_node_exist) //ugly incomming !
    {

        if(this->topologicalSortRec(elected_node,l_sorted)==false)
        {
            cout << "Topological Sort : ERROR : NOT A DAG ! ABORTING \n";
            return;
        }
        unmarked_node_exist=false;
        for(node *n:this->listOfNodes) //told ya
            if(!n->isMarkedNode())
            {
                unmarked_node_exist=true;
                elected_node=n;
            }
    }

    this->printTopologicalSort(l_sorted);

    //for each node p of the sorted list we search wich node is the farthest from p
    for (node *p:l_sorted)
        for (node *o:p->l_successors)
            if (o->int_dist <= p->int_dist +1) //the weight of our edge is always 1 so +1
            {
                o->int_dist=p->int_dist+1;
                o->predecessor=p;
            }

    //we traverse the graph to find the higest distance
    node *end_of_longestpath=NULL;
    int max_dist=0;
    max_dist=this->findMaximumDistance(end_of_longestpath);

    //then from the end_of_longestpath we get each of his predecessors and we show the result while popping the stach (a list here, yes a list...)
    this->printLongestPath(this->reconstructFromEnd(end_of_longestpath),max_dist);
    this->unmarkAll();
}

int graph::findMaximumDistance(node *end_of_longestpath=NULL)
{
    int max_dist=0;
    for(node *v:this->listOfNodes)
        if(v->int_dist>max_dist)
        {
            max_dist=v->int_dist;
            end_of_longestpath=v;
        }
    return max_dist;
}

//return false if not a dag
bool graph::topologicalSortRec(node *n, list<node *> &l_sorted)
{
    if(n->b_tempMark) //flemme to do accessors
        return false; //if it is marked temporarly then it was also a n in a upper call of traverse, there fore we hav a cycle

    if(!n->isMarkedNode())
    {
        n->b_tempMark=true;
        for(node *m:n->l_successors)
            this->topologicalSortRec(m,l_sorted); //for each child of n we call recursivly
        n->markNode(); //we mark the node n because all operation are finished with him
        n->b_tempMark=false; //
        l_sorted.push_front(n); //we add n to the list of sorted node
    }
    return true;
}

void graph::printTopologicalSort(list<node *> &l_sorted)
{
    cout << "Topological Sort : Sorted list is : ";
    for(node *m:l_sorted)
        cout << m->uint_name << ";";
    cout << "\n";
}

list<unsigned int> graph::reconstructFromEnd(node *end_of_longestpath)
{
    list<unsigned int> path;
    while(end_of_longestpath->predecessor != NULL)
    {
        path.push_back(end_of_longestpath->uint_name);
        end_of_longestpath=end_of_longestpath->predecessor;
        for(unsigned int to_test:path)
            if(to_test == end_of_longestpath->uint_name)
                end_of_longestpath->predecessor=NULL;
    }
    return path;
}

void graph::printLongestPath(list<unsigned int> path, int max_dist)
{
    cout<< "A longest path is found of size "<< max_dist << ": " << endl;
    while(!path.empty())
    {
        cout<< path.back() << ";";
        path.pop_back();
    }
    cout<< endl;
}

graph::~graph()
{
    while(!this->listOfNodes.empty())
    {
        delete this->listOfNodes.front();
        this->listOfNodes.pop_front();
    }
}
