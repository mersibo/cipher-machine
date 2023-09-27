#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "functions.h"
#include <iostream>
#include <QMessageBox>


using namespace std;


int modInverse(int a, int m)
/*
 *Функция modInverse принимает два аргумента: a - число, модуль которого нужно найти обратную величину, m - модуль.
 *Сначала функция преобразует число a так, чтобы его можно было поделить на модуль m.
 *Затем запускается цикл, который перебирает возможные значения x от -m до m.
 *Если произведение ax по модулю m дает в результате 1, функция возвращает значение x.
 *Если такого значения не найдено, функция вернет 0
*/
{
    a=a%m;
    for(int x=-m;x<m;x++)
        if((a*x)%m==1)
            return x;
    return 0;
}
void getMinorMatrix(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){
/*
 *Функция getMinorMatrix принимает в качестве аргументов две матрицы: a и temp.
 *Матрица a представляет исходную матрицу, а temp - матрицу, в которую будут записываться cofactors.
 *Также функция получает три целочисленных аргумента: p - строка, с которой начинается удаление элемента, q - столбец, с которого начинается удаление элемента
 *и n - размер матрицы
 *Функция выполняет обход исходной матрицы и копирует элементы,
 *которые не находятся в p-ой строке и q-ом столбце, в temp-матрицу.
 *После завершения обхода, temp-матрица будет содержать миноры исходной матрицы.
*/
int i=0,j=0;
    for(int row=0;row<n;row++){
        for(int col=0;col<n;col++){
            if(row!=p&&col!=q){
                temp[i][j++] = a[row][col];
                if (j==n-1){
                    j=0;
                    i++;
                }
            }
        }
    }
}
int determinant(vector<vector<int> > &a, int n, int N){
/*
 * Функция determinant принимает в качестве аргументов матрицу а, и два целочисленных аргумента N и n.
 * Функция находит детерминант исходной матрицы используя матрицу миноров.
 * Также функция использует функцию getMinorMatrix, описсанную ранее.
*/
    int D = 0;
    if(n==1)
        return a[0][0];
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0;f<n;f++){
        getMinorMatrix(a, temp, 0, f, n);
        D += sign * a[0][f] * determinant(temp, n - 1, N);
        sign = -sign;
    }
    return D;
}
void adjMatrix(vector<vector<int> > &a,vector<vector<int> > &adj,int N){
/*
 * Функция inverse принимает в качестве аргументов две матрицы: a и adj.
 * Также принимает целочисленный аргумент N.
 * Далее находит матрицу дополнений используя функцию getMinorMatrix.
*/
    if(N == 1){
        adj[0][0] = 1;
        return;
    }
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            getMinorMatrix(a, temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, N-1 , N));
        }
    }
}
bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N){
/*
 * Функция inverse принимает в качестве аргументов две матрицы: a и inv.
 * Также принимает целочисленный аргумент N.
 * Далее функция находит обратную матрицу используя функции modinverse и adjoint.
 *
*/

    int det = determinant(a, N, N);
    if(det == 0){
        cout << "Матрица не обратима";
    }
    int invDet = modInverse(det,26);
    cout<<det%26<<' '<<invDet<<'\n';
    vector<vector<int> > adj(N, vector<int>(N));
    adjMatrix(a, adj, N);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            inv[i][j] = (adj[i][j]*invDet)%26;
    return true;
}
