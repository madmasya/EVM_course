#pragma once
#include <iostream>
#include <ctime>
#include "Constants.h"

class Command
{
private:
	int countOfClockCyclesForSeqEx = 0; // счетчик тиков при последовательном выполнение
	int countOfClockCyclesForPipelineEx = 0; // счетчик тиков при конвейрном выполнение
	double randomNumber = 0.0; // случайное число для первого операнда и выбора типа команды
	double randomNumberForOperand2 = 0.0; // случайное число для второго операнда и записи в память
	int counter = 0; // счетчик прошедних тактов для операндов или типа команды, если используется N или M
	int currentStatusOfCommand = 1; // стадий - 5, счетчик текущей стадии
	bool canGoToAnotherStage = false; // можно перейти к следующей стадии
	bool writesToMemory = false; // команда пишется в память
	bool isWaiting = false; // команда стоит в очереди на запись
	bool isFinished = false; // команда заврешена

public:
	void choiceOfActionToPerformOnThisStep();
	bool getIsFinished();
	void setWaiting();
	void unsetWaiting();
	bool isCanGoToAnotherStage();
	bool isWritesToMemory();
	int getCountOfClockCyclesForSeqEx();
	int getCountOfClockCyclesForPipelineEx();
	void goToTheNextStage();
	void decrypt();
	void selectFirstOperand();
	void selectSecondOperand();
	void selectCommand();
	void writeToMemory();
	double generateRandomNumber();
	void selectOperandOrCommand(double probability, int numberOfClockCycles, double randomNumber);
	bool operator != (Command* c2);
};