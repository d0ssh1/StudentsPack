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

    const string &getName() const {
        return name;
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
protected:
    string name;
    string surname;
    unsigned int age;
    Subjects specialization;
    bool MoodState = (rand() % 2 == 0); // 1 = good, 0 = bad
public:

    Teacher(const string &name, const string &surname, unsigned int age, Subjects specialization) : name(name),
                                                                                                    surname(surname),
                                                                                                    age(age),
                                                                                                    specialization(
                                                                                                            specialization) {}

    void giveMark(Student &student, unsigned int mark) {
        student.getMark(mark, specialization);
    }

    virtual void MoodyMoodMark(Student &student) {

        bool exc = student.isExcellentStudent();

        if (MoodState && exc) {
            giveMark(student, 5);
        }

        if (!MoodState && exc) {
            giveMark(student, (4 + (rand() % 2 == 0)));
        }

        if (MoodState && !exc) {
            giveMark(student, 4);
        }

        if (!MoodState && !exc) {
            giveMark(student, (2 + (rand() % 2 == 0)));
        }

    }

    bool isMoodState() const {
        return MoodState;
    }
};

class GODTeacher : public Teacher {
private:
    bool MoodState = 1;
public:
    GODTeacher(const string &name, const string &surname, unsigned int age, Subjects specialization)
            : Teacher(name, surname, age, specialization) {}

    void MoodyMoodMark(Student &student) override {
        giveMark(student, 5);
        cout << student.getName() << " got 5! I love everything in this world! I'm so happy to live!\n";
    };
};

class DEVILTeacher : public Teacher {
private:
    bool MoodState = 0;
public:
    DEVILTeacher(const string &name, const string &surname, unsigned int age, Subjects specialization)
            : Teacher(name, surname, age, specialization) {}

    void MoodyMoodMark(Student &student) override {
        giveMark(student, 2);
        cout << student.getName() << " got 2! I hate everything in this world! I want to destroy Earth!\n";
    };
};

class Lesson {
public:
    vector<Student> Stud;

    void addToLesson(Student student) {
        Stud.push_back(student);
    }

    void Marking(Teacher teacher) {
        if (teacher.isMoodState()) {
            Student bedolaga = Stud[rand() % Stud.size()];
            teacher.MoodyMoodMark(bedolaga);
            cout << "Student " << bedolaga.getName() << " got new mark!\n";
            // Берем рандомное число и от него берем остаток от деления на количество студентов.
            // Получится рандомный студент и ему делаем оценку по настроению
        }

        if (!teacher.isMoodState()) {
            for (Student stud: Stud) {
                teacher.MoodyMoodMark(stud);
                cout << "All of the students got new mark >:(\n";
            }
        }
    }
};

int main() {
    srand(time(0));


    Student Tema("Artem", "Orlov", 19);
    Student Kolya("Nikolay", "Gavrilyouk", 19);

    Tema.getMark(5, Math);
    cout << Tema.isExcellentStudent() << endl;

    Teacher Eugene("Eugene", "Abramovich", 19, Math);
    Teacher Vika("Viktoria", "Hromova", 19, Physics);

    Eugene.giveMark(Tema, 3);

    cout << Tema.isExcellentStudent() << endl;

    Lesson Matth;
    Matth.addToLesson(Tema);
    Matth.Marking(Eugene);

    Lesson Phys;
    Phys.addToLesson(Kolya);
    Phys.Marking(Vika);

    GODTeacher Boris("Boris", "Abakumov", 24, Math);
    Lesson OOP;
    OOP.addToLesson(Tema);
    Boris.MoodyMoodMark(Tema);

    DEVILTeacher Skurihin("Eugene", "Skurihin", 100, Math);
    Lesson Geometry;
    Geometry.addToLesson(Tema);
    Skurihin.MoodyMoodMark(Tema);

    return 0;
}
