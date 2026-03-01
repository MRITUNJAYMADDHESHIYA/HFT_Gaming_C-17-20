// Facade pattern provides a simplified, unified interface to a set of complex subsystem.
// It hides the complexity of the system and exposes only what is necessary.
// 
// --->Hide the complexity
// 
// 
// Client(ComputerFacade, startComputer())--------->ComputerFacade(PowerSupply, coolingSystem, CPU,Memory, HardDisk, Bios, OS, startComputer())
//                                                                |
// PowerSupply(providePower())------------------------------------|
// CoolingSystem(startFans())-------------------------------------|
// CPU(initialize)------------------------------------------------|
//    |                                                           |
//Bios(CPU, Memory, boot)                                         |
//    |                                                           |
// Memory(selfTest)-----------------------------------------------|
// OS(load())-----------------------------------------------------|
// HardDisk(spinUP())---------------------------------------------|
// 
// 


#include<iostream>
using namespace std;

class PowerSupply{
    public:
        void providePower(){
            cout<<"Power supply: Providing power..."<<endl;
        }
};

class CoolingSystem{
    public:
        void startFans(){
            cout<<"Cooling System: Fans started..."<<endl;
        }
};

class CPU{
    public:
        void initialize(){
            cout<<"CPU: Initialization started..."<<endl;
        }
};

class Memory{
    public:
        void selfTest(){
            cout<<"Memory: self-Test passed..."<<endl;
        }
};

class HardDrive{
    public:
        void spinUP(){
            cout<<"Hard Drive: spinnig up..."<<endl;
        }
};

class BIOS{
    public:
        void boot(CPU& cpu, Memory& memory){
            cout<<"BIOS: Booting CPU and Memory checks..."<<endl;
            cpu.initialize();
            memory.selfTest();
        }
};

class OperatingSystem{
    public:
        void load(){
            cout<<"Operating system: Loading intomemory..."<<endl;
        }
};

class ComputerFacade{
    private:
        PowerSupply powerSupply;
        CoolingSystem coolingSystem;
        CPU cpu;
        Memory memory;
        HardDrive hardDrive;
        BIOS bios;
        OperatingSystem os;
    public:
        void startComputer(){
            cout<<"======Starting Computer ========="<<endl;
            powerSupply.providePower();
            coolingSystem.startFans();
            bios.boot(cpu, memory);
            hardDrive.spinUP();
            os.load();
            cout<<"Computer Booted Successfully!"<<endl;
        }
};

int main(){
    ComputerFacade computer;
    computer.startComputer();

    return 0;
}
