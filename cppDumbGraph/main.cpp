#include "graph.h"
#include "matrixreader.h"
using namespace std;

int main()
{
    //MatrixReader *adjMat =new  MatrixReader("mat1.txt");
    MatrixReader *adjMat =new  MatrixReader("tarjanTest.txt");

    graph *oDG= new graph(adjMat->getMatrix(),adjMat->getSize()); //odg for original di-graph
    delete adjMat;
    cout << "Main : start dfs " << endl;
    oDG->dfs();
    cout << "Main : start tarjan" << endl;
    oDG->tarjan();
    delete oDG;
    return 0;
}

