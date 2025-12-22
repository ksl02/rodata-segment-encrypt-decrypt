#include <stdio.h>
#include <sys/mman.h>
#include "encrypt.h"

#define customData __attribute__((section(".custom_data")))
int PAGE_SIZE_ customData = sysconf(_SC_PAGESIZE);

//required constants for decryptor
extern const void * START_RODATA;
extern const void * END_RODATA;

int main() 
{
    //allow write permissions for rodata segment 
    int size = (uint32_t)&END_RODATA-(uint32_t)&START_RODATA;
    void* rodata_page_start = (void*)((uint32_t)&START_RODATA - (uint32_t)&START_RODATA % PAGE_SIZE_);
    int pages = 1 + ((((uint32_t)&START_RODATA + size + PAGE_SIZE_ - 1) & ~0xFFF - (uint32_t)rodata_page_start)) / PAGE_SIZE_;
    mprotect(rodata_page_start, pages*PAGE_SIZE_, PROT_READ | PROT_WRITE | PROT_EXEC);

    //detect anyone trying to tamper with the application here

    //decrypt rodata segment
    decrypt((char*)&START_RODATA, (uint32_t)&END_RODATA - (uint32_t)&START_RODATA);

    mprotect(rodata_page_start, pages*PAGE_SIZE_, PROT_READ | PROT_EXEC);

    printf("Hello World!\n");
    return 0;
}