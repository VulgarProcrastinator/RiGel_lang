#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"
#include <stdio.h>

VM vm;

static InterpretResult run(){
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    

for (;;){
    
#ifdef DEBUG_TRACE_EXECUTION
    
    
    disassembleInstraction(vm.chunk, (int)(vm.ip - vm.chunk->code));
    //printf(" %d, %d \n", vm.ip, vm.chunk->code);
    // (vm.ip -vm.chunk->code) the returning value will be the offset
    // vm.ip aka next thing that is going to be executed - vm.chunk aka current hing that is executed
    // to be honest have no idea how it works?
     

#endif
    
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            printValue(constant);
            printf("\n");
            break;
        }
        case OP_RETURN:{
            return INTERPRET_OK;
        }
    
    }
}
#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    // ip is always pointing to the next extraction that is going to be executed
    vm.ip = vm.chunk->code;
   return run();
}


void initVM(){

}
void freeVM(){

}
