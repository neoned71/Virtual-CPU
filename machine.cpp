#include<iostream>
#include "instructions.hpp"
#include<vector>

class CPU{

    //cpu registers
    int ip,sp,bp;

    int flag=0;
    bool debugging=false;

    //memory regions
    std::vector<int> stack;
    std::vector<int> code;
    std::vector<int> data;

    public:
        CPU(std::vector<int>&& instructions,int main_address,int datasize=100,int stacksize=20):sp(-1),bp(0),ip(main_address),stack(stacksize),data(datasize),code(instructions) {
        }

        void run()
        {
            std::cout<<"Cpu Started" << std::endl;
            // ip=0;
            int value;
            int i;
            while(ip<code.size())
            {
                int instruction = fetch();//fetch
                //std::cout<<instruction<<" ";
                switch(instruction)//decode
                {
                    case IPUSH:
                        value=code[ip++];
                        stack[++sp] = value;
                        //std::cout<<"Pushing now: "<< value <<ip<<std::endl;
                        printStack();
                        break;

                    case IADD:
                        stack[++sp]=code[ip++]+code[ip++];
                        printStack();
                        break;

                    case ISUB:
                        stack[++sp]=code[ip++]-code[ip++];
                        printStack();
                        break;

                    case IMUL:
                        stack[++sp]=code[ip++]*code[ip++];
                        printStack();
                        break;

                    case IADDS:// instruction for when operands are on the stack! IADDS 0 1
                        value=stack[bp-code[ip++]]+stack[bp-code[ip++]];
                        std::cout<<value;
                        stack[++sp]=value;
                        printStack();
                        break;

                    case ISUBS:// instruction for when operands are on the stack! ISUBS 0 1
                        stack[++sp]=stack[bp-code[ip++]]-stack[bp-code[ip++]];
                        printStack();
                        break;

                    case IMULS:// instruction for when operands are on the stack! IMULS 0 1
                        stack[sp]=stack[bp-code[ip++]]*stack[bp-code[ip++]];
                        printStack();
                        break;

                    case ICMPS: // ICMP -1 3. relative to the base pointer
                        value=stack[bp-code[ip++]];
                        i=stack[bp-code[ip]];
                        if(value == i)
                        {
                            flag = 0;   
                        }
                        else if(value > i)
                        {
                            flag =1;
                        }
                        else{
                            flag=-1;
                        }
                        ip++;
                        printStack();
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
                        printStack();
                        break;

                    case JUMP:
                        ip=code[ip];
                        printStack();
                        break;

                    case JEQ:
                        if(flag==0)
                        {
                            ip=code[ip];
                        }
                        else{
                            ip++;
                        }
                        // execute
                        printStack();
                        break;
                    
                    case JLT:
                        if(flag<0)
                        {
                            ip=code[ip];
                        }
                        else{
                            ip++;
                        }
                        printStack();
                        break;
                    
                    case JGT:
                        if(flag>0)
                        {
                            ip=code[ip];
                        }
                        else{
                            ip++;
                        }
                        printStack();
                        break;

                    case PRINT:
                        if(sp>-1)
                        {
                            std::cout << "Stack top: "<<stack[sp] <<" and flag: "<<flag<<std::endl;
                        } 
                        else{
                            std::cout << "Stack Empty! and flag: "<<flag<<std::endl;
                        }
                        printStack();
                        break;


                    case HALT:
                        std::cout<<"Halting now"<<std::endl;
                        printStack();
                        break;
                    
                    case POP:
                        std::cout<<"Popping now: "<<stack[sp]<<std::endl;
                        sp--;
                        printStack();
                        break;    

                    case STORE:
                        data[code[ip++]]=stack[sp--];
                        printStack();
                        break;

                    case LOAD:
                        stack[++sp]=data[code[ip++]];
                        printStack();
                        break; 

                    case LOCAL_LOAD:
                        std::cout<<"Local Loading from offset: "<<code[ip]<<std::endl;
                        stack[++sp]=data[bp+code[ip++]];
                        std::cout<<"stack:" <<stack[sp] << std::endl;
                        printStack();
                        break; 

                    //functions=> syntax-> `CALL address #arguments`
                    case CALL:
                        value = code[ip++];
                        stack[++sp] = code[ip++];;//number of arguments
                        stack[++sp] = bp;//base pointer
                        stack[++sp] = ip;//return address: address of the next instruction after call
                        bp=sp;
                        ip = value;
                        printStack();
                        break;

                    //clear everything upto the last argument and put returned value on the top of the stack!
                    case RET:
                        int return_value = stack[sp--];
                        sp=bp;//deleting everything above the bp
                        ip=stack[sp--];
                        bp=stack[sp--];
                        sp -= stack[sp--];
                        stack[++sp] = return_value;
                        printStack();
                        break;
                }
            }
        }

    private:
        int fetch()
        {
            return code[ip++];
        }

        void printStack()
        {
            if(debugging)
            {
                for(auto i : stack){
                std::cout<<i<<',';
            }
            std::cout<<"Ip:"<<ip<<" bp:"<<bp<<" flag:"<<flag;
            std::cout<<std::endl;
            }
        }



};
