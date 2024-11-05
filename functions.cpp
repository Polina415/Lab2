#include "functions.h"
#include <iostream>
#include <map>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>

void functions::logAction(const std::string& action)
{
	std::ofstream logFile("logirovanie.txt", std::ios::app);//std::ios::app -������������� ����� ����������. �� ���������, ��� ������ ����� ������������ � ����� �����, � �� �������������� ��� ����������.
	if (logFile.is_open())
	{
		logFile << action << "##########" << std::endl;
	}
	else
	{
		std::cerr << "���� ��� ����������� �� �����������" << std::endl;
	}
	logFile.close();
}



void functions::readPipe(std::map<int, Cpipes>& pipes)
{
	setlocale(LC_ALL, "RU");

	Cpipes p;
	std::string name;
	int length;
	int diameter;

	while (true) {
		std::cout << "������� �������� �����: " << std::endl;
		std::getline(std::cin >> std::ws, name); // ��������� ��� ����� � ������������ ��������.

		// ���������, ��� ��� �� ������ � �� ������� ������ �� ����
		if (name.empty() || std::all_of(name.begin(), name.end(), ::isdigit)) {
			// ���� ������ ������ ��� �������� ������ �����, ������ ��������� �� ������
			std::cin.clear();  // ������� ���� ������ ������
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���������� ������� ������
			std::cout << "���������� �����! ������������ ������! " << std::endl;
		}
		else {
			// ���� ������� ���������� ���, ������������� ���
			p.setName(name);
			break; // ������� �� �����
		}
	}

	//while (true)
	//{
	//	std::cout << "������� �������� �����:";
	//	std::getline(std::cin >> std::ws, name);// ��������� ��� ����� � ��������� � ������������� ��� � ������ `p`.

	//	if (name.empty() || std::all_of(name.begin(), name.end(), ::isdigit))
	//	
	//	{
	//		std::cin.clear(); 
	//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//		std::cout << "���������� �����! ������������ ������! " << std::endl;
	//	}
	//	else
	//	{
	//		p.setName(name);
	//		break;
	//	}


	//}
	while (true)
	{
		std::cout << "������� ����� �����: ";
		std::cin >> length;

		if (std::cin.good() && length > 0 && std::cin.peek() == '\n') //std::cin.peek �������� ���������� ������� � ������ ��� ��� ����������. ���� ��������� ������ /n, �� ������� ����� ��������.
		{
			p.setLength(length);
			break;
		}
		else
		{
			std::cin.clear();  // ������� 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			std::cout << "���������� �����! ������������ ������! " << std::endl;
		}
	}
	while (true)
	{
		std::cout << "������� ������� �����: ";
		std::cin >> diameter;
		if(std::cin.good() && diameter > 0 && std::cin.peek() == '\n')
		{ 
			p.setDiameter(diameter);  
			break;
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "���������� �����! ������������ ������! " << std::endl;
		}
	}


	int id = pipes.empty() ? 1 : (pipes.rbegin()->first + 1); // ������������� ���������� ID. ���� `map` ������, ID ����� 1; ����� � �� 1 ������ ����������/
	pipes.emplace(id, p);// ��������� ������ `Cpipes` � `map` � ���� ID.
	logAction("���������� ����� � ID " + std::to_string(id));
}


void functions::displayAllPipes(std::map<int, Cpipes>& pipes)
{
	setlocale(LC_ALL, "RU");
	if (size(pipes) == 0)//map ������
	{ 
		std::cout << "����� �� �������!" << std::endl;
	}
	else
	{
		for (auto& p : pipes)//��������� �� ���� ������
		{   
			std::cout << "*******" << std::endl;
			std::cout << "ID: " << p.first << std::endl;   
			p.second.display();
		}
	}	 
}
void functions::delitepipes(std::map<int, Cpipes>& pipes)
{
	int id;
	std::cout << "������� ID �����, ������� ����� �������: ";
	std::cin >> id;

	if (pipes.find(id) != pipes.end())// ���� ID ����������, ������� �����.
	{ 
		pipes.erase(id);//�������� ��������� ��������� (erase ��������� ������ ���������� ��������)
		logAction("�������� ����� � ID " + std::to_string(id));
	}
	else
	{
		std::cout << "����� ����� ���." << std::endl;  
	}
}


