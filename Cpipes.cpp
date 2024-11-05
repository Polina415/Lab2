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

//���������� �������-��������

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

//���������� ������ � ����� 
void Cpipes::display() const

{
	setlocale(LC_ALL, "RU");
	if (name.empty() || length <= 0 || diameter <= 0)
	{
		std::cout << "������! ������������ ������!���������� �����!";
	}
	else
	{
		std::cout<<"�����: "<<name<<"\n�����: "<<length<<"\n�������: "<<diameter<<"\n� �������:"<< (isUnderRepair ? "��" : "���") << std::endl;
	}
}
//����� ��� �������������� ��������� �����
void Cpipes::editRepairStatus()
{
	if (name.empty() || length <= 0 || diameter <= 0)
	{
		std::cout << "���������� ������ ��������, ��� ��� ������ ���" << std::endl;
	}
	else
	{
		isUnderRepair = !isUnderRepair;
		std::cout << "���������: " << std::endl;
		std::cout << (isUnderRepair ? "��" : "���") << std::endl;
	}
}
