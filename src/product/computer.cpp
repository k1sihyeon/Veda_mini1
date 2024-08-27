#include <string>

#include "product.h"

using namespace std;

class Computer : public Product {
   private:
    string cpu;
    int ram;
    string gpu;

   public:
    Computer(string name, int price, string company, string cpu, int ram, string gpu) 
        : Product(name, price, (string)"Computer", company, 0), cpu(cpu), ram(ram), gpu(gpu) {}

    string getMoreDetails(int option = 0) override {
        if (option == 0)
            return cpu + "," + to_string(ram) + "," + gpu;
        
        else if (option == 1)
            return "CPU: " + cpu + "\tRAM: " + to_string(ram) + "\tGPU: " + gpu;
    }

    string getCpu() {
        return cpu;
    }

    int getRam() {
        return ram;
    }

    string getGpu() {
        return gpu;
    }

    void setCpu(string cpu) {
        this->cpu = cpu;
    }

    void setRam(int ram) {
        this->ram = ram;
    }

    void setGpu(string gpu) {
        this->gpu = gpu;
    }
};