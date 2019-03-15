#ifndef __P1_THREADS
#define __P1_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <math.h>
#include "p1_process.h"


using namespace std;

struct student{
	std::string ID;
	double grade;
};
struct svdata{
	double mean;
	double median;
	float stddev;
	std::vector<student> sv;
};
	
int readfile(ifstream& ifile, vector<student> &student_vect);
void student_swap(student* a, student* b);
int partition(vector<student> &sv, int low, int high);
void quick_sort(vector<student> &sv, int low, int high);
void* quick_sort_t(void* input);
void* mean_t(void* input);
void* median_t(void* input);
void* stddev_t(void* input);
double find_mean(vector<student> &sv, int max);
double find_median(vector<student> &sv, int max);
float find_stddev(vector<student> &sv, int max);
void outputdatacsvfile(std::string class_name, double mean, double median, float stddev);
void outputsortedcsvfile(std::string class_name, vector<student> &sv, int l);
#endif
