#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Person {
protected:
    string name;
public:
    Person(const string& n) : name(n) {}
    virtual ~Person() {}
    virtual void printInfo() const {
        cout << "Персона: " << name << endl;
    }
};

class Student : public Person {
public:
    Student(const string& n) : Person(n) {}
    void printInfo() const override {
        cout << "Студент: " << name << endl;
    }
};

class Teacher : public Person {
public:
    Teacher(const string& n) : Person(n) {}
    void printInfo() const override {
        cout << "Учитель: " << name << endl;
    }
};

class School {
private:
    unique_ptr<Person> people[10];
    int count = 0;
public:
    void addPerson(unique_ptr<Person> p) {
        if (count < 10) {
            people[count++] = move(p);
        }
    }
    void listPeople() const {
        for (int i = 0; i < count; ++i) {
            if (dynamic_cast<Student*>(people[i].get())) {
                cout << "(Студент) ";
            }
            else if (dynamic_cast<Teacher*>(people[i].get())) {
                cout << "(Учитель) ";
            }
            people[i]->printInfo();
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    School school;
    school.addPerson(make_unique<Student>("Алиса"));
    school.addPerson(make_unique<Teacher>("Андрей"));

    school.listPeople();

    unique_ptr<Person> p = make_unique<Student>("Михаил");
    Person* rawPtr = static_cast<Person*>(p.get());
    cout << "Пример static_cast: ";
    rawPtr->printInfo();

    return 0;
}
