#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memlayout.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
//function for call memlayout and print out the results
int call(struct memregion *regions, unsigned int size){
    unsigned char *show;
    unsigned int counter = get_mem_layout(regions, size);
    printf("Have total of %d regions(only showing the first 8 regions)\n",counter);
    for(unsigned int i =0;i<8;i++){
        unsigned int from = (uintptr_t)regions[i].from;
        unsigned int to = (uintptr_t)regions[i].to;
        unsigned char mode = (unsigned char) regions[i].mode;
        if(mode=='0'){
            show="RW";
        }
        if(mode=='1'){
            show="RO";
        }
        if(mode=='2'){
            show="NO";
        }
        printf("0x%x-->0x%x  %s\n",from,to,show);
    }

}

int main(){
    //initizlize the size and struct array
    unsigned int size = 8;
    struct memregion regions[8];
    struct memregion new[8];
    call(regions,size);

    //create a file with large storage
    struct stat st;
    int n=5000000;
    char *enter="aghairgbuiawhgiawbegi \n";
    FILE *txt;
    txt = fopen("temp.txt","w+");
    for(int i=0; i<n;i++){
        fprintf(txt,"%s",enter);
    }
    //sign file to memory
    fclose(txt);
    int fd = open("./temp.txt",O_RDWR);
    char *see = mmap(NULL,4095,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);


    call(new,size);


}
