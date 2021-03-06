#include <bits/stdc++.h> // all library
#include <chrono>

using namespace std;


#define superbig 30001

// input size n 5-15
//cost range 1-99

int n; //n input range from 10000 - 30000
int k; //kth big
vector<int> arr; //storing all number

// below are quicksort part for vector-----------------------
void swap(vector<int>& vec, int head, int tail) {      //swap function
    int temp = vec[head];
    vec[head] = vec[tail];
    vec[tail] = temp;

}
void Qsort(vector<int> &vec, int head, int tail) {
    int i, j, mid, piv;
    i = head;
    j = tail;
    mid = head + (tail - head) / 2;
    piv = vec[mid];

    while (i<tail || j>head) {
        while (vec[i] < piv)
            i++;
        while (vec[j] > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j); //error=swap function doesnt take 3 arguments
            i++;
            j--;
        }
        else {
            if (i < tail)
                Qsort(vec, i, tail);
            if (j > head)
                Qsort(vec, head, j);
            return;
        }
    }
}

//---------------------------------------- 

int select(vector<int> arrp, int number, int rank){

   //cout << number << endl;
   
    int need = number%5;

    if(need >0)
        need = 5 - need;
    number += need;
    for(int i =0;i<need;i++){
        arrp.push_back(superbig);
    }    

    if(number <=5){
        Qsort(arrp,0,number-1);  // directly brute force search   
         
        return arrp[rank-1];
    }
    else{
       
        vector<int> middle;       //sort each 5 item group and sort all group by median 
      
        int number_d = number/5;
        for(int i=0;i<number_d;i++){
     
            Qsort(arrp,5*i,5*i+4);
            
            middle.push_back(arrp[5*i+2]);
            
        }
        Qsort(middle,0,number_d-1);
        

    
        int median = middle[number/10-1];
        int small =0;
        int equal =0;
        int big   =0;
        vector<int> arrb;
        vector<int> arrs;
      
        for(auto x: arrp){
            if(x > median && x != 30001){
                arrb.push_back(x);
                big++;
            }
            else if(x < median){
                arrs.push_back(x);
                small++;
            }

        }
        equal = number -small -big -need;
        // next recursive

        if(rank <= small)  return select(arrs, small, rank);
        else if(rank <= small +equal) return median;
        else return select(arrb, number-small-equal-need, rank-small-equal);
        
    }


}

void select_ps(){   

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    //pre-add some superbig to make array can be divided by 5
   
    int answer = select(arr,n,k);

    // calculate time
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double diff = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    diff /= 1000000;
    
    // save to file
    
    fstream file;
    file.open("PS.txt",ios::out);
    file.setf(ios::fixed);
    file << answer << endl;
    file << setprecision(6)<<diff<< endl;
    file.close();
}



void readFile(){
 
    fstream file; 
    int tmp;
    file.open("input.txt",ios::in);
    file >> n;  //n for total number
    file >> k; //k for kth big
   
    for(int i=0;i<n;i++){
         file >> tmp;
         arr.push_back(tmp);
        
    }
    file.close();
}


void select_quick(){

     std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    vector<int> arrq =arr;
    Qsort(arrq, 0,n-1);
    // calculate time
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double diff = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    diff /= 1000000;
    
    // save to file
    fstream file;
    file.open("QS.txt",ios::out);
    file.setf(ios::fixed);  
    file <<arrq[k-1] << endl; //number
    file << setprecision(6)<<diff<< endl; //time
    file.close();

}


int main(void){

    readFile();
  
    select_quick();
    select_ps();

 

    return 0;
}
