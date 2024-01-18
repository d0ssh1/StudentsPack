#include <iostream>
#include "vector"
#include "numeric"

using namespace std;

enum Subjects {
    Math, Russian, History, Literature, Physics
};

struct Marks {
    vector<unsigned int> Math;
    vector<unsigned int> Russian;
    vector<unsigned int> History;
    vector<unsigned int> Literature;
    vector<unsigned int> Physics;
};

class Student {
private:
    string name;
    string surname;
    unsigned int age;
public:
    Marks marks;

    Student(const string &name, const string &surname, unsigned int age) : name(name), surname(surname), age(age) {}

    void getMark(int mark, Subjects subject) {
        switch (subject) {
            case Math: {
                this->marks.Math.push_back(mark);
                break;
            }
            case Russian: {
                this->marks.Russian.push_back(mark);
                break;
            }
            case History: {
                this->marks.History.push_back(mark);
                break;
            }
            case Literature: {
                this->marks.Literature.push_back(mark);
                break;
            }
            case Physics: {
                this->marks.Physics.push_back(mark);
                break;
            }
        }
    }

    static bool isExcellentInSubject(const vector<unsigned int> &marks) {
        if (marks.empty()) { return true; }

        float averageMark = accumulate(marks.begin(), marks.end(), 0.0) / marks.size();
        return averageMark >= 4.5;
    }

    bool isExcellentStudent() {
        if (!isExcellentInSubject(this->marks.Math)) return false;
        if (!isExcellentInSubject(this->marks.Russian)) return false;
        if (!isExcellentInSubject(this->marks.History)) return false;
        if (!isExcellentInSubject(this->marks.Literature)) return false;
        if (!isExcellentInSubject(this->marks.Physics)) return false;

        return true;
    }
};

class Teacher {
private:
    string name;
    string surname;
    unsigned int age;
    Subjects specialization;
public:
    Teacher(const string &name, const string &surname, unsigned int age, Subjects specialization) : name(name),
                                                                                                    surname(surname),
                                                                                                    age(age),
                                                                                                    specialization(
                                                                                                            specialization) {}

    void giveMark(Student &student, unsigned int mark) {
        student.getMark(mark, specialization);
    }
};

int main() {
    Student Tema("Artem", "Orlov", 19);
    Tema.getMark(5, Math);
    cout << Tema.isExcellentStudent() << endl;
    Teacher Eugene("Eugene", "Abramovich", 19, Math);
    Eugene.giveMark(Tema, 3);
    cout << Tema.isExcellentStudent() << endl;
    return 0;
}
