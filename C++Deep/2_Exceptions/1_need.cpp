//1.One of the most common ways to handle potential errors is via return codes
//2.Exceptions in cpp are implemented using three keywords: try, throw, catch



#include<string_view> //Doesn’t allocate or copy characters — just points to existing memory.

int findFirstChar(std::string_view str, char ch){
    for(std::size_t = 0; i < str.length(); ++i){
        if(str[i] == ch){
            return i;
        }
    }
    return -1; //not found
}

////////////////////////////////////////////
throw -1; //integer
throw ENUM_INVALID_ARGUMENT; //enum value
throw std::string("Invalid argument"); //string
throw dX; //double variable
throw MyExceptionType("Invalid argument"); //object of class

/////////////////////////////////////////
try{
    //code that may throw an exception
    throw -1;
}


/////////Complete example//////////
try {
    int code = 2;

    if (code == 1)
        throw 404;
    else if (code == 2)
        throw "Invalid operation";
    else
        throw runtime_error("Unknown error");
}
catch (int e) {
    cout << "Integer exception: " << e << endl;
}
catch (const char* msg) {
    cout << "String exception: " << msg << endl;
}
catch (const exception& e) {
    cout << "Standard exception: " << e.what() << endl;
}
