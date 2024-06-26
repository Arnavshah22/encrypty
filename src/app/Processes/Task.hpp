#ifndef TASK_HPP
#define TASK_HPP
#include<string>
#include<iostream>
#include<sstream>

#include "../fileHandling/IO.hpp";


enum class Action {
    ENCRYPT,
    DECRYPT
};

struct Task
{
    std::string filepath;
    std::fstream f_stream;
    Action action;

    Task(std::fstream &&stream,Action act,std::string filepath):f_stream(std::move(stream)),action(act),filepath(filepath)//&& assign karne ke pass ho raha hai (volatile)
    {}

    std::string toString(){
        std::ostringstream oss;
        oss<<filepath<<","<<(action==Action::ENCRYPT?"ENCRYPT":"DECRYPT");
        //test.txt  ENCRYPT  f_stream
        //"test.txt"
        return oss.str();
    }

    static Task fromString(const std::string &taskData){
        std::istringstream iss(taskData);
        std::string filepath;
        std::string actionStr;

        if(std::getline(iss,filepath,',') && std::getline(iss,actionStr)){
               //TEST.TXT DECRYPT ACTION
               Action action=   (actionStr=="ENCRYPT"?Action::ENCRYPT:Action::DECRYPT);
               IO io(filepath);
               std::fstream f_stream=std::move(io.getFileStream());
               if(f_stream.is_open()){
                  return Task(std::move(f_stream),action,filepath);

               }else{
                  throw std::runtime_error("Failed to open file" + filepath);

               }
        }else{
            throw std::runtime_error("Invalid Task data  format");
        }
    }

};


#endif