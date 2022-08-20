/**
 * @file arvore-de-segmentos.cpp
 * @author Gabriel Bergoc (gabriel.bergoc@outlook.com)
 * @brief Algoritmos de manipulação de árvore de segmentos. Fonte: https://neps.academy/br/course/estruturas-de-dados-(codcad)/lesson/arvore-de-segmentos
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 * Sn = a1 + a2 + ... + an
 * Sn = a1 + a1*q + a1*q^2 + ... + a1*q^(n-1)       (1)
 * q*Sn = q*a1 + a1*q^2 + a1*q^3 + ... + a1*q^n     (2)
 * (1) - (2):
 * Sn - q*Sn = a1 - a1*q^n
 * Sn(1 - q) = a1(1 - q^n)
 * Sn = a1(1 - q^n)/(1 - q)
 * Portanto, o número de nós de uma árvore binária com n folhas é (1 - 2^n)/(1 - 2) = -(1 - 2^n) = 2^n - 1
 */

#include <iostream>
#include <cmath>

const int MAX_N = pow(2, 4);
const int TOTAL = pow(2, MAX_N);

int stocksValues[MAX_N]{0};
int segTree[TOTAL]{0};

// update value of stock at index <POS> with <NEW_VALUE> and paths of segment tree
void update(int iNode, int i, int j, int POS, int NEW_VALUE)
{
    if (i == j) // we found the leaf in desired position
    {
        segTree[iNode] = i;
        stocksValues[POS] = NEW_VALUE;
    }
    else    // keep searching
    {
        int l = 2 * iNode;        // left child
        int r = 2 * iNode + 1;    // right child
        int m = (i + j) / 2;      // middle of interval

        if (POS <= m)   // choose the child that contains the wanted position
        {
            update(l, i, m, POS, NEW_VALUE);
        }
        else
        {
            update(r, m + 1, j, POS, NEW_VALUE);
        }

        int iMinLeft = segTree[l];  // index of the minimum element of left subtree
        int iMinRight = segTree[r]; // index of the minimum element of right subtree

        // update current node to hold the index of it's minimum leaf
        if (stocksValues[iMinLeft] < stocksValues[iMinRight])
        {
            segTree[iNode] = iMinLeft;
        }
        else
        {
            segTree[iNode] = iMinRight;
        }

    }
}

// retrieve the index of the minimum stock value in interval [A, B]
int minLeaf(int iNode, int i, int j, int A, int B)
{
    // Case 1: [i, j]⊆[A, B] -> return the value of this node
    if (A <= i && j <= B)
    {
        return segTree[iNode];
    }

    // Case 2: [i, j] and [A, B] are disjoint -> return -1 (not found)
    if (j < A || i > B)
    {
        return -1;
    }

    // Case 3: [i, j]∩[A, B] ≠ ∅ but [i, j]⊄[A, B] -> return the best between the children
    int l = 2 * iNode;        // left child
    int r = 2 * iNode + 1;    // right child
    int m = (i + j) / 2;      // middle of interval

    int bestLeft = minLeaf(l, i, m, A, B);
    int bestRight = minLeaf(r, m + 1, j, A, B);

    // return whichever is not -1 or the one whose stock value is the smallest
    if (bestRight == -1 || bestLeft != -1 && stocksValues[bestLeft] <= stocksValues[bestRight])
    {
        return bestLeft;
    }
    else
    {
        return bestRight;
    }
}

int main()
{
    std::cout << (stocksValues[60]);
}