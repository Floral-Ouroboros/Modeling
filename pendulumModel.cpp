#include <iostream>
#include <cmath>
#include <fstream>

// * * * * * NOT WORKING CODE * * * * *

double pi = 3.14159;
double grav = 9.81;
double delT = 0.01;

class pendulum {
    private:
        double bobMass; //measured in grams
        double bobWeight; //measured in grams
        double stringLength; //measured in m
        double force; //measured in newtons
        double bobAngle; //measured in radians
        double angularAcceleration; //measured in radians
        double angularVelocity; //measured in radians
    public:
        //Constructors:
            pendulum();
        //Setters:
            void setBobMass(double x);
            void setBobWeight(double x);
            void setStringLength(double x);
            void setForce(double x);
            void setBobAngle(double x);
            void setAngularAcceleration(double x);
            void setAngularVelocity(double x);
        //Getters:
            double getBobMass();
            double getBobWeight();
            double getStringLength();
            double getForce();
            double getBobAngle();
            double getAngularAcceleration();
            double getAngularVelocity();
        //Utility:
            void calculateBobWeight();
            void calculateAngularAcceleration();
            void calculateForce();
            void print();
            void model(double runTime); //runTime is measured in sec and the duration of modelling
};

//Constructors:
pendulum::pendulum() {
    bobMass = 0;
    bobWeight = 0;
    stringLength = 0;
    force = 0;
    bobAngle = 0;
    angularAcceleration = 0;
    angularVelocity = 0;
}

//Setters:
void pendulum::setBobMass(double x) {
    bobMass = x;
}
void pendulum::setBobWeight(double x) {
    bobWeight = x;
}
void pendulum::setStringLength(double x) {
    stringLength = x;
}
void pendulum::setForce(double x) {
    force = x;
}
void pendulum::setBobAngle(double x) {
    bobAngle = x;
}
void pendulum::setAngularAcceleration(double x) {
    angularAcceleration = x;
}
void pendulum::setAngularVelocity(double x) {
    angularVelocity = x;
}

//Getters:
double pendulum::getBobMass() {
    return bobMass;
}
double pendulum::getBobWeight() {
    return bobWeight;
}
double pendulum::getStringLength() {
    return stringLength;
}
double pendulum::getForce() {
    return force;
}
double pendulum::getBobAngle() {
    return bobAngle;
}
double pendulum::getAngularAcceleration() {
    return angularAcceleration;
}
double pendulum::getAngularVelocity() {
    return angularVelocity;
}

//Utility:
void pendulum::calculateForce() {
    force = bobMass * angularAcceleration;
}
void pendulum::calculateBobWeight() {
    bobWeight = bobMass * grav;
}
void pendulum::calculateAngularAcceleration() {
    angularAcceleration = -grav * sin(bobAngle) / stringLength;
}
void pendulum::print() {
    std::cout << angularAcceleration << std::endl;
}
void pendulum::model(double runTime) {
    std::ofstream data;
    data.open("pendulumData.txt");

    for (double time = 0; time <= runTime; time += delT) {
        calculateAngularAcceleration();
        angularVelocity +=  delT / angularAcceleration;
        bobAngle += angularVelocity;

        print();
        data << angularAcceleration << std::endl;
    }

    data.close();
}



int main() {
    pendulum x;
    x.setBobAngle(pi/4);
    x.setStringLength(1);

    x.model(6);
    return 0;
}

// * * * * * NOT WORKING CODE * * * * *