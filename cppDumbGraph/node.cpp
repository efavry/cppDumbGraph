#include <node.h>
node::node(unsigned int name)
{
    this->uint_name= name;
    this->number=-1;
    this->numberA=-1;
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
    this->number=-1;
    this->numberA=-1;
    this->b_mark=false;
    this->scc_mark=0;
}
void node::addNeighbor(node * n)
{
    this->edgesList.push_back(n);
}


node::~node()
{

}
