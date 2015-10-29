#include <node.h>
node::node(unsigned int name)
{
    this->uint_name= name;
    this->int_number=-1;
    this->int_numberA=-1;
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
    this->int_number=-1;
    this->int_numberA=-1;
    this->b_mark=false;
    this->b_tempMark=false;
    this->int_scc_mark=0;
    this->predecessor=NULL;
    this->int_dist=0;
}
void node::addNeighbor(node * n)
{
    this->l_successors.push_back(n);
}
/*
void node::addParent(node * n)
{
    this->parentList.push_back(n);
}
*/
node::~node()
{

}
