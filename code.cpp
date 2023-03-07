#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <string>
using namespace std;

#define NUM_THREADS 8
#define MAX 1000000

int data[MAX];
long global_sum = 0;

int main(int argc, char *argv[])
{ 
    int cores = omp_get_num_procs();
    cout << "The number of cores on this machine = " << cores << endl;

    #pragma omp parallel default(none) shared(data, global_sum)
    {
        long tid = omp_get_thread_num();
        long sum = 0;
        int range = MAX / NUM_THREADS;
        int start = tid * range ;
        int end = start + range ;

        for(int i = start ; i < end ; i++) {
            sum += data[i];
        }

        #pragma omp critical
        global_sum += sum;
    }

    cout << "The final sum = " << global_sum << endl;
}
