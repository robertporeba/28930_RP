#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <vector>

#define MATRIX_H 30000
#define MATRIX_W 30000

//operators
//+
//-
//*
//&
//|
//^
//&&
//||

uint8_t** matrix;

uint32_t sumMatrix(){
    uint32_t sum = 0;

    for(uint32_t i = 0;i<MATRIX_H;i++){
        for(uint32_t k = 0;k<MATRIX_W;k++){
            sum += matrix[i][k];
        }
    }

    return sum;
}

uint32_t sumMatrixParallel(){
    uint32_t sum = 0;
    uint32_t i;
    uint32_t k;

    #pragma omp parallel for shared(matrix) private(i, k)
    for(i = 0;i<MATRIX_H;i++){
        for(k = 0;k<MATRIX_W;k++){
            sum += matrix[i][k];
        }
    }

    return sum;
}

uint32_t randomArray(){
    int* array = new int[100000000];
    uint32_t sum = 0;

    for(int i = 0; i<100000000;i++)
    {
        uint32_t variable = rand() % 10;
        array[i] = variable;
        sum += array[i];
    }
    return sum;
}

uint32_t randomArrayParrarel(){
    int* array = new int[100000000];
    uint32_t i;
    uint32_t sum = 0;
    #pragma omp parallel for private(i) reduction(+ : sum)
    for(int i = 0; i<100000000;i++)
    {
        uint32_t variable = rand() % 10;
        array[i] = variable;
        sum += array[i];
    }
    return sum;
}

int main(){
    //alloc matrix
    // matrix = (uint8_t**)new uint8_t*[MATRIX_H];
    // for (uint32_t i = 0;i<MATRIX_H;i++)
    //     matrix[i] = new uint8_t[MATRIX_W];

    //fill matrix random data normal way
    // for(uint32_t i = 0;i<MATRIX_H;i++){
    //     for(uint32_t k = 0;k<MATRIX_W;k++){
    //         matrix[i][k] = (uint16_t)(rand() % 10);
    //     }
    // }

    auto start = std::chrono::high_resolution_clock::now();
     uint32_t sum = randomArray();
    auto end = std::chrono::high_resolution_clock::now();

    printf("Sum calculated normal way: %u in time: %llu ms\r\n", sum,
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
     sum = randomArrayParrarel();
    end = std::chrono::high_resolution_clock::now();

    printf("Sum calculated parralel way: %u in time: %llu ms\r\n", sum,
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}