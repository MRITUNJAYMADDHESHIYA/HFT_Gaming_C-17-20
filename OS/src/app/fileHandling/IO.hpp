#ifndef IO_HPP
#define IO_HPP

#include<fstream>  //work with file input/output
#include<string>
#include<iostream>

class IO{
    public:
        IO(const std::string &file_path);  //constructor
        ~IO();                             //destructor
        std::fstream getFileStream();      //get file

    private:
        std::fstream file_stream;
};

#endif