#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>

class Employee;

using EmployeePtr = std::shared_ptr<Employee>;

class EmployeeWorkPlace {
public:
    virtual ~EmployeeWorkPlace() = default;
    virtual void addEmployee(const EmployeePtr employee) = 0;
    virtual void removeEmployee(const Employee& employee) = 0;
};

using EmployeeWorkPlacePtr = std::shared_ptr<EmployeeWorkPlace>;

class Employee {
public:
    explicit Employee(const std::string& initialEmployeeName,
                      const EmployeeWorkPlacePtr initialEmployeeWorkPlace)
        : employeeName{ initialEmployeeName },
          employeeWorkPlace{ initialEmployeeWorkPlace} { }
    void setWorkPlace(const EmployeeWorkPlacePtr newWorkPlace) {
        employeeWorkPlace = newWorkPlace;
    }
private:
    std::string employeeName;
    EmployeeWorkPlacePtr employeeWorkPlace;
};

using EmployeeCollection = std::vector<EmployeePtr>;

class CompanyOfNiu : public EmployeeWorkPlace, public std::enable_shared_from_this<CompanyOfNiu> {
public:
    void addEmployee(const EmployeePtr employee) override {
        employees.push_back(employee);
        //设置员工的工作场所为当前公司
        employee->setWorkPlace(shared_from_this());
    }
    void removeEmployee(const Employee& employee) override {
        employees.erase(std::remove_if(begin(employees), end(employees),
                    [&](const EmployeePtr& s){
                        return s.get() == &employee;
                    }), end(employees));
    }
private:
    EmployeeCollection employees;
};

class CompanyOfTom : public EmployeeWorkPlace, public std::enable_shared_from_this<CompanyOfTom> {
public:
    void addEmployee(const EmployeePtr employee) override {
        employees.push_back(employee);
        //设置员工的工作场所为当前公司
        employee->setWorkPlace(shared_from_this());
    }
    void removeEmployee(const Employee& employee) override {
        employees.erase(std::remove_if(begin(employees), end(employees),
                    [&](const EmployeePtr& s){
                        return s.get() == &employee;
                    }), end(employees));
    }
private:
    EmployeeCollection employees;
};

class CompanyOfBob : public EmployeeWorkPlace, public std::enable_shared_from_this<CompanyOfBob> {
public:
    void addEmployee(const EmployeePtr employee) override {
        employees.push_back(employee);
        //设置员工的工作场所为当前公司
        employee->setWorkPlace(shared_from_this());
    }
    void removeEmployee(const Employee& employee) override {
        employees.erase(std::remove_if(begin(employees), end(employees),
                    [&](const EmployeePtr& s){
                        return s.get() == &employee;
                    }), end(employees));
    }
private:
    EmployeeCollection employees;
};

using CompanyOfNiuPtr = std::shared_ptr<CompanyOfNiu>;
using CompanyOfTomPtr = std::shared_ptr<CompanyOfTom>;
using CompanyOfBobPtr = std::shared_ptr<CompanyOfBob>;

int main()
{
    CompanyOfNiuPtr companyOfNiu = std::make_shared<CompanyOfNiu>();
    CompanyOfBobPtr companyOfBob = std::make_shared<CompanyOfBob>();
    CompanyOfTomPtr companyOfTom = std::make_shared<CompanyOfTom>();

    EmployeePtr employee1 = std::make_shared<Employee>("niu0217", companyOfNiu);
    EmployeePtr employee2 = std::make_shared<Employee>("leidazao", companyOfNiu);
    EmployeePtr employee3 = std::make_shared<Employee>("madongmei", companyOfNiu);

    companyOfNiu->addEmployee(employee1);
    companyOfNiu->addEmployee(employee2);

    companyOfNiu->removeEmployee(*employee2);

    companyOfNiu->addEmployee(employee3);

    companyOfBob->addEmployee(employee2);
    employee2->setWorkPlace(companyOfBob);
}

