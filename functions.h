#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
using namespace std;


int modInverse(int a, int m);

void getMinorMatrix(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n);

int determinant(vector<vector<int> > &a, int n, int N);

void adjMatrix(vector<vector<int> > &a,vector<vector<int> > &adj,int N);

bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N);


#endif // FUNCTIONS_H
