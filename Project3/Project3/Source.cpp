#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Engine {
protected:
    string fuelType;
    int power;
public:
    Engine(const string& fuel, int p) : fuelType(fuel), power(p) {}
    virtual ~Engine() {}
    virtual void printInfo() const {
        cout << "Двигатель: " << fuelType << ", мощность: " << power << " л.с." << endl;
    }
};

class PetrolEngine : public Engine {
public:
    PetrolEngine(int p) : Engine("Бензин", p) {}
};

class ElectricEngine : public Engine {
public:
    ElectricEngine(int p) : Engine("Электро", p) {}
};

class Car {
private:
    unique_ptr<Engine> engine;
    string name;
    int serialNumber;
public:
    Car(string n, int s, unique_ptr<Engine> e) : name(n), serialNumber(s), engine(move(e)) {}
    void printInfo() const {
        cout << "Автомобиль: " << name << ", Серийный номер: " << serialNumber << endl;
        engine->printInfo();
    }
    Engine* getEngine() const {
        return engine.get();
    }
};

class Company {
private:
    unique_ptr<Car> cars[5];
    int count = 0;
public:
    void addCar(unique_ptr<Car> c) {
        if (count < 5) {
            cars[count++] = move(c);
        }
    }
    void listCars() const {
        for (int i = 0; i < count; ++i) {
            cout << "(Автомобиль) ";
            cars[i]->printInfo();
            if (dynamic_cast<PetrolEngine*>(cars[i]->getEngine())) {
                cout << "Тип двигателя: Бензиновый" << endl;
            }
            else if (dynamic_cast<ElectricEngine*>(cars[i]->getEngine())) {
                cout << "Тип двигателя: Электрический" << endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    Company company;
    company.addCar(make_unique<Car>("Toyota", 101, make_unique<PetrolEngine>(150)));
    company.addCar(make_unique<Car>("Tesla", 202, make_unique<ElectricEngine>(300)));

    company.listCars();

    return 0;
}
