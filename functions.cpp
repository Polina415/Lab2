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
	std::ofstream logFile("logirovanie.txt", std::ios::app);//std::ios::app -устанавливает режим добавления. Он указывает, что данные будут записываться в конец файла, а не перезаписывать его содержимое.
	if (logFile.is_open())
	{
		logFile << action << "##########" << std::endl;
	}
	else
	{
		std::cerr << "Файл для логирования не открывается" << std::endl;
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
		std::cout << "Введите название трубы: " << std::endl;
		std::getline(std::cin >> std::ws, name); // Считываем имя трубы с возможностью пробелов.

		// Проверяем, что имя не пустое и не состоит только из цифр
		if (name.empty() || std::all_of(name.begin(), name.end(), ::isdigit)) {
			// Если строка пустая или содержит только цифры, выдаем сообщение об ошибке
			std::cin.clear();  // Очищаем флаг ошибки потока
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем остаток строки
			std::cout << "Попробуйте снова! Некорректные данные! " << std::endl;
		}
		else {
			// Если введено корректное имя, устанавливаем его
			p.setName(name);
			break; // Выходим из цикла
		}
	}

	//while (true)
	//{
	//	std::cout << "Введите название трубы:";
	//	std::getline(std::cin >> std::ws, name);// Считываем имя трубы с пробелами и устанавливаем его в объект `p`.

	//	if (name.empty() || std::all_of(name.begin(), name.end(), ::isdigit))
	//	
	//	{
	//		std::cin.clear(); 
	//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//		std::cout << "Попробуйте снова! Некорректные данные! " << std::endl;
	//	}
	//	else
	//	{
	//		p.setName(name);
	//		break;
	//	}


	//}
	while (true)
	{
		std::cout << "Введите длину трубы: ";
		std::cin >> length;

		if (std::cin.good() && length > 0 && std::cin.peek() == '\n') //std::cin.peek просмотр следующего символа в потоке без его извлечения. Если следующий символ /n, то условие будет истинным.
		{
			p.setLength(length);
			break;
		}
		else
		{
			std::cin.clear();  // Очищаем 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			std::cout << "Попробуйте снова! Некорректные данные! " << std::endl;
		}
	}
	while (true)
	{
		std::cout << "Введите диаметр трубы: ";
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
			std::cout << "Попробуйте снова! Некорректные данные! " << std::endl;
		}
	}


	int id = pipes.empty() ? 1 : (pipes.rbegin()->first + 1); // Устанавливаем уникальный ID. Если `map` пустой, ID равен 1; иначе — на 1 больше последнего/
	pipes.emplace(id, p);// Добавляем объект `Cpipes` в `map` с этим ID.
	logAction("Добавление трубы с ID " + std::to_string(id));
}


