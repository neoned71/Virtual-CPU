#ifndef __INSTRUCTIONS_HEAD_ADDED__
#define __INSTRUCTIONS_HEAD_ADDED__

enum Instructions : int {
    HALT = 10,
    
    //binary operations
    IADD,
    ISUB,
    IMUL,

    //boolean operations
    //TODO: implement these with flags!
    ICMP,

    //memory operations
    IPUSH ,
    PRINT ,
    POP,
    STORE ,
    LOAD,
    LOCAL_LOAD,

    //branching operations
    JUMP,
    JLT,
    JGT,
    JEQ,

    //functions
    CALL,
    RET
    
};


#endif