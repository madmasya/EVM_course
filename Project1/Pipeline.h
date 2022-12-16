#pragma once
#include <vector>
#include "Command.h"

class Pipeline
{
private:
    int allCountOfTics = 0; // ����� ���������� ����� ��� ���������� ������
    const int countOfCommands; // ����� ���������� ������ ��� ����������
    int countOfCommandsNow = 1; // ���������� ������ ���������� �� ��������
    bool flag = false; // ����, ���� ������� ��� ������ ���� ��������� � �� ���������� ��������� � ����� ��������
    Command** commands; // ���������� ������ ������ ��� ����������
    std::vector<Command*> queue; // ������� ��� ������, ������� ������ ��������� ���� ������, ����� ����������� �������� ������
    std::vector<Command*> queueForWritingInMemoryCommands; // ������� ��� ������, ������� ����� � ������ �� ������ ������

public:
    Pipeline(int countOfCommands);
    void printTicsForAllCommandsPipelineEx();
    void printTicsForAllCommandsSeqEx();
    int getAllSeqTics();
    double getAvgSeqTics();
    int getAllPipelineOfTics();
    double getAvgPipelineTics();
    void startThePipeline();

private:
    void executeCommandsAtTheCurrentStage();
    void createQueuesOfCurrentCommands();
    void performActionsForCommands();
    void unsetCommandsWaiting();
    void setCommandsWaiting(Command* c2);
    bool checkForPromotion();
    void goToNextStageForCurrentCommands();
};