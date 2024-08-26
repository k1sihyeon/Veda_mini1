#include "product.h"
#include <string>

using namespace std;

//public
class Computer : public Product {
   private:
    string cpu;
    int ram;
    string gpu;

   public:
    Computer(string name, int price, string company, string cpu, int ram, string gpu) 
        : Product(name, price, (string)"Computer", company, 0), cpu(cpu), ram(ram), gpu(gpu) {}

    string getMoreDetails() override {
        //return "CPU: " + cpu + ",\t RAM: " + to_string(ram) + ",\t GPU: " + gpu;
        return cpu + ", " + to_string(ram) + ", " + gpu;
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