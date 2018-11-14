 ///
 /// @file    threadsort.c
 /// @author  westring(westringliu@gmail.com)
 /// @date    2018-11-14 09:44:43
 ///
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
typedef struct{
	int array[100];
	int arrlen;
	int index;
}vec;

int compare(const void *a,const void *b)
{
	return *(int*)a - *(int*)b;
}

void *routine(void *arg)
{
	pthread_mutex_t mutex;
	int arr[100];
	int i = ((vec*)arg)->index;;
	int itemsize = sizeof(((vec*)arg)->array[0]);
	int arrsize = ((vec*)arg)->arrlen;
	memcpy(arr,((vec*)arg)->array,arrsize*itemsize);
	qsort(arr,arrsize,itemsize,compare);
	pthread_mutex_lock(&mutex);
	((vec*)arg)->index++;
	pthread_mutex_unlock(&mutex);
	printf("%d ",arr[i]);
	fflush(stdout);
	return NULL;
}

int main()
{
	int err,i;
	pthread_t thid;
	int arr[] = {11,3,998,5455,1,152,990};
	vec nums;
	nums.index = 0;
	nums.arrlen = sizeof(arr)/sizeof(arr[0]);
	memcpy(nums.array,arr,sizeof(arr[0])*nums.arrlen);
	for(i = 0;i < nums.arrlen;i++)
	{
		err = pthread_create(&thid,NULL,routine,&nums);
	}
	sleep(2);
	printf("\n");
	return 0;
}