void functions::editPipe(std::map<int, Cpipes>& pipes) 
{
	int id;
	std::cout << "������� ID ����� ��� ��������������: ";
	std::cin >> id;

	if (pipes.find(id) != pipes.end())
	{
		pipes[id].editRepairStatus();// []��� ��� ���������� � �������
		logAction("����������������� ����� �  ID " + std::to_string(id));
	}
	else 
	{
		std::cout << "����� �� �������" << std::endl;             
	}
}
//������� ��� �������� ��������������
void functions::batchPipes(std::map<int, Cpipes>& pipes)
{
	bool editAll;
	int choice;
	std::cout << "����������� ��� �����? (1-��, 0-���): ";

	std::cin >> editAll;
	std::cout << "1.�������" << std::endl;
	std::cout << "2.��������" << std::endl;

	std::cin >> choice;

	if (editAll)//������� ������ ���� ����
	{
		switch (choice)
		{
		case 1:
			if (size(pipes) == 0)
			{
				std::cout << "����� �� �������." << std::endl;
				break;
			}
			for (auto& pipe : pipes) 
			{
				pipes.erase(pipe.first);
			}
			logAction("�������� �������� ���� ����.");
			break;


		case 2:
			if (size(pipes) == 0)
			{
				std::cout << "����� �� �������." << std::endl;
				break;
			}
			for (auto& pipe : pipes) 
			{
				pipe.second.editRepairStatus();
			}
			logAction("�������� ������������� ���� ����.");
			break;


		default:
			std::cout << "���������� �����!" << std::endl;
			break;
		}
	}
	else //������� ������ ���������� ��������
	{
		std::vector<int> ids;// ������ ��� �������� ID ����, ������� ����� ���������������.
		int id;
		std::cout << "������� ID ��� �������������� ��� �������� (-100 ��������� ��������): ";

		while (std::cin >> id && id != -100) // ������ ID ����, ���� ������������ �� ������ -1.
		{
			if (pipes.find(id) != pipes.end())// �������� �� �������������
			{
				ids.push_back(id); // ��������� ID � ������ ��� ��������������.
			}
			else
			{
				std::cout << "����� � ID " << id << " �� �������" << std::endl;
			}
		}
		switch (choice) 
		{
		case 1:
			for (int pipeId : ids)
			{
				pipes.erase(pipeId); //�������� ����� �� id
			}
			logAction("�������� �������� �����");
			break;


		case 2:
			for (int pipeId : ids)
			{
				pipes[pipeId].editRepairStatus(); // �������� ������ ������� ��������� ����.
			}
			logAction("�������� ��������� ����");
			break;

		default:
			std::cout << "���������� �����!" << std::endl;
			break;
		}
	}
}
void functions::readst(std::map<int, Compressor_St>& stations)
{
	setlocale(LC_ALL, "RU");
	Compressor_St st;
	std::string name;
	int workshopCount;
	int workshopsInOperation;
	int efficiency;
	while (true)
	{
		std::cout << "������� �������� ��: " << std::endl;
		std::getline(std::cin >> std::ws, name);
		if (std::all_of(name.begin(), name.end(), [](unsigned char c)
			{
				return !std::isdigit(c);
			}))
		{
			st.setName(name);
			break;
		}		
		else 
		{
			std::cin.clear();  
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "���������� �����! ������������ ������! " << std::endl;

		}
	}
	while (true) 
	{
		std::cout << "������� ����� ��: ";
		std::cin >> workshopCount;
		if (std::cin.good() && workshopCount > 0 && std::cin.peek() == '\n') 
		{
			st.setWorkshopCount(workshopCount);
			break;
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������������ ������! ���������� �����! " << std::endl;
		}
	}
	while (true)
	{
		std::cout << "������� ����� �� � ������ : ";
		std::cin >> workshopsInOperation;

		if (std::cin.good() && workshopsInOperation > 0 && workshopsInOperation <= workshopCount && std::cin.peek() == '\n') {
			st.setWorkshopInOperation(workshopsInOperation);
			break;
		}
		else 
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������������ ������! ���������� �����! " << std::endl;
		}
	}
	if (workshopCount == 0) 
	{
		efficiency = 0;
	}
	else 
	{
		efficiency = (100 * workshopsInOperation) / workshopCount;
	}

	st.setEfficiency(efficiency);

	//����������� ����
	int id = stations.empty() ? 1 : (stations.rbegin()->first + 1);
	stations.emplace(id, st);
	logAction("��������� �� � ID " + std::to_string(id));
}

