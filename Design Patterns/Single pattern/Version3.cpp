/*
 * 这是一种比较推荐的懒汉模式写法，用到的主要思想是：如果当变量在初始化的时候，并发同时进入声明语句，并发线程将会阻塞等待初始化结束。
 * 这样就保证了并发线程在获取局部变量的时候一定是经过初始化的，具有线程安全性。
 * C++静态变量的生存期是从声明到程序结束。
 * 注意使用的时候需要声明单例的引用才能获取对象
 */

#include<iostream>

class Singleton{
private:
    ~Singleton(){
        std::cout << " destructor called" << std::endl;
    }

public:
    Singleton(){
        std::cout << "constructor called" << std::endl;
    }
    Singleton(Singleton&) = delete;
    Singleton operator=(const Singleton&) = delete;
    static Singleton& get_instance(){
        static Singleton m_instance;
        return m_instance;
    }
};

int main(){
    Singleton& instance1 = Singleton::get_instance();
    Singleton& instance2 = Singleton::get_instance();

    return 0;
}