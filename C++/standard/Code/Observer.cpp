#include<iostream>
#include<algorithm>
#include<memory>
#include<vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual int getId() = 0;
    virtual void update() = 0;
};

using ObserverPtr = std::shared_ptr<Observer>;

class IsEqualTo final {
public:
    explicit IsEqualTo(const ObserverPtr& observer)
        : observer{ observer } { }
    bool operator()(const ObserverPtr& observerToCompare) {
        return observerToCompare->getId() == observer->getId();
    }
private:
    ObserverPtr observer;
};

class Subject {
public:
    void addObserver(ObserverPtr& observerToAdd) {
        auto iter = std::find_if(begin(observers), end(observers),
                IsEqualTo(observerToAdd));
        if(iter == end(observers)) {
            observers.push_back(observerToAdd);
        }
    }
    void removeObserver(ObserverPtr& observerToRemove) {
        observers.erase(std::remove_if(begin(observers), end(observers),
                    IsEqualTo(observerToRemove)), end(observers));
    }
protected:
    void notifyAllObservers() const {
        for(const auto& observer : observers) {
            observer->update();
        }
    }
private:
    std::vector<ObserverPtr> observers;
};

class SpreadsheetModel : public Subject {
public:
    void changeCellValue(std::string_view column, const int row, const double value) {
        std::cout<<"Cell["<<column<<","<<row<<"] = "<<value<<std::endl;
        notifyAllObservers();
    }
};

class TableView : public Observer {
public:
    explicit TableView(SpreadsheetModel& theModel)
        : model{ theModel } { }
    int getId() override {
        return 1;
    }
    void update() override {
        std::cout<<"Upadate of TableView..."<<std::endl;
    }
private:
    SpreadsheetModel& model;
};

class BarChartView : public Observer {
public:
    explicit BarChartView(SpreadsheetModel& theModel)
        : model{ theModel } { }
    int getId() override {
        return 2;
    }
    void update() override {
        std::cout<<"Update of BarChartView..."<<std::endl;
    }
private:
    SpreadsheetModel& model;
};

class PieChartView : public Observer {
public:
    explicit PieChartView(SpreadsheetModel& theModel)
        : model{ theModel } { }
    int getId() override {
        return 3;
    }
    void update() override {
        std::cout<<"Update of PieChartView..."<<std::endl;
    }
private:
    SpreadsheetModel& model;
};

int main()
{
    SpreadsheetModel spreadsheetModel{};

    ObserverPtr observer1 = std::make_shared<TableView>(spreadsheetModel);
    spreadsheetModel.addObserver(observer1);

    ObserverPtr observer2 = std::make_shared<BarChartView>(spreadsheetModel);
    spreadsheetModel.addObserver(observer2);

    spreadsheetModel.changeCellValue("A", 1, 42);

    spreadsheetModel.removeObserver(observer1);

    spreadsheetModel.changeCellValue("B", 2, 23.1);

    ObserverPtr observer3 = std::make_shared<PieChartView>(spreadsheetModel);
    spreadsheetModel.addObserver(observer3);

    spreadsheetModel.changeCellValue("C", 3, 3.13444);

    return 0;
}

