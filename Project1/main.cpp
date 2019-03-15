#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include "p1_process.h"
#include "p1_threads.h"

using namespace std;


//student arr1[1000001];

int main(int argc, char** argv)
{
	printf("Main process is created. (pid: %d)\n", getpid());
	int num_processes = 0;
	int num_threads = 0;

	std::string class_name[] = { "os", "architecture", "java", "algorithm", "digital-design" };
	int arrl = (sizeof(class_name)/sizeof(class_name[0]));
//	std::cout<<"\narrl: " <<arrl;
	// Check the argument and print error message if the argument is wrong
	if(argc == 3 && (atoi(argv[1]) > 0 && atoi(argv[2]) > 0))
	{
	num_processes = atoi(argv[1]);
	num_threads = atoi(argv[2]);
	// Call the process
	get_statistics(class_name, num_processes, num_threads,arrl);
	}
	else
	{
	printf("[ERROR] Expecting 2 arguments with integral value greater than zero.\n");
	printf("[USAGE] p1_exec <number of processes> <number of threads>\n");
	} 
/*	std::ifstream ip;
	ip.open("java.csv");
	if (ip.good()) {
		readfile(ip, arr1);
		std::cout << arr1[0].ID << "\n" << arr1[0].grade << "\n";
		std::cout << arr1[999999].ID << "\n" << arr1[999999].grade << "\n";
		quick_sort(arr1, 0, 999999);
		outputcsvfile("java", arr1, 999999);
	}
	else  cout << "Error\n";
	ip.close(); */
	printf("Main process is terminated. (pid: %d)\n", getpid());
	return 0;

}

