/*
* 20171030
*/

#define RunTime

#include <cstdio>
#include <cstring>
#include <ctime>

#define maxn 1000

const char colorA[10] = "\e[01;31m";
const char colorB[10] = "\e[01;34m";
const char colorC[10] = "\e[01;32m";
const char colorS[10] = "\e[0m";
const char keyA = '\r';
const char keyB = '\n';

char filenameA[100];
char filenameB[100];
FILE* fileAp = NULL;
FILE* fileBp = NULL;

char ansA[maxn];
char ansB[maxn];
int res[maxn];
int linenum = 0;
int colA = 0;
int colB = 0;

void solve()
{
	int lenA = strlen(ansA);
	int lenB = strlen(ansB);
	if(lenA!=lenB)
	{ 
		printf("line:%d %s(A)%s(A) %s(B)%s(B) %s\n",linenum,colorA,ansA,colorB,ansB,colorS);
		return ;
	}
	memset(res,0,sizeof(res));
	bool flag = true;
	for(int i=0;i<lenA;i++) if(ansA[i]!=ansB[i]){ res[i] = 1;flag = false;}
	if(flag) return ;
	printf("line:%d %s(A)",linenum,colorA);
	for(int i=0;i<lenA;i++) 
		if(res[i]==1) printf("%s%c%s",colorC,ansA[i],colorA);
		else printf("%c",ansA[i]);
	printf("(A) %s (B)",colorB);
	for(int i=0;i<lenA;i++) 
		if(res[i]==1) printf("%s%c%s",colorC,ansB[i],colorB);
		else printf("%c",ansB[i]);
	printf("(B)%s\n",colorS);
}

int main(int argc,char** argv)
{
	#ifdef RunTime
		double tstart = (double)clock();
	#endif

	if(argc<3) printf("%sError :: %sNeed Two filename%s\n",colorA,colorB,colorS);
	else
	{
		strcpy(filenameA,argv[1]);
		strcpy(filenameB,argv[2]);
		fileAp = fopen(filenameA,"r");
		fileBp = fopen(filenameB,"r");
		if(fileAp==NULL)
		{
			printf("%sError :: %scan not find file named '%s'.%s\n",colorA,colorB,filenameA,colorS);
			return 0;
		}	
		if(fileBp==NULL)
		{
			printf("%sError :: %scan not find file named '%s'.%s\n",colorA,colorB,filenameB,colorS);
			return 0;
		}
		char a;
		char b;
		while(fscanf(fileAp,"%c",&a)!=EOF&&fscanf(fileBp,"%c",&b)!=EOF)
		{
			memset(ansA,0,sizeof(ansA));
			memset(ansB,0,sizeof(ansB));
			linenum++;
			colA = 0;
			colB = 0;
			
			if(a!=keyB)
			{
				ansA[colA++] = a;
				while(fscanf(fileAp,"%c",&a)!=EOF&&a!=keyB) ansA[colA++] = a;
			}

			if(b!=keyB)
			{
				ansB[colB++] = b;
				while(fscanf(fileBp,"%c",&b)!=EOF&&b!=keyB) ansB[colB++] = b;
			}

			solve();
		}
		printf("\n%sThe A End\n",colorA);
		while(fscanf(fileAp,"%c",&a)!=EOF) printf("%c",a);
		printf("\n%sThe B End\n",colorB);
		while(fscanf(fileBp,"%c",&b)!=EOF) printf("%c",b);
		printf("%s\n",colorS);
		fclose(fileAp);
		fclose(fileBp);
	}
	
	#ifdef RunTime
		double tfinish = (double)clock();
		printf("\e[01;34m Program use Time: \e[01;31m%.4f ms\e[0m\n",tfinish-tstart);
	#endif
	return 0;
}