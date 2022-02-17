//version1 with problems below:
// 1.thread is not safe
// 2.memory leak
/*
 * 线程安全问题：
 *  1.当一个线程判断m_instance== nullptr之后，进入if开始构造m_instance之前，
 *      另一个线程也判断m_instance == nullptr，则两个线程都会构建m_instance
 *      改进： 加锁
 *  2. 内存泄漏问题：通过new创建对象，没有对应使用delete，析构函数里也没有使用。
 *      改进： 使用智能指针
 *
 *
*/
#include<iostream>
class Singeton{
private:
    Singeton(){
        std::cout << " constructor is calling " << std::endl;
    }
    Singeton( Singeton& ) = delete;
    Singeton& operator=(const Singeton& ) = delete;
    static Singeton* m_instance;
public:
    ~Singeton(){
        std::cout << "destructor is calling" << std::endl;
    }
    static Singeton* get_instance(){
        if( m_instance == nullptr){
            m_instance = new Singeton;
        }
        return m_instance;
    }
    void use() const{
        std::cout << " in use " << std::endl;
    }
};

Singeton* Singeton::m_instance = nullptr;
int main() {
    Singeton *instance = Singeton::get_instance();
    Singeton *instance2 = Singeton::get_instance();

    return 0;
}