/*
This program demonstrate templates and overload in c++

Mult matrix to matrix or matrix to vector.
02.2019 P.Sh.
*/
#include <iostream>
#include <string>
#include <limits>
using namespace std;

template <class Type>
Type get_value(const char*, Type, Type );

void clear_mem(float **arr, int r);
int read_matr(float** &pointer, int &r, int &c);
void print_matr(float **arr, int r, int c);
float** mult(float** matr1, float** matr2, int r, int rc, int c);
double* mult(float** matr, double* vector, int r, int c);

int main()
{
    // choise mode
    int mode;
    cout << "Choice action:" << endl;
    cout << "   1: Mult matrix on matrix" << endl;
    cout << "   2: Mult matrix on vector" << endl;
    mode = get_value("Action: ", 1, 2);

    int r1 = 0;
    int c1 = 0;
    
    float **matr1;
    cout << endl << "   Matrix1:"<< endl;
    int code = read_matr(matr1,r1,c1);
    cout << "Matrix1:" << endl;
    print_matr(matr1,r1,c1); 
    cout << endl;

    if (mode == 1)
    {
        int r2 = 0;
        int c2 = 0;

        float **matr2;
        cout << endl << "   Matrix2:"<< endl;
        int code = read_matr(matr2,r2,c2);
        cout << "Matrix2:"<< endl;
        print_matr(matr2,r2,c2); 

        if (c1 != r2)
        {
            cout << "Invalid matrix size!!!" << endl;
            cout << "Matrix1.Colums != Matrix2.Rows" << endl;
            clear_mem(matr1,r1);
            return 0;
        }
        float **result;
        result = mult(matr1, matr2, r1, r2, c2);
        cout << endl;
        cout << "Result:"<< endl;
        print_matr(result,r1,c2); 
        clear_mem(matr1,r1);
        clear_mem(matr2,r2);
        clear_mem(result,r1);
    }
    else
    {
        double *vector;
        cout << "    Vector:" << endl;
        int vector_size = get_value("Vector size: " ,(-1)*numeric_limits<int>::max(), numeric_limits<int>::max()); 
        if (vector_size != c1)
        {
            cout << "Invalid vector size!!!" << endl;
            clear_mem(matr1,r1);
            return 0;
        }
        vector = new  double[vector_size];
        for (int i = 0; i < vector_size; i++)
        {
        cout << "v[" << (i+1) << "]= ";
           vector[i] = get_value("", (-1)*numeric_limits<int>::max(), numeric_limits<int>::max());
        }
        double *result;
        result = mult(matr1,vector,r1,c1);
        cout << endl <<"Result:"<< endl;
        for(int i = 0; i < r1; i++)
        {
            cout << result[i] << " ";
        }
        cout << endl;
        clear_mem(matr1,r1);
        delete[] vector;
        delete[] result;
    }
    return 0;
}

template <class Type>
Type get_value(const char *promt_str, Type min, Type max)    // get size min < a < max
{
    while (true) 
    {
        std::cout << promt_str;
        Type a;
        std::cin >> a;
 
        // check valve
        if ((std::cin.fail()) || (a < min) || (a > max)) 
        {
            std::cin.clear(); // recover cin
            std::cin.ignore(32767,'\n'); // clear buffer and ingnoge other chars
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767,'\n'); 
            return a;
        }
    }
}

int read_matr(float** &pointer, int &r, int &c)
{
    cout << "Enter matrix size (r x c)" << endl;
    r = get_value("    Rows = ", 1, numeric_limits<int>::max());
    c = get_value("    Colums = ", 1, numeric_limits<int>::max());
    cout << r << " x " << c << endl;
    
    // create matrix
        float **b;
        b = new float*[r];
        
        for (int i = 0; i < r; ++i)
        {
            b[i] = new float[c];
        }
        pointer = b;

    // read elements
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            cout << "a[" << (i+1) << "][" << (j+1) << "]= ";
            b[i][j] = get_value("",(-1)*numeric_limits<float>::max(),numeric_limits<float>::max()) ;
        }
    cout << endl;
    }
    return 0;
}

float** mult(float** matr1, float** matr2, int r, int rc, int c)
{
    // create matrix
    float **result;
    result = new float*[r];
    for (int i = 0; i < r; ++i)
    {
        result[i] = new float[c];
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < rc; k++)
            {
                result[i][j] += matr1[i][k] * matr2[k][j];
            }
        }
    }
    return result;
}

double* mult(float** matr, double* vector, int r, int c)
{
    // create vector
    double *result;
    result = new double[r];
    for (int i = 0; i < r; i++)
    {
        result[i] = 0;
        for (int k = 0; k < c; k++)
        {
            result[i] += matr[i][k] * vector[k];
        }
    }
    return result;
}
void print_matr(float **arr, int r, int c)
{
  for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            cout << arr[i][j] << " ";
        }
    cout << endl;    
    }
}

void clear_mem(float **arr, int r)
{
    for(int i = 0; i < r;i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}
