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
		std::cout << "Некоррекктные данные! Попробуйте снова!" << std::endl;
	}

	else
	{
		std::cout << "Компрессорная станция: " << name <<"\n Общее число : " << workshopCount
			<< "\n В работе: " << workshopInOperation
			<< "\n Эффективность: " << efficiency << std::endl;
	}
}
//Функция для изменения состояния цехов
void Compressor_St::toggleWorkshopStatus()
{
	int choice;
	int number;
	if (name.empty() || workshopCount <= 0 || workshopInOperation <= 0 || efficiency <= 0)
	{
		std::cout << "КС отсутствуют" << std::endl;
	}
	else
	{
		std::cout << "1. Добавить новую КС" << std::endl;
		std::cout << "2. Остановить КС" << std::endl;

		
		std::cin >> choice;

		std::cout << "Введите, сколько рабочих станций вы хотите остановить или запустить" << std::endl;

		std::cin >> number;

		switch(choice)
		{
		case 1:
			if (workshopInOperation < workshopCount && workshopInOperation + number <= workshopCount)
			{
				//Проверка, можно ли запустить новые цехи. Включаемые цехи не должны превышать общее количество
				workshopInOperation += number;
				efficiency = (100 * workshopInOperation) / workshopCount;
				std::cout << "Добавлены новые КС. Сейчас в работе: " << workshopInOperation << " КС" << std::endl;
			}
			else
			{
				//Если проверка прошла, увеличиваем workshopInOperation и пересчитываем эффективность.
				if (workshopInOperation == workshopCount)
				{
					std::cout << "Все КС запущены." << std::endl;
				}
				else
				{
					std::cout << "Невозможно выполнить действие, нет столько КС" << std::endl;
				}
			}
			break;


		case 2:
			if (workshopInOperation > 0 && workshopInOperation - number > 0)
			{
				//Проверка, можно ли отключить указанное количество цехов. Отключаемые цехи (workshopInOperation - number) не должны быть меньше нуля.
				workshopInOperation = workshopInOperation - number;
				efficiency = (100 * workshopInOperation) / workshopCount;
				std::cout << "Остановлено. Сейчас " << workshopInOperation << " КС в работе: " << std::endl;
			}
			else
			{
				if (workshopInOperation == 0) 
				{
					std::cout << "Все остановлены" << std::endl;
				}
				else
				{
					std::cout << "Нельзя отключить больше КС, чем активировано!" << std::endl;
				}
			}
			break;
		default:
			std::cout << "Неккоректное действие! Попробуйте снова!" << std::endl;
			break;
		}
	}	
}


