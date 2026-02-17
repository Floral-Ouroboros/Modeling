#include <iostream>
#include <cmath>
#include <fstream>

class disease {
    private:
        float susceptible;
        float exposed;
        float infected;
        float recovered;
        float days; // The average amount of time one spend infected
        float incubation; // The average incubation period
        float transmissionConstant; // % of possible contacts that are infected per day
    public:
        //Constructors:
        disease();

        //Setters:
        void setSusceptible(float x);
        void setExposed(float x);
        void setInfected(float x);
        void setRecovered(float x);
        void setDays(float x);
        void setTransmissionConstant(float x);
        void setIncubation(float x);

       //Getters:
       float getSusceptible();
       float getExposed();
       float getInfected();
       float getRecovered();
       float getDays();
       float getTransmissionConstant();
       float getIncubation();

       //Utilities:
       void calculateExposed();
       void calculateInfected();
       void calculateRecovered();
       void calculateTranmissionConstant(); //Add later
       void model(float x); //Model situation for x amount of days

};

//Constructors:
disease::disease() {
    float susceptible= 0;
    float exposed = 0;
    float infected = 0;
    float recovered = 0;
    float days = 0; // The average amount of time one spend infected
    float transmissionConstant = 0; // % of possible contacts that are infected per day
}

//Setters:
void disease::setSusceptible(float x) {
    susceptible = x;
}
void disease::setExposed(float x) {
    exposed = x;
}
void disease::setInfected(float x) {
    infected = x;
}
void disease::setRecovered(float x) {
    recovered = x;
}
void disease::setDays(float x) {
    days = x;
}
void disease::setTransmissionConstant(float x) {
    transmissionConstant = x;
}
void disease::setIncubation(float x) {
    incubation = x;
}

//Getters:
float disease::getSusceptible() {
    return susceptible;
}
float disease::getExposed() {
    return exposed;
}
float disease::getInfected() {
    return infected;
}
float disease::getRecovered() {
    return recovered;
}
float disease::getDays() {
    return days;
}
float disease::getTransmissionConstant() {
    return transmissionConstant;
}
float disease::getIncubation() {
    return incubation;
}

//Utilities:
void disease::calculateExposed() {
    exposed += transmissionConstant * susceptible * infected;
    susceptible -= transmissionConstant * susceptible * infected;
}
void disease::calculateInfected() {
    infected += (1 / incubation) * exposed;
    exposed -= (1 / incubation) * exposed;
}
void disease::calculateRecovered() {
    recovered += (1 / days) * infected;
    infected -= (1 / days) * infected;
}
void disease::calculateTranmissionConstant() {
    //Add later
} 
void disease::model(float x) {
    std::ofstream sus, exp, inf, rec;;


    sus.open("diseaseModel_Susceptibles.txt");
    exp.open("diseaseModel_Exposed.txt");
    inf.open("diseaseModel_Infected.txt");
    rec.open("diseaseModel_Recovered.txt");
    
    for (int time = 0; time <= x; time++) {
        sus << susceptible << std::endl;

        calculateRecovered();
        rec << recovered << std::endl;

        calculateInfected();
        inf << infected << std::endl;

        calculateExposed();
        exp << exposed << std::endl;
    }

    sus.close();
    exp.close();
    inf.close();
    rec.close();
}


int main() {
    disease x;
    x.setSusceptible(800);
    x.setTransmissionConstant(0.00218);
    x.setInfected(1);
    x.setDays(2);
    x.setIncubation(3);

    x.model(90);

    return 0;
}