#include <iostream>
#include <string>
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
        cout << "Вчитель: " << name << endl;
    }
};

class School {
private:
    Person* people[10];
    int count = 0;
public:
    ~School() {
        for (int i = 0; i < count; ++i) {
            delete people[i];
        }
    }
    void addPerson(Person* p) {
        if (count < 10) {
            people[count++] = p;
        }
    }
    void listPeople() const {
        for (int i = 0; i < count; ++i) {
            if (dynamic_cast<Student*>(people[i])) {
                cout << "(Студент) ";
            }
            else if (dynamic_cast<Teacher*>(people[i])) {
                cout << "(Вчитель) ";
            }
            people[i]->printInfo();
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    School school;
    Student* s1 = new Student("Алиса");
    Teacher* t1 = new Teacher("Андрей");
    school.addPerson(s1);
    school.addPerson(t1);

    school.listPeople();

    Person* p = static_cast<Person*>(s1);
    cout << "Статист: ";
    p->printInfo();

    return 0;
}