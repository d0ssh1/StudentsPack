#include <iostream>
#include "vector"
#include "numeric"
#include <algorithm>

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

    bool operator==(const Student &other) const {
        // Пример сравнения по имени
        return this->name == other.name;
    };

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

    bool isExcellentInSubject(const vector<unsigned int> &marks) {
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
    unsigned int mark_counter;

    Teacher(const string &name, const string &surname, unsigned int age, Subjects specialization) : name(name),
                                                                                                    surname(surname),
                                                                                                    age(age),
                                                                                                    specialization(
                                                                                                            specialization) {}

    void giveMark(Student &student, unsigned int mark) {
        student.getMark(mark, specialization);
        mark_counter += 1;
        checkMood();
        cout << "Student " << student.getName() << " got " << mark << endl;
    }

    virtual void checkMood() {
        if (mark_counter % 5 == 0) {
            this->setMoodState((rand() % 2 == 0));
        }
    }

    void setMoodState(bool moodState) {
        MoodState = moodState;
    }

    virtual void MoodyMoodMark(Student &student) {

        bool exc = student.isExcellentStudent();
        unsigned int rmark = (rand() % 2 == 0);

        if (MoodState && exc) {
            giveMark(student, 5);
            mark_counter += 1;
            checkMood();
        }

        if (!MoodState && exc) {
            giveMark(student, (4 + rmark));
            mark_counter += 1;
            checkMood();
        }

        if (MoodState && !exc) {
            giveMark(student, 4);
            mark_counter += 1;
            checkMood();
        }

        if (!MoodState && !exc) {
            giveMark(student, (2 + rmark));
            mark_counter += 1;
            checkMood();
        }

        cout << "Student " << student.getName() << " got new mark!" << endl;

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

class RandomMoodTeacher : public Teacher {
private:
    int randomNumberMood = (rand() % 10) + 3;
public:
    RandomMoodTeacher(const string &name, const string &surname, unsigned int age, Subjects specialization) : Teacher(
            name, surname, age, specialization) {}

    void checkMood() override {
        if (mark_counter % randomNumberMood == 0) {
            this->setMoodState((rand() % 2 == 0));
        }
    }

};

class Parent {
private:
    vector<Student> childs;
    vector<string> cringeStories = {" used to piss himself in bed in childhood up for 5 y.o. LOL ",
                                    " belched so hard that a tooth fell out (DAMN SON WHERE'D YOU FIND THIS) ",
                                    " hit the school window 32 times (by accident) ",
                                    " attacked passers-by under the age of 18 (for fun) ",
                                    " drank two liters of water a day and brushed teeth ",
                                    " shoots tic tol videos about dragons and dances to cool music "};
    string name;
    bool MoodState = (rand() % 2 == 0);
public:

    explicit Parent(const string &name) : name(name) {}

    void addChild(Student &student) {
        childs.push_back(student);
    }

    void tellAboutChild(Student &student) {
        string exc_status;
        if (student.isExcellentStudent()) {
            exc_status = "excellent student! ";
        } else exc_status = "worst student in the world! ";

        cout << "Parent " << name << " is saying that his child " << student.getName()
             << cringeStories[rand() % cringeStories.size()]
             << "but also " << student.getName() << cringeStories[rand() % cringeStories.size()]
             << "and I want to say that thank's god he is the " <<
             exc_status << endl;
    }

    void tellAboutRandomChild() {
        if (childs.empty()) {
            cout << "Sterilny (childfree)\n";
            return;
        } else {
            unsigned int randChildIndex = rand() % childs.size();
            tellAboutChild(childs[randChildIndex]);
        }
    }

    void tellAboutSpecificChild(Student &student) {
        auto it = find(childs.begin(), childs.end(), student);
        if (it != childs.end()) {
            tellAboutChild(student);
        } else {
            cout << "Sorry but this parent don't have this child. Try later ;) hehe\n";
        }
    }

    void tellAboutAllChildrenShort() {
        for (Student &child: childs) {
            if (child.isExcellentStudent()) {
                cout << "All of my children amazing!\n";
            } else {
                cout << "Hmhm.. Weather is amazing today ;)\n";
            }
        }
    }

    void tellAboutAllChildren() {
        for (Student &child: childs) {
            tellAboutChild(child);
            cout << endl;
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

    RandomMoodTeacher Stepanova("Alena", "Stepanova", 55, Math);
    Lesson Algebra;
    Algebra.addToLesson(Tema);
    Stepanova.MoodyMoodMark(Tema);

    cout << endl;
    Parent Natalya("Natalya");
    Natalya.addChild(Tema);
    Natalya.addChild(Kolya);
    Natalya.tellAboutAllChildren();

    return 0;
}
