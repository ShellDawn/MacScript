/*
* 20171029
*/

#define RunTime

#include <cstdio>
#include <ctime>

int main()
{
	#ifdef RunTime
		double tstart = (double)clock();
	#endif

	printf("%d\n",getpid())
	printf("\e[01;34m Hello World   \e[01;31m\e[5mShellDawn\e[0m\e[01;34m   ^_^ !~!\e[0m\n");
	
	#ifdef RunTime
		double tfinish = (double)clock();
		printf("\e[01;34m Program use Time: \e[01;31m%.4f ms\e[0m\n",tfinish-tstart);
	#endif
	return 0;
}