#include <stdio.h>
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


static const command_t commands[] = {
    {"help", "<command> -show help text for <command>", help},
    {"build_linkers_and_loaders", "build linkers and loaders demo", build_linkers_and_loaders},
};

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
    return 0;
}
