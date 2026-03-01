//Task:-
//1. A channel can upload video(different category include)
//2. All the subscribers(simple and primium) get notified

// Observer pattern: when one object (Publisher) changes its state,
// all its dependent objects (Subscribers) are automatically notified.

//The observer hold the pointer of the subject ans aks the subject for somthing when it/s notified
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

/////////////////////////////////////// Most useful ////////////////////////////////////////////////////////
class Subscriber {
public:
    virtual void notify(const string& videoTitle, const string& category) = 0;
    virtual ~Subscriber() = default;
};


class PremiumUser; // forward declaration
///////////////////////////////////////////////////- Channel /////////////////////////////////////////////////
class Channel {
    string name;
    vector<weak_ptr<Subscriber>> subscribers;
public:
    Channel(const string& channelName) : name(channelName) {}

    void subscribe(const shared_ptr<Subscriber>& sub) {
        subscribers.push_back(sub);
    }

    void unsubscribe(const shared_ptr<Subscriber>& sub) {
        subscribers.erase(remove_if(subscribers.begin(), subscribers.end(),
            [&](const weak_ptr<Subscriber>& wsub) {
                auto s = wsub.lock();
                return !s || s == sub;
            }),
            subscribers.end()
        );
    }

    void uploadVideo(const string& title, const string& category); //declretion
};

///////////////////////////////////////////////////// Normal Subscriber /////////////////////////////////////////////////
class User : public Subscriber {
    string username;
    vector<string> categories;
    bool muted = false;

public:
    User(const string& name, vector<string> cats = {})
        : username(name), categories(move(cats)) {}

    void setMute(bool m) { muted = m;} //set mute for spcific subscriber

    void notify(const string& videoTitle, const string& category) override {
        if (muted) return;
        if (categories.empty() ||
            find(categories.begin(), categories.end(), category) != categories.end()) {
            cout << username << " got notified: New Video - "
                 << videoTitle << " [" << category << "]" << endl;
        }
    }
};

////////////////////////////////////////// Premium Subscriber /////////////////////////////////////////////////////////
class PremiumUser : public User {
public:
    PremiumUser(const string& name, vector<string> cats = {})
        : User(name, move(cats)) {}

    void notify(const string& videoTitle, const string& category) override {
        cout << "[PREMIUM] ";
        User::notify(videoTitle, category);
    }
};

//////////////////////////////////////////// Define uploadVideo AFTER PremiumUser ////////////////////////////////////
void Channel::uploadVideo(const string& title, const string& category) {
    cout << "\n[" << name << "] uploaded: " << title
         << " (Category: " << category << ")" << endl;

    // Premium first
    for (auto& wsub : subscribers) {
        if (auto sub = wsub.lock()) {
            if (dynamic_cast<PremiumUser*>(sub.get())) {
                sub->notify(title, category);
            }
        }
    }

    // Normal later
    for (auto& wsub : subscribers) {
        if (auto sub = wsub.lock()) {
            if (!dynamic_cast<PremiumUser*>(sub.get())) {
                sub->notify(title, category);
            }
        }
    }
}

//////////////////////////////////////////////////// Main function ///////////////////////////////////////////////////
int main() {
    Channel cppNuts("CppNuts");

    auto user1 = make_shared<User>("Mritunjay", vector<string>{"Tech", "C++"});
    auto user2 = make_shared<User>("Ram");
    auto user3 = make_shared<PremiumUser>("Rohit", vector<string>{"Tech"});
    auto user4 = make_shared<PremiumUser>("Sneha", vector<string>{"Gaming"});

    cppNuts.subscribe(user1);
    cppNuts.subscribe(user2);
    cppNuts.subscribe(user3);
    cppNuts.subscribe(user4);

    cppNuts.uploadVideo("Observer pattern in C++", "Tech");
    cppNuts.uploadVideo("Gaming with Unreal Engine", "Gaming");

    cout << "\nMritunjay mutes notifications...\n";
    user1->setMute(true);

    cppNuts.uploadVideo("Smart pointers in C++", "Tech");
}
