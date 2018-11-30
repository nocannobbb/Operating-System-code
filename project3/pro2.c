#include<stdio.h>
#include<cstdlib>
#include<iostream>
//#include<windows.h>
#include <pthread.h>
#include <unistd.h> 
using namespace std;

#define N 5//哲学家数量
//哲学家状态
int state[N];
#define STATE_THINKING 11 //思考
#define STATE_EATING 12 //吃饭
#define STATE_HUNGRY 13 //饥饿
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //信号量
pthread_mutex_t s[N] = {PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER};


//检查哲学家的状态,如思考、吃饭以及饥饿
/*void checkState(int i)
{

}*/


//哲学家尝试拿起筷子
void takeForks(int i)
{
	pthread_mutex_lock(&s[i]);
}


//哲学家就餐完后,进行放下手中筷子操作
void putForks(int i)
{
	int left = i;
	int right = (i + 1) % N;
	pthread_mutex_unlock(&s[right]);
	pthread_mutex_unlock(&s[left]);
}


//哲学家进行思考,这里设置为思考 3 秒钟
void think(int i)
{
	printf("philosopher %d is thinking...\n", i);
	//等待一段时间
	int m;
	srand(time(NULL));
	m = 1 +  rand()%5;
	sleep(m);
}

//哲学家进膳
void eat(int i)
{
	//cout << "before lock " << i << endl;
	pthread_mutex_lock(&mutex);
	//cout << "after lock " << i << endl;
	int left = i;
	int right = (i + 1) % N;
	sleep(1);
	if(i % 2 == 0)
	{
		//cout << "before take right" << i <<  endl;
		takeForks(right);
		takeForks(left);
		//pthread_mutex_lock(&s[right]);
		//cout << "lock right kuaizi     " << right << "i: " << i << endl;
		//pthread_mutex_lock(&s[left]);
		//cout << "lock left kuaizi     " <<  left << "i: " << i << endl;
		//cout << "after take right" << i <<  endl;
	}
	else
	{
		//cout << "before take left" << i << endl;
		takeForks(left);
		takeForks(right);
		//pthread_mutex_lock(&s[left]);
		//cout << "lock left kuaizi     " <<  left << "i: " << i << endl;
		//pthread_mutex_lock(&s[right]);
		//cout << "lock right kuaizi     " << right << "i: " << i << endl;
		//cout << "after take left" << i <<  endl;
	}
	//cout << "before unlock " << i << endl;
	pthread_mutex_unlock(&mutex);
	sleep(1);
	//cout << "after unlock " << i << endl << endl;
	srand(time(NULL));
	int m = 1 + rand()%5;
	//sleep(1);
	printf("philosopher %d is eating...\n", i);
	sleep(m);
	//cout << "after sleep" << i << endl;
	putForks(i);

}

//哲学家线程的创建,包括其思考、进餐等内容设置
void* creatPhilosopher(void* vargp)
{
	int id = *(int *)vargp;
	//cout << "id:" << id << endl;
	while(1){
		think(id);
		eat(id);
	}
}


int main()
{
	int ret[N];
	pthread_t tid[N];
	int i;
	int id[N] = {0,1,2,3,4};
	for(i = 0; i < N; ++i)
	{
		//int n = i;
		ret[i] = pthread_create(&tid[i],NULL,&creatPhilosopher,&id[i]);
		if(ret[i] == 0)
			cout << "main thread " << i << "created" << endl;
		else
			cout << "main thread " << i << "created failed" << endl;  
		sleep(1);
	}
	
	for(i = 0; i < N; ++i)
	{
		pthread_join(tid[i],NULL);
	}

	return 0;
}
