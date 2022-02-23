#include<iostream>
#include<vector>
#include "instructions.hpp"
#include "machine.cpp"


std::vector<int> fabricate_instructions()
{
    //read file or throw an exception;
    return {
        IPUSH, 10,
        IPUSH, 20,
        STORE, 1,
        LOAD, 1,
        PRINT,
        POP,
        PRINT,
        POP,
        PRINT,
        PRINT,
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

        CPU vm(std::move(program),0,120,300);
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