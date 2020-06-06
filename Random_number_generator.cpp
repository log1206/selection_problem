#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main()
{
    srand(time(NULL));

    int n;
    int k;
    cin >> n >> k;
    while(k > n)
        k = rand()%30000 + 1;
    // cout << n << " " << k << endl;

    int array[n];
    for(int i = 0; i < n; i++){
        array[i] = rand()%20000+1;
    }
    // cout << rand()%20000+1 << endl;
    ofstream f;
    f.open ("input.txt");
    f << n;
    f << " ";
    f << k;
    f << endl;
    for(int i = 0; i < n-1; i++){
        f << array[i];
        f << " ";
    }
    f << array[n-1];
    f.close();
    return 0;
}