#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memlayout.h"
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
//deep recursive function
int recursive(int a){
    if(a<=1){
        return 1;

    }
    return a+recursive(a-1);

}

int main(){
    //initizlize the size and struct array
    unsigned int size = 8;
    struct memregion regions[8];
    struct memregion new[8];
    call(regions,size);
   
    printf("here");
    int value = 100000;
    printf("here");
    int receive = recursive(value);


 
    call(new,size);




}



