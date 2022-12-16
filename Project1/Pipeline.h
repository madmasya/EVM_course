#pragma once
#include <vector>
#include "Command.h"

class Pipeline
{
private:
    int allCountOfTics = 0; // общее количество тиков для конвейрной работы
    const int countOfCommands; // всего количество команд для выполнения
    int countOfCommandsNow = 1; // количество команд выложенных на конвейер
    bool flag = false; // флаг, если команда для записи была выполнена и ее необходимо поставить в режим ожидания
    Command** commands; // Изначально массив команд для выполнения
    std::vector<Command*> queue; // очередь для команд, которые должны выполнить свои стадии, чтобы передвинуть конвейер дальше
    std::vector<Command*> queueForWritingInMemoryCommands; // очередь для команд, которые пишут в память на данной стадии

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