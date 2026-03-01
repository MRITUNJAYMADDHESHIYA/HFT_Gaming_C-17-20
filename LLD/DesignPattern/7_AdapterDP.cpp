//Adapter converts the interface of a class into another interface that client expect.
// 
// ---->To make the interaction between completely difference interfaces
// Real world:- 1. 3rd party vender
//           :- 2. lageacy code(old code) || modern code
// 
// This is object Adapter.(composition)
// second class Adapter. (Inheritance)
// Client(IReport)----->IReport(getJsonData())<---is-a--XmlDataProviderAdapter(XmlDataProvider, getJsonData())
//                                                                     |
//                                                                     |has-a
//                                                       XmlDataProvider(getXmlData())

#include<iostream>
#include<string>
using namespace std;

class IReports{
    public:
        virtual string getJsonData(const string& data) = 0;
        virtual ~IReports() {}
};

class XmlDataProvider{
    public:
        string getXmlData(const string& data){
            size_t sep = data.find(':');
            string name = data.substr(0, sep);
            string id   = data.substr(sep + 1);

            return "<user>"
                    "<name>" + name + "</name"
                    "<id>"   + id   + "</id>"
                    "</user>";
        }
};

class XmlDataProviderAdapter : public IReports{
    private:
        XmlDataProvider* xmlProvider;
    public:
        XmlDataProviderAdapter(XmlDataProvider* provider){
            this->xmlProvider = provider;
        }

        string getJsonData(const string& data) override{
            //1.Get xml from the adaptee
            string xml = xmlProvider->getXmlData(data);

            //2.Naively parse out <name> and <id> values
            size_t startName = xml.find("<name>") + 6;
            size_t endName   = xml.find("</name>");
            string name      = xml.substr(startName, endName-startName);

            size_t startId   = xml.find("<id>") + 4;
            size_t endId     = xml.find("</id>");
            string id        = xml.substr(startId, endId-startId);

            //3.Build and return JSON
            return "{\"name\":\"" + name + "\", \"id\":" + id +"}";
        }
};

class Client{
    public:
        void getReport(IReports* report, string rawData){
            cout<<"Processed JSON: "<<report->getJsonData(rawData)<<endl;
        }
};

int main(){
    //1. create the adaptee
    XmlDataProvider* xmlProv = new XmlDataProvider();

    //2.make our adaptee
    IReports* adapter = new XmlDataProviderAdapter(xmlProv);

    //3.give it some raw data
    string rawData = "Alice:42";

    //4.client prints the JSON
    Client* client  =  new Client();
    client->getReport(adapter, rawData);

    delete adapter;
    delete xmlProv;
    return 0;
}