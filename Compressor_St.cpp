#include<iostream>
#include"Compressor_St.h"

void Compressor_St::setName(std::string& n)
{
	name = n;
}
void Compressor_St::setWorkshopCount(int& w)
{
	workshopCount = w;
}
void Compressor_St::setWorkshopInOperation(int& aw)
{
	workshopInOperation = aw;
}
void Compressor_St::setEfficiency(int& ef)
{
	efficiency = ef;
}


std::string Compressor_St::getName()
{
	return name;
}
int Compressor_St::getWorkshopCount()
{
    return workshopCount;
}
int Compressor_St::getWorkshopInOperation()
{
    return workshopInOperation;
}
int Compressor_St::getEfficiency()
{
    return efficiency;
}

void Compressor_St::displayst() const
{
	setlocale(LC_ALL, "RU");
	if (name.empty() || workshopCount <= 0 || workshopInOperation <= 0 || efficiency <= 0)
	{
		std::cout << "������������� ������! ���������� �����!" << std::endl;
	}

	else
	{
		std::cout << "������������� �������: " << name <<"\n ����� ����� : " << workshopCount
			<< "\n � ������: " << workshopInOperation
			<< "\n �������������: " << efficiency << std::endl;
	}
}
//������� ��� ��������� ��������� �����
void Compressor_St::toggleWorkshopStatus()
{
	int choice;
	int number;
	if (name.empty() || workshopCount <= 0 || workshopInOperation <= 0 || efficiency <= 0)
	{
		std::cout << "�� �����������" << std::endl;
	}
	else
	{
		std::cout << "1. �������� ����� ��" << std::endl;
		std::cout << "2. ���������� ��" << std::endl;

		
		std::cin >> choice;

		std::cout << "�������, ������� ������� ������� �� ������ ���������� ��� ���������" << std::endl;

		std::cin >> number;

		switch(choice)
		{
		case 1:
			if (workshopInOperation < workshopCount && workshopInOperation + number <= workshopCount)
			{
				//��������, ����� �� ��������� ����� ����. ���������� ���� �� ������ ��������� ����� ����������
				workshopInOperation += number;
				efficiency = (100 * workshopInOperation) / workshopCount;
				std::cout << "��������� ����� ��. ������ � ������: " << workshopInOperation << " ��" << std::endl;
			}
			else
			{
				//���� �������� ������, ����������� workshopInOperation � ������������� �������������.
				if (workshopInOperation == workshopCount)
				{
					std::cout << "��� �� ��������." << std::endl;
				}
				else
				{
					std::cout << "���������� ��������� ��������, ��� ������� ��" << std::endl;
				}
			}
			break;


		case 2:
			if (workshopInOperation > 0 && workshopInOperation - number > 0)
			{
				//��������, ����� �� ��������� ��������� ���������� �����. ����������� ���� (workshopInOperation - number) �� ������ ���� ������ ����.
				workshopInOperation = workshopInOperation - number;
				efficiency = (100 * workshopInOperation) / workshopCount;
				std::cout << "�����������. ������ " << workshopInOperation << " �� � ������: " << std::endl;
			}
			else
			{
				if (workshopInOperation == 0) 
				{
					std::cout << "��� �����������" << std::endl;
				}
				else
				{
					std::cout << "������ ��������� ������ ��, ��� ������������!" << std::endl;
				}
			}
			break;
		default:
			std::cout << "������������ ��������! ���������� �����!" << std::endl;
			break;
		}
	}	
}


