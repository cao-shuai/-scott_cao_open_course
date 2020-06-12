#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <execinfo.h>   /* for backtrace() */
#include <signal.h>    /* for signal */
#include "function_addr_demo.h"


/*
 * define a handler for functions
 * @param argc:
 * @param argv:
 * @return: 0 sucess, other error no
 */
typedef int (*handler_t)(int argc, char** argv);


/*
 *define a struct for demo command
 */
typedef struct{
    const char* name; //examples of public lecture notest for command name 
    const char* help; //examples of public lecture notest for command explain 
    handler_t handler; //examples of public lecture notest demo function
} command_t;


static int help(int argc,char**argv);
static int build_linkers_and_loaders(int argc, char**argv);

//define commands for handler
static const command_t commands[] = {
    {"help", "<command> -show help text for <command>", help},
    {"build_linkers_and_loaders", "build linkers and loaders demo", build_linkers_and_loaders},
};

//find command 
static const command_t* find_command(const char* name){
    int index = 0;
    for(index= 0; index <2; index++) //todo: need fix array size 
    {
        if(!strcmp(commands[index].name,name))
        { 
            printf("find command '%s' \n",name);
            return &commands[index];
         }
    } 
    return NULL;
}


#define CORE_SIZE (1024*1024*500)
/*
 * reset system coredump limit
 */
static void open_coredump() {
    struct rlimit rlmt;
    if(getrlimit(RLIMIT_CORE,&rlmt) == -1)
    { 
        printf("get current core dump limit size error %s ,%d",__FUNCTION__,__LINE__);
        return ;
    }
    printf("Before set rlimit Core dump current is :%d,max is :%d\n",(int)rlmt.rlim_cur,(int)rlmt.rlim_max);
    rlmt.rlim_cur = (rlim_t)CORE_SIZE;
    rlmt.rlim_max = (rlim_t)CORE_SIZE;
    if(setrlimit(RLIMIT_CORE,&rlmt) == -1)
    { 
        printf("set current core dump limit size error %s ,%d",__FUNCTION__,__LINE__);
        return ;   
    }
    if(getrlimit(RLIMIT_CORE,&rlmt) == -1)
    {
        printf("get current core dump limit size error %s ,%d",__FUNCTION__,__LINE__);
        return ;
    } 
    printf("after set rlimit Core dump current is :%d,max is :%d\n",(int)rlmt.rlim_cur,(int)rlmt.rlim_max);
}


/*
 *open backtrace
 */
#define BACKTRACE_SIZE   16
 static void dump()
 {
    int j, nptrs;
    void *buffer[BACKTRACE_SIZE];
    char **strings;
    nptrs = backtrace(buffer, BACKTRACE_SIZE);
    printf("backtrace() returned %d addresses\n", nptrs);
    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL)
    {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }
    for (j = 3; j < nptrs; j++)
    {
        printf("  [%02d] %s\n", j-3, strings[j]);
    }
    free(strings);

 }
 static void signal_handler(int signo)
 {
    printf("\n=========>>>catch signal %d <<<=========\n", signo);
    printf("Dump stack start...\n");
    dump();
    printf("Dump stack end...\n");
    signal(signo, SIG_DFL);// reset signal default handler
    raise(signo);//send signal again
 }


int main(int argc, char**argv)
{ 
     if(argc < 2){
        help(argc,argv);
        return -1;
     }

    const command_t* command = find_command(argv[1]);

    if(!command){
        printf("unrecongized command '%s'\n",argv[1]);
        return -2;
    } 

    if(!command->handler){
        printf("Unhandled command '%s'\n",argv[1]);
        return -3;
    }

    //open_coredump();
    signal(SIGSEGV, signal_handler);//for SIGSEGV handler
    return command->handler(argc-2,&argv[2]);

}  

//for command help
static int help(int argc,char** argv){
    printf("help need to do \n");
    return 0;
}

//for build_linkers_and_loaders demo
static int build_linkers_and_loaders(int argc, char** argv)
{ 
    /*if(argc < 2){
        printf("%s,%d\n",__FUNCTION__,__LINE__);
        return 0;
    }
    if(!strcmp(argv[1],"addr_calcuation")){*/
        build_linkers_and_loaders_addr_calcuation();
    /*}else{
        printf("only support:\n");
        printf("1. addr_calcuation\n");
    }*/
    return 0;
}
