#include "graph.h"
#include "matrixreader.h"
using namespace std;

int main()
{
    MatrixReader *adjMat =new  MatrixReader("mat1.txt");

    graph *oDG= new graph(adjMat->getMatrix(),adjMat->getSize()); //odg for original di-graph
    delete adjMat;

    oDG->unmarkAll();//to be sure
    oDG->dfs(oDG->getFirst());
    oDG->unmarkAll();//to be sure
    delete oDG;
    return 0;
}

