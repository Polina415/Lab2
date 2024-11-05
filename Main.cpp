#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Cpipes.h"
#include "Compressor_St.h"
#include "functions.h"
#include <sstream>

using namespace std;

template <typename T>


void saveToFile(const map<int, T> elements, const string& filename) 
{
	setlocale(LC_ALL, "RU");
	std::ofstream file(filename);

	functions f;

	if (file.is_open())
	{
		for (const auto& element : elements)
		{
			file << element.second.toString() << std::endl;
		}
		f.logAction("���������� ������: " + filename);
	}
	else
	{
		std::cerr << "���������� ��������� ������!" << std::endl;
		f.logAction("������ �� ���������: " + filename);
	}
	file.close();
}
void loadFromFile(map<int, Cpipes>& pipes, map<int, Compressor_St>& stations, string& filename)
{
    std::ifstream file(filename);
	// ��������� ��������� �������, ����� ���� ��������� ������
	Cpipes p;                  
	Compressor_St st;      
	functions f;

    std::string name;
	int length;
	int diameter;
	int workshops;
	int activew;
	int efficiency;
	int status;

    if (file.is_open())
    {
        while (!file.eof())
        {
            std::string line;
            while (getline(file, line))//����� ������ �� ����� � ��������� �� � ����
            {
                if (line.substr(0, 4) == "Pipe")//���� ������ ������ ������� ������, �� ����������� ���������� �������
                {
                    size_t pos1 = line.find(';');//�������������,��� ����� ������ ; ����� ������ ������������
                    //������ ���, ���� �� ������� ��� 4 ����������
                    size_t pos2 = line.find(';', pos1 + 1);
                    size_t pos3 = line.find(';', pos2 + 1);
                    size_t pos4 = line.find(';', pos3 + 1);

                    name = line.substr(pos1 + 8, pos2 - pos1 - 8);
                    length = stoi(line.substr(pos2 + 10, pos3 - pos2 - 10));
                    diameter = stoi(line.substr(pos3 + 12, pos4 - pos3 - 12));
                    status = stoi(line.substr(pos4 + 16, line.length() - pos4 - 16));

                    p.setName(name);
                    p.setLength(length);
                    p.setDiameter(diameter);

                    pipes.emplace(stoi(line.substr(6, pos1 - 6)), p);
                    // ��������� ���� ������ � ��������� pipes, ��������� ��� ��� �������� ��� �����, ����������� �� ��������� line.
                }
                else
                {
                    if (line.substr(0, 18) == "Compressor_Station") 
                    {
                        size_t pos1 = line.find(';');
                        size_t pos2 = line.find(';', pos1 + 1);
                        size_t pos3 = line.find(';', pos2 + 1);
                        size_t pos4 = line.find(';', pos3 + 1);

                        name = line.substr(pos1 + 10, pos2 - pos1 - 10);
                        workshops = stoi(line.substr(pos2 + 13, pos3 - pos2 - 13));
                        activew = stoi(line.substr(pos3 + 19, pos4 - pos3 - 19));
                        efficiency = stoi(line.substr(pos4 + 14, line.length() - pos4 - 14));

                        st.setName(name);
                        st.setWorkshopCount(workshops);
                        st.setWorkshopInOperation(activew);
                        st.setEfficiency(efficiency);

                        stations.emplace(stoi(line.substr(20, pos1 - 20)), st);
                    }
                    else
                    {
                        std::cerr << "�� ������� ��������� ������." << std::endl;
                        f.logAction("�� ������� ��������� �������� ���������: " + filename);
                    }
                }
            }
        }
        f.logAction("���������: " + filename);
    }
    else
    {
        std::cerr << "���� �� ����� ���������." << std::endl;
        f.logAction("�� ���������� ������� ���� : " + filename);
    }
    file.close();
}
int main()
{
    setlocale(LC_ALL, "RU");
    map<int, Cpipes> pipes;
    map<int, Compressor_St> stations;
    functions f;
    int choice;
    while (true)
    {
        std::cout << "********************************************************" << std::endl;
        std::cout << "����: " << std::endl;
        std::cout << "1. �������� �����" << std::endl;
        std::cout << "2. �������� ��" << std::endl;
        std::cout << "3. ������� �����" << std::endl;
        std::cout << "4. ������� ��" << std::endl;
        std::cout << "5. ����������� ��� �������" << std::endl;
        std::cout << "6. ��������������� �����" << endl;
        std::cout << "7. ��������������� ��" << std::endl;
        std::cout << "8. ����� ����" << std::endl;
        std::cout << "9. ����� ��" << std::endl;
        std::cout << "10. ��������� � ����" << std::endl;
        std::cout << "11. ��������� �� �����" << std::endl;
        std::cout << "0. �����" << std::endl;
        std::cout << "********************************************************" << std::endl;
        std::cin >> choice;
        std::cout << "********************************************************" << std::endl;
        if (cin.fail() || choice < 0 || choice > 11 || cin.peek() != '\n')
        {
            cout << "���������� �����!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            f.readPipe(pipes);
            break;
        }
        case 2:
        {
            f.readst(stations);
        }
        case 3:
        {
            f.delitepipes(pipes);
            break;
        }
        case 4:
        {
            f.delitest(stations);
            break;
        }
        case 5:
        {
            f.displayAllPipes(pipes);

            f.displayAllStations(stations);
            break;
        }
        case 6:
        {
            f.editPipe(pipes);
            break;
        }
        case 7:
        {
            f.editStation(stations);
            break;
        }
        case 8:
        {
            f.searchPipes(pipes);
            break;
        }
        case 9:
        {
            f.searchStations(stations);
            break;
        }
        case 10:
        {
            std::string filename;
            std::cout << "������� �������� ����� ��� ����������: ";
            std::cin >> filename;
            saveToFile(pipes, filename);
            saveToFile(stations, filename);
            break;
        }
        case 11:
        {
            std::string filename;
            std::cout << "������� �������� �����: ";
            std::cin >> filename;
            loadFromFile(pipes, stations, filename);
            break;
        }
        case 0:
            return 0;
        default:
        {
            std::cout << "���������� �����!" << std::endl;
        }
        return 0;
        }
    }
}
  

























//void saveToFilepipes(map<int, Cpipes>& pipes, string& filename) //map �������� Cpipes, ��� ������ �������� ����� �����
//{
//	setlocale(LC_ALL, "RU");
//	ofstream file(filename);
//	functions f;
//	if (file.is_open()) 
//	{
//		for (auto& p : pipes) 
//		{
//			file << "�����: " << p.first <<
//				"; ��������:" << p.second.getName()
//				<< "; �����:" << p.second.getLength()
//				<< "; �������:" << p.second.getDiameter()
//				<< "; � �������:" << p.second.getRepairStatus() << std::endl;
//		}
//		f.logAction("��������� � ����: " + filename);
//	}
//	else
//	{
//		std::cerr << "���������� ��������� ������!" << std::endl;
//		f.logAction("������ �� ���������: " + filename);
//	}
//	file.close();
//}

	