#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

// function declarations
void* malloc(size_t);
void free(void *);
void dump_memory_map(void);
int raise_power(int);


const int HEAPSIZE = (1*1024*1024); // 1 MB
const int MINIMUM_ALLOC = sizeof(int) * 2;

// global file-scope variables for keeping track
// of the beginning of the heap.
void* heap_begin = NULL;
void* freelist = NULL;


void* malloc(size_t request_size) {

    // if heap_begin is NULL, then this must be the first
    // time that malloc has been called.  ask for a new
    // heap segment from the OS using mmap and initialize
    // the heap begin pointer.
    if (!heap_begin) {
        heap_begin = mmap(NULL, HEAPSIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
        if (heap_begin == MAP_FAILED) {
            fprintf(stderr, "malloc failed: %s\n", errno);
        }
        freelist = heap_begin;
        *((uint32_t*)freelist + 0) = HEAP_SIZE;
        *((uint32_t*)freelist + 1) = 0;
        atexit(dump_memory_map);
    }
    
    uint32_t alloc_size = raise_power(request_size + MINIMUM_ALLOC);


}

void free(void* memory_block) {
    if (!memory_block) { // memory_block == NULL
        assert memory_block == NULL;
        return;
    }

}

void dump_memory_map(void) {

}

int raise_power(int num) {
    int result = 1; // 2^0 = 1
    while (result < num) {
        result *= 2;
    }
    return result;
}

