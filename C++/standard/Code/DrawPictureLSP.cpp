#include<iostream>
#include<memory>
#include<vector>

class Point final {
public:
    Point() : x{ 5 }, y{ 5 } { }
    Point(const unsigned int initialX, const unsigned int initialY) :
        x{ initialX }, y{ initialY } { }
    void setCoordinates(const unsigned int newX, const unsigned int newY) {
        x = newX;
        y = newY;
    }
private:
    unsigned int x;
    unsigned int y;
};

class Shape {
public:
    Shape() : isVisible{ false } { }
    virtual ~Shape() = default;
    virtual void moveTo(const Point& newCenterPoint) {
        hide();
        centerPoint = newCenterPoint;
        show();
    }
    virtual void show();
    virtual void hide();
private:
    Point centerPoint;
    bool isVisible;
};

void Shape::show() {
    isVisible = true;
}

void Shape::hide() {
    isVisible = false;
}

class Rectangle : public Shape {
public:
    Rectangle() : width{ 2 }, height{ 1 } { }
    Rectangle(const unsigned int initialWidth, const unsigned int initialHeight) :
        width{ initialWidth }, height{ initialHeight } { }
    void show() override {
        Shape::show();
        std::cout<<"Rectangle"<<std::endl;
    }
    void hide() override {
        Shape::hide();
    }
    void setWidth(const unsigned int newWidth) {
        width = newWidth;
    }
    void setHeight(const unsigned int newHeight) {
        height = newHeight;
    }
    void setEdges(const unsigned int newWidth, const unsigned int newHeight) {
        width = newWidth;
        height = newHeight;
    }
    unsigned long long getArea() const {
        return static_cast<unsigned long long>(width) * height;
    }
private:
    unsigned int width;
    unsigned int height;
};

class Square : public Shape {
public:
    Square() {
        impl.setEdges(5, 5);
    }
    explicit Square(const unsigned int edgeLength) {
        impl.setEdges(edgeLength, edgeLength);
    }
    void setEdge(const unsigned int length) {
        impl.setEdges(length, length);
    }
    void moveTo(const Point& newCenterPoint) override {
        impl.moveTo(newCenterPoint);
    }
    void show() override {
        std::cout<<"Square ";
        impl.show();
    }
    void hide() override {
        impl.hide();
    }
    unsigned long long getArea() const {
        return impl.getArea();
    }
private:
    Rectangle impl;
};

using ShapePtr = std::shared_ptr<Shape>;
using ShapeCollection = std::vector<ShapePtr>;

void showAllShapes(const ShapeCollection& shapes) {
    for(auto& shape : shapes) {
        shape->show();
    }
}

int main()
{
    ShapeCollection shapes;
    shapes.push_back(std::make_shared<Rectangle>());
    shapes.push_back(std::make_shared<Square>());
    showAllShapes(shapes);
}

