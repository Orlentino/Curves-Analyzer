#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
// Базовый класс для всех кривых
class Curve
{
public:
    virtual vector<double> getPoint(double t) const = 0; // Получение точки на кривой по параметру t
    virtual vector<double> getDerivative(double t) const = 0; // Получение первой производной по параметру t
    virtual ~Curve() {} // Виртуальный деструктор для полиморфизма
};
// Определение класса для круга
class Circle : public Curve
{
private:
    double radius;
public:
    Circle(double r) : radius(max(0.0, r)) {} //Исправляем отрицательные радиусы
    vector<double> getPoint(double t) const override
    {
        return
        {
            radius * cos(t), radius * sin(t), 0.0 //Точка на круге
        };
    }
    vector<double> getDerivative(double t) const override
    {
        return
        {
            -radius * sin(t), radius * cos(t), 0.0 //Производная (касательный вектор)
        };
    }
    double getRadius() const
    {
        return radius;  //Получение радиуса круга
    }
};
// Определение класса для эллипса
class Ellipse : public Curve
{
private:
    double radiusX, radiusY;
public:
    Ellipse(double rx, double ry) : radiusX(max(0.0, rx)), radiusY(max(0.0, ry)) {} //Исправляем отрицательные радиусы
    vector<double> getPoint(double t) const override
    {
        return
        {
            radiusX * cos(t), radiusY * sin(t), 0.0 //Точка на эллипсе
        };
    }
    vector<double> getDerivative(double t) const override
    {
        return
        {
            -radiusX * sin(t), radiusY * cos(t), 0.0 //Производная (касательный вектор)
        };
    }
};
//Определение класса для спирали
class Helix : public Curve
{
private:
    double radius, step;
public:
    Helix(double r, double s) : radius(max(0.0, r)), step(s) {} //Исправляем отрицательные радиусы
    vector<double> getPoint(double t) const override
    {
        return
        {
            radius * cos(t), radius * sin(t), step * t / (2 * M_PI)  //Точка на спирали
        };
    }
    vector<double> getDerivative(double t) const override
    {
        return
        {
            -radius * sin(t), radius * cos(t), step / (2 * M_PI) //Производная (касательный вектор)
        };
    }
};

int main()
{
    srand(time(NULL));
    //Заполняем контейнер случайными кривыми
    vector<Curve*> curves;
    int n = rand();
    while (n == 0)
        n = rand();
    for (int i = 0; i < n; i++)
    {
        double r1 = rand(); // Радиус
        double r2 = rand(); // Радиус для эллипса
        double s = rand(); // Шаг спирали
        int type = rand() % 3; // Тип кривой
        Curve* curve;
        switch (type)
        {
        case 0:
            curve = new Circle(r1);
            break;
        case 1:
            curve = new Ellipse(r1, r2);
            break;
        case 2:
            curve = new Helix(r1, s);
            break;
        }
        curves.push_back(curve);
    }
    //Выводим координаты точек и производных всех кривых при t = PI/4
    cout << "Coordinates and derivatives at t=PI/4:\n";
    for (Curve* curve : curves)
    {
        vector<double> point = curve->getPoint(M_PI / 4);
        vector<double> derivative = curve->getDerivative(M_PI / 4);
        cout << "Point: (" << point[0] << ", " << point[1] << ", " << point[2] << "), ";
        cout << "Derivative: (" << derivative[0] << ", " << derivative[1] << ", " << derivative[2] << ")\n";
    }
    //Создаем второй контейнер с кругами через указатели
    vector<Circle*> circles;
    for (Curve* curve : curves)
    {
        if (dynamic_cast<Circle*>(curve))//Проверяем, является ли кривая кругом
        {
            circles.push_back(static_cast<Circle*>(curve));
        }
    }
    //Сортируем контейнер кругов по радиусу
    sort(circles.begin(), circles.end(), [](const Circle* a, const Circle* b) {
        return a->getRadius() < b->getRadius();
        });
    //Вычисляем сумму радиусов всех кругов во втором контейнере
    double sumRadii = 0;
    for (const Circle* circle : circles)
    {
        sumRadii += circle->getRadius();
    }
    cout << "Total sum of radii of circles: " << sumRadii << endl;
    //Чистим память
    for (Curve* curve : curves)
    {
        delete curve;
    }
    return 0;
}