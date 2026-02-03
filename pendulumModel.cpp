#include <iostream>
#include <cmath>
#include <fstream>

// * * * * * NOT WORKING CODE * * * * *

float pi = 3.14159;
float grav = 9.81;
float delT = 0.01;

class pendulum {
    private:
        float bobMass; //measured in grams
        float bobWeight; //measured in grams
        float stringLength; //measured in m
        float force; //measured in newtons
        float bobAngle; //measured in radians
        float angularAcceleration; //measured in radians
        float angularVelocity; //measured in radians
    public:
        //Constructors:
            pendulum();
        //Setters:
            void setBobMass(float x);
            void setBobWeight(float x);
            void setStringLength(float x);
            void setForce(float x);
            void setBobAngle(float x);
            void setAngularAcceleration(float x);
            void setAngularVelocity(float x);
        //Getters:
            float getBobMass();
            float getBobWeight();
            float getStringLength();
            float getForce();
            float getBobAngle();
            float getAngularAcceleration();
            float getAngularVelocity();
        //Utility:
            void calculateBobWeight();
            void calculateAngularAcceleration();
            void calculateForce();
            void print();
            void model(float runTime); //runTime is measured in sec and the duration of modelling
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
void pendulum::setBobMass(float x) {
    bobMass = x;
}
void pendulum::setBobWeight(float x) {
    bobWeight = x;
}
void pendulum::setStringLength(float x) {
    stringLength = x;
}
void pendulum::setForce(float x) {
    force = x;
}
void pendulum::setBobAngle(float x) {
    bobAngle = x;
}
void pendulum::setAngularAcceleration(float x) {
    angularAcceleration = x;
}
void pendulum::setAngularVelocity(float x) {
    angularVelocity = x;
}

//Getters:
float pendulum::getBobMass() {
    return bobMass;
}
float pendulum::getBobWeight() {
    return bobWeight;
}
float pendulum::getStringLength() {
    return stringLength;
}
float pendulum::getForce() {
    return force;
}
float pendulum::getBobAngle() {
    return bobAngle;
}
float pendulum::getAngularAcceleration() {
    return angularAcceleration;
}
float pendulum::getAngularVelocity() {
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
void pendulum::model(float runTime) {
    std::ofstream data;
    data.open("pendulumData.txt");

    for (float time = 0; time <= runTime; time += delT) {
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