void functions::displayAllPipes(std::map<int, Cpipes>& pipes)
{
	setlocale(LC_ALL, "RU");
	if (size(pipes) == 0)//map пустой
	{ 
		std::cout << "Трубы не найдены!" << std::endl;
	}
	else
	{
		for (auto& p : pipes)//пробегаем по всем трубам
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
	std::cout << "Введите ID трубы, которую нужно удалить: ";
	std::cin >> id;

	if (pipes.find(id) != pipes.end())// Если ID существует, удаляем трубу.
	{ 
		pipes.erase(id);//удаление указанных элементов (erase принимает индекс удаляемого элемента)
		logAction("Удаление трубы с ID " + std::to_string(id));
	}
	else
	{
		std::cout << "Такой трубы нет." << std::endl;  
	}
}


void functions::editPipe(std::map<int, Cpipes>& pipes) 
{
	int id;
	std::cout << "Введите ID трубы для редактирования: ";
	std::cin >> id;

	if (pipes.find(id) != pipes.end())
	{
		pipes[id].editRepairStatus();// []так как обращаемся к индексу
		logAction("Отредактированная труба с  ID " + std::to_string(id));
	}
	else 
	{
		std::cout << "Труба не найдена" << std::endl;             
	}
}
//Функция для пактного редактирования
void functions::batchPipes(std::map<int, Cpipes>& pipes)
{
	bool editAll;
	int choice;
	std::cout << "Редактируем все трубы? (1-Да, 0-Нет): ";

	std::cin >> editAll;
	std::cout << "1.Удалить" << std::endl;
	std::cout << "2.Изменить" << std::endl;

	std::cin >> choice;

	if (editAll)//выбрали редакт всех труб
	{
		switch (choice)
		{
		case 1:
			if (size(pipes) == 0)
			{
				std::cout << "Трубы не найдены." << std::endl;
				break;
			}
			for (auto& pipe : pipes) 
			{
				pipes.erase(pipe.first);
			}
			logAction("Пакетное удаление всех труб.");
			break;


		case 2:
			if (size(pipes) == 0)
			{
				std::cout << "Трубы не найдены." << std::endl;
				break;
			}
			for (auto& pipe : pipes) 
			{
				pipe.second.editRepairStatus();
			}
			logAction("Пакетное редактировние всех труб.");
			break;


		default:
			std::cout << "Попробуйте снова!" << std::endl;
			break;
		}
	}
	else //Выбрали редакт нескольких объектов
	{
		std::vector<int> ids;// Вектор для хранения ID труб, которые будут отредактированы.
		int id;
		std::cout << "Введите ID для редактирования или удаления (-100 остановит действие): ";

		while (std::cin >> id && id != -100) // Чтение ID труб, пока пользователь не введет -1.
		{
			if (pipes.find(id) != pipes.end())// проверка на существование
			{
				ids.push_back(id); // Добавляем ID в список для редактирования.
			}
			else
			{
				std::cout << "Труба с ID " << id << " не найдена" << std::endl;
			}
		}
		switch (choice) 
		{
		case 1:
			for (int pipeId : ids)
			{
				pipes.erase(pipeId); //удаление трубы по id
			}
			logAction("Пакетное удаление трубы");
			break;


		case 2:
			for (int pipeId : ids)
			{
				pipes[pipeId].editRepairStatus(); // Изменяем статус ремонта выбранных труб.
			}
			logAction("Пакетное изменение труб");
			break;

		default:
			std::cout << "Попробуйте снова!" << std::endl;
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
		std::cout << "Введите название КС: " << std::endl;
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
			std::cout << "Попробуйте снова! Некорректные данные! " << std::endl;

		}
	}
	while (true) 
	{
		std::cout << "Введите число КС: ";
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
			std::cout << "Некорректные данные! Попробуйте снова! " << std::endl;
		}
	}
	while (true)
	{
		std::cout << "Введите число КС в работе : ";
		std::cin >> workshopsInOperation;

		if (std::cin.good() && workshopsInOperation > 0 && workshopsInOperation <= workshopCount && std::cin.peek() == '\n') {
			st.setWorkshopInOperation(workshopsInOperation);
			break;
		}
		else 
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Некорректные данные! Попробуйте снова! " << std::endl;
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

	//присваиваем айди
	int id = stations.empty() ? 1 : (stations.rbegin()->first + 1);
	stations.emplace(id, st);
	logAction("Добавлена КС с ID " + std::to_string(id));
}

void functions::delitest(std::map<int, Compressor_St>& stations)
{
	int id;
	std::cout << "Введите ID КС. котрую хотите удалить:" << std::endl;
	std::cin >> id;
	if (stations.find(id) != stations.end()) {
		stations.erase(id);
		logAction("Редактированая КС с ID " + std::to_string(id));
	}
	else 
	{
		std::cout << "КС не найдена" << std::endl;
	}
}


void functions::displayAllStations(std::map<int, Compressor_St>& stations)

{
	setlocale(LC_ALL, "RU");
	if (size(stations) == 0) {
		std::cout << "КС не найдена" << std::endl;
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
	std::cout << "Введите ID для радактирования: ";
	std::cin >> id;
	if (stations.find(id) != stations.end()) {
		stations[id].toggleWorkshopStatus();
		logAction("Отредактированная КС с ID " + std::to_string(id));
	}
	else 
	{
		std::cout << "КС не найдена" << std::endl;
	}
}

void functions::searchPipes(std::map<int, Cpipes>& pipes)
{
	std::string query;//quary приняли на временное пользование
	bool inRepair;
	int choice;
	int ch;

	std::vector<int> ids;

	std::cout << "1.Поиск по имени " << std::endl;
	std::cout << "2.Поиск по состоянию ремонта" << std::endl;
	std::cout << "3.Пакетное редактирование" << std::endl;

	std::cin >> choice;
	
	switch (choice) 
	{
	case 1:
		std::cout << "Введите имя для поиска: ";
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
			std::cout << "Трубы не найдены" << std::endl;
			break;
		}

		std::cout << "1.Удалить" << std::endl;
		std::cout << "2.Изменить" << std::endl;
		std::cin >> ch;
		//нашли трубу, что будем делать с ней?

		switch (ch)
		{
		case 1:
			for (int idd : ids) 
			{
				pipes.erase(idd);
				logAction("Удалены трубы с ID " + std::to_string(idd));
			}
			break;
		case 2:
			for (int idd : ids) 
			{
				pipes[idd].editRepairStatus();
				logAction("Отредактированная труба с  ID " + std::to_string(idd));
			}
			break;
		default:
			std::cout << "Некорректные данные! Попробуйте снова!" << std::endl;
			break;
		}
		break;

	case 2:
		std::cout << "В ремонте ? (1-Да, 0-Нет): ";
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
			std::cout << "Трубы не найдены" << std::endl;
			break;
		}
		std::cout << "1.Удалить" << std::endl;
		std::cout << "2.Изменить" << std::endl;
		std::cin >> ch;

		switch (ch)
		{
		case 1:
			for (int idd : ids) 
			{
				pipes.erase(idd);
				logAction("Удаленная труба с ID " + std::to_string(idd));
			}
			break;
		case 2:
			for (int idd : ids) 
			{
				pipes[idd].editRepairStatus();
				logAction("Отредактированная труба с ID " + std::to_string(idd));
			}
			break;
		default:
			std::cout << "Некорректные данные! Попробуйте снова!" << std::endl;
			break;
		}
		break;

	case 3:
		batchPipes(pipes);
		break;

	default:
		std::cout << "Некорректные данные! Попробуйте снова!" << std::endl;
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
	std::cout << "1.Поиск по имени" << std::endl;
	std::cout << "2.Поиск по эффективности" << std::endl;
	std::cin >> choice;

	switch (choice) {
	case 1:
		std::cout << "Введите имя КС: ";
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
			std::cout << "КС не найдена" << std::endl;
			break;
		}
		std::cout << "1.Удалить" << std::endl;
		std::cout << "2.Изменить" << std::endl;
		std::cin >> ch;
		switch (ch)
		{
		case 1:
			for (int idd : ids)
			{
				stations.erase(idd);
				logAction("Удаленная КС с ID " + std::to_string(idd));
			}
			break;
		case 2:
			for (int idd : ids)
			{
				stations[idd].toggleWorkshopStatus();
				logAction("Удаленная КС с ID " + std::to_string(idd));
			}
			break;
		default:
			std::cout << "Неккоректные данные! Попробуйте снова!" << std::endl;
			break;
		}
		break;


	case 2:
		std::cout << "Введите максимальный процент холостого хода: ";
		std::cin >> maxIdlePercentage;
		std::cout << "1.Указана производительность компрессорных станций с меньшим процентом КПД" << std::endl;
		std::cout << "2.Указана производительность компрессорных станций с высоким процентом КПД" << std::endl;
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
				std::cout << "КС не найдена" << std::endl;
				break;
			}
			std::cout << "1.Удалить" << std::endl;
			std::cout << "2.Изменить" << std::endl;
			std::cin >> ch;
			switch (ch)
			{
			case 1:
				for (int idd : ids) 
				{
					stations.erase(idd);
					logAction("Удаленная КС с  ID " + std::to_string(idd));
				}
				break;
			case 2:
				for (int idd : ids)
				{
					stations[idd].toggleWorkshopStatus();
					logAction("Отредактированная КС с ID " + std::to_string(idd));
				}
				break;
			default:
				std::cout << "Некорректные данные! Попробуйте снова!" << std::endl;
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
				std::cout << "КС не найдена" << std::endl;
				break;
			}
			std::cout << "1.Удалить" << std::endl;
			std::cout << "2.Изменить" << std::endl;
			std::cin >> ch;


			switch (ch)
			{
			case 1:
				for (int idd : ids) 
				{
					stations.erase(idd);
					logAction("Удаленная КС с ID " + std::to_string(idd));
				}
				break;


			case 2:
				for (int idd : ids)
				{
					stations[idd].toggleWorkshopStatus();
					logAction("Измененная КС с ID " + std::to_string(idd));
				}
				break;
			default:
				std::cout << "Неккоректные данные! Попробуйте снова!" << std::endl;
				break;
			}
			break;
		default:
			std::cout << "Неккоректные данные! Попробуйте снова!" << std::endl;
			break;
		}
		break;
	default:
		std::cout << "Неккоректные данные! Попробуйте снова!" << std::endl;
		break;
	}
}






