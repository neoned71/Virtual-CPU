#include "instructions.hpp"
#include<iostream>
#include<vector>

class CPU{

    //cpu registers
    int ip,sp,bp;

    int flag=0;

    //memory regions
    std::vector<int> stack;
    std::vector<int> code;
    std::vector<int> data;

    public:
        CPU(std::vector<int>&& instructions,int main_address,int datasize=100,int stacksize=200):sp(-1),bp(0),ip(main_address),stack(stacksize),data(datasize),code(instructions) {
            // std::cout<< data.size() <<std::endl;
            // std::cout<< code.size() <<std::endl;
        }

        void run()
        {
            std::cout<<"Cpu Started" << std::endl;
            ip=0;
            int value;
            while(ip<code.size())
            {
                int instruction = fetch();//fetch
                switch(instruction)//decode
                {
                    case IPUSH:
                        value=code[ip++];
                        stack[++sp] = value;
                         std::cout<<"Pushing now: "<< value <<std::endl;
                        // execute
                        break;

                    case IADD:
                        stack[++sp]=code[ip++]+code[ip++];
                        //  = value;
                         std::cout<<"Adding Ans: "<< stack[sp] <<std::endl;
                        // execute
                        break;

                    case ISUB:
                        stack[++sp]=code[ip++]-code[ip++];
                        //  = value;
                         std::cout<<"Subtracting Ans: "<< stack[sp] <<std::endl;
                        // execute
                        break;

                    case IMUL:
                        stack[++sp]=code[ip++]*code[ip++];
                        //  = value;
                         std::cout<<"Multiplying Ans: "<< stack[sp] <<std::endl;
                        // execute
                        break;

                    case ICMP:
                        value=code[ip++];
                        if(value == code[ip])
                        {
                            flag = 0;   
                        }
                        else if(value > code[ip])
                        {
                            flag =1;
                        }
                        else{
                            flag=-1;
                        }
                        ip++;
                        //  = value;
                         std::cout<<"Multiplying Ans: "<< stack[sp] <<std::endl;
                        // execute
                        break;

                    case JUMP:
                        ip=code[ip];
                        //  = value;
                        std::cout<<"Jumping to: "<< ip <<std::endl;
                        // execute
                        break;

                    case JEQ:
                        if(flag=0)
                        {
                            ip=code[ip];
                        //  = value;
                            std::cout<<"Jumping with flag 0 to: "<< ip <<std::endl;
                        }
                        else{
                            ip++;
                        }
                        // execute
                        break;
                    
                    case JLT:
                        if(flag<0)
                        {
                            ip=code[ip];
                        //  = value;
                            std::cout<<"Jumping with flag < 0 to: "<< ip <<std::endl;
                        }
                        else{
                            ip++;
                        }
                        // execute
                        break;
                    
                    case JGT:
                        if(flag=0)
                        {
                            ip=code[ip];
                        //  = value;
                            std::cout<<"Jumping with flag > 0 to: "<< ip <<std::endl;
                        }
                        else{
                            ip++;
                        }
                        // execute
                        break;

                    case PRINT:
                        if(sp>-1)
                        {
                            std::cout << "Stack top: "<<stack[sp] <<std::endl;
                        } 
                        else{
                            std::cout << "Stack Empty!"<<std::endl;
                        }
                        break;

                    case HALT:
                        std::cout<<"Halting now"<<std::endl;
                        break;
                    
                    case POP:
                        std::cout<<"Popping now: "<<stack[sp]<<std::endl;
                        sp--;
                        break;    

                    case STORE:
                        std::cout<<"Storing now to data address: "<<code[ip]<<std::endl;
                        data[code[ip++]]=stack[sp--];
                        std::cout<<"Data:" <<data[code[ip-1]] << std::endl;
                        break;

                    case LOAD:
                        std::cout<<"Loading now from data address: "<<code[ip]<<std::endl;
                        stack[++sp]=data[code[ip++]];
                        std::cout<<"stack:" <<stack[sp] << std::endl;
                        // sp--;
                        break; 

                    case LOCAL_LOAD:
                        std::cout<<"Local Loading from offset: "<<code[ip]<<std::endl;
                        stack[++sp]=data[bp+code[ip++]];
                        std::cout<<"stack:" <<stack[sp] << std::endl;
                        // sp--;
                        break; 

                    //functions=> syntax-> `CALL address #arguments`
                    case CALL:
                        value = code[ip++];
                        stack[++sp] = code[ip++];;//number of arguments
                        stack[++sp] = bp;//base pointer
                        stack[++sp] = ip;//return address
                        bp=sp;
                        ip = value;
                        break;

                    //clear everything upto the last argument and put returned value on the top of the stack!
                    case RET:
                        int return_value = stack[sp--];
                        sp=bp;//deleting everything above the bp
                        ip=stack[sp--];
                        bp=stack[sp--];
                        sp -= stack[sp--];
                        stack[++sp] = return_value;
                        break;
                }
            }
        }

    private:
        int fetch()
        {
            return code[ip++];
        }

};