void functions::delitest(std::map<int, Compressor_St>& stations)
{
	int id;
	std::cout << "������� ID ��. ������ ������ �������:" << std::endl;
	std::cin >> id;
	if (stations.find(id) != stations.end()) {
		stations.erase(id);
		logAction("�������������� �� � ID " + std::to_string(id));
	}
	else 
	{
		std::cout << "�� �� �������" << std::endl;
	}
}


void functions::displayAllStations(std::map<int, Compressor_St>& stations)

{
	setlocale(LC_ALL, "RU");
	if (size(stations) == 0) {
		std::cout << "�� �� �������" << std::endl;
	}
	else 
	{
		for (auto& cs : stations) 
		{
			std::cout << "*******" << std::endl;
			std::cout << "ID: " << cs.first << std::endl;
			cs.second.displayst();
		}
	}
}

void functions::editStation(std::map<int, Compressor_St>& stations)
{
	setlocale(LC_ALL, "RU");
	int id;
	std::cout << "������� ID ��� ��������������: ";
	std::cin >> id;
	if (stations.find(id) != stations.end()) {
		stations[id].toggleWorkshopStatus();
		logAction("����������������� �� � ID " + std::to_string(id));
	}
	else 
	{
		std::cout << "�� �� �������" << std::endl;
	}
}

