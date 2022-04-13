#include<iostream>
#include<vector>
#include "instructions.hpp"
#include "machine.cpp"


std::vector<int> fabricate_instructions()
{
    //read file or throw an exception;
    return {
        //Start of the factorial function!, index=0
        IPUSH, 1,

        ICMPS, -1, 3,//compare the 1 @ stack[bp-(-1)] in stack, just pushed with
                     // the argument, @ stack[bp-(3)]

        JEQ, 16,// jump to return if it is equal, 1==1, then just return 1, which is alread on the stack top.

        ISUBS, 3,-1, // if the argument is not equal to 1 then call self with n-1 as argument.

        CALL, 0, 1,// call self, return value will be stored at the stack!

        IMULS,3,-2, // multiply n @stack[bp-(3)] with stack[bp+(2)]

        RET,//end of the factorial function, index=16
        0,
        0,
        0,
        IPUSH,5,// Main function: index=20. pushing 5 to call factorial(5)
        CALL, 0, 1,//calling the factorial function with 5 at the stack!
        PRINT,//printing the top of the stack = factorial(5) = 120
        HALT
    };
}

std::vector<int> read_instructions(int count,char* path)
{
    return {};
    // return static_cast<std::vector<int>>(NULL);
}



int main(int argc, char *argv[])
{
    std::vector<int> program;
    //read file and get instructions!
    try{
        if(argc == 1)
        {
            program=fabricate_instructions();
            
        }
        else{
            program=read_instructions(argc,argv[1]);
        }

        int address_of_main=20,data_segment_size=20,stack_size=100;
        CPU vm(std::move(program),
                address_of_main,
                data_segment_size,
                stack_size
                );
        vm.run();
        // std::cout<<"starting cpu!"<<program[0]<<program[1];
    }
    catch(char* msg)
    {
        std::cout << "Error!";
        std::cout << msg;
    }
    return 0;
}
