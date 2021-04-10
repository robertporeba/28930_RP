#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <omp.h>

void somethingLong(uint64_t* result){
    uint64_t buf = 0;
    for(uint64_t i = 0;i<UINT32_MAX;i++)
        buf+=i;
    *result = buf;
}

void somethingLong2(uint64_t* result2){
    uint64_t buf = 0;
    for(uint64_t i = 0;i<UINT32_MAX;i++)
        buf+=i;
    *result2 = buf;
}

void somethingLong3(uint64_t* result3){
    uint64_t buf = 0;
    for(uint64_t i = 0;i<UINT32_MAX;i++)
        buf+=i;
    *result3 = buf;
}

void somethingLong4(uint64_t* result4){
    uint64_t buf = 0;
    for(uint64_t i = 0;i<UINT32_MAX;i++)
        buf+=i;
    *result4 = buf;
}

int main(){
    uint64_t result1 = 0;
    uint64_t result2 = 0;
    uint64_t result3 = 0;
    uint64_t result4 = 0;
    uint64_t result11 = 0;
    uint64_t result12 = 0;
    uint64_t result13 = 0;
    uint64_t result14 = 0;

    auto start = std::chrono::high_resolution_clock::now();

    somethingLong(&result1);
    printf("Normal result1=%llu\n", result1);
    somethingLong2(&result2);
    printf("Normal result2=%llu\n", result2);
    somethingLong3(&result3);
    printf("Normal result3=%llu\n", result3);
    somethingLong4(&result4);
    printf("Normal result4=%llu\n", result4);

    auto end = std::chrono::high_resolution_clock::now();

    printf("Calculated normal way in %llu miliseconds\n", 
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel sections private(result11, result12, result13, result14)
    {
        #pragma omp section
        {
            somethingLong(&result11);
            printf("Sec result1=%llu -> watek %d\n", result11, omp_get_thread_num());
        }
        #pragma omp section
        {
            somethingLong2(&result12);
            printf("Sec result2=%llu -> watek %d\n", result12,omp_get_thread_num());
        }
        #pragma omp section
        {
            somethingLong2(&result13);
            printf("Sec result3=%llu -> watek %d\n", result13,omp_get_thread_num());
        }
        #pragma omp section
        {
            somethingLong2(&result14);
            printf("Sec result4=%llu -> watek %d\n", result14,omp_get_thread_num());
        }
    }

    end = std::chrono::high_resolution_clock::now();

    printf("Calculated parrallel way in %llu miliseconds\n",
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}