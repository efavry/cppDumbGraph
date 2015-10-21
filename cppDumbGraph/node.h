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
    //this part of the member is used to store the predecesor and the value of the path
    int int_weightOfPath;
    node* predecessor;

public:
    node(unsigned int name);
    node (const node&); //copy constructor
    bool isMarkedNode();
    void markNode();
    void unmarkNode();
    void addNeighbor(node*);
    void depthFirsSearchRecursive(unsigned int name);
    //node &operator=(const node&); // operator =: not coded because WE WANT to comapre the adress of the pointer
    ~node(); //detructor
}
;




#endif // NODE_H
