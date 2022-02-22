/*
 * 工厂方法： 定义一个用于创建产品的接口，由子类决定生产什么产品
 * 优点：
 *      1.用户只需要知道具体工厂的名称就可得到所要的产品，无需知道产品的具体创建过程
 *      2.在系统增加新的产品时，只需要添加具体产品类和对应的具体工厂类，无需对原工厂进行任何修改，满足开闭原则。
 *
 * 缺点：
 *      1.每增加一个产品就要增加一个具体产品类和一个对应的具体工厂类，这增加了系统的复杂度
 *
 * 应用场景：
 *      1.客户只知道创建产品的工厂名，不知道产品的具体名
 *      2.创建对象的任务由多个具体工厂中的某一个完成，而抽象工厂只提供创建产品的接口
 *      3.客户不关心产品的细节，只关心产品的品牌
 *
 * 注意：
 *      当需要生产的产品不多且不会增加时，一个具体的工厂类就可以完成任务时，可删除抽象工厂类。这是工厂方法模式将退化到简单工厂模式
 *      简单工厂模式： 一个具体工厂根据输入参数的不同，调用不同的具体产品的实现，所有具体产品的实现继承自一个公用类
 */

#include<iostream>

namespace factory{
    class  AbstractProduct{
    public:
        virtual ~AbstractProduct(){};
        virtual void show() = 0;
    };

    class ConcreteProduct : public AbstractProduct {
        void show() {
            std::cout << "ConcreteProduct show ..." << std::endl;
        }
    };

    class AbstractFactory{
    public:
        virtual ~AbstractFactory(){};
        virtual AbstractProduct* CreateProduct() = 0;
    };

    class ConcreteFactory: public AbstractFactory{
    public:
        virtual AbstractProduct* CreateProduct(){
            AbstractProduct* ptr = new ConcreteProduct();
            return ptr;
        }
    };
}

int main(){
    factory::AbstractFactory* ptr_factory = new factory::ConcreteFactory;
    factory::AbstractProduct* ptr_product = ptr_factory->CreateProduct();
    ptr_product->show();

    return 0;
}