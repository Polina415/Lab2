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
		f.logAction("Сохранение данных: " + filename);
	}
	else
	{
		std::cerr << "Невозможно сохранить данные!" << std::endl;
		f.logAction("Данные не сохранены: " + filename);
	}
	file.close();
}
void loadFromFile(map<int, Cpipes>& pipes, map<int, Compressor_St>& stations, string& filename)
{
    std::ifstream file(filename);
	// Использую временные объекты, чтобы туда загружать данные
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
            while (getline(file, line))//берет строку из файла и сохраняет ее в лайн
            {
                if (line.substr(0, 4) == "Pipe")//если первые четыре символа раввны, то выполняется дальнейшие условия
                {
                    size_t pos1 = line.find(';');//подразумеваем,что перед первым ; будет первое наименование
                    //делаем так, пока не получим все 4 переменные
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
                    // добавляет этот объект в коллекцию pipes, используя его как значение для ключа, полученного из подстроки line.
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
                        std::cerr << "Не удалось выполнить чтение." << std::endl;
                        f.logAction("Не удалось выполнить действие прочтения: " + filename);
                    }
                }
            }
        }
        f.logAction("Загружено: " + filename);
    }
    else
    {
        std::cerr << "Файл не может открыться." << std::endl;
        f.logAction("Не получается открыть файл : " + filename);
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
        std::cout << "Меню: " << std::endl;
        std::cout << "1. Добавить трубу" << std::endl;
        std::cout << "2. Добавить КС" << std::endl;
        std::cout << "3. Удалить трубу" << std::endl;
        std::cout << "4. Удалить КС" << std::endl;
        std::cout << "5. Просмотреть все объекты" << std::endl;
        std::cout << "6. Отредактировать трубу" << endl;
        std::cout << "7. Отредактировать КС" << std::endl;
        std::cout << "8. Поиск труб" << std::endl;
        std::cout << "9. Поиск КС" << std::endl;
        std::cout << "10. Сохранить в файл" << std::endl;
        std::cout << "11. Загрузить из файла" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "********************************************************" << std::endl;
        std::cin >> choice;
        std::cout << "********************************************************" << std::endl;
        if (cin.fail() || choice < 0 || choice > 11 || cin.peek() != '\n')
        {
            cout << "Попробуйте снова!" << endl;
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
            std::cout << "Введите название файла для сохранения: ";
            std::cin >> filename;
            saveToFile(pipes, filename);
            saveToFile(stations, filename);
            break;
        }
        case 11:
        {
            std::string filename;
            std::cout << "Введите название файла: ";
            std::cin >> filename;
            loadFromFile(pipes, stations, filename);
            break;
        }
        case 0:
            return 0;
        default:
        {
            std::cout << "Попробуйте снова!" << std::endl;
        }
        return 0;
        }
    }
}
  

























//void saveToFilepipes(map<int, Cpipes>& pipes, string& filename) //map объектов Cpipes, где ключом является целое число
//{
//	setlocale(LC_ALL, "RU");
//	ofstream file(filename);
//	functions f;
//	if (file.is_open()) 
//	{
//		for (auto& p : pipes) 
//		{
//			file << "Труба: " << p.first <<
//				"; Название:" << p.second.getName()
//				<< "; Длина:" << p.second.getLength()
//				<< "; Диаметр:" << p.second.getDiameter()
//				<< "; В ремонте:" << p.second.getRepairStatus() << std::endl;
//		}
//		f.logAction("Сохранить в файл: " + filename);
//	}
//	else
//	{
//		std::cerr << "Невозможно сохранить данные!" << std::endl;
//		f.logAction("Данные не сохранены: " + filename);
//	}
//	file.close();
//}

	