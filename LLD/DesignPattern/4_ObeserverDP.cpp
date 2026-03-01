//Define a one-to-many relationship between objects so that when one object changes states,
//all of it's dependents are notified, and updated automatically.

//many objects want to know when, one main object change
//What is difference in Polling and Pushing.
//Observable------>observer


//Real world:-
//1.notification service
//2.Event-handling



//UML:-
//  <<abstract>>                                                             <<abstract>>
//IObservable(add, remove, notify())------------------------------------------>IObserver(update())
//   |                                                                                  |
//   |                                                                                  |
//ConcreteObservable(vector<IObserver> list, add, remove, notify())<--------ConcreteObserver(concreteObserable, update())
// 
//
//channel(string name, latestvideo)<---------------------------------------Subscriber(string name, Channel channel, update())
//        (vector<Isubscribe> subscribers)
//        (subscribe(Isubscribe), unsubscribe(Isubscribe))
//        (notify(), uploadingVideo)

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

//abstract observer
class ISubscriber{
    public:
        virtual void update() = 0;
        virtual ~ISubscriber() {}
};

//abstract observable
class IChannel{
    public:
        virtual void subscribe(ISubscriber* subscriber) = 0;
        virtual void unsubscribe(ISubscriber* subscriber) = 0;
        virtual void notifySubscribers() = 0;
        virtual ~IChannel() {}
};


//Concrete: a youtube channel
class Channel : public IChannel{
    private:
        vector<ISubscriber*> subscribers; //list of subscribers
        string name;
        string latestVideo;
    public:
        Channel(const string& name){
            this->name = name;
        }

        //add a subscriber(no dublicate)
        void subscribe(ISubscriber* subscriber) override{
            if(find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()){
                subscribers.push_back(subscriber);
            }
        }

        //remove a subscriber if present
        void unsubscribe(ISubscriber* subscriber) override{
            auto it  = find(subscribers.begin(), subscribers.end(), subscriber);
            if(it != subscribers.end()){
                subscribers.erase(it);
            }
        }

        //Notify all subscribers of the latest video
        void notifySubscribers() override{
            for(ISubscriber* sub : subscribers){
                sub->update();
            }
        }

        //upload a new video and notify
        void uploadVideo(const string& title){
            latestVideo = title;
            cout<<"\n[" << name <<" uploaded \"" << title << "\"]\n";
            notifySubscribers();
        }

        //read voideo data
        string getVideoData(){
            return "\nCheckout our new Video : " + latestVideo + "\n";
        }
};

//Concrete: a subscriber
class Subscriber : public ISubscriber{
    private:
        string name;
        Channel* channel;

    public:
        Subscriber(const string& name, Channel* channel){
            this->name = name;
            this->channel = channel;
        }

        //prints notification message
        void update() override{
            cout<<"Hey" << name <<"," << this->channel->getVideoData();
        }
};

int main(){
    //create channel
    Channel* channel = new Channel("TradeCoder");

    Subscriber* sub1 = new Subscriber("atul", channel);
    Subscriber* sub2 = new Subscriber("Mrity", channel);

    channel->subscribe(sub1);
    channel->subscribe(sub2);

    //upload a video
    channel->uploadVideo("How to Trade?");

    //atul unsubscribe
    channel->unsubscribe(sub1);

    //upload another video
    channel->uploadVideo("Why algo tradeing is winning?");

    return 0;
}