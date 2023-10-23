#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/common.h"
#include "lib/vm.h"

static void repl(){
    char line[1024];
    for(;;){
        printf("> ");
        
        if (!fgets(line, sizeof(line), stdin)){
            printf("\n");
            break;
        }
        
        interpret(line);
    }
}

static char* readFile(const char* path){
    FILE* file = fopen(path, "rb");

    if (file == NULL){
        fprintf(stderr, "Could not open a file \"%s\". \n", path);
        exit(74);
    } 

    char* extension = strrchr(path, '.');
    if (!(extension != NULL && strcmp(extension, ".rig") == 0)){
        printf("Files should end with .rig \n");
        exit(1);
    }
    
    fseek(file, 0L, SEEK_END);   
    size_t fileSize = ftell(file); // how many bites we are from the start
    rewind(file);// go the vary start
    
    char* buffer = (char*)malloc(fileSize +1); 
    if (buffer == NULL){
        fprintf(stderr, "Not enough memory to read \"%s\". \n", path);
        exit(74);
    }
    size_t bytesRead = fread(buffer, sizeof(char),fileSize, file);
    if (bytesRead < fileSize){
        fprintf(stderr, "Could not read a file \"%s\". \n", path);
        exit(74);
    }
    buffer[bytesRead] = '\0'; 

    fclose(file);
    return buffer;
}
static void runFile(const char* path){
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result ==  INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}


int main(int argc, const char* argv[]) {
    initVM();  
    // try having vm as global variable
    //VM vm;  
    //vm.ip = NULL;
    if (argc ==1){
        repl();
    }else if(argc ==2){
        runFile(argv[1]);
    }else {
        fprintf(stderr, "Usage: RiGel [path]\n");
        exit(64);
    }
    

    freeVM();
    return 0;
}
