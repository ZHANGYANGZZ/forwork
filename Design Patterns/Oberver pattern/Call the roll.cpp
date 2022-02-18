/*
 * 观察者模式定义一种一对多的关系，一个对象状态改变，多个对象会接收到通知。状态改变的对象并不知道哪些对象在接收通知。
 *
 * 观察者模式即定义一种交互，即发布-订阅：
 *  1.一个对象自身状态发生改变时，会发出通知，但是并不知道谁是接受者，但每个接受者都会收到通知，这些接受者称为观察者
 *  2.作为对通知的响应，每个观察者都查询目标状态，然后改变自身的状态和目标状态进行同步。
 * 代码场景：
 *      A,B,C,D四个学生，A在上课， BCD不在，老师点名时，A在QQ群里通知BCD
 */

#include<iostream>
#include<string>
#include<list>

class Observer;

class Subject{
public:
    virtual ~Subject() {};
    virtual void registerObser(Observer* obser) = 0;
    virtual void removeObser(Observer* obser) = 0;
    virtual void notifyObsers(const std::string &msg) = 0;
};

class  Observer{
public:
    virtual ~Observer(){};
    virtual void Update(const std::string &msg) = 0;
    virtual std::string getName() = 0;
protected:
    Observer(){};
};

class QQGroup : public Subject {
public:
    QQGroup(){ _observers = new std::list<Observer*>();};
    void registerObser(Observer* obser);
    void removeObser(Observer* obser);
    void notifyObsers(const std::string &msg);
private:
    std::list<Observer*> *_observers;
};

void QQGroup::registerObser(Observer *obser) {
    _observers->push_back(obser);
}

void QQGroup::removeObser(Observer *obser) {
    if(_observers->size() > 0){
        _observers->remove(obser);
    }
}

void QQGroup::notifyObsers(const std::string &msg) {
    std::cout << "群消息： " << msg << std::endl;
    std::list<Observer*>::iterator ite = _observers->begin();
    for( ; ite != _observers->end() ; ite ++){
        (*ite)->Update(msg);
    }
}

class RoomMate : public Observer{
public:
    RoomMate(std::string _name, std::string _action, std::string _now){
        name = _name;
        action = _action;
        now = _now;
    }
    void Update(const std::string& msg){
        std::cout << " this is : " << getName() << std::endl;
        if(msg == "点名了"){
            std::cout << "Action: " << now << std::endl;
        }
        else{
            std::cout << "Go on : " << action << std::endl;
        }
    }
    std::string getName();
private:
    std::string name;
    std::string action;
    std::string now;
};

std::string RoomMate::getName() {
    return name;
}

int main(){
    RoomMate* B = new RoomMate("B", "sleeping", "get dressed and run to classroom");
    RoomMate* C = new RoomMate("C", "playing games", "pay the fee and run to classroom");
    RoomMate* D = new RoomMate("D", "shopping with girl friend", "go back to school and be worried about girl friend's angry");

    QQGroup* qqgroup = new QQGroup();
    qqgroup->registerObser(B);
    qqgroup->registerObser(C);
    qqgroup->registerObser(D);

    qqgroup->notifyObsers("没点名");
    qqgroup->notifyObsers("点名了");

    system("Pause");
    return 0;
}