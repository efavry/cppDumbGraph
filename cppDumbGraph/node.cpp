#include <node.h>
node::node(unsigned int name)
{
    this->uint_name= name;
}

bool node::isMarkedNode()
{
    return this->b_mark;
}
void node::markNode()
{
    this->b_mark=true;
}
void node::unmarkNode()
{
    this->b_mark=false;
}
void node::addNeighbor(node * n)
{
    this->edgesList.push_back(n);
}


node::~node()
{

}
