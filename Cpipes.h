#pragma once
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <sstream>

class Cpipes
{
private:
	std::string name;
	int diameter;
	bool isUnderRepair;
	int length;

public:
	void setName(std::string& n);//для установки значения поля(ссылка на строку n)
	void setLength(int& l);
	void setDiameter(int& d);
	void setRepairStatus(bool& status);

	std::string getName();//для получения значений
	int getLength();
	int getDiameter();
	bool getRepairStatus();

	void display() const;
	void editRepairStatus();//без const тк переключает статус с true на false

	std::string toString() const
	{
		std::ostringstream oss;
		oss << "Pipe; Name: " << name
			<< "; Length: " << length
			<< "; Diameter: " << diameter
			<< "; RepairStatus: " << (isUnderRepair ? "1" : "0");
		return oss.str();
	} 
};

