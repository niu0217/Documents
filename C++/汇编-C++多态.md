# 汇编-C++多态

## 1. 案例1

代码：

```c++
#include<iostream>
using namespace std;

class Animal {
public:
    virtual void speak() {
        cout<<"I am base"<<endl;
    }
    virtual void run() {
        cout<<"Running"<<endl;
    }
};

class Cat: public Animal {
public:
    void speak() override {
        cout<<"I am a cat"<<endl;
    }
};

class Dog: public Animal {
public:
    void run() override {
        cout<<"Dog running"<<endl;
    }
};

int main()
{
    Cat cat_object;
    Dog dog_object;
    Animal *animal_object_ptr = new Animal();
    animal_object_ptr = &cat_object;
    animal_object_ptr->speak();
    animal_object_ptr->run();
}
```

