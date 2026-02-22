#include <iostream>
#include <fstream>
#include "enzyme.h"

/*
Need:
External environment struct
Internal environment class- two enzymes
*/

struct environment {
    float glucose; //Amount of glucose, measured in Molar.
    float lactose; //Amount of lactose, measured in Molar.
    float galactose; //Amount of galactose, measured in Molar.
};

class organism {
    private:
        float glucose; //Amount of glucose, measured in Molar.
        float lactose; //Amount of lactose, measured in Molar.
        float galactose; //Amount of galactose, measured in Molar.
        float transportEfficiencyLactose; //The amount of lactose (M) that the organism can take in per second
        reaction lactoseDecom; //Enzyme model defined in "enzyme.h"
        environment stage;

    public:
        //Constructors:
        organism(); //Default Constructor

        //Setters:
        void setGlucose(float x);
        void setLactose(float x);
        void setGalactose(float x);
        void setSubstrate(float x);
        void setEnzyme(float x);
        void setK1(float x);
        void setK2(float x);
        void setK3(float x);
        void setK4(float x);
        void setTransportEfficiencyLactose(float x);

        //Getters:
        float getGlucose();
        float getLactose();
        float getGalactose();
        float getSubstrate();
        float getEnzyme();
        float getK1();
        float getK2();
        float getK3();
        float getK4();
        float getTransportEfficiencyLactose();

        //Utility:
        void transport();
        void model();
};

//Constructors:
organism::organism() { //Default Constructor
    glucose = 0; 
    lactose = 0; 
    galactose = 0; 
    transportEfficiencyLactose = 0; 
    lactoseDecom;
    stage;
}

//Setters:
void organism::setGlucose(float x) {
    glucose = x;
}
void organism::setLactose(float x) {
    lactose = x;
}
void organism::setGalactose(float x) {
    galactose = x;
}
void organism::setSubstrate(float x) {
    lactoseDecom.setSubstrate(x);
}
void organism::setEnzyme(float x) {
    lactoseDecom.setEnzyme(x);
}
void organism::setK1(float x) {
    lactoseDecom.setK1(x);
}
void organism::setK2(float x) {
    lactoseDecom.setK2(x);
}
void organism::setK3(float x) {
    lactoseDecom.setK3(x);
}
void organism::setK4(float x) {
    lactoseDecom.setK4(x);
}
void organism::setTransportEfficiencyLactose(float x) {
    transportEfficiencyLactose = x;
}

//Getters:
float organism::getGlucose() {
    return glucose;
}
float organism::getLactose() {
    return lactose;
}
float organism::getGalactose() {
    return galactose;
}
float organism::getSubstrate() {
    return lactoseDecom.getSubstrate();
}
float organism::getEnzyme() {
    return lactoseDecom.getEnzyme();
}
float organism::getK1() {
    return lactoseDecom.getK1();
}
float organism::getK2() {
    return lactoseDecom.getK2();
}
float organism::getK3() {
    return lactoseDecom.getK3();
}
float organism::getK4() {
    return lactoseDecom.getK4();
}
float organism::getTransportEfficiencyLactose() {
    return transportEfficiencyLactose;
}

//Utility:
void organism::transport() {
    lactose += transportEfficiencyLactose * stage.lactose;

    // ! ! ! Add a separate one for glucose ! ! !
}
void organism::model() {
    // Place holder
}



int main() {
    std::cout << "testing";
    return 0;
}