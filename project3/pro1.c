#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include <pthread.h>
#include <unistd.h> 
using namespace std;


#define THREADNUM 20

pthread_mutex_t mymutex;


struct VirtualPCB
{
	pthread_t tid;
	int priority;
	int wait_time;
	int run_time;
	int arrive_time;
	int visit;
	pthread_cond_t cond;
	//int finish;
	//int temprun_time;

}PCB[THREADNUM];

int start;


void initPCB()
{
	srand(time(NULL));
	int i;
	for(i = 0;i < THREADNUM; ++i)
	{
		//PCB[i].tid = i;
		//PCB[i].finish = 0;   
		PCB[i].priority = 1 + rand()%19;
		PCB[i].wait_time = 0;
		PCB[i].run_time = 1 + rand()%19;
		PCB[i].arrive_time = 0;
		PCB[i].visit = 0;
		PCB[i].cond = PTHREAD_COND_INITIALIZER;
		//PCB[i].temprun_time = 0;
		
	}
	
}


void* thread_func(void * n)
{
	int i = *(int *)(n);
	pthread_mutex_lock(&mymutex);
	while(PCB[i-1].run_time)
	{
		while(!PCB[i-1].visit)     //double for loop
		{
			pthread_cond_wait(&PCB[i-1].cond,&mymutex);
			//printf("Thread%2d:%2d\n",i,start - PCB[i-1].run_time);
			printf("Thread%2d:%2d\n",i,start);
		}
		//cout << "wrong!!!" << endl;
	}

	//sleep(1);
	pthread_mutex_unlock(&mymutex);
	pthread_exit(0);
}


//pretend to schedule
void FCFS()
{
	cout << "---------------FCFS Schedule---------------" << endl;
	int arrive_time = 0;
	start = 0;
	int i,temp;
	for(i = 0; i < THREADNUM; ++i)
	{
		
		if(PCB[i].arrive_time == arrive_time && PCB[i].visit == 0)
		{
			pthread_mutex_lock(&mymutex);
			PCB[i].wait_time = start;
			temp = PCB[i].run_time;
			PCB[i].run_time = 0;
			PCB[i].visit = 1;
			pthread_cond_signal(&(PCB[i].cond));
			pthread_mutex_unlock(&mymutex);	
			//cout << "tid:" << i  << PCB[i].gettid() << endl;
			pthread_join(PCB[i].tid,NULL);

		}
		start += temp;	
	}
	
}


void SJF()
{
	int k;
	start = 0;
	for(k = 0; k < THREADNUM; ++k)
	{
		PCB[k].wait_time = 0;
		PCB[k].visit = 0;
	}
	cout << "----------------SJF Schedule----------------" << endl;
	int i,j;

	/*for(i = 1; i < THREADNUM; ++i)
	{
		for(j = 0; j < THREADNUM; ++j)
		{
			
			if(PCB[j].run_time == i && PCB[j].visit == 0)
			{
					
				cout << "before lock" << endl;
				pthread_mutex_lock(&mymutex);
				cout << "after lock" << endl;
				PCB[i].wait_time = start;
				start += PCB[i].run_time;
				PCB[i].visit = 1;
				cout << "before singal" << endl;
				pthread_cond_signal(&(PCB[i].cond));
				cout << "after singal" << endl;
				cout << "before unlock" << endl;
				pthread_mutex_unlock(&mymutex);	
				cout << "after unlock" << endl;
				if(pthread_join(PCB[i].tid,NULL) == 0)
				{
					cout << "thread" << i << "exits" << endl;
				}
			}
		}
	}*/

	int order[THREADNUM];
	int count = 0;
	for(i = 1; i < THREADNUM; ++i)
	{
		for(j = 0; j < THREADNUM; ++j)
		{
			if(PCB[j].run_time == i && PCB[j].visit == 0)
			{
				order[count++] = j;
			}
		}
	}
	/*for(i = 0; i < THREADNUM; ++i)
	{
		cout << order[i] << "  ";
	}
	cout << endl;*/
	int item;
	int temp;
	for(i = 0; i < THREADNUM; ++i)
	{
		item = order[i];
		pthread_mutex_lock(&mymutex);
		PCB[item].wait_time = start;
		//start += PCB[item].run_time;
		PCB[item].visit = 1;
		temp = PCB[item].run_time;
		PCB[item].run_time = 0;
		pthread_cond_signal(&(PCB[item].cond));
		pthread_mutex_unlock(&mymutex);	
		pthread_join(PCB[item].tid,NULL);
		start += temp;
	}
}


