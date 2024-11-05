#include<iostream>
#include"Cpipes.h"

void Cpipes::setName(std::string& n) 
{
	name = n;
}
void Cpipes::setLength(int& l)
{
	length = l;
}
void Cpipes::setDiameter(int& d) 
{
	diameter = d;
}
void Cpipes::setRepairStatus(bool& status)
{
	isUnderRepair = status;
}

//Реализация методов-геттеров

std::string Cpipes::getName()
{
	return name;
}
int Cpipes::getLength()
{
	return length;
}
int Cpipes::getDiameter()
{
	return diameter;
}
bool Cpipes::getRepairStatus()
{
	return isUnderRepair;
}

//Отображаем данные о трубе 
void Cpipes::display() const

{
	setlocale(LC_ALL, "RU");
	if (name.empty() || length <= 0 || diameter <= 0)
	{
		std::cout << "Ошибка! Неккоректные данные!Попробуйте снова!";
	}
	else
	{
		std::cout<<"Труба: "<<name<<"\nДлина: "<<length<<"\nДиаметр: "<<diameter<<"\nВ ремонте:"<< (isUnderRepair ? "Да" : "Нет") << std::endl;
	}
}
//Метод для редактирования состояния трубы
void Cpipes::editRepairStatus()
{
	if (name.empty() || length <= 0 || diameter <= 0)
	{
		std::cout << "Невозможно ничего поменять, так как ничего нет" << std::endl;
	}
	else
	{
		isUnderRepair = !isUnderRepair;
		std::cout << "Состояние: " << std::endl;
		std::cout << (isUnderRepair ? "Да" : "Нет") << std::endl;
	}
}
