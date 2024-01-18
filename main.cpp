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

    const string &getName() const {
        return name;
    }

    bool operator==(const Teacher &teacher) const {
        // Пример сравнения по имени
        return this->name == teacher.name;
    };

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
    Teacher teacher;

    explicit Lesson(Teacher teacherOfTheLesson) : teacher(teacherOfTheLesson) {}

    void addToLesson(const Student& student) {
        Stud.push_back(student);
    }

    const Teacher &getTeacher() const {
        return teacher;
    }

    void Marking() {
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

public:
    bool MoodState = (rand() % 2 == 0);

    explicit Parent(const string &name) : name(name) {}

    void addChild(Student &student) {
        childs.push_back(student);
    }

    bool isMyChild(Student &student) {
        auto it = find(childs.begin(), childs.end(), student);
        if (it != childs.end()) {
            return true;
        } else {
            return false;
        }
    }

    virtual void tellAboutChild(Student &student) {
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

    virtual void tellAboutAllChildrenShort() {
        for (Student &child: childs) {
            if (child.isExcellentStudent() && MoodState) {
                cout << "All of my children are amazing!\n";
            } else {
                cout << "Hmhm.. Weather is amazing today ;) and I don't have any children-n.. mm... by-e~~~ (damn)\n";
            }
        }
    }

    virtual void tellAboutAllChildren() {
        for (Student &child: childs) {
            tellAboutChild(child);
            cout << endl;
        }
    }
};

class Meeting {
private:
    vector<Parent> ParentOnMeeting;
    vector<Teacher> TeachersOnMeeting;
    vector<Lesson> LessonsOnMeeting;
    vector<Student> StudentsForDiscuss;

    vector<Teacher> EmptyTeachers;
    vector<Student> StudentsWithSuspiciousParents;

public:
    void addParents(const vector<Parent> &parents) {
        ParentOnMeeting.insert(ParentOnMeeting.end(), parents.begin(), parents.end());
    }

    void addTeachers(const vector<Teacher> &teachers) {
        TeachersOnMeeting.insert(TeachersOnMeeting.end(), teachers.begin(), teachers.end());
    }

    void addLessons(const vector<Lesson> &lessons) {
        LessonsOnMeeting.insert(LessonsOnMeeting.end(), lessons.begin(), lessons.end());
    }

    void checkTeachersOfLessons() {
        for (const Lesson &lesson: LessonsOnMeeting) {
            // Получаем преподавателя занятия
            Teacher lessonTeacher = lesson.getTeacher();

            // Проверяем, присутствует ли этот преподаватель на собрании
            if (find(TeachersOnMeeting.begin(), TeachersOnMeeting.end(), lessonTeacher) == TeachersOnMeeting.end()) {
                EmptyTeachers.push_back(lessonTeacher);
            }
        }
    }

    void checkParentsOfStudents() {
        for (Student &student: StudentsForDiscuss) {
            bool parentFound = false;

            for (Parent &parent: ParentOnMeeting) {
                if (parent.isMyChild(student)) {
                    parentFound = true;
                    break; // Родитель найден, переходим к следующему ученику
                }
            }

            if (!parentFound) {
                // Добавить ученика в список, если его родитель не найден
                StudentsWithSuspiciousParents.push_back(student);
            }
        }
    }

    void conductMeeting() {
        checkTeachersOfLessons();
        checkParentsOfStudents();
        discussStudents();
        generateMeetingReport();
    }

    void discussStudents() {
        for (const Student &student: StudentsForDiscuss) {
            // Проверяем, обсуждается ли этот студент (есть ли у него родитель на собрании)
            if (std::find(StudentsWithSuspiciousParents.begin(), StudentsWithSuspiciousParents.end(), student) ==
                StudentsWithSuspiciousParents.end()) {
                // Логика обсуждения студента
                cout << "Discussing student " << student.getName() << endl;
            } else {
                cout << "Student " << student.getName() << " is not discussing because his parent is apsent\n" << endl;
            }
        }
    }

    void generateMeetingReport() {
        cout << "Report about meeting:" << endl;
        cout << "Apsent teachers:" << endl;
        for (const Teacher &teacher: EmptyTeachers) {
            // Вывод информации об отсутствующих учителях
            cout << teacher.getName() << endl;
        }
        cout << "Students with apsent parents:" << endl;
        for (const Student &student: StudentsWithSuspiciousParents) {
            // Вывод информации о студентах с отсутствующими родителями
            cout << student.getName() << endl;
        }
    }


};

class Grandmother : public Parent {
private:
    string name;
public:

    Grandmother(const string &name, const string &name1) : Parent(name), name(name1) {}

    void tellAboutChild(Student &student) {
        cout << "My grandchild " << student.getName() << "is the best!\n";
    }

    void tellAboutAllChildren() {
        cout << "My grandchildren are the best!\n";
    }

    void tellAboutOther() {
        vector<string> Phrases = {"Hmm.. you so stinky! Please get off from me and my grandchilds!",
                                  "Ohhh... you soooo sweaty! Take this! *right hoock* BIM BIM BAM BAM",
                                  "~H-Hi... TAKE THIS *left hoock*",
                                  "Why are you so swagy swag? KYS! ╰（‵□′）╯",
                                  "You look amazing today!",
                                  "You are the worst child in the world! Heck...",
                                  "What are you doing this evening? Do you want to sit on the bench with me?"};

        int randPhrase = (rand() % Phrases.size());
        cout << Phrases[randPhrase];

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

    Lesson Matth(Eugene);
    Matth.addToLesson(Tema);
    Matth.Marking();

    Lesson Phys(Vika);
    Phys.addToLesson(Kolya);
    Phys.Marking();

    GODTeacher Boris("Boris", "Abakumov", 24, Math);
    Lesson OOP(Boris);
    OOP.addToLesson(Tema);
    Boris.MoodyMoodMark(Tema);

    DEVILTeacher Skurihin("Eugene", "Skurihin", 100, Math);
    Lesson Geometry(Skurihin);
    Geometry.addToLesson(Tema);
    Skurihin.MoodyMoodMark(Tema);

    RandomMoodTeacher Stepanova("Alena", "Stepanova", 55, Math);
    Lesson Algebra(Stepanova);
    Algebra.addToLesson(Tema);
    Stepanova.MoodyMoodMark(Tema);

    cout << endl;
    Parent Natalya("Natalya");
    Natalya.addChild(Tema);
    Natalya.addChild(Kolya);
    Natalya.tellAboutAllChildren();

    Grandmother MotherOfMother("GodMother", "RegularMother");
    MotherOfMother.tellAboutOther();

    return 0;
}
