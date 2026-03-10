#include <iostream>
#include <fstream>

class reaction {
    private:
        double substrate; //Amount of substrate, measured in Molar.
        double enzyme; //Amount of enzyme, measured in Molar.
        double enzymeComplex; //Amount of combined enzyme and substrate, measured in Molar.
        double product; //Amount of product, measured in Molar.
        double K1; //Rate of change of Enzyme + Substrate --> Enzyme_ Complex
        double K2; //Rate of change of Enzyme_Complex --> Enzyme + Substrate
        double K3; //Rate of change of Enzyme_ Complex --> Enzyme + Product
        double K4; //Rate of change of Enzyme + Product --> Enzyme_ Complex
        double enzymeDegradation; //A proportionality constant used to degrade the enzyme ( % per sec)

    public:
        //Constructors:
        reaction();

        //Setters:
        void setSubstrate(double x); 
        void setEnzyme(double x); 
        void setEnzymeComplex(double x); 
        void setProduct(double x);
        void setK1(double x); 
        void setK2(double x); 
        void setK3(double x); 
        void setK4(double x); 
        void setEnzymeDegradation(double x);

        //Getters:
        double getSubstrate(); 
        double getEnzyme(); 
        double getEnzymeComplex(); 
        double getProduct();
        double getK1(); 
        double getK2(); 
        double getK3(); 
        double getK4(); 
        double getEnzymeDegradation();

        //Utility:
        void model(double time, double delt); //The amount of time we want to model (seconds) and the timestep length
        void model(double delt);
        void twoPartModel(double delt, double& p);
};

//Constructors:
reaction::reaction() {
    substrate = 0; 
    enzyme = 0; 
    enzymeComplex = 0;
    product = 0; 
    K1 = 0;
    K2 = 0; 
    K3 = 0;
    K4 = 0;
    enzymeDegradation = 1;
}

//Setters:
void reaction::setSubstrate(double x) {
    substrate = x;
}
void reaction::setEnzyme(double x) {
    enzyme = x;
}
void reaction::setEnzymeComplex(double x) {
    enzymeComplex = x;
}
void reaction::setProduct(double x) {
    product = x;
}
void reaction::setK1(double x) {
    K1 = x;
}
void reaction::setK2(double x) {
    K2 = x;
}
void reaction::setK3(double x) {
    K3 = x;
}
void reaction::setK4(double x) {
    K4 = x;
}
void reaction::setEnzymeDegradation(double x) {
    enzymeDegradation = x;
}

//Getters:
double reaction::getSubstrate() {
    return substrate;
}
double reaction::getEnzyme() {
    return enzyme;
}
double reaction::getEnzymeComplex() {
    return enzymeComplex;
}
double reaction::getProduct() {
    return product;
}
double reaction::getK1() {
    return K1;
}
double reaction::getK2() {
    return K2;
}
double reaction::getK3() {
    return K3;
}
double reaction::getK4() {
    return K4;
}
double reaction::getEnzymeDegradation() {
    return enzymeDegradation;
}

//Utility:
void reaction::model(double time, double delt) { //The amount of time we want to model (seconds) and the timestep length
    std::ofstream sub, com, pro, enz;
    //The vairables are so we don't change things we need for further calculation
    double complexStorage; 
    double substrateStorage;
    double productStorage;
    double enzymeStorage;

    //Opening the files used to log results:
    sub.open("enzymeModel_Substrate.txt");
    com.open("enzymeModel_Complex.txt");
    pro.open("enzymeModel_Product.txt");
    enz.open("enzymeModel_Enzyme.txt");

    for (double t = 0; t <= time; t += delt) {
        complexStorage = enzymeComplex; 
        substrateStorage = substrate;
        productStorage = product;
        enzymeStorage = enzyme;

        //Storage in file:
        sub << substrate << std::endl;
        com << enzymeComplex << std::endl;
        pro << product << std::endl;
        enz << enzyme << std::endl;

        //enzyme *= (1 - enzymeDegradation) * delt; //Degradation

        //Calculation
        substrate += (K2 * complexStorage) - (K1 * enzymeStorage * substrateStorage);
        product += (K3 * complexStorage) - (K4 * enzymeStorage * productStorage);
        enzyme += ((K2 + K3) * complexStorage) -(K1 * enzymeStorage * substrateStorage) - (K4 * enzymeStorage * productStorage);
        enzymeComplex += (K1 * enzymeStorage * substrateStorage) + (K4 * enzymeStorage * productStorage) - ((K2 + K3) * complexStorage);

    }

    //Closing logging files:
    sub.close();
    com.close();
    pro.close();
    enz.close();
}

void reaction::model(double delt) {
    //The vairables are so we don't change things we need for further calculation
    double complexStorage; 
    double substrateStorage;
    double productStorage;
    double enzymeStorage;

    complexStorage = enzymeComplex; 
    substrateStorage = substrate;
    productStorage = product;
    enzymeStorage = enzyme;

    if (enzymeDegradation != 1) {
        enzyme *= (1 - enzymeDegradation) * delt; //Degradation
    }
    

    //Calculation:
    substrate += (K2 * complexStorage) - (K1 * enzymeStorage * substrateStorage);
    product += (K3 * complexStorage) - (K4 * enzymeStorage * productStorage);
    enzyme += ((K2 + K3) * complexStorage) -(K1 * enzymeStorage * substrateStorage) - (K4 * enzymeStorage * productStorage);
    enzymeComplex += (K1 * enzymeStorage * substrateStorage) + (K4 * enzymeStorage * productStorage) - ((K2 + K3) * complexStorage);
}

void reaction::twoPartModel(double delt, double& p) {
    //The vairables are so we don't change things we need for further calculation
    double complexStorage; 
    double substrateStorage;
    double productStorage;
    double enzymeStorage;

    complexStorage = enzymeComplex; 
    substrateStorage = substrate;
    productStorage = p;
    enzymeStorage = enzyme;

    enzyme *= (1 - enzymeDegradation) * delt; //Degradation

    //Calculation:
    substrate += (K2 * complexStorage) - (K1 * enzymeStorage * substrateStorage);
    product += (K3 * complexStorage) - (K4 * enzymeStorage * productStorage);
    p += (K3 * complexStorage) - (K4 * enzymeStorage * productStorage);
    enzyme += ((K2 + K3) * complexStorage) -(K1 * enzymeStorage * substrateStorage) - (K4 * enzymeStorage * productStorage);
    enzymeComplex += (K1 * enzymeStorage * substrateStorage) + (K4 * enzymeStorage * productStorage) - ((K2 + K3) * complexStorage);
}