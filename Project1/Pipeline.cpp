#include "Pipeline.h"

Pipeline::Pipeline(int countOfCommands) : countOfCommands(countOfCommands)
{
    commands = new Command*[countOfCommands];

    for (int i = 0; i < countOfCommands; ++i)
    {
        commands[i] = new Command;
    }
}

void Pipeline::printTicsForAllCommandsPipelineEx()
{
    std::cout << "����������� ��������� ������" << std::endl;
    for (int i = 0; i < countOfCommands; ++i)
    {
        std::cout << "�������: " << i + 1 << " - " << commands[i]->getCountOfClockCyclesForPipelineEx() << std::endl;
    }
}
void Pipeline::printTicsForAllCommandsSeqEx()
{
    std::cout << "���������������� ��������� ������" << std::endl;
    for (int i = 0; i < countOfCommands; ++i)
    {
        std::cout << "�������: " << i + 1 << " - " << commands[i]->getCountOfClockCyclesForSeqEx() << std::endl;
    }
}
int Pipeline::getAllSeqTics()
{
    int seqTics = 0;
    for (int i = 0; i < countOfCommands; ++i)
    {
        seqTics += commands[i]->getCountOfClockCyclesForSeqEx();
    }
    return seqTics;
}
double Pipeline::getAvgSeqTics()
{
    return (double)getAllSeqTics() / (double)countOfCommands;
}
int Pipeline::getAllPipelineOfTics()
{
    return allCountOfTics;
}
double Pipeline::getAvgPipelineTics()
{
    return (double)allCountOfTics / (double)countOfCommands;
}
void Pipeline::startThePipeline()
{
    while (!commands[countOfCommands - 1]->getIsFinished())
    { // ���������, ���� �� ����� ��������� ��������� �������
        createQueuesOfCurrentCommands(); // ��������� ������� ������ �� ���������� �� ������� ������ ���������
        executeCommandsAtTheCurrentStage(); // ��������� ��� ������� �� ������� ������ ��������, ������� ���-�� �����

        if (countOfCommands != countOfCommandsNow) // ��������� ����� ������� �� ����������, ���� �� ���������
            countOfCommandsNow++;                 // �������� ����� ������

        goToNextStageForCurrentCommands(); // ��������� � ��������� ������ ���������
        unsetCommandsWaiting(); // ������� �������� ������ ��� ������ � ������ � ������ ��� ���������� ����
        queue.clear(); // ������� �������
        queueForWritingInMemoryCommands.clear();
    }
}

void Pipeline::executeCommandsAtTheCurrentStage()
{
    while (!checkForPromotion())
    {
        if (!queueForWritingInMemoryCommands.empty())
        {
            auto c = queueForWritingInMemoryCommands[0];
            if (c->isCanGoToAnotherStage())
            {
                c->setWaiting();
                queueForWritingInMemoryCommands.erase(queueForWritingInMemoryCommands.begin());
                flag = true;
            }

            if (flag && !queueForWritingInMemoryCommands.empty())
            {
                c = queueForWritingInMemoryCommands[0];
                c->unsetWaiting();
                flag = false;
            }

            setCommandsWaiting(c);
        }
        performActionsForCommands();
        allCountOfTics++;
    }
}
void Pipeline::createQueuesOfCurrentCommands()
{
    for (int i = 0; i < countOfCommands; ++i)
    {
        if (!commands[i]->getIsFinished())
        {
            if (commands[i]->isWritesToMemory())
            {
                queueForWritingInMemoryCommands.push_back(commands[i]);
            }
            queue.push_back(commands[i]);
        }
    }
}

void Pipeline::performActionsForCommands()
{
    for (auto com : queue)
    {
        com->choiceOfActionToPerformOnThisStep();
    }
}
void Pipeline::unsetCommandsWaiting()
{
    for (auto com : queue)
    {
        com->unsetWaiting();
    }
}
void Pipeline::setCommandsWaiting(Command* c2)
{
    for (auto c : queueForWritingInMemoryCommands)
    {
        if (c->isWritesToMemory() && c != c2)
        {
            c->setWaiting();
        }
    }
}
bool Pipeline::checkForPromotion()
{
    for (auto c : queue)
    {
        if (!c->isCanGoToAnotherStage()) return false;
    }
    return true;
}
void Pipeline::goToNextStageForCurrentCommands()
{
    for (auto c : queue)
    {
        c->goToTheNextStage();
    }
}