/*
 *  在工厂方法模式中，每一个具体工厂对应一个具体产品，工厂方法也具有唯一性，一般情况下，一个具体工厂中只有一个工厂方法或者一组重载的工厂方法。
 *  但是，我们有些时候需要一个工厂可以提供多个产品对象，而不是单一的产品对象。
 *
 *  比如： 海尔公司生产海尔电视，海尔冰箱。海尔电视和海尔冰箱属于海尔公司的一个产品族。TCL公司生产TCL电视和TCL冰箱， TCL电视和TCl冰箱属于TCL公司的一个产品族。
 *  海尔电视和TCL电视属于一个产品等级，海尔冰箱和TCL冰箱属于一个产品等级
 *
 *  角色：
 *      1. 抽象工厂： 它声明了一组用于创建一族产品的方法，每个方法对应一个产品
 *      2. 具体工厂： 它实现了在抽象工厂中声明的创建产品的方法，生成一组具体产品，这些产品构成了一个产品族，每一个产品都位于某个产品等级结构中
 *      3. 抽象产品： 它为每种产品提供抽象接口，在抽象产品中声明了产品所具有的业务方法
 *      4. 它定义具体工厂生产的具体产品对象，实现抽象产品接口中声明的业务方法。在抽象工厂中声明了多个工厂方法，用于创建不同类型的产品
 */

#include<iostream>

//定义抽象产品类
class AbstractPhoneProduct {
public:
    virtual ~AbstractPhoneProduct() = default;
    virtual void productName() = 0;
    virtual void productIntroduce() = 0;

protected:
    AbstractPhoneProduct() = default;
};

class AbstractTvProduct {
public:
    virtual ~AbstractTvProduct() = default;
    virtual void productName() = 0;
    virtual void productIntroduce() = 0;

protected:
    AbstractTvProduct() = default;
};

//定义具体产品类

class HWPhone : public AbstractPhoneProduct {
public:
    HWPhone() = default;
    ~HWPhone() override {
        std::cout << "HWPhone Bye" << std::endl;
    }

    void productName() {
        std::cout << "This is a HWPhone " << std::endl;
    }

    void productIntroduce() {
        std::cout << "HWPhone Introduce" << std::endl;
    }
};

class MIPhone:public AbstractPhoneProduct{
public:
    MIPhone() = default;
    ~MIPhone() {
        std::cout << "bye MIPhone" << std::endl;
    }
    void productName() {
        std::cout << "This is a MIPhone " << std::endl;
    }
    void productIntroduce() {
        std::cout << "MIPhone Introduce" <<std::endl;
    }
};


class HWTV: public AbstractTvProduct {
public:
    HWTV() = default;
    ~HWTV() {
        std::cout << " bye HWTV " << std::endl;
    }

    void productName() {
        std::cout << " This is a HWTV " << std::endl;
    }

    void productIntroduce() {
        std::cout << "HWTV Introduce" << std::endl;
    }
};

class MITV : public AbstractTvProduct {
public:
    MITV() = default;
    ~MITV() {
        std::cout << "bye MITV " << std::endl;
    }

    void productName() {
        std::cout << " This is a MITV " << std::endl;
    }

    void productIntroduce() {
        std::cout << " MITV introduce " << std::endl;
    }
};

class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual AbstractPhoneProduct* createPhone() = 0;
    virtual AbstractTvProduct* createTV() = 0;

protected:
    AbstractFactory() = default;
};

class HWFactory : public AbstractFactory{
public:
    HWFactory() = default;

    ~HWFactory() {
        std::cout << "bye HWFactory " << std::endl;
    }

    AbstractPhoneProduct* createPhone() {
        return new HWPhone();
    }

    AbstractTvProduct* createTV() {
        return new HWTV();
    }
};

class MIFactory : public AbstractFactory {
public:
    MIFactory() = default;

    ~MIFactory() {
        std::cout << "bye MIFactory" << std::endl;
    }

    AbstractPhoneProduct* createPhone() {
        return new MIPhone();
    }

    AbstractTvProduct* createTV() {
        return new MITV();
    }
};

int main() {
    std::cout << "抽象工厂模式" << std::endl;

    AbstractTvProduct* TV  = nullptr;
    AbstractPhoneProduct* phone = nullptr;
    AbstractFactory* factory = nullptr;

    factory = new HWFactory();
    phone = factory->createPhone();
    phone->productName();
    TV = factory->createTV();
    TV->productIntroduce();
    delete factory;
    delete phone;
    delete TV;

    factory = new MIFactory();
    phone = factory->createPhone();
    phone->productName();
    TV = factory->createTV();
    TV->productIntroduce();
    delete factory;
    delete phone;
    delete TV;

    getchar();
    return 0;

}