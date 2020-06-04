#include <bits/stdc++.h> // all library
#include <chrono>

using namespace std;

// input size n 5-15
//cost range 1-99



void TSP_brute(){   

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    
    vector<int> path; //path for this round 
    for(int i=1; i <n ;i++){    //initialization: load every node to path except first node 0
            path.push_back(i);
    }
    int cost =INT_MAX; //initial biggest number to minimum cost
    vector<int> final_path;
    do{
                
        int node =0; //head = 0 in array
        int cur_cost = 0; // current path cost
        for(int i=0;i < path.size();i++){
            cur_cost += graph[node][path[i]];
            node = path[i];
        }
        cur_cost += graph[node][0]; // add the cost of last node to head
        if(cost > cur_cost){
            final_path = path;  //maybe has problem
            cost =cur_cost;
        }
    }
    while(next_permutation(path.begin(),path.end()));

    // calculate time
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double diff = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    diff /= 1000000;

    // save to file
    fstream file;
    file.open("BF.txt",ios::out);
    file.setf(ios::fixed);
    
    file << "Solution : 0 - ";
    for(int i=0;i<final_path.size();i++){
        file << final_path[i] <<" - ";
    }
    file << "0" << endl;
    file << "Cost     : "<< cost << endl;
    file << "Time     : " << setprecision(6)<<diff<< endl;
    file.close();
}


    

void readFile(){
 
    fstream file; 
    file.open("input.txt",ios::in);
    file >> n;  //n for city number
    graph = new int*[n];
    for(int i = 0; i < n; ++i)  //initial each line
        graph[i] = new int[n];

    for(int i=0; i<n;i++)      //input each line
        for(int j=0;j<n;j++)
            file >> graph[i][j];
    file.close();
}



int main(void){

    readFile();

    
    select_quick();
 

    return 0;
}