void functions::searchPipes(std::map<int, Cpipes>& pipes)
{
	std::string query;//quary ������� �� ��������� �����������
	bool inRepair;
	int choice;
	int ch;

	std::vector<int> ids;

	std::cout << "1.����� �� ����� " << std::endl;
	std::cout << "2.����� �� ��������� �������" << std::endl;
	std::cout << "3.�������� ��������������" << std::endl;

	std::cin >> choice;
	
	switch (choice) 
	{
	case 1:
		std::cout << "������� ��� ��� ������: ";
		std::cin >> std::ws;


		getline(std::cin, query);

		for (auto& p : pipes) 
		{
			if (p.second.getName().find(query) != std::string::npos || p.second.getName().rfind(query) != std::string::npos) {
				std::cout << "ID: " << p.first << " ";
				p.second.display();
				ids.push_back(p.first);
			}
		}
		if (size(ids) == 0) 
		{
			std::cout << "����� �� �������" << std::endl;
			break;
		}

		std::cout << "1.�������" << std::endl;
		std::cout << "2.��������" << std::endl;
		std::cin >> ch;
		//����� �����, ��� ����� ������ � ���?

		switch (ch)
		{
		case 1:
			for (int idd : ids) 
			{
				pipes.erase(idd);
				logAction("������� ����� � ID " + std::to_string(idd));
			}
			break;
		case 2:
			for (int idd : ids) 
			{
				pipes[idd].editRepairStatus();
				logAction("����������������� ����� �  ID " + std::to_string(idd));
			}
			break;
		default:
			std::cout << "������������ ������! ���������� �����!" << std::endl;
			break;
		}
		break;

	case 2:
		std::cout << "� ������� ? (1-��, 0-���): ";
		std::cin >> inRepair;

		for (auto& p : pipes)
		{
			if (p.second.getRepairStatus() == inRepair)
			{
				std::cout << "ID: " << p.first << " ";
				p.second.display();
				ids.push_back(p.first);
			}
		}
		if (size(ids) == 0)
		{
			std::cout << "����� �� �������" << std::endl;
			break;
		}
		std::cout << "1.�������" << std::endl;
		std::cout << "2.��������" << std::endl;
		std::cin >> ch;

		switch (ch)
		{
		case 1:
			for (int idd : ids) 
			{
				pipes.erase(idd);
				logAction("��������� ����� � ID " + std::to_string(idd));
			}
			break;
		case 2:
			for (int idd : ids) 
			{
				pipes[idd].editRepairStatus();
				logAction("����������������� ����� � ID " + std::to_string(idd));
			}
			break;
		default:
			std::cout << "������������ ������! ���������� �����!" << std::endl;
			break;
		}
		break;

	case 3:
		batchPipes(pipes);
		break;

	default:
		std::cout << "������������ ������! ���������� �����!" << std::endl;
		break;
	}
}
void functions::searchStations(std::map<int, Compressor_St>& stations) 
{
	std::string query;
	std::vector<int> ids;
	double maxIdlePercentage;
	int choice;
	int percent;
	int ch;
	std::cout << "1.����� �� �����" << std::endl;
	std::cout << "2.����� �� �������������" << std::endl;
	std::cin >> choice;

	switch (choice) {
	case 1:
		std::cout << "������� ��� ��: ";
		std::cin >> std::ws;
		getline(std::cin, query);
		for (auto& cs : stations)
		{
			if (cs.second.getName().find(query) != std::string::npos || cs.second.getName().rfind(query) != std::string::npos)
			{
				std::cout << "ID: " << cs.first << " ";
				cs.second.displayst();
				ids.push_back(cs.first);
			}
		}
		if (size(ids) == 0) 
		{
			std::cout << "�� �� �������" << std::endl;
			break;
		}
		std::cout << "1.�������" << std::endl;
		std::cout << "2.��������" << std::endl;
		std::cin >> ch;
		switch (ch)
		{
		case 1:
			for (int idd : ids)
			{
				stations.erase(idd);
				logAction("��������� �� � ID " + std::to_string(idd));
			}
			break;
		case 2:
			for (int idd : ids)
			{
				stations[idd].toggleWorkshopStatus();
				logAction("��������� �� � ID " + std::to_string(idd));
			}
			break;
		default:
			std::cout << "������������ ������! ���������� �����!" << std::endl;
			break;
		}
		break;


	case 2:
		std::cout << "������� ������������ ������� ��������� ����: ";
		std::cin >> maxIdlePercentage;
		std::cout << "1.������� ������������������ ������������� ������� � ������� ��������� ���" << std::endl;
		std::cout << "2.������� ������������������ ������������� ������� � ������� ��������� ���" << std::endl;
		std::cin >> percent;
		switch (percent)
		{
		case 1:
			for (auto& cs : stations) 
			{
				if (100 - cs.second.getEfficiency() <= maxIdlePercentage)
				{
					std::cout << "ID: " << cs.first << " ";
					cs.second.displayst();
					ids.push_back(cs.first);
				}
			}
			if (size(ids) == 0)
			{
				std::cout << "�� �� �������" << std::endl;
				break;
			}
			std::cout << "1.�������" << std::endl;
			std::cout << "2.��������" << std::endl;
			std::cin >> ch;
			switch (ch)
			{
			case 1:
				for (int idd : ids) 
				{
					stations.erase(idd);
					logAction("��������� �� �  ID " + std::to_string(idd));
				}
				break;
			case 2:
				for (int idd : ids)
				{
					stations[idd].toggleWorkshopStatus();
					logAction("����������������� �� � ID " + std::to_string(idd));
				}
				break;
			default:
				std::cout << "������������ ������! ���������� �����!" << std::endl;
				break;
			}
			break;
		case 2:
			for (auto& cs : stations)
			{
				if (100 - cs.second.getEfficiency() >= maxIdlePercentage)
				{
					std::cout << "ID: " << cs.first << " ";
					cs.second.displayst();
					ids.push_back(cs.first);
				}
			}
			if (size(ids) == 0)
			{
				std::cout << "�� �� �������" << std::endl;
				break;
			}
			std::cout << "1.�������" << std::endl;
			std::cout << "2.��������" << std::endl;
			std::cin >> ch;


			switch (ch)
			{
			case 1:
				for (int idd : ids) 
				{
					stations.erase(idd);
					logAction("��������� �� � ID " + std::to_string(idd));
				}
				break;


			case 2:
				for (int idd : ids)
				{
					stations[idd].toggleWorkshopStatus();
					logAction("���������� �� � ID " + std::to_string(idd));
				}
				break;
			default:
				std::cout << "������������ ������! ���������� �����!" << std::endl;
				break;
			}
			break;
		default:
			std::cout << "������������ ������! ���������� �����!" << std::endl;
			break;
		}
		break;
	default:
		std::cout << "������������ ������! ���������� �����!" << std::endl;
		break;
	}
}






