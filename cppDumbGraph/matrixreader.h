#ifndef MATRIXREADER_H
#define MATRIXREADER_H
#include "includecentral.h"
//everything in the flash beacuase "flemme"
class MatrixReader
{
private :
    ifstream file;
    unsigned int uint_matrix_size;
    vector<vector<unsigned int>> matrix;
public:
    MatrixReader(string filename)
    {
        unsigned int i,j; //used int the for loop
        string temp;
        file.open(filename);
        //first line is size
        file >> temp;
        //temp >> uint_matrix_size;
        uint_matrix_size = atoi(temp.c_str());
        temp.clear();
        //allocating now the matrix
        matrix.resize(uint_matrix_size);

        for (i=0; i<uint_matrix_size; ++i)
            matrix[i].resize(uint_matrix_size);

        //then we have size line to read
        for (j=0; j<uint_matrix_size; ++j)
        {
            for (i=0; i<uint_matrix_size; ++i)
            {
                file >>temp;
                //cout << temp<<endl;
                matrix[i][j]= atoi(temp.c_str());
                temp.clear(); //not necessary
            }
        }

        temp.clear();
        file.close(); //now that the import is finished we close the file

        cout << "Imported matrix is : \n";
        for (j=0; j<uint_matrix_size; ++j)
        {
            for (i=0; i<uint_matrix_size; ++i)
            {
                cout << matrix[i][j];
                cout << " ";
            }
            cout << endl;
        }
    }

    int getSize()
    {
        return uint_matrix_size;
    }

    vector<vector<unsigned int>>& getMatrix()
    {
        return this->matrix;
    }

    ~MatrixReader()
    {
        this->matrix.clear();
    }

};

#endif // MATRIXREADER_H
