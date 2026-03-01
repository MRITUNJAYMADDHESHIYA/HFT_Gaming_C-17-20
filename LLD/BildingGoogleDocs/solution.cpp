////1.Document Elenemt-->render();
//1.a.textElement-->render()  and 1.b.imageElement-->render()

////2.Document-->vector<DocumentElement> element;
//            -->addElement(Document element);
//            -->render();

///3.Persistence-->save();
//3.a.saveTofile-->save() ans 3.b.saveToDB-->save()

///4.Document Editor-->Document doc;
//                  -->Persistance db;
//addText(string txt) and addImage(string path)
//renderdoc();
//save();


//////////////////////////////Some Methods for /////////////////////////
//SRP-->DocumentElement + Document + Persistence + DocumentEditor
//OCP-->we can put anything in any class new thing
//LSP-->Document follow the DocumentElement
//ISP-->
//DIP-->interface in every class
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

//abstraction for document element
class DocumentElement{
    public:
        virtual string render() = 0;
};

class TextElement : public DocumentElement{
    private:
        string text;
    public:
        TextElement(string text){
            this->text = text;
        }

        string render() override{
            return text;
        }
};

class ImageElement : public DocumentElement{
    private:
        string imagePath;
    public:
        ImageElement(string imagePath){
            this->imagePath = imagePath;
        }

        string render() override{
            return "[Image: " + imagePath + "]";
        }
};

class NewLineElement : public DocumentElement{
    public:
        string render() override{
            return "\n";
        }
};

class TabSpaceElement : public DocumentElement{
    public:
        string render() override{
            return "\t";
        }
};

////Document class responsible for holding a collection of elements
class Document{
    private:
        vector<DocumentElement*> documentElements;
    public:
        void addElement(DocumentElement* element){
            documentElements.push_back(element);
        }

        //renders the document by its all the it self render call
        string render(){
            string result;
            for(auto element: documentElements){
                result += element->render();
            }
            return result;
        }
};


//////Persistence Interface
class Persistence{
    public:
        virtual void save(string data) = 0;
};

//filestorage implementation of persistence
class FileStorage : public Persistence{
    public:
        void save(string data) override{
            ofstream outFile("Document.txt");
            if(outFile){
                outFile << data;
                outFile.close();
                cout<<"Document saved to document.txt" <<endl;
            }else{
                cout<<"Error: Unable to open file for writing."<<endl;
            }
        }
};

class DBStorage : public Persistence{
    public:
        void save(string data) override{
            //save to DB
        }
};


//////DocumentEditor class managing client interactions
class DocumentEditor{
    private:
        Document* document;
        Persistence* storage;
        string renderdDocument;
    public:
        DocumentEditor(Document* document, Persistence* storage){
            this->document = document;
            this->storage  = storage;
        }

        void addText(string text){
            document->addElement(new TextElement(text));
        }

        void addImage(string imagePath){
            document->addElement(new ImageElement(imagePath));
        }

        //Adds a new linr to the document
        void addNewLine(){
            document->addElement(new NewLineElement());
        }

        void addTabSpace(){
            document->addElement(new TabSpaceElement());
        }

        string renderDocument(){
            if(renderdDocument.empty()){
                renderdDocument = document->render();
            }
            return renderdDocument;
        }

        void saveDocument() {
            storage->save(renderDocument());
        }
};

//client usage example
int main(){
    Document* document = new Document();
    Persistence* persistence = new FileStorage();
    DocumentEditor* editor   = new DocumentEditor(document, persistence);

    //simulate a client using the editor with common text
    editor->addText("Hello, wolrd");
    editor->addNewLine();
    editor->addText("This is the end.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Hi and bye");
    editor->addNewLine();
    editor->addImage("picture.png");

    cout<<editor->renderDocument() <<endl;

    editor->saveDocument();
    return 0;
}