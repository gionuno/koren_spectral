#ifndef KOREN_HPP_INCLUDED
#define KOREN_HPP_INCLUDED

#include <armadillo>
#include <iostream>

using namespace arma;
using namespace std;

fmat get_spectral(fmat & G,int K,int MAX_IT=250)
{

    fmat D = zeros<fvec>(G.n_rows);
    for(int i=0;i<G.n_rows;i++)
        D(i) = sum(G.row(i));
    fmat V = randn<fmat>(G.n_rows,K+1);

    for(int i=0;i<V.n_rows;i++)
        V(i,0) = 1.0/sqrt(V.n_rows);

    for(int k=1;k<=K;k++)
    {
        int t = 0;
        V.col(k) /= norm(V.col(k));
        do
        {
            for(int l=0;l<k;l++)
                V.col(k) -= dot(V.col(k),D%V.col(l))/dot(V.col(l),D%V.col(l))*V.col(l);
            for(int j=0;j<G.n_rows;j++)
            {
                for(int l=0;l<G.n_rows;l++)
                    V(j,k) += G(j,l)*V(l,k)/D(j);
                V(j,k) *= 0.5;
            }
            V.col(k) /= norm(V.col(k));
            t++;
            cout << k << " " << t << endl;
        }while(t < MAX_IT);
    }
    return V.cols(1,K);
}

#endif // KOREN_HPP_INCLUDED
