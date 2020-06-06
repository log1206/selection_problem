#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

long int *array_wait;

int main()
{
    srand(time(NULL));

    long int n;
    long int k;
    cin >> n >> k;
    while(k > n)
        k = rand()%30000 + 1;
    // cout << n << " " << k << endl;

    array_wait = new long int[n];
    for(long long int i = 0; i < n; i++){
        array_wait[i] = rand()%20000+1;
    }
    // cout << rand()%20000+1 << endl;
    ofstream f;
    f.open ("input.txt");
    f << n;
    f << " ";
    f << k;
    f << endl;
    for(long int i = 0; i < n-1; i++){
        f << array_wait[i];
        f << " ";
    }
    f << array_wait[n-1];
    f.close();

    delete[] array_wait;
    return 0;
}