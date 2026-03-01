//1.using coroutine-based awaitable
//2.readline function returns an Awaitable object

#include<iostream>
#include<fstream>
#include<string>
#include<coroutine>
#include<future>

class FileReader{
    private:
        std::ifstream file;
    public:
        struct Awaitable{
            std::ifstream& file;
            std::string    buffer;
            bool await_ready() {return false;}
            void await_suspend(std::coroutine_handle<> handle){
                std::async(std::launch::async, [this, handle]{
                    std::getline(file, buffer);
                    handle.resume();
                });
            }
            std::string await_resume(){return buffer;}
        };
        FileReader(const std::string& filename): file(filename) {}

        auto readline(){
            return Awaitable{file};
        }
};


int main(){
    FileReader reader("example.txt");

    auto line = reader.readline();

    std::cout << "Read line: " << line << std::endl;
    return 0;
}