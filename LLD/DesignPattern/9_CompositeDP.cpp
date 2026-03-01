//1.Treat individual objects and groups of objects in the same way
//File System Example:- file and folder




//      <<abstract>>
//FileSystemItem(ls, openAll, getSize, getName)----------------|
//     |                                                       |is-a + has-a
//     |                                                       |
//File(name, size, ls, openAll, getSize, getName)        Folder(name, vector<FileSystem>, ls, openAll, getSize, getName)


#include<iostream>
#include<vector>
#include<string>
#include<stdexcept>
using namespace std;

class FileSystemItem{
    public:
        virtual ~FileSystemItem() {};
        virtual void ls(int indent = 0) = 0;
        virtual void openAll(int indent = 0) = 0;
        virtual int getSize() = 0;
        virtual FileSystemItem* cd(const string& name) = 0;
        virtual string getName() = 0;
        virtual bool isFolder()  = 0;
};

class File : public FileSystemItem{
    string name;
    int size;
    public:
        File(const string& n, int s){
            name = n;
            size = s;
        }

        void ls(int indent = 0) override{
            cout<< string(indent, ' ') << name << "\n";
        }

        
        void openAll(int indent = 0) override{
            cout<< string(indent, ' ') << name << "\n";
        }

        int getSize() override{
            return size;
        }

        FileSystemItem* cd(const string& name) override{
            throw runtime_error("Cannot cd into a file");
        }

        string getName() override{
            return name;
        }

        bool isFolder() override{
            return false;
        }
};

class Folder : public FileSystemItem{
    string name;
    vector<FileSystemItem*> children;
    public:
        Folder(const string& n){
            name = n;
        }
        ~Folder(){
            for(auto &c: children){
                delete c;
            }
        }

        void add(FileSystemItem* item){
            children.push_back(item);
        }

        void ls(int indent = 0) override{
            for(auto &c : children){
                if(c->isFolder()){
                    cout<< string(indent, ' ') << "+ " << c->getName() << "\n";
                }else{
                    cout<< string(indent, ' ') <<c->getName() << "\n";
                }
            }
        }

        void openAll(int indent = 0) override{
            cout<< string(indent, ' ') << "+ " << name << "\n";
            for(auto child : children){
                child->openAll(indent + 4);
            }
        }

        int getSize() override{
            int totalSize = 0;
            for(auto &c : children){
                totalSize += c->getSize();
            }
            return totalSize;
        }

        FileSystemItem* cd(const string& target) override{
            for(auto child : children){
                if(child->isFolder() && child->getName() == target){
                    return child;
                }
            }
            //not found
            return nullptr;
        }

        string getName() override{
            return name;
        }
        bool isFolder() override{
            return true;
        }
};

int main(){
    Folder* root = new Folder("root");
    root->add(new File("file1.txt", 1));
    root->add(new File("file2.txt", 2));

    Folder* docs = new Folder("docs");
    docs->add(new File("resume.pdf", 1));
    docs->add(new File("coverletter.docx", 1));
    root->add(docs);

    Folder* images = new Folder("images");
    images->add(new File("photo1.jpg", 1));
    root->add(images);

    root->ls();
    docs->ls();
    root->openAll();

    FileSystemItem* cwd = root->cd("docs");
    if(cwd != nullptr){
        cwd->ls();
    }else{
        cout<<"\n Could not cd into docs \n";
    }

    cout<<root->getSize()<<"\n";

    delete root;
    return 0;
}





