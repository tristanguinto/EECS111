#include "p1_process.h"

//student arr1[1000001];
void get_statistics(std::string class_name[], int num_processes, int num_threads, int arrl) {


	// You need to create multiple processes here (each process
	// handles at least one file.)


	// Each process should use the sort function which you have defined  		
	// in the p1_threads.cpp for multithread sorting of the data. 

	// Your code should be able to get the statistics and generate
	// the required outputs for any number of child processes and threads.

	pid_t pid1, pid2;

	int ptof =  arrl/num_processes ;
	int ptofc = arrl% num_processes ;
	int FileAmt = 0;
	int arr_c = 0;
	int s = 0;
	std::vector<string> FilesPerProcess;
	for (int i = 0; i < num_processes; i++) {
		if(ptofc == 0){
			FileAmt = ptof;	
		}
		else if (ptofc > 0){
			FileAmt = ptof + 1;
			ptofc--;
		}

		for(int j = 0; j< FileAmt; j++){
			FilesPerProcess.push_back(class_name[arr_c]);
			std::cout<<"File "<<FilesPerProcess[j]<< "pushed\n";
			arr_c++;
		}
		pid1 = fork();
		if(pid1 == 0){
			break;
		}
		FilesPerProcess.clear();
		std:cout<<"\nProcessed files vector cleared\n";
	}



	if(pid1==0){
		std::cout<<"\nChild Process is created. (pid: "<<getpid()<<")\n";
		for(int k = 0; k<FilesPerProcess.size(); k++){
			int tc = num_threads;
			std::ifstream ip;
			std::string intitle = "input/"+FilesPerProcess[k]+".csv";
			std::vector<student> student_vector;
			svdata SV_data;
			ip.open(intitle.c_str());
			if(ip.good()){
				int vlen = readfile(ip, student_vector);
				quick_sort(student_vector, 0,vlen-1);
				outputsortedcsvfile(FilesPerProcess[k],student_vector, vlen);
			} else { std::cout<<"Error reading/writing file";}
			std::cout<<"\nFile "<< FilesPerProcess[k]<< ".csv has been read/sorted/written";
			SV_data.sv = student_vector;	
			pthread_t threads[3];
			int rc1, rc2, rc3;
			rc1 = pthread_create(&threads[0],NULL,mean_t, &SV_data);
			rc2 = pthread_create(&threads[1],NULL,median_t, &SV_data);
			rc3 = pthread_create(&threads[2],NULL,stddev_t, &SV_data);
			for(int t = 0; t < 3; t++){
				pthread_join(threads[t],NULL);
				if(rc1||rc2||rc3) {
					std::cout<<"\nError! Return code from pthread_create() is \nrc1: "<<rc1<<"\nrc2: "<<rc2<<"\nrc3: "<<rc3;
					exit(-1);
				}
			}
			outputdatacsvfile(FilesPerProcess[k],SV_data.mean,SV_data.median,SV_data.stddev);
			std::cout<<"\n"<<FilesPerProcess[k]<<"-data.csv file has been written\n";	
		}	
		std::cout<<"Child process is terminated. (pid: "<<getpid()<<")\n";
		exit(0);
	}
	while((pid2 = wait(&s)) > 0 ){
		std::cout<<"Child process is terminated. (pid: "<<getpid()<<")\n";
	}
}	
