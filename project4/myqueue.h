#include<stdio.h>
#include<stdlib.h>


typedef struct queue
{
	int* ptr;
	int front;
	int rear;
	int current;
	int currentSize;
	int maxSize;

}Queue;


void createQueue(Queue* myqueue,int size)
{
	//Queue* myqueue;
	myqueue->ptr=(int *)malloc(sizeof(int) * size);
	if(myqueue->ptr == NULL)
	{
		printf("create queue failed!\n");
		exit(-1);
	}
	myqueue->front = 0;
	myqueue->rear = 0;
	myqueue->current = 0;
	myqueue->currentSize = 0;
	myqueue->maxSize = size;
	//return myqueue;
}


int isfull(Queue* queue)
{
	if(queue->currentSize == queue->maxSize)
	{
		return 1;
	}
	return 0;
}
int isempty(Queue* queue)
{
	if(queue->currentSize == 0)
	{
		return 1;
	}
	return 0;
}

void enqueue(Queue* queue,int item)
{
	if(!isfull(queue))
	{
		queue->ptr[queue->rear] = item;
		queue->rear = (queue->rear + 1) % queue->maxSize;  
		queue->currentSize++;
	}


}
int dequeue(Queue* queue)
{
	if(!isempty(queue))
	{
		int item = queue->ptr[queue->front];
		queue->front = (queue->front + 1) % queue->maxSize;
		queue->currentSize--;
		return item;
	}
}



/*int main()
{
	Queue queue;
	createQueue(&queue,1000000);
	//queue = createQueue(10);
	enqueue(&queue,1);
	enqueue(&queue,2);
	enqueue(&queue,3);
	enqueue(&queue,4);
	enqueue(&queue,5);
	enqueue(&queue,6);
	enqueue(&queue,7);
	enqueue(&queue,8);
	enqueue(&queue,9);
	enqueue(&queue,10);
	enqueue(&queue,11);
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));
	printf("item:%d\n",dequeue(&queue));


}*/
