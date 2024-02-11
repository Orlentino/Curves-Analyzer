#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
// ������� ����� ��� ���� ������
class Curve
{
public:
    virtual vector<double> getPoint(double t) const = 0; // ��������� ����� �� ������ �� ��������� t
    virtual vector<double> getDerivative(double t) const = 0; // ��������� ������ ����������� �� ��������� t
    virtual ~Curve() {} // ����������� ���������� ��� ������������
};
// ����������� ������ ��� �����
class Circle : public Curve
{
private:
    double radius;
public:
    Circle(double r) : radius(max(0.0, r)) {} //���������� ������������� �������
    vector<double> getPoint(double t) const override
    {
        return
        {
            radius * cos(t), radius * sin(t), 0.0 //����� �� �����
        };
    }
    vector<double> getDerivative(double t) const override
    {
        return
        {
            -radius * sin(t), radius * cos(t), 0.0 //����������� (����������� ������)
        };
    }
    double getRadius() const
    {
        return radius;  //��������� ������� �����
    }
};
// ����������� ������ ��� �������
class Ellipse : public Curve
{
private:
    double radiusX, radiusY;
public:
    Ellipse(double rx, double ry) : radiusX(max(0.0, rx)), radiusY(max(0.0, ry)) {} //���������� ������������� �������
    vector<double> getPoint(double t) const override
    {
        return
        {
            radiusX * cos(t), radiusY * sin(t), 0.0 //����� �� �������
        };
    }
    vector<double> getDerivative(double t) const override
    {
        return
        {
            -radiusX * sin(t), radiusY * cos(t), 0.0 //����������� (����������� ������)
        };
    }
};
//����������� ������ ��� �������
class Helix : public Curve
{
private:
    double radius, step;
public:
    Helix(double r, double s) : radius(max(0.0, r)), step(s) {} //���������� ������������� �������
    vector<double> getPoint(double t) const override
    {
        return
        {
            radius * cos(t), radius * sin(t), step * t / (2 * M_PI)  //����� �� �������
        };
    }
    vector<double> getDerivative(double t) const override
    {
        return
        {
            -radius * sin(t), radius * cos(t), step / (2 * M_PI) //����������� (����������� ������)
        };
    }
};

int main()
{
    srand(time(NULL));
    //��������� ��������� ���������� �������
    vector<Curve*> curves;
    int n = rand();
    while (n == 0)
        n = rand();
    for (int i = 0; i < n; i++)
    {
        double r1 = rand(); // ������
        double r2 = rand(); // ������ ��� �������
        double s = rand(); // ��� �������
        int type = rand() % 3; // ��� ������
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
    //������� ���������� ����� � ����������� ���� ������ ��� t = PI/4
    cout << "Coordinates and derivatives at t=PI/4:\n";
    for (Curve* curve : curves)
    {
        vector<double> point = curve->getPoint(M_PI / 4);
        vector<double> derivative = curve->getDerivative(M_PI / 4);
        cout << "Point: (" << point[0] << ", " << point[1] << ", " << point[2] << "), ";
        cout << "Derivative: (" << derivative[0] << ", " << derivative[1] << ", " << derivative[2] << ")\n";
    }
    //������� ������ ��������� � ������� ����� ���������
    vector<Circle*> circles;
    for (Curve* curve : curves)
    {
        if (dynamic_cast<Circle*>(curve))//���������, �������� �� ������ ������
        {
            circles.push_back(static_cast<Circle*>(curve));
        }
    }
    //��������� ��������� ������ �� �������
    sort(circles.begin(), circles.end(), [](const Circle* a, const Circle* b) {
        return a->getRadius() < b->getRadius();
        });
    //��������� ����� �������� ���� ������ �� ������ ����������
    double sumRadii = 0;
    for (const Circle* circle : circles)
    {
        sumRadii += circle->getRadius();
    }
    cout << "Total sum of radii of circles: " << sumRadii << endl;
    //������ ������
    for (Curve* curve : curves)
    {
        delete curve;
    }
    return 0;
}