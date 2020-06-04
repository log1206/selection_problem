#include <bits/stdc++.h> // all library
#include <chrono>

using namespace std;

// input size n 5-15
//cost range 1-99


int** graph; //graph for city relationship
int n;  //n city

// assumption: every time start at zero

//for branch and bound
int final_cost = INT_MAX;
int final_path[16]; 
bool visited[16]; 



/* we know that brute force is to try every possible path
so we can calculate every path's cost  and find which is the smallest*/

int firSmall(int row) //In order to fine the smallest in the row
{ 
	int min = INT_MAX; 
	for (int i=0; i<n; i++) 
		if (graph[row][i]<min && row != i ) //smaller and not itself 
			min =graph[row][i]; 
	return min; 
} 

int firSmall_c(int col) //In order to fine the smallest in the row
{ 
	int min = INT_MAX; 
	for (int i=0; i<n; i++) 
		if (graph[i][col]<min && col != i && visited[i]!= true) //smaller and not itself 
			min =graph[i][col]; 
	return min; 
} 



// function to find the second minimum edge cost 
// having an end at the vertex i 
int secSmall(int row) 
{ 
	int first = INT_MAX, second = INT_MAX; 
	for (int j=0; j<n; j++) 
	{ 
		if (row == j) 
			continue; 

		if (graph[row][j] <= first) //smaller than first
		{ 
			second = first; 
			first = graph[row][j]; 
		} 
		else if (graph[row][j] <= second && graph[row][j] != first) // smaller than second 
			second = graph[row][j]; 
	} 
	return second; 
} 

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


void TSPLev(int boundN, int level, int pathN[]) 
{ 
	cout<<"";
  
	if (level==n) //if reach final level
	{ 
		

        int costN = boundN + graph[pathN[level-1]][pathN[0]]; //calculate result for now 

        if (costN < final_cost) 
        { 
            for (int i=0; i<n; i++) 
                final_path[i] = pathN[i]; 
            final_path[n] = pathN[0]; 
            final_cost = costN; 
     
        } 
		
		return; 
	} 
    
    bool curAva[n];
	int pos;
    int now_s;
    int temp;
	for (int i=0; i<n; i++) //build graph for other level 
	{       
    
        now_s = INT_MAX; 
    	for (int j=0; j<n; j++) { //find the path to choose this round for current level 
            if (graph[pathN[level-1]][j]<now_s && pathN[level-1] != j && visited[j] == false && curAva[j]==false){
                 now_s = graph[pathN[level-1]][j]; 
                 pos = j;
            }
        }
        if(now_s>99) return;

		curAva[pos] = true; 
        temp = boundN; 
        boundN += now_s;     //calculate the weight now 
    cout<<endl;
 
      //  cout << "this round: " << boundN << " this pos: "<< pos << " this now_s: "<< now_s;
   
        if (boundN < final_cost) //determine if we need to go further 
        { 
            pathN[level] = pos; 
            visited[pos] = true;     
            TSPLev(boundN, level+1, pathN); //call next level 
        } 
        else   return;
        
       
            

        
    
        boundN = temp; 

    
        
        visited[pos] = false; 
		
	} 
} 
void TSP_BB(){

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    int graphB[n][n];
    int pathN[n+1]; //initialization
	int boundN = 0;  
	int small;
    memset(pathN, -1, sizeof(pathN)); 
	memset(visited, 0, sizeof(pathN)); 
 
   
   //calculate for first lower bound (row)
	for (int i=0; i<n; i++)  {
        small = firSmall(i);
        boundN +=  small;
        for(int j =0;j<n;j++){
            if(i!=j)
                graph[i][j] -= small;
        }

    }


    for (int i=0; i<n; i++)  {
        small = firSmall_c(i);
        boundN +=  small;
        for(int j =0;j<n;j++){
            if(i!=j)
                graph[j][i] -= small;
        }
    }
	
	
	visited[0] = true; //first is 0  
	pathN[0] = 0; 

	
	TSPLev(boundN, 1, pathN); //start next level 

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double diff = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    diff /= 1000000;

   
    // write the answer to BF.txt
    
    fstream file;
    
    file.open("BB.txt",ios::out);
    file.setf(ios::fixed);
  
    file << "Solution : ";
    for(int i=0;i<n;i++){
        file << final_path[i] <<" - ";
    }
    file << "0" << endl;
    file << "Cost     : "<< final_cost << endl;
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

    
    TSP_brute();
 
    TSP_BB();
   

    return 0;
}

