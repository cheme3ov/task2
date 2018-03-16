/*
 * task1.cpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: artemchemezov
 */
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <iterator>
#include <algorithm> 
#include <limits>
#include <cstddef>
using namespace std;

mutex m;
vector<double> req(int shrt, int lenght, int N, vector<double> vec){
    vector<double> v2;
    vector<double*> pv;
    vector<int> pv2;
    v2.reserve(lenght);
    pv.reserve(N);
    pv2.reserve(N);
    for(int i = 0; i < N; ++i) pv2[i] = 0;
    double minval;
    int nummin;



    for (int i = 0; i < N; ++i){
        pv[i] = &vec[i * shrt];
    }

   
    for(int i = 0; i < lenght; ++i){
    //for (int k = 0; k < N + 1; ++k){cerr << "---pv{" << k << "] = " << *pv[k] << endl; }

        minval = std::numeric_limits<double>::max();//*pv[0];
        for (int j = 0; j < N; ++j){
            if (*pv[j] < minval && *pv[j] != std::numeric_limits<double>::max()) {
                minval = *pv[j];
                nummin = j;
            }
        
        }
        
        
        //cerr << minval << endl;
        v2.push_back(minval);

        if ((pv2[nummin] + 1) != shrt && (nummin * shrt + pv2[nummin] + 1 < lenght)) {
            pv[nummin]++;
            pv2[nummin]++;
        }
        else *pv[nummin] =  std::numeric_limits<double>::max();

}

    
return v2;
}

void run(int i, int shrt, int lenght, vector<double> vec){

                auto beg = vec.begin();
                auto end = vec.begin();

                advance(beg, i * shrt);

                if( (i+1) * shrt < lenght) advance(end, (i + 1) * shrt);
                else advance(end, lenght);
                
                sort(beg, end);

}

int main(int argc, char* argv[]){
    const int n = 50;
	double * array = new double[n];
	for (int i = 0; i < n; ++i) {
        array[i] = rand() % 100;
        cerr << "----------------number :" << array[i] << endl;
    }
	int lenght = n;//_msize(array) / sizeof(array[0]);

	vector<double> vec(array, array + n);

    if(argc < 2){
        cerr << "Not enough arguments, please specify the number of threads\n";
        return 1;
    }


    int N = stoi(argv[1]);
    if(N < 1){
        cerr << "Invalid number of threads\n";
        return 1;
    }

    vector<thread> threads;
    threads.reserve(N);
    

    	int shrt = N==1 ? lenght : lenght / N + 1;
        while ((shrt-1) * N > lenght + shrt) shrt--;
        //while ((shrt - 1) * N > lenght) shrt--;
        cerr << "shrt: " << shrt << "; len: " << lenght << endl;

    for(int i = 0; i < N; ++i){
        threads[i] = thread(run, i, shrt, lenght, vec);
    }

     for(int i = 0; i < N; ++i)
        threads[i].join();

    for (int i = 0; i < n; ++i) {
        cerr << "--number :" << vec[i] << endl;
    }

    vec = req(shrt, lenght, N, vec);

   



    for (int i = 0; i < n; ++i) {
        cerr << "number "<< i << ":" << vec[i] << endl;
    }
    
    return 0;
}



