#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Mon Dec 19 12:23:34 2016

@author: gionuno
"""

import matplotlib.pyplot as plt;
import numpy as np;

N = 64;

#fully connected graph
A = np.zeros((N,N));
for i in range(N):
    for j in range(i+1,N):
        A[i,j] = A[j,i] = 1;

plt.imshow(A);
np.save("full_"+str(N),A);

#kings moves on N*N board
N = 8;
A = np.zeros((N*N,N*N));
V = np.array([[1,0],[0,1],[-1,0],[1,0],[-1,-1],[1,1],[-1,1],[1,-1]]);
for i in range(N):
    for j in range(N):
        Vij = [i,j] + V;
        for p in Vij:
            if 0 <= p[0] < N and 0 <= p[1] < N:
                A[N*i+j,N*p[0]+p[1]] = A[N*p[0]+p[1],N*i+j] = 1;

plt.imshow(A);
np.save("king_"+str(N),A);

#pawns moves on N*N board
A = np.zeros((N*N,N*N));
V = np.array([[1,0],[1,1],[1,-1]]);
for i in range(N):
    for j in range(N):
        Vij = [i,j] + V;
        for p in Vij:
            if 0 <= p[0] < N and 0 <= p[1] < N:
                A[N*i+j,N*p[0]+p[1]] = A[N*p[0]+p[1],N*i+j] = 1;
        if i == 0:
            A[N*i+j,N*(i+2)+j] = A[N*(i+2)+j,N*i+j] = 1;

plt.imshow(A);
np.save("pawn_"+str(N),A);

#knights moves on N*N board
A = np.zeros((N*N,N*N));
V = np.array([[1,2],[1,-2],[-1,2],[-1,-2],[2,1],[2,-1],[-2,1],[-2,-1]]);
for i in range(N):
    for j in range(N):
        for q in V:
            p = q + [i,j];
            if 0 <= p[0] < N and 0 <= p[1] < N:
                A[N*i+j,N*p[0]+p[1]] = A[N*p[0]+p[1],N*i+j] = 1;

plt.imshow(A);
np.save("knight_"+str(N),A);

#queens moves on N*N board
A = np.zeros((N*N,N*N));
V = np.array([[1,0],[0,1],[-1,0],[1,0],[-1,-1],[1,1],[-1,1],[1,-1]]);
for i in range(N):
    for j in range(N):
        for q in V:
            for k in range(1,N):
                p = k*q + [i,j];
                if 0 <= p[0] < N and 0 <= p[1] < N:
                    A[N*i+j,N*p[0]+p[1]] = A[N*p[0]+p[1],N*i+j] = 1;

plt.imshow(A);
np.save("queen_"+str(N),A);


#NxNxN cube grid 
N = 8;
A = np.zeros((N*N*N,N*N*N));
V = np.array([[-1,0,0],[1,0,0],[0,-1,0],[0,1,0],[0,0,-1],[0,0,1]]);
for i in range(N):
    for j in range(N):
        for k in range(N):
            Vijk = [i,j,k] + V;
            for p in Vijk:
                if 0 <= p[0] < N and 0 <= p[1] < N and 0 <= p[2] < N:
                    A[N*N*i+N*j+k,N*N*p[0]+N*p[1]+p[2]] = A[N*N*p[0]+N*p[1]+p[2],N*N*i+N*j+k] = 1;

plt.imshow(A);
np.save("cube_"+str(N),A);

#NxN torus
N = 25;
A = np.zeros((N*N,N*N));
V = np.array([[1,0],[0,1],[0,-1],[-1,0]]);
for i in range(N):
    for j in range(N):
        Vij = [i,j] + V;
        for p in Vij:
            p[0] = (N+p[0]) % N;
            p[1] = (N+p[1]) % N;
            A[N*i+j,N*p[0]+p[1]] = A[N*p[0]+p[1],N*i+j] = 1;

plt.imshow(A);
np.save("torus_"+str(N),A);

#NxN mobius band
N = 25;
A = np.zeros((N*N,N*N));
V = np.array([[1,0],[0,1],[0,-1],[-1,0]]);
for i in range(N):
    for j in range(N):
        Vij = [i,j] + V;
        for p in Vij:
            if 0<= p[0] < N:
                if not ( 0<= p[1] < N):
                    p[1] = (N+p[1])%N;
                    p[0] = N-1-p[0];
                A[N*i+j,N*p[0]+p[1]] = A[N*p[0]+p[1],N*i+j] = 1;

plt.imshow(A);
np.save("mobius_"+str(N),A);

#NxN mobius/mobius band
N = 25;
A = np.zeros((N*N,N*N));
V = np.array([[1,0],[0,1],[0,-1],[-1,0]]);
for i in range(N):
    for j in range(N):
        Vij = [i,j] + V;
        for p in Vij:
            if not ( 0 <= p[1] < N):
                p[1] = (N+p[1])%N;
                p[0] = N-1-p[0];
            if not ( 0 <= p[0] < N):
                p[1] = N-1-p[1];
                p[0] = (N+p[0])%N;
            A[N*i+j,N*p[0]+p[1]] = A[N*p[0]+p[1],N*i+j] = 1;

plt.imshow(A);
np.save("mm_"+str(N),A);

#NxN mobius/torus band
N = 25;
A = np.zeros((N*N,N*N));
V = np.array([[1,0],[0,1],[0,-1],[-1,0]]);
for i in range(N):
    for j in range(N):
        Vij = [i,j] + V;
        for p in Vij:
            p[0] = (N+p[0])%N;
            if not ( 0<= p[1] < N):
                p[1] = (N+p[1])%N;
                p[0] = N-1-p[0];
            A[N*i+j,N*p[0]+p[1]] = A[N*p[0]+p[1],N*i+j] = 1;

plt.imshow(A);
np.save("mt_"+str(N),A);


        