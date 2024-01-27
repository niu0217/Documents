#include <iostream>
#include <string>

//Strategy
class Weapon {
public:
    virtual std::string fightAlgorithm() const = 0;
};

class Nife : public Weapon {
public:
    std::string fightAlgorithm() const override {
        return "使用匕首计算损伤。";
    }
};
class Axe : public Weapon {
public:
    std::string fightAlgorithm() const override {
        return "使用斧子计算损伤。";
    }
};
//Context
class Hero {
private:
    Weapon* m_weapon;
public:
    Hero(Weapon* weapon = nullptr) :m_weapon(weapon) {}
    void setWeapon(Weapon* weapon) { m_weapon = weapon; }

    void fight() {
        std::cout << m_weapon->fightAlgorithm() << "\n";
    }
};
int main()
{
    std::cout << "客户端：英雄使用匕首攻击。\n";
    Nife nife;
    Hero hero(&nife);
    hero.fight();
    std::cout << "客户端：英雄使用斧子攻击。\n";
    Axe axe;
    hero.setWeapon(&axe);
    hero.fight();
}
