#include <node.h>
node::node(unsigned int name)
{
    this->uint_name= i;
}

bool node::isMarkedNode()
{
    return this->mark;
}
void node::markNode()
{
    this->mark=true;
}
void node::unmarkNode()
{
    this->mark=false;
}
void node::addNeighbor(node * n)
{
    this->edgesList.push_back(n);
}


node::~node()
{

}
