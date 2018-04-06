#include<stdio.h> 
#include<conio.h>
#include<stdlib.h>	
int i=0,j,n=3,m=3;


int curneed[3][3];
int safeseq[3];

	
int available[3]={3,2,2};
int alocated[][3]={{0,0,1},{3,2,0},{2,1,1}};
int maxneed[][3]={{8,4,3},{6,2,0},{3,3,3}};

bool end[3]={false,false,false};
	

int *ResAvl,*ResAlloc,*Promax,*Proneed;
	

void display();
int Check_Algo(int,int *);
int Request_Algo(int,int *);
int Safety_Algo(int,int *,bool *);
void needcalculator();
int safeseqnce();
void displaysafe();
	

int main(){
		printf("There are 3 processes and 3 resources in this problem.\nThe instances of different processes are allocated to processes.\nAnd the maximum need of instances by each process is also been given.\n\n");
		printf("I have used safety Algorithm And Request Algorithm for solving this problem.\n");
		printf("This Program correctly tell you about the system is in safe state or not.\n");
		needcalculator();
		display();
		int *R,a[3],p,req;
		
		printf("How many requests? :");
		scanf("%d",&req);
		for(int i=0;i<req;i++)
		{
			printf("\n\n=======Request %d======\n",i+1);
			printf("Enter Process which generated request(0, 1, 2): \n");scanf("%d",&p);
			
		printf("Enter resource Requests: ");
		scanf("%d",a);
		scanf("%d",a+1);
		scanf("%d",a+2);
		R=a;
		printf("For Process P%d checking Request\n",p);
		Check_Algo(p,R);
		
	    }
	    
}
int Check_Algo(int pid,int *R){
		if(Request_Algo(pid,R)==1)display();
		else{
			printf("Request Not Satisfied\n");
			return 0;
		}
		printf("Now Checking Safety\n");
		if(safeseqnce()!=0)displaysafe();
		else printf("Safe Sequence is not Possible\n");
}
int Request_Algo(int pid,int *R){
		ResAvl=available;
		ResAlloc=alocated[pid];
		Proneed=curneed[pid];
		
		for(i=0;i<m;i++){
			if(*(R+i)>*(Proneed+i))
			return 0;
			if(*(R+i)>*(ResAvl+i))
			return 0;
		}
		printf("Request is possible!\n");
		for(i=0;i<m;i++){
			*(ResAlloc+i)+=*(R+i);
			*(ResAvl+i)-=*(R+i);
			*(Proneed+i)-=*(R+i);
		}
		return 1;
}
bool Safety_Algo(int pid){
		printf("Possible Process to Run: P%d\n",pid);
		ResAvl=available;
		ResAlloc=alocated[pid];
		for(i=0;i<3;i++){
			*(ResAvl+i)+=*(ResAlloc+i);
			*(ResAlloc+i)=0;
			*(Proneed+i)=0;
		}
		return true;
}
int safeseqnce(){
		int *W=available,flag;
		int *Seq=safeseq,k=0,g=0;
		bool *F=end;
		for(i=0;i<10;i++){
			k=i%3;
			if(*(F+k)==true)continue;
			Proneed=curneed[k];
			flag=1;
			printf("Need:");
			for(j=0;j<3;j++){
				printf(" %d",*(Proneed+j));
				if(*(Proneed+j)>*(W+j))flag=0;
			}
			printf("\n");
			if(flag==1){
				*(F+k)=Safety_Algo(k);
				*(Seq+(g++))=k;
				display();		
			}
			else *(F+k)=false;
			if(*(F)&*(F+1)&*(F+2)==true)return 1;
		}
		return 0;
}
void displaysafe(){
		int *Seq=safeseq,i;
		printf("Safety Sequence:");
		printf("<");
		for(i=0;i<3;i++)
		printf("%d,",*(Seq+i));
		printf(">\n");
}
void needcalculator(){
		int pid,i,j;
		for(pid=0;pid<n;pid++){
			Proneed=curneed[pid];
			ResAlloc=alocated[pid];
			Promax=maxneed[pid];
			for(i=0;i<m;i++){
				*(Proneed+i)=*(Promax+i)-*(ResAlloc+i);
			}
		}
}
void display(){
		int i,j;
		printf("\n|Process|\t|Maximum|\t|Allocated|\t |Need|\t\t |Available|\n\n");
	  	for(j=0;j<n;j++){
			ResAlloc=alocated[j];
			ResAvl=available;
			Promax=maxneed[j];
			Proneed=curneed[j];
			printf("|P%d\t|\t|",j);
			for(i=0;i<m;i++){
				printf("%d ",*(Promax+i));
			}
			printf("|\t |");
			for(i=0;i<m;i++){
				printf("%d ",*(ResAlloc+i));
			}
			printf("|\t|");
			for(i=0;i<m;i++){
				printf("%d ",*(Proneed+i));
			}
			printf("|\t|");
			printf("Resource%d: %d ",j,*(ResAvl+j));
			printf("|\n");
		}
		printf("\n");
}


