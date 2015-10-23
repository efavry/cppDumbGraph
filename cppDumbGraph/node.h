#ifndef NODE_H
#define NODE_H
#include <includecentral.h>
class node
{//TODO : CLear inconsistent naming
private:
    friend class graph;
    unsigned int uint_name;
    bool b_mark;
    list<node*> edgesList;
    //list<node*> parentList; //more easy for the longest path problem to have this
    //this part of the member is used to store the predecesor and the value of the path
    //int int_weightOfPath;
    node* predecessor;

    //used for tarjan
    int number; //when the node is visited
    int numberA; //will decrease
    bool inStack;
    int scc_mark; //define the scc where he belong

    //for topological sort
    bool b_tempMark;

    //for longest path
    int dist; //(0 by default)
    node (const node&); //copy constructor
public:
    node(unsigned int name);

    bool isMarkedNode();
    void markNode();
    void unmarkNode();
    void addNeighbor(node*); //more like add son
    //void addParent(node * n);
    void depthFirsSearchRecursive(unsigned int name);
    //node &operator=(const node&); // operator =: not coded because WE WANT to comapre the adress of the pointer
    ~node(); //detructor
}
;




#endif // NODE_H
