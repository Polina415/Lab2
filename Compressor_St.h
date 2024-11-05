#pragma once
#include <string>
#include <map>
#include <iostream>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <vector>
#include <fstream>
#include <sstream>


class Compressor_St
{
private:
    std::string name;
    int workshopCount;
    int workshopInOperation;
    int efficiency;

public:
    void setName(std::string& n);
    void setWorkshopCount(int& w);
    void setWorkshopInOperation(int& aw);
    void setEfficiency(int& ef);

    std::string getName();
    int getWorkshopCount();
    int getWorkshopInOperation();
    int getEfficiency();

    void displayst() const;
    void toggleWorkshopStatus();

    std::string toString() const
    {
        std::ostringstream oss;
        oss << "Compressor Station; Name: " << name
            << "; Workshop Count: " << workshopCount
            << "; Workshops in Operation: " << workshopInOperation
            << "; Efficiency: " << efficiency;
        return oss.str();
    }
};
