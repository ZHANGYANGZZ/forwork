/*
 * 优点： 1.使用 shared_ptr通过对象管理资源，当shared_ptr析构的时候,new出来的对象也会被delete掉，以此避免内存泄漏
 *       2.加了锁，使用互斥量来达到线程安全。但是开销变大，并且当编译器优化，指令重排序的时候会出现重大问题！！！！
 */
#include<iostream>
#include<mutex>

class Singleton{
private:
    Singleton(){
        std::cout << " constructor called" << std::endl;
    }

    static std::shared_ptr<Singleton> m_instance;
    static std::mutex mtx;
public:
    Singleton(Singleton&) = delete;
    Singleton& operator=(const Singleton&)= delete;
    ~Singleton(){
        std::cout << " destructor called" << std::endl;
    }
    static std::shared_ptr<Singleton> get_instance(){
        if(m_instance == nullptr) {
            std::unique_lock<std::mutex> lk(mtx);
            if(m_instance == nullptr){
                m_instance = std::shared_ptr<Singleton>(new Singleton());
            }
        }
        return m_instance;
    }
};

std::shared_ptr<Singleton> Singleton::m_instance = nullptr;
std::mutex Singleton::mtx;

int main(){
    std::shared_ptr<Singleton> instance1 = Singleton::get_instance();
    std::shared_ptr<Singleton> instance2 = Singleton::get_instance();

    return 0;
}
