//it's a data type that can hold any type of value
//Type-safe access	Must use std::any_cast<T>()

// #include <any>
// #include <iostream>
// using namespace std;

// int main() {
//     std::any a = 10;        // holds an int
//     std::cout << std::any_cast<int>(a) << '\n';

//     a = std::string("Hello");
//     std::cout << std::any_cast<std::string>(a) << '\n';
// }



#include<iostream>
#include<any>
#include<string>
#include<unordered_map>
using namespace std;

//At compile-time(template),,,,, At runtime(any)
class SettingsManager{
    public:
        template<typename T>
        void setSetting(const string& name, const T& value){
            settings_[name] = value;
        }

        template<typename T>
        T getSetting(const string& name) const {
            auto it = settings_.find(name);
            if (it != settings_.end()) {
                return any_cast<T>(it->second);
            }
            return T{}; //this is when no match, return default of the type
        }
    private:
        unordered_map<string, any> settings_;
};

int main(){
    SettingsManager sm;

    sm.setSetting("ThemeColor", string("Blue"));
    sm.setSetting("FontSize", 14);
    sm.setSetting("SoundVolume", 0.8);

    cout<<"Theme Color: " << sm.getSetting<string>("ThemeColor") << endl;
    cout<<"Font Size: " << sm.getSetting<int>("FontSize") << endl;
    cout<<"Sound Volume: " << sm.getSetting<double>("SoundVolume") << endl;
    cout<<"Non-existent setting: " << sm.getSetting<string>("NonExistent") << endl; //returns default value for string

    return 0;
}