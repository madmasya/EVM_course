#pragma once
#include <iostream>
#include <ctime>
#include "Constants.h"

class Command
{
private:
	int countOfClockCyclesForSeqEx = 0; // ������� ����� ��� ���������������� ����������
	int countOfClockCyclesForPipelineEx = 0; // ������� ����� ��� ���������� ����������
	double randomNumber = 0.0; // ��������� ����� ��� ������� �������� � ������ ���� �������
	double randomNumberForOperand2 = 0.0; // ��������� ����� ��� ������� �������� � ������ � ������
	int counter = 0; // ������� ��������� ������ ��� ��������� ��� ���� �������, ���� ������������ N ��� M
	int currentStatusOfCommand = 1; // ������ - 5, ������� ������� ������
	bool canGoToAnotherStage = false; // ����� ������� � ��������� ������
	bool writesToMemory = false; // ������� ������� � ������
	bool isWaiting = false; // ������� ����� � ������� �� ������
	bool isFinished = false; // ������� ���������

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