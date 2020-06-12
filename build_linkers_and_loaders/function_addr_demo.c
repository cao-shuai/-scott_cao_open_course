#include<stdio.h>
#include"function_addr_demo.h"

void test(){
    char *s ="abc";
     *s='x';
}
static int add(int a, int b){
    test();
    return a+b;
}



void build_linkers_and_loaders_addr_calcuation()
{
    int a=5;
    int b=10;
    int c= add(a,b);
    printf("%d + %d = %d\n",a,b,c);
}
