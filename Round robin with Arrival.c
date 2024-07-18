#include<stdio.h>
#include<limits.h>
#define MAX 100
void roundrobin(int n, int a[], int b[], int tq)
{
	int wt[MAX], tat[MAX], rem_b[MAX];
	int t=0;
	int total_wt=0, total_tat=0,i;
	for(i=0;i<n;i++)
	{
		rem_b[i]=b[i];
		wt[i]=0;
	}
	printf("Order of execution:");
	while(1)
	{
		int done=1;
		for(i=0;i<n;i++)
		{
			if(rem_b[i]>0&&a[i]<=t)
			{
				done=0;
				if(rem_b[i]>tq)
				{
					printf("P%d ",i+1);
					t+=tq;
					rem_b[i]-=tq;
				}
				else
				{
					printf("P%d ",i+1);
					t+=rem_b[i];
					wt[i]=t-b[i]-a[i];
					rem_b[i]=0;
				}
			}
		}
		if(done==1)
		{
			break;
		}
	}
	printf("\n\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
	for(i=0;i<n;i++)
	{
		tat[i]=wt[i]+b[i];
		total_wt+=wt[i];
		total_tat+=tat[i];
		printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, a[i], b[i], wt[i], tat[i]);
	}
	printf("The average waiting time = %.2f",(float)total_wt/n);
	printf("\nThe average turn around time = %.2f",(float)total_tat/n);
}
int main()
{
	int n,a[MAX],b[MAX];
	int tq,i;
	printf("Enter number of processes:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter arrival time of P%d: ",i+1);
		scanf("%d",&a[i]);
		printf("Enter burst time of P%d: ",i+1);
		scanf("%d",&b[i]);
	}
	printf("Enter time quantum:");
	scanf("%d",&tq);
	roundrobin(n,a,b,tq);
	return 0;
}
