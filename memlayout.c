#include <stdio.h>
#include <stdlib.h>
#include "memlayout.h"
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

unsigned int PAGE_SIZE=4096;
unsigned int action =0;
jmp_buf env;

void signalError(int signo){
    action=1;
    //reset the handler
    struct sigaction handle;
    handle.sa_flags = SA_NODEFER; // no flags
    sigemptyset(&handle.sa_mask); // clear the mask so no signals are blocked
    handle.sa_handler = signalError; // set function pointer for handler
    sigaction(SIGSEGV, &handle, NULL); // set the handler
    sigaction(SIGBUS, &handle, NULL);
    siglongjmp(env, 1);
}

int get_mem_layout (struct memregion *regions, unsigned int size){

    unsigned int count =0;//count how many regions we have
    unsigned int checker=0;//record if the mode is RO or NO
    unsigned char mode=' ';//record the mode of current region
    unsigned char n_mode =' ';//the mode gone change to 
    unsigned int spot=0;//record which place in array should store the info

    //from lab1, set up the signal handler
    struct sigaction handle;
    handle.sa_flags = SA_NODEFER; // no flags
    sigemptyset(&handle.sa_mask); // clear the mask so no signals are blocked
    handle.sa_handler = signalError; // set function pointer for handler
    sigaction(SIGSEGV, &handle, NULL); // set the handler
    sigaction(SIGBUS, &handle, NULL);
   
    unsigned char *address = (unsigned char*)0x00000000;

    for(unsigned int i =0; (i<(0xffffffff/PAGE_SIZE));i++){

        if(sigsetjmp(env, 0)==0){
            checker=2;
            unsigned char temp = *address;//check for read
            checker = 1;
            *address = temp;//check for write
            n_mode = '0';
            //RW is checking here
            if(n_mode!=mode){//can read and write won't cause singal handler so need set separately
                count+=1;
                if(spot<size){           
                    regions[spot].from = address;
                          
                    if(spot>=1){
                        regions[spot-1].to = address-1;
                    }
                    regions[spot].mode = n_mode;
                    spot+=1;
                }
                
                mode = '0';
	    }
         //when signal handler being called, check if region changes(RO  or   NO is checking here)
        }else{
            if(action==1){
                if(checker==1){
                    n_mode = '1'; 
                }else if(checker==2) {
                    n_mode = '2';
                }
                action=0;
            }
            if(n_mode != mode){//if new mode have different number with previous mode then its new region
            	count+=1;
                
                if(spot<size){
                    regions[spot].from = address; 
                          
                    if(spot>=1){
                        regions[spot-1].to = address-1;
                    }
                    regions[spot].mode = n_mode;
                    spot+=1;
            	}
                
            	mode = n_mode;
            }
        }
        address+=PAGE_SIZE;
    }
      
    if(spot <=size-1){
        regions[spot].to = (void*)0xffffffff; 
    }
    action=0;
    return count;

}
