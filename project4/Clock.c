#include"myqueue.h"

#define NUMBER 1000


Queue queue;
int fault = 0;
int time[NUMBER] = {0};



int find(int item)
{
	/*int i;
	for(i = 0; i < NUMBER; ++i)
	{
		if(queue.ptr[i] == item)
		{
			return 1;
		}
	}
	return 0;*/
	int i;
	for(i = 0; i < NUMBER; ++i)
	{
		if(queue.ptr[i] == item)
		{
			time[i] = 1;
			return 1;
		}
		return 0;
	}
	

}



void clock(int item)
{
	int i;
	int flag = 0;
	if(!find(item) && !isfull(&queue))
	{
		enqueue(&queue,item);
		fault++;
	}
	else if(!find(item) && isfull(&queue))
	{
		/*dequeue(&queue);
		enqueue(&queue,item);
		fault++;*/
		while(1)
		{
			queue.current = queue.front;
			//for(i = queue.front; i != queue.rear; i = (i + 1) % (queue.maxSize))
			for(i = 0; i < NUMBER; ++i )
			{
				if(time[queue.current] == 0)
				{
					queue.ptr[i] = item;
					flag = 1;
					fault++;
					break;
				}
				else if(time[i] == 1)
				{
					time[i] = 0;
				}
			}

			if(flag == 1)
			{
				break;
			}	
			printf("lala\n");
		}
	}
}



int main()
{
	char temp[16];
	FILE* fp;
	fp = fopen("./workload/workload1","r");
	int item;
	createQueue(&queue,NUMBER);
	while(!feof(fp))
	{
		fscanf(fp,"%s",temp);
		item = atoi(temp);
		//printf("item:%d\n",item);
		clock(item);
	}
	
	//fifo(set,&queue,len);
	printf("fault:%d\n",fault);




	return 0;

}
