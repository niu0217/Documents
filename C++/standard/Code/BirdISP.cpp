#include<iostream>
#include<vector>
#include<memory>

class Lifeform {
public:
    virtual void eat() = 0;
    virtual void move() = 0;
};

class Flyable {
public:
    virtual void fly();
};

class Audiable {
public:
    virtual void makeSound() = 0;
};

class Sparrow : public Lifeform, public Flyable, public Audiable {

};

class Penguin : public Lifeform, public Audiable {

};

