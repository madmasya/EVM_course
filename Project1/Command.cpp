#include "Command.h"

void Command::choiceOfActionToPerformOnThisStep()
{
    if (isFinished) return;

    if (canGoToAnotherStage || isWaiting)
    {
        countOfClockCyclesForPipelineEx++;
        return;
    }

    switch (currentStatusOfCommand)
{
    case 1:
        decrypt();
        break;

    case 2:
        selectFirstOperand();
        break;

    case 3:
        selectSecondOperand();
        break;

    case 4:
        selectCommand();
        break;

    case 5:
        writeToMemory();
        break;

    default:
        std::cout << "������� ���� �������� � ������!" << std::endl;
        break;
    }
}
bool Command::getIsFinished()
{
    return isFinished;
}
void Command::setWaiting()
{
    isWaiting = true;
}
void Command::unsetWaiting()
{
    isWaiting = false;
}
bool Command::isCanGoToAnotherStage()
{
    return canGoToAnotherStage;
}
bool Command::isWritesToMemory()
{
    return writesToMemory;
}
int Command::getCountOfClockCyclesForSeqEx()
{
    return countOfClockCyclesForSeqEx;
}
int Command::getCountOfClockCyclesForPipelineEx()
{
    return countOfClockCyclesForPipelineEx;
}
void Command::goToTheNextStage()
{
    canGoToAnotherStage = false;
    currentStatusOfCommand++;
    //writesToMemory = currentStatusOfCommand == 2 || currentStatusOfCommand == 3 || currentStatusOfCommand == 5;
    if (currentStatusOfCommand == 2 || currentStatusOfCommand == 3 || currentStatusOfCommand == 5)
        writesToMemory = true;
    else writesToMemory = false;
}
void Command::decrypt()
{
    countOfClockCyclesForSeqEx++;
    countOfClockCyclesForPipelineEx++;
    canGoToAnotherStage = true;
}
void Command::selectFirstOperand()
{
    countOfClockCyclesForSeqEx++;
    countOfClockCyclesForPipelineEx++;
    canGoToAnotherStage = true;
}
void Command::selectSecondOperand()
{
    double randomNumber = generateRandomNumber();
    selectOperandOrCommand(P1, N, randomNumber);
}
void Command::selectCommand()
{
    double randomNumber = generateRandomNumber();
    selectOperandOrCommand(P2, M, randomNumber);
}
void Command::writeToMemory()
{
    selectOperandOrCommand(P1, N, randomNumberForOperand2);
    if (canGoToAnotherStage) isFinished = true;
}
double Command::generateRandomNumber()
{
    if (counter == 0)
    { // ���������� ��������� ����� � ��������� �� ���� �� ��� ��� �������
        srand(time(NULL));
        randomNumber = ((double)(rand() % (10 + 1))) / 10;
    }
    return randomNumber;
}
void Command::selectOperandOrCommand(double probability, int numberOfClockCycles, double randomNumber)
{
    if (randomNumber > probability)
    { // ���� ����� ������ �������� �����������, ����� ��������� ��� ���������� ���������� ����� ����������� N ��� M ������
        counter++;
        if (counter != numberOfClockCycles)
        {// �������� �� ������ �� ������ ���������� ������ ��� ���������� �������� � ���������� �����
            canGoToAnotherStage = false;
        }
        else
        {
            counter = 0;
            canGoToAnotherStage = true;
        }
    }
    else
    {
        canGoToAnotherStage = true;
    }

    countOfClockCyclesForSeqEx++;
    countOfClockCyclesForPipelineEx++;
}

bool Command::operator != (Command* c2)
{
    return !(countOfClockCyclesForSeqEx == c2->countOfClockCyclesForSeqEx
        && countOfClockCyclesForPipelineEx == c2->countOfClockCyclesForPipelineEx
        && !(c2->randomNumber == randomNumber)
        && !(c2->randomNumberForOperand2 == randomNumberForOperand2)
        && counter == c2->counter
        && currentStatusOfCommand == c2->currentStatusOfCommand
        && canGoToAnotherStage == c2->canGoToAnotherStage
        && writesToMemory == c2->writesToMemory
        && isWaiting == c2->isWaiting
        && isFinished == c2->isFinished);
}