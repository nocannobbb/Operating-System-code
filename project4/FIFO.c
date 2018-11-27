#include"myqueue.h"

#define NUMBER 1000


Queue queue;
int fault = 0;



int find(int item)
{
	int i;
	for(i = 0; i < NUMBER; ++i)
	{
		if(queue.ptr[i] == item)
		{
			return 1;
		}
	}
	return 0;

}



void fifo(int item)
{

	if(!find(item) && !isfull(&queue))
	{
		enqueue(&queue,item);
		fault++;
	}
	else if(!find(item) && isfull(&queue))
	{
		dequeue(&queue);
		enqueue(&queue,item);
		fault++;
	}

	
}



int main()
{
	char temp[16];
	FILE* fp;
	fp = fopen("./workload/workload1","r");
	int item;
	createQueue(&queue,NUMBER);
	//fscanf(fp,"%s",temp);
	//printf("item:%s\n",temp);
	while(!feof(fp))
	{
		fscanf(fp,"%s",temp);
		item = atoi(temp);
		//printf("item:%d\n",item);
		fifo(item);
	}
	
	//fifo(set,&queue,len);
	printf("fault:%d\n",fault);




	return 0;

}
