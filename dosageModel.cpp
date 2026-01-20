#include <iostream>
#include <cmath>

float euler = 2.71828;

class blood {
    private:
        float weight; //Patient's weight measured in kilograms
        float initialDosage;//Measured in mcg
        float currentDosage; //Measured in mcg
        float concentration; //Meaured in mcg/kg
        float desiredConcentration; //Meaured in mcg/kg
        float halfLife; //Measured in hrs
        float k; //The const. of proportionality used to model the exponential decay of drug

        float minEffect; //The minimum effective concentration varies for each dosage type 
        // Assumptions for each dosage type:
        //Low = 1 mcg/kg
        //Mod. = 2 mcg/kg
        //high = 20 mcg/kg

        float minToxic; //The minimum effective concentration varies for each dosage type
        // Assumptions for each dosage type:
        //Low = 2 mcg/kg
        //Mod. = 20 mcg/kg
        //high = 50 mcg/kg

        int dosageType; //1 = low; 2 = moderate; 3 = high
    public:
        //Constructors:
        blood();

        //Getters:
        float getWeight(); 
        float getInitialDosage();
        float getCurrentDosage(); 
        float getConcentration();
        float getDesiredConcentration(); 
        float getHalfLife();
        float getK();
        float getMinEffect();
        float getMinToxic();
        int getDosageType();

        //Setters:
        void setWeight(float x); 
        void setInitialDosage(float x);
        void setCurrentDosage(float x); 
        void setConcentration(float x);
        void setDesiredConcentration(float x);
        void setHalfLife(float x);
        void setK(float x);
        void setMinEffect(float x);
        void setMinToxic(float x);
        void setDosageType(int x);

        //Utility:
        void degrade(float time); //Calculates to a specific time step of degradation (Accepts time in hrs)
        void model(float x); //Performs multiple degradations to create a table of concentration (Accepts hrs to be modeled)
        void model(float x, bool y); //Performs degradations without loading anymore drug (Accepts hrs to be modeled)
        void dose(float x); //Accepts an amount in micrograms administered to a patient
        void print(float time);

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
float blood::getWeight() {
    return weight;
}
float blood::getInitialDosage() {
    return initialDosage;
}
float blood::getCurrentDosage() {
    return currentDosage;
}
float blood::getConcentration() {
    return concentration;
}
float blood::getDesiredConcentration() {
    return desiredConcentration;
}
float blood::getHalfLife() {
    return halfLife;
}
float blood::getK() {
    return k;
}
float blood::getMinEffect() {
    return minEffect;
}
float blood::getMinToxic() {
    return minToxic;
}
int blood::getDosageType() {
    return dosageType; 
}

//Setters:
void blood::setWeight(float x) {
    weight = x;
}
void blood::setInitialDosage(float x) {
    initialDosage = x;
}
void blood::setCurrentDosage(float x) {
    currentDosage = x;
}
void blood::setConcentration(float x) {
    concentration = x;
}
void blood::setDesiredConcentration(float x) {
    desiredConcentration = x;
}
void blood::setHalfLife(float x) {
    halfLife = x;
}
void blood::setK(float x) {
    k = x;
}
void blood::setMinEffect(float x) {
    minEffect = x;
}
void blood::setMinToxic(float x) {
    minToxic = x;
}
void blood::setDosageType(int x) {
    dosageType = x; 
}
//Utility:
void blood::degrade (float time) {
    if (k == 0) {
        k = -log(0.5) / halfLife;
    }
    currentDosage = initialDosage * pow(euler, (-k*time)); //Q = Q_0 * e^(-K * time)
    std::cout << "\ntest: " << currentDosage << std::endl;
    concentration = currentDosage / weight; 
}
void blood::model(float x) {
    float maintenenceDose; //Should I include this in the class? ? ?
    float increment = 1;
    float time = increment;

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

    for (float count = 1; count <= x; count += increment) {
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
void blood::model(float x, bool y) {
    float increment = 1;
    float time = increment;

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

    for (float count = 1; count <= x; count += increment) {
        if (concentration > minToxic) {
            std::cout << minToxic << std::endl << "Too Toxic! ! !";
            return;  //If after degradation the amount of drug is over the limit then stop modelling
        }

        degrade(count);
        
        print(count);
    }
}
void blood::dose(float x) {
    initialDosage = currentDosage + x;
}
void blood::print(float time) {
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
    a.setInitialDosage(30);
    a.setWeight(60);
    a.setDesiredConcentration(30/60);
    a.setDosageType(3);

    a.model(24, 1);
    return 0; 
}