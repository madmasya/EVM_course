#include "Command.h"
#include "Pipeline.h"

const int countOfCommands = 200;

int main()
{
    system("chcp 1251");
	Pipeline* pipeline = new Pipeline(countOfCommands);
	pipeline->startThePipeline();
    std::cout << "��� ����������� ������ ����� ����� ���������� ���� ������: " << pipeline->getAllPipelineOfTics() << std::endl;
    std::cout << "��� ���������� ������ ������� ����� ���������� ����� �������: " << pipeline->getAvgPipelineTics() << std::endl;
    pipeline->printTicsForAllCommandsPipelineEx();

    std::cout << "\n��� ���������������� ������ ����� ����� ���������� ���� ������: " << pipeline->getAllSeqTics() << std::endl;
    std::cout << "��� ���������������� ������ ������� ����� ���������� ����� �������: " << pipeline->getAvgSeqTics() << std::endl;
    pipeline->printTicsForAllCommandsSeqEx();

    std::cout << "\n�������� ���� ������� � " << (double)pipeline->getAllSeqTics() / (double)pipeline->getAllPipelineOfTics() << " ���";
	return 0;
}