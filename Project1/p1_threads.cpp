#include "p1_threads.h"
 
// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function

using namespace std;


int readfile (ifstream&  ifile, vector<student> &student_vector){
    string title, grade, studentid; 
    double g;
    cout<<"\nReading File:"<< ifile; 
    if(ifile.good()){
	getline(ifile, title,',');
	getline(ifile, title, '\n');
	}	
    while(ifile.good()){
        student vs;
	getline(ifile,studentid,',');
        getline(ifile, grade, '\n');
	g = strtod(grade.c_str(), NULL);
        vs.ID = studentid;
	vs.grade = g;
	if(studentid != ""){
	student_vector.push_back(vs);
	}
    }
    printf("\nFile read complete\n");
    std::cout<<"size: "<<student_vector.size()<<"\n";
    return student_vector.size();
}

void student_swap(student* a, student* b){
	student t = *a;
	*a = *b;
	*b = t;
}

int partition(vector<student> &sv, int low, int high){
	student pivot = sv[high];   
	int i = low - 1;  
	for (int j = low; j <= high - 1; j++)
	{
		if (sv[j].grade >= pivot.grade)
		{
			i++;    
			student_swap(&sv[i], &sv[j]);
		}
	}
	student_swap(&sv[i + 1], &sv[high]);
	return (i + 1);
}
void quick_sort(vector<student> &sv, int low, int high){
	if (low < high)
	{	
		int n = partition(sv, low, high);
		quick_sort(sv, low, n - 1);
		quick_sort(sv, n + 1, high);
	}
}

void* quick_sort_t(void* input){
	struct svdata* data = (struct svdata*) input;
	quick_sort(data->sv, 0, data->sv.size()-1);
	std::cout<<"\n"<<data->sv[0].grade;
	std::cout<<"\n"<<data->sv[1].grade;
	std::cout<<"\n"<<data->sv[2].grade;
		
}

void* mean_t(void* input){
	double mean;
	struct svdata* data = 	(struct svdata*) input;
	mean = find_mean(data->sv, data->sv.size());
	data->mean = mean;
}

void* median_t(void* input){
	double median;
	struct svdata *data = (struct svdata*) input;
	median = find_median(data->sv, data->sv.size());
	data->median = median;
}

void* stddev_t(void* input){
	float stddev;
	struct svdata *data = (struct svdata*) input;
	stddev = find_stddev(data->sv , data->sv.size());
	data->stddev = stddev;
}

double find_mean(vector<student> &sv, int max) {
	double mean;
	double sum = 0;
	for (int i = 0; i < max; i++) {
		sum += sv[i].grade;
	}
	mean = sum / max;
	std::cout << "\nMean: " << mean;
	return mean;
}

double find_median(vector<student> &sv, int max){
	double median;
	int mid = (max/2) - 1;
	if(max%2 == 0){
		median = sv[mid].grade;
	}
	else if( max%2 == 1){
		median = ( (sv[mid].grade)+(sv[mid+1].grade) ) /2.0;
	}
	std::cout<<"\nMedian: "<< median;
	return median;
}

float find_stddev(vector<student> &sv, int max){
	float stddev;
	double mean = find_mean(sv, max);
	float sum = 0;
	float sub;
	for( int i = 0; i <max; i++){
		sum += pow((sv[i].grade - mean) , 2);	
	}
	
	stddev = sqrt(sum/max);
	std::cout<<"\nStandard Deviation: "<<stddev;
	return stddev;
}

void outputdatacsvfile(std::string class_name, double mean, double median, float stddev){
	std::string title = "output/"+ class_name +"-data.csv";
	ofstream OutFile;
	OutFile.open(title.c_str());
	if(OutFile.good()){
	OutFile <<"Mean"<<","<<"Median"<<","<<"Standard Deviation"<<"\n";
	OutFile <<mean<<","<<median<<","<<stddev;
	}
	else std::cout<<"\nError\n";
	OutFile.close();	

}

void outputsortedcsvfile(std::string class_name,vector<student> &sv, int l) {
	
	std::string title = "output/" + class_name + "-sorted.csv";
	ofstream OutFile;
	OutFile.open(title.c_str());
	if(OutFile.good()){
	OutFile <<"Rank"<<","<< "Student ID"<<","<<"Grade"<<"\n";
	for (int i = 0; i < l; i++) {
		OutFile <<(i+1)<<","<< sv[i].ID << "," << sv[i].grade <<"\n";
	}
	} 
	else std::cout<<"\nError\n";
	OutFile.close();
}	 		 	
