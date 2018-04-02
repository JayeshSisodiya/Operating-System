#include <stdio.h>
#include <stdlib.h>
#define SIZE 50


typedef struct process
{
	int pid;
	int ar_time;
	int bt_time;
	int wt_time;
	int algo;
	int pri;
}PROCESS;

PROCESS QRR[10];
PROCESS QSRTF[10];
int count1 = 0, count2 = 0, count3 = 0, count4 = 0, time=0;

int i, limit, total = 0, x, counter = 0, time_quantum; 
int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10]; 
float average_wait_time, average_turnaround_time;

void RR()
{
	printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");
      for(total = 0, i = 0; x != 0;) 
      { 
            if(temp[i] <= time_quantum && temp[i] > 0) 
            { 
                  total = total + temp[i]; 
                  temp[i] = 0; 
                  counter = 1; 
            } 
            else if(temp[i] > 0) 
            { 
                  temp[i] = temp[i] - time_quantum; 
                  total = total + time_quantum; 
            } 
            if(temp[i] == 0 && counter == 1) 
            { 
                  x--; 
                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burst_time[i], total - arrival_time[i], total - arrival_time[i] - burst_time[i]);
                  wait_time = wait_time + total - arrival_time[i] - burst_time[i]; 
                  turnaround_time = turnaround_time + total - arrival_time[i]; 
                  counter = 0; 
            } 
            if(i == limit - 1) 
            {
                  i = 0; 
            }
            else if(arrival_time[i + 1] <= total) 
            {
                  i++;
            }
            else 
            {
                  i = 0;
            }
      } 
      average_wait_time = wait_time * 1.0 / limit;
      average_turnaround_time = turnaround_time * 1.0 / limit;
      printf("\n\nAverage Waiting Time:\t%f", average_wait_time); 
      printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);
}




void SRTF()
{
	printf("\nQUEUE 1: Shortest Remaining Time First\n");
	int i, j, time1=0;
	for (i=0; i<count1; i++)
	{
		time1 += QSRTF[i].bt_time;
	}
	for (i=count1-1; i>=0; i--)
	{
		for (j=0; j<i; j++)
		{
			if (QSRTF[j].ar_time > QSRTF[j+1].ar_time)
			{
				PROCESS temp = QSRTF[j];
				QSRTF[j] = QSRTF[j+1];
				QSRTF[j+1] = temp;
			}
		}
	}
	i=0;
	int prev = -1;
	while (i<time1)
	{
		int min = 9999, pos;
		for (j=0; j<count1; j++)
		{
			if (QSRTF[j].ar_time<=i && QSRTF[j].bt_time<min && QSRTF[j].bt_time>0)
			{
				min = QSRTF[j].bt_time;
				pos = j;
			}
		}
		if (prev != pos)
		{
			if (prev != -1)
				printf("%d: process %d", i+time, QSRTF[prev].pid);
			printf("\nfrom %d to ", i+time);
		}
		prev = pos;
		QSRTF[pos].bt_time--;
		i++;
	}
	printf("%d: process %d", i+time, QSRTF[prev].pid);
	time+=time1;
}



PROCESS readProcess (PROCESS p)
{
	printf("\nEnter Process ID, Arrival Time, Burst Time and Algorithm \n(1 for SRTF, 2 for RR\n");
	scanf("%d %d %d %d", &p.pid, &p.ar_time, &p.bt_time, &p.algo);
	p.pri = 0;
	/*if (p.algo == 4)
	{
		printf("Enter priority: ");
		scanf("%d", &p.pri);
	}*/
	p.wt_time=0;
	switch (p.algo)
	{
	
		case 1:	QSRTF[count1++]=p;
		break;
		case 2:QRR[count2++]=p;
		break;
	
		default:printf("\nInvalid selection\n");
	}
	return p;
}



void dispProc(PROCESS p)
{
	printf("\nPID: %d\tArrival time: %d\tBurst time: %d\tAlgorithm: %d", p.pid, p.ar_time, p.bt_time, p.algo);
	if (p.algo==2)
    {
        printf("\nEnter Time Quantum:\t"); 
      scanf("%d", &time_quantum); 
    }
    printf("\n");
}

int main()
{
	int i, n;
	printf("\nEnter the number of processes: ");
	scanf("%d", &n);
	PROCESS parr[n];
	for (i=0;i<n;i++)
	{
		parr[i] = readProcess(parr[i]);
	}
	printf("\nEntered details are: \n");
	for (i=0;i<n;i++)
	{
		dispProc(parr[i]);
	}
	printf("\nPriority between queues:\n1. SRTF\n2. RR");

	SRTF();
	RR();
}
