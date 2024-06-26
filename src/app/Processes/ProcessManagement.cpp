 #include "ProcessManagement.hpp"
 #include <iostream>
 #include <cstring>

//  #include "../encryptDecrypt/Cryption.hpp"
ProcessManagement::ProcessManagement(){}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task>Task){
    taskQueue.push(std::move(Task));
    return true;

}

void ProcessManagement::executeTask(){
       while(!taskQueue.empty()){
        std::unique_ptr<Task>taskToExecute=std::move(taskQueue.front());
        taskQueue.pop();
        std::cout<<"Executing task: "<<taskToExecute->toString()<<std::endl;
        executeCryption(taskToExecute->toString());

       }  
}