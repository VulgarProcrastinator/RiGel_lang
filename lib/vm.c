#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "compiler.h"
#include "value.h"
#include "vm.h"
#include <stdio.h>

VM vm;

static InterpretResult run(){
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)\
    do{\
        double b = pop();\
        double a = pop();\
        push(a op b);\
    } while(false)
// [3] -> [3][1] -> ?3-1? -> b = 1 -> [3][pop] -> a = 3 -> [pop] -> a-b 

for (;;){
    
#ifdef DEBUG_TRACE_EXECUTION
    
    for (Value* slot = vm.stack; slot < vm.stackTOP; slot++ ){
        printf("[");
        printValue(*slot);
        printf("]");
    }
    printf("/n");   
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
            push(constant);
            break;
        }
        case OP_NEGATE:{
            // implement it without pop?
            push(-pop()); break;
        }
        case OP_ADD:{
            BINARY_OP(+); break;
        }
        case OP_SUBTRACT:{
            BINARY_OP(-); break;
        }
        case OP_MULTIPLY:{
            BINARY_OP(*); break;
        }
        case OP_DIVIDE:{
            BINARY_OP(/); break;
        }

        case OP_RETURN:{
            printValue(pop());
            printf(" poped \n");
            return INTERPRET_OK;
        }
    
    }
}
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

static void resetStack(){
    vm.stackTOP = vm.stack;
}
void push(Value value){
    // remember * to get the value of the pointer
    *vm.stackTOP = value;
    // poiner itself
    vm.stackTOP++;
}

Value pop(){
    vm.stackTOP--;
    return *vm.stackTOP;    
}



InterpretResult interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}

void initVM(){
    resetStack();
}


void freeVM(){

}
