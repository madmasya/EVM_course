#include "Command.h"
#include "Pipeline.h"

const int countOfCommands = 200;

int main()
{
    system("chcp 1251");
	Pipeline* pipeline = new Pipeline(countOfCommands);
	pipeline->startThePipeline();
    std::cout << "Для конвейерной работы общее время выполнения всех команд: " << pipeline->getAllPipelineOfTics() << std::endl;
    std::cout << "Для конвейрной работы среднее время выполнение одной команды: " << pipeline->getAvgPipelineTics() << std::endl;
    pipeline->printTicsForAllCommandsPipelineEx();

    std::cout << "\nДля последовательной работы общее время выполнения всех команд: " << pipeline->getAllSeqTics() << std::endl;
    std::cout << "Для последовательной работы среднее время выполнение одной команды: " << pipeline->getAvgSeqTics() << std::endl;
    pipeline->printTicsForAllCommandsSeqEx();

    std::cout << "\nКонвейер дает выигрыш в " << (double)pipeline->getAllSeqTics() / (double)pipeline->getAllPipelineOfTics() << " раз";
	return 0;
}