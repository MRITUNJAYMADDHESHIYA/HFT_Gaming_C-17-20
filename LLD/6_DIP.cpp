//Dependency Inversion Principe
//High level module should not depend on low level module but both should depend on abstruction

#include<iostream>
#include<stdexcept>

class MySqlDatabase{
    public:
        void saveToSql(string data){
            std::cout<<"Executing sql query: insert into users values("<<data<<");"<<std::endl;
        }
};

class MongoDBDatabase{
    public:
        void saveToMango(string data){
            std::cout<<"Executing MongoDB "<<data << std::endl;
        }
};

//high level module
class UserService{
    private:
        MySqlDatabase sqlDb; //direct dependency on sql
        MongoDBDatabase mlongoDb; //direct dependency on monogDB
    public:
        void storeUserToSQL(string user){
            sqlDb.saveToSql(user);
        }

        void storeUserToMongo(string user){
            mlongoDb.saveToMango(user);
        }
};

int main(){
    UserService sevice;
    service.storeUserToSQL("Mritunjay");
    service.storeUserToMongo("Raj");

    return 0;
}


///////////////////solution////////////////////////
class Database{
    public:
        virtual void save(string data) = 0;
};

class MySQLDatabase : public Database{
    public:
        void save(string data) override{
            std::cout<<"Executing SQL Query: "<<data <<std::endl;
        }
};

class MongoDBDatabase : public Database{
    public:
        void save(string data) override{
            std::cout<<"Executing MongoDB: "<<data << std::endl;
        }
};

class UserService{
    private:
        Database* db;
    public:
        UserService(Database* database){
            db = database;
        }

        void storeUser(string user){
            db->save(user);
        }
};

int main(){
    MySqlDatabase mysql;
    MongoDBDatabase mongodb;

    UserService UserService1(&mysql);
    UserService1.storeUser("Mritunjay");

    UserService UserService2(&mongodb);
    UserService2.storeUser("rAH");

    return 0;
}


//OCP is a target then DIP is the solution
//