void priority()
{
	int k;
	start = 0;
	for(k = 0; k < THREADNUM; ++k)
	{
		PCB[k].wait_time = 0;
		PCB[k].visit = 0;
	}
	cout << "----------------Priority Schedule----------------" << endl;
	int i,j;
	int order[THREADNUM];
	int count = 0;
	for(i = 1; i < THREADNUM; ++i)
	{
		for(j = 0; j < THREADNUM; ++j)
		{
			if(PCB[j].priority == i && PCB[j].visit == 0)
			{
				order[count++] = j;
			}
		}
	}

	int item;
	int temp;
	for(i = 0; i < THREADNUM; ++i)
	{
		item = order[i];
		pthread_mutex_lock(&mymutex);
		PCB[item].wait_time = start;
		//start += PCB[item].run_time;
		PCB[item].visit = 1;
		temp = PCB[item].run_time;
		PCB[item].run_time = 0;
		pthread_cond_signal(&(PCB[item].cond));
		pthread_mutex_unlock(&mymutex);	
		pthread_join(PCB[item].tid,NULL);
		start += temp;
	}
}


void rr(int slice)
{

	int k;
	start = 0;
	for(k = 0; k < THREADNUM; ++k)
	{
		PCB[k].wait_time = 0;
		PCB[k].visit = 0;
	}
	cout << "----------------RR Schedule----------------" << endl;

	int i;
	int max = 0;
	for(i = 0; i < THREADNUM; ++i)
	{
		if(PCB[i].run_time > max)
		{
			max = i;
		}	
	}
	//cout << "max" << max << endl;
	int temp;
	int count = 1;
	while(PCB[max].run_time)
	{
		cout << "round" << count++ << endl;
		for(i = 0; i < THREADNUM; ++i)
		{
			if(PCB[i].run_time > 0)
			{	
				pthread_mutex_lock(&mymutex);
				if(PCB[i].run_time > slice)
				{
					PCB[i].run_time -= slice;
					pthread_cond_signal(&(PCB[i].cond));
					pthread_mutex_unlock(&mymutex);	
					sleep(1);
					start += slice;
				}
				else
				{
					temp = PCB[i].run_time;
					PCB[i].run_time = 0;
					PCB[i].visit = 1;
					pthread_cond_signal(&(PCB[i].cond));
					pthread_mutex_unlock(&mymutex);
					//pthread_join(PCB[i].tid,NULL);
					sleep(1);
					start += temp;
					
				}
			}

		}
	}
	cout << "over" << endl;
	
	
}

void *Children(void*)
{
	int i;
	int ret[THREADNUM];
	//pthread_t tid[THREADNUM];
	initPCB();
	pthread_mutex_init(&mymutex,NULL);
	for(i = 0; i < THREADNUM; ++i)
	{
		int n = i + 1;
		//printf("Thread%2d:%2d",n,start);
		ret[i] = pthread_create(&(PCB[i].tid),NULL,&thread_func,&n);
		if (ret[i] == 0)
		{
			printf("thread %2d created successfully!\n",i);
			sleep(1);
		}
		else{
			printf("thread %2d fail to create!",i);
		}
		
	}	

	for(i = 0; i < THREADNUM; ++i)
	{
		//pthread_join(tid[i],NULL);
		pthread_join(PCB[i].tid,NULL);
	}
	
	pthread_mutex_destroy(&mymutex);
	pthread_exit(0);
}





int main()
{
	int ret1;
	//创建主线程
	pthread_t tid1;
	ret1 = pthread_create(&tid1,NULL,&Children,NULL);
	if(ret1 == 0)
	{
		printf("creating child threads...\n...\n");
		sleep(20);
	}
	else{
		printf("Create Main Thread failed!\n");
	}

	//FCFS();
	// SJF();
	//priority();
	cout << "Please enter rr time:";
	int slice;
	cin >> slice;
	rr(slice);
	pthread_join(tid1,NULL);
	return 0;

		


	/*int i;
	int ret1;
	for(i = 0; i < 4; ++i)
	{
		switch(i)
		{
			case 0 :
				pthread_t tid1;
				ret1 = pthread_create(&tid1,NULL,&Children,NULL);
				if(ret1 == 0)
				{
					printf("creating child threads......\n");
					sleep(20);
				}	
				else{
					printf("Create Main Thread failed!\n");
				}
				FCFS();
				cout << "xixi" << endl;
				pthread_join(tid1,NULL);
				break;
			case 1 :
				pthread_t tid2;
				ret1 = pthread_create(&tid2,NULL,&Children,NULL);
				if(ret1 == 0)
				{
					printf("creating child threads......\n");
					sleep(20);
				}	
				else{
					printf("Create Main Thread failed!\n");
				}
				SJF();
				pthread_join(tid2,NULL);
				break;
			case 2 :
				pthread_t tid3;
				ret1 = pthread_create(&tid3,NULL,&Children,NULL);
				if(ret1 == 0)
				{
					printf("creating child threads......\n");
					sleep(20);
				}	
				else{
					printf("Create Main Thread failed!\n");
				}
				priority();
				pthread_join(tid3,NULL);
				break;
			case 3 :
				pthread_t tid4;
				ret1 = pthread_create(&tid4,NULL,&Children,NULL);
				if(ret1 == 0)
				{
					printf("creating child threads......\n");
					sleep(20);
				}	
				else{
					printf("Create Main Thread failed!\n");
				}
				int slice;
				cout << "Please enter rr time:";
				cin >> slice;
				rr(slice);
				pthread_join(tid4,NULL);
				break;
		}
		cout << "lala" << endl;
	}*/
}


