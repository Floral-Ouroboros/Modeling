#include <iostream>
#include <cmath>
#include <fstream>

class disease {
    private:
        double susceptible;
        double exposed;
        double infected;
        double recovered;
        double days; // The average amount of time one spend infected
        double incubation; // The average incubation period
        double transmissionConstant; // % of possible contacts that are infected per day
    public:
        //Constructors:
        disease();

        //Setters:
        void setSusceptible(double x);
        void setExposed(double x);
        void setInfected(double x);
        void setRecovered(double x);
        void setDays(double x);
        void setTransmissionConstant(double x);
        void setIncubation(double x);

       //Getters:
       double getSusceptible();
       double getExposed();
       double getInfected();
       double getRecovered();
       double getDays();
       double getTransmissionConstant();
       double getIncubation();

       //Utilities:
       void calculateExposed();
       void calculateInfected();
       void calculateRecovered();
       void calculateTranmissionConstant(); //Add later
       void model(double x); //Model situation for x amount of days

};

//Constructors:
disease::disease() {
    double susceptible= 0;
    double exposed = 0;
    double infected = 0;
    double recovered = 0;
    double days = 0; // The average amount of time one spend infected
    double transmissionConstant = 0; // % of possible contacts that are infected per day
}

//Setters:
void disease::setSusceptible(double x) {
    susceptible = x;
}
void disease::setExposed(double x) {
    exposed = x;
}
void disease::setInfected(double x) {
    infected = x;
}
void disease::setRecovered(double x) {
    recovered = x;
}
void disease::setDays(double x) {
    days = x;
}
void disease::setTransmissionConstant(double x) {
    transmissionConstant = x;
}
void disease::setIncubation(double x) {
    incubation = x;
}

//Getters:
double disease::getSusceptible() {
    return susceptible;
}
double disease::getExposed() {
    return exposed;
}
double disease::getInfected() {
    return infected;
}
double disease::getRecovered() {
    return recovered;
}
double disease::getDays() {
    return days;
}
double disease::getTransmissionConstant() {
    return transmissionConstant;
}
double disease::getIncubation() {
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
void disease::model(double x) {
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