#include <stdio.h>

void assert(int condition, const char *message){
    if (!condition){
        printf("Assertion failed: %s\n", message);
    }
}

void main(){
    //example:
    assert(1==1,"1 is apparently not equal to 1 ");
    assert(0==1,"0 is definitely not equal to 1 ");
}