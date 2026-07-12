#include <stdio.h>
#include <conio.h>
struct details
{
	int id;
	char name[50];
	int quantity;
};
void savetofile(struct details d[],int n);
int loadfromfile(struct details d[]);
struct details createlist(void);
void main()
{
	struct details d[100];
	int ch,i=0,j,k,searchid,newqty,found=0;
	i=loadfromfile(d);
	clrscr();
	do
	{
		printf("\n\t Craft material and management system");
		printf("\n 1.Add craft item");
		printf("\n 2.Display craft item");
		printf("\n 3.Search craft item");
		printf("\n 4.Update quantity");
		printf("\n 5.Delete craft item");
		printf("\n 6.Exit");
		printf("\n Enter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				d[i]=createlist();
				i++;
				savetofile(d,i);
				break;
			case 2:
				if(i==0)
				{
					printf("\n No item added yet!");
				}
				else
				{
					printf("\n Id\t Name\t Quantity\n");
					for(j=0;j<i;j++)
					{
						printf("\n %d\t %s\t %d",d[j].id,d[j].name,d[j].quantity);
					}
				}
				break;
			case 3:
				printf("\n Enter item Id:");
				scanf("%d",&searchid);
				for(j=0;j<i;j++)
				{
					if(d[j].id==searchid)
					{
						found=1;
						printf("\n Id found!");
						printf("\n Id:%d",d[j].id);
						printf("\n Name:%s",d[j].name);
						printf("\n Quantity:%d",d[j].quantity);
						break;
					}
				}
				if(found==0)
					printf("\n Id not found!");
				break;
			case 4:
				printf("\n Enter id:");
				scanf("%d",&searchid);
				for(j=0;j<i;j++)
				{
					if(searchid==d[j].id)
					{
						found=1;
						printf("\n Id:%d",d[j].id);
						printf("\n Current quantity:%d",d[j].quantity);
						printf("\n Enter new quantity:");
						scanf("%d",&newqty);
						d[j].quantity=newqty;
						savetofile(d,i);
						printf("\n Quantity updated!");
						break;
					}
				}
				if(found==0)
				{
					printf("\n Id not found!");
				}
				break;
			case 5:
				printf("\n Enter Id to delete:");
				scanf("%d",&searchid);
				for(j=0;j<i;j++)
				{
					if(searchid==d[j].id)
					{
						found=1;
						for(k=j;k<i-1;k++)
						{
							d[k]=d[k+1];
						}
						i--;
						savetofile(d,i);
						printf("\n Id deleted successfully!");
						break;
					}
				}
				if(found==0)
					printf("\n It not found!");
				break;
			case 6:
				printf("\n Exiting the program");
				printf("\n press enter key!");
				break;
			default:
				printf("\n Wrong choice!");
				break;
		}
	}while(ch!=6);
	getch();
}
struct details createlist(void)
{
	struct details d;
	printf("\n Enter item Id:");
	scanf("%d",&d.id);
	fflush(stdin);
	printf("\n Enter item Name:");
	gets(d.name);
	printf("\n Enter item Quantity:");
	scanf("%d",&d.quantity);
	return d;
}
void savetofile(struct details d[],int n)
{
	FILE *fp;
	fp=fopen("craft.dat","wb");
	if(fp==NULL)
	{
		printf("\n Error saving file");
		return;
	}
	fwrite(&n,sizeof(int),1,fp);
	fwrite(d,sizeof(struct details),n,fp);
	fclose(fp);
}
int loadfromfile(struct details d[])
{
	FILE *fp;
	int n=0;
	fp=fopen("craft.dat","rb");
	if(fp==NULL)
	{
		return 0;
	}
	fread(&n,sizeof(int),1,fp);
	fread(d,sizeof(struct details),n,fp);
	fclose(fp);
	return n;
}
