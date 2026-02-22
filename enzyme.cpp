#include <iostream>
#include <fstream>
#include <enzyme.h>


int main() {
    reaction a;

    a.setK1(0.05);
    a.setK2(0.1);
    a.setK3(0.02);
    a.setK4(0.0);

    a.setSubstrate(1);
    a.setEnzyme(1);

    a.model(30, 0.05);
    
    return 0;
}