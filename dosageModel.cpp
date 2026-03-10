#include <iostream>
#include <cmath>

double euler = 2.71828;

class blood {
    private:
        double weight; //Patient's weight measured in kilograms
        double initialDosage;//Measured in mcg
        double currentDosage; //Measured in mcg
        double concentration; //Meaured in mcg/kg
        double desiredConcentration; //Meaured in mcg/kg
        double halfLife; //Measured in hrs
        double k; //The const. of proportionality used to model the exponential decay of drug

        double minEffect; //The minimum effective concentration varies for each dosage type 
        // Assumptions for each dosage type:
        //Low = 1 mcg/kg
        //Mod. = 2 mcg/kg
        //high = 20 mcg/kg

        double minToxic; //The minimum effective concentration varies for each dosage type
        // Assumptions for each dosage type:
        //Low = 2 mcg/kg
        //Mod. = 20 mcg/kg
        //high = 50 mcg/kg

        int dosageType; //1 = low; 2 = moderate; 3 = high
    public:
        //Constructors:
        blood();

        //Getters:
        double getWeight(); 
        double getInitialDosage();
        double getCurrentDosage(); 
        double getConcentration();
        double getDesiredConcentration(); 
        double getHalfLife();
        double getK();
        double getMinEffect();
        double getMinToxic();
        int getDosageType();

        //Setters:
        void setWeight(double x); 
        void setInitialDosage(double x);
        void setCurrentDosage(double x); 
        void setConcentration(double x);
        void setDesiredConcentration(double x);
        void setHalfLife(double x);
        void setK(double x);
        void setMinEffect(double x);
        void setMinToxic(double x);
        void setDosageType(int x);

        //Utility:
        void degrade(double time); //Calculates to a specific time step of degradation (Accepts time in hrs)
        void model(double x); //Performs multiple degradations to create a table of concentration (Accepts hrs to be modeled)
        void model(double x, bool y); //Performs degradations without loading anymore drug (Accepts hrs to be modeled)
        void dose(double x); //Accepts an amount in micrograms administered to a patient
        void print(double time);

};

//Constructors:
blood::blood () {
    weight = 0;
    initialDosage = 0;
    currentDosage = 0; 
    concentration = 0;
    desiredConcentration = 0;
    halfLife = 0;
    k = 0;
    minEffect = 0;
    minToxic = 0;
    dosageType = 0; 
}

//Getters:
double blood::getWeight() {
    return weight;
}
double blood::getInitialDosage() {
    return initialDosage;
}
double blood::getCurrentDosage() {
    return currentDosage;
}
double blood::getConcentration() {
    return concentration;
}
double blood::getDesiredConcentration() {
    return desiredConcentration;
}
double blood::getHalfLife() {
    return halfLife;
}
double blood::getK() {
    return k;
}
double blood::getMinEffect() {
    return minEffect;
}
double blood::getMinToxic() {
    return minToxic;
}
int blood::getDosageType() {
    return dosageType; 
}

//Setters:
void blood::setWeight(double x) {
    weight = x;
}
void blood::setInitialDosage(double x) {
    initialDosage = x;
}
void blood::setCurrentDosage(double x) {
    currentDosage = x;
}
void blood::setConcentration(double x) {
    concentration = x;
}
void blood::setDesiredConcentration(double x) {
    desiredConcentration = x;
}
void blood::setHalfLife(double x) {
    halfLife = x;
}
void blood::setK(double x) {
    k = x;
}
void blood::setMinEffect(double x) {
    minEffect = x;
}
void blood::setMinToxic(double x) {
    minToxic = x;
}
void blood::setDosageType(int x) {
    dosageType = x; 
}
//Utility:
void blood::degrade (double time) {
    if (k == 0) {
        k = -log(0.5) / halfLife;
    }
    currentDosage = initialDosage * pow(euler, (-k*time)); //Q = Q_0 * e^(-K * time)
    concentration = currentDosage / weight; 
}
void blood::model(double x) {
    double maintenenceDose; //Should I include this in the class? ? ?
    double increment = 1;
    double time = increment;

    switch (dosageType) {
    case 1:
        minEffect = 1 / weight;
        minToxic = 2 / weight;
        break;
    case 2:
        minEffect = 2 / weight;
        minToxic = 20 / weight;
        break;
    case 3:
        minEffect = 20 / weight;
        minToxic = 50 / weight;
        break;
    default:
        std::cout << "\n\nError in model function of blood class. \n\n";
        break;
    }

    for (double count = 1; count <= x; count += increment) {
        degrade(time);
        if (concentration <= minEffect && concentration < minToxic) {
            std::cout << "Dosing\n\n";
            maintenenceDose = (desiredConcentration * weight) - (concentration * weight);
            time = increment;
            dose(maintenenceDose);
            print(count);
        }
        else {
            if (concentration > minToxic) {
                std::cout << minToxic << std::endl << "Too Toxic! ! !";
                return;  //If after degradation the amount of drug is over the limit then stop modelling
            }
        }
        
    }
}
void blood::model(double x, bool y) {
    double increment = 1;
    double time = increment;

    switch (dosageType) {
    case 1:
        minEffect = 1;
        minToxic = 2;
        break;
    case 2:
        minEffect = 2;
        minToxic = 20;
        break;
    case 3:
        minEffect = 20;
        minToxic = 50;
        break;
    default:
        std::cout << "\n\nError in model function of blood class. \n\n";
        break;
    }

    for (double count = 1; count <= x; count += increment) {
        if (concentration > minToxic) {
            std::cout << minToxic << std::endl << "Too Toxic! ! !";
            return;  //If after degradation the amount of drug is over the limit then stop modelling
        }

        degrade(count);
        
        print(count);
    }
}
void blood::dose(double x) {
    initialDosage = currentDosage + x;
}
void blood::print(double time) {
    std::cout << "Hour: " << time << std::endl;
    std::cout << "Current concentration: " << concentration  << " mcg/kg" << std::endl << std::endl;
}

//Blood Helper Functions:
void fentanylCitrate(blood& model) {
    model.setHalfLife(3.65);
}
/*
    weight = 0; *****
    initialDosage = 0; *****
    currentDosage = 0; 
    concentration = 0;
    halfLife = 0;
    k = 0;
    minEffect = 0;
    minToxic = 0;
    dosageType = 0; ****
*/
int main () {
    blood a;
    fentanylCitrate(a);
    a.setInitialDosage(3000);
    a.setWeight(60);
    a.setDesiredConcentration(300/60);
    a.setDosageType(1);

    a.model(24, 1);
    return 0; 
}