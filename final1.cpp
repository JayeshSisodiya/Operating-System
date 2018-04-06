#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#define M 50
#define INF 32767
int time;
typedef struct Q{
	int q[M];
	int f,r;
}Q;

typedef struct Task
{
	int pid,ArT,BrT,CrT,TAT,WrT,RrT,type;
}Task;



void Ins(Q *t,int element)
{
	t->r++;
	t->q[t->r] = element;
}

int FrontQ (Q *t)
{
	return t->q[t->f];
}

int del(Q *t){
	int i=t->f;
	int z=t->q[t->f];
	while(i < t->r){
		t->q[i] = t->q[i+1];
		i++;
	}
	t->r--;
	return z;
}


void sortArT(Task p[],int n)
{
	int i,j;
	Task val;
	for(i=0;i<n-1;i++)
	{
		val = p[i+1];
		for(j=i;j>=0;j--)
			if(val.ArT<p[j].ArT)
				p[j+1] = p[j];
			else 
				break;
		p[j+1] = val;
	}
}

int minRrT(Task p[],int n,int time)
{
	int min=INF,pos;
	for(int i=0;i<n;i++)
	{
		if(p[i].type==1)
			if(p[i].ArT <= time&&p[i].RrT != 0)
				if(p[i].RrT<min)
				{
					min = p[i].RrT;
					pos = i;
				}
		if(p[i].ArT>time)
			break;
	}
	return pos;
}	

void sorting(Task p[],int n)
{
	int i,j;
	Task val;
	for(i=0;i<n-1;i++)
	{
		val = p[i+1];
		for(j=i;j>=0;j--)
			if(val.type<p[j].type)
				p[j+1] = p[j];
			else 
				break;
		p[j+1] = val;
	}
}

int srtf(Task p[],int n,int time)
{
	int i = minRrT(p,n,time);
	p[i].RrT--;
	if(p[i].RrT == 0)
	{
		p[i].CrT  = time+1;
		p[i].TAT = p[i].CrT - p[i].ArT;
		p[i].WrT  = p[i].TAT - p[i].BrT;
	}
	return p[i].pid;
}

int rr(Task p[],Q *t,int tq,int n,int time)
{
	int i,runTime,cp;//cp -> currnet Task
	cp = FrontQ(t);
	for(i=0;i<n;i++)
		if(p[i].pid == cp)
			break;
	p[i].RrT--;
	runTime = p[i].BrT-p[i].RrT;
	if(runTime%tq == 0 && p[i].RrT != 0)
	{
		del(t);
		Ins(t,cp);
	}
	if(p[i].RrT == 0)
	{
		p[i].CrT  = time+1;
		p[i].TAT = p[i].CrT - p[i].ArT;
		p[i].WrT  = p[i].TAT - p[i].BrT;
		del(t);
	}
	return p[i].pid;
}

float avgTAT(Task p[],int n)
{
	int i;
	float avg=0;
	for(i=0;i<n;i++)
		avg += p[i].TAT;
	avg = avg / n;
	return avg;
}

float avgWrT(Task p[],int n)
{
	int i;
	float avg=0;
	for(i=0;i<n;i++)
		avg += p[i].WrT;
	avg = avg / n;
	return avg;
}

void display(Task p[],int n)
{
	printf("===================================######################====================================================\n");
	printf("\nFirst Queue is for Shortest Remaining Time First. \nSecond Queue is for Round Robin.\n\n");
	printf("===================================######################====================================================\n");
	int i;
	printf("|Process Id | Arrival Time | Brust Time | Complition Time | Turn Around Time | Waiting Time | Types|\n");
	for(i=0;i<n;i++)
	{
		printf("|%10d |%14d| %11d| %16d| %17d| %13d| %5d|\n",p[i].pid,p[i].ArT,p[i].BrT,p[i].CrT,p[i].TAT,p[i].WrT,p[i].type);
	}
	printf("\n");
}

void mlqueue(Task p[],int n,int tq,int chart[])
{
	
	int t,i,j,T=0; 
	int cur_pid;
	Q x;
	x.f = 0;
	x.r = -1;
	for(i=0;i<n;i++)
		T += p[i].BrT;
	sortArT(p,n);
	sorting(p,n);
	
	for(t=0;t<T;t++)
	{
		for(i=0;i<n;i++)
			if(p[i].type == 2 && p[i].ArT==t)
				Ins(&x,p[i].pid);
    	for(i=0;i<n;i++)
            if(p[i].ArT <= t && p[i].RrT != 0)
                break;
		if(i==n)
			break;
		switch(p[i].type)
		{
			case 1 :cur_pid = srtf(p,n,t);
					break;
			case 2 :cur_pid = rr(p,&x,tq,n,t);
					break;
			
			default:printf("Please Enter Correct Option\n");
					exit(1);
		}
		
		chart[t] = cur_pid;
	}
}

int main()
{
	
	int i,n,q,chart[M];
	
	Task p[M];
	
	float avg_tat,avg_wt;
	
	printf("============================######################===========================================================");
	printf("\n\nFirst Queue is for Shortest Remaining Time First. \nSecond Queue is for Round Robin.\n\n");
	printf("============================######################===========================================================\n\n");
	printf("Enter number of Proceses to be executed: ");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		printf("Enter ARRIVAL time for %d process: ",i+1);
		scanf("%d",&p[i].ArT);
		printf("Enter BURST time for %d process: ",i+1);
		scanf("%d",&p[i].BrT);
		printf("Enter the type of Process:\t1.System process\t2.Interactive process \n>>>");
		scanf("%d",&p[i].type);
		p[i].pid = i+1;
		p[i].RrT = p[i].BrT;
	}

	
	printf("Enter Time Quantum: ");
	scanf("%d",&q);

	mlqueue(p,n,q,chart);
	display(p,n);
	avg_tat = avgTAT(p,n);
	printf("Average TurnAroundTime = %.2f milisecond\n",avg_tat);
	avg_wt = avgWrT(p,n);
	printf("Average WaitingTime= %.2f milisecond\n",avg_wt);
	
}
