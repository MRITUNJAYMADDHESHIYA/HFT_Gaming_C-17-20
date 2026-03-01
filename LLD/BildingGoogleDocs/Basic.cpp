//1.Make Document Editor

//1.document editor:- 1.txt and image (vector<string> )
//                 :- 2.addTxt(string text)
//                 :- 3.addImag(string path)
//                 :- 4.renderDocument();
//                 :- 5.saveTofile();


/////Problem and solution
//1.SIP has to follow
//2.OCP has to follow
//
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class DocumentEditor{
    private:
        vector<string> documentElements;
        string renderedDocument;
    public:
        //adds text as a plain string
        void addText(string text){
            documentElements.push_back(text);
        }

        //adds an image by its file path
        void addImage(string imagePath){
            documentElements.push_back(imagePath);
        }

        //renders the document by checking the type of each element at runtime
        string renderDocument(){
            if(renderedDocument.empty()){
                string ans;
                for(auto element: documentElements){
                    if(element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" || element.substr(element.size() - 4) == ".png")){
                        ans += "[Image: " + element + "]" + "\n";
                    }else{
                        ans += element + "\n";
                    }
                }
                renderedDocument = ans;
            }
            return renderedDocument;
        }
        //save file
        void saveToFile(){
            ofstream file("document.txt");
            if(file.is_open()){
                file<<renderDocument();
                file.close();
                cout<<"Document saved to document.txt"<<endl;
            }else{
                cout<<"Error: unable to open file for writing."<<endl;
            }
        }
};

int main(){
    DocumentEditor editor;
    editor.addText("Hello, world!");
    editor.addImage("picture.png");
    editor.addText("This is the end.");

    cout<<editor.renderDocument() <<endl;
    editor.saveToFile();

    return 0;
}
