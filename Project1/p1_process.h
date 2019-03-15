#ifndef __P1_PROCESS
#define __P1_PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include "p1_threads.h"

using namespace std;
/*struct student {
	string ID;
	long double grade;
}; */
void get_statistics(std::string class_name[], int num_processes, int num_threads, int arrl);

#endif
