/*
* 20171111
*/

#define RunTime

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <ctime>

#define eps 0.00001

const char s[] = {'(',')','+','-','*','/','^'};

struct Node{
	char tp;
	double va;
	Node(char tp,double va){this->tp=tp;this->va=va;}
};

bool is_operator(char c)
{
	int len = strlen(s);
	for(int i=0;i<len;i++)
	{
		if(s[i] == c) return true;
	}
	return false;
}

double tr_number(char* c)
{
	int len = strlen(c);
	double ans = 0;
	int bk = len;
	for(int i=0;i<len;i++)
	{
		if(c[i]=='.')
		{
			bk = i+1;
			break;
		}
		ans*=10;
		ans+=(c[i]-'0');
	}
	double res = 1;
	for(int i=bk;i<len;i++)
	{
		res/=10;
		ans+=res*(c[i]-'0');
	}
	return ans;
}

void do_operator(double& ans,char type,double res)
{
	if(type == '+') ans+=res;
	else if(type == '-') ans-=res;
	else if(type == '*') ans*=res;
	else if(type == '/') ans/=res;
	else if(type == '^')
	{
		int pwr = (int)(res+eps);
		double temp = 1;
		for(int i=0;i<pwr;i++)
		{
			temp*=ans;
		}
		ans = temp;
	}
}

void print(std::queue<Node> t)
{
	while(!t.empty())
	{
		printf("%c %f\n",t.front().tp,t.front().va);
		t.pop();
	}
}

double solve(std::queue<Node> p)
{
	if(p.size() <= 1) return p.front().va;

	//处理括号
	std::queue<Node> vbracket;
	int cnt = 0;
	while(!p.empty())
	{
		if(p.front().tp == '(')
		{
			p.pop();
			std::queue<Node> vbt;
			while(!p.empty())
			{
				if(p.front().tp == ')')
				{
					if(cnt==0)
					{
						p.pop();
						break;
					}
					cnt--;
				}else if(p.front().tp == '(') cnt++;
				Node tt(p.front().tp,p.front().va);
				vbt.push(tt);
				p.pop();
			}
			Node t(' ',solve(vbt));
			vbracket.push(t);
		}else
		{
			Node t(p.front().tp,p.front().va);
			vbracket.push(t);
			p.pop();
		}
	}

	//处理阶乘
	std::queue<Node> vfactorial;
	double va;
	while(!vbracket.empty())
	{
		if(vbracket.front().tp == '^')
		{
			vbracket.pop();
			do_operator(va,'^',vbracket.front().va);
		}else if(vbracket.front().tp == ' ')
		{
			va = vbracket.front().va;
		}else
		{
			Node t1(' ',va);
			vfactorial.push(t1);
			Node t2(vbracket.front().tp,vbracket.front().va);
			vfactorial.push(t2);
		}
		vbracket.pop();
	}
	Node t0(' ',va);
	vfactorial.push(t0);


	//处理乘除
	std::queue<Node> vMultiAndDiv;
	va = 0;
	while(!vfactorial.empty())
	{
		if(vfactorial.front().tp == '*'||
			vfactorial.front().tp == '/')
		{
			char vt = vfactorial.front().tp;
			vfactorial.pop();
			do_operator(va,vt,vfactorial.front().va);
		}else if(vfactorial.front().tp == ' ')
		{
			va = vfactorial.front().va;
		}else
		{
			Node t1(' ',va);
			vMultiAndDiv.push(t1);
			Node t2(vfactorial.front().tp,vfactorial.front().va);
			vMultiAndDiv.push(t2);
		}
		vfactorial.pop();
	}
	Node t3(' ',va);
	vMultiAndDiv.push(t3);

	//处理加减
	va = 0;
	while(!vMultiAndDiv.empty())
	{
		if(vMultiAndDiv.front().tp == '+'||
			vMultiAndDiv.front().tp == '-')
		{
			char vt = vMultiAndDiv.front().tp;
			vMultiAndDiv.pop();
			do_operator(va,vt,vMultiAndDiv.front().va);
		}else
		{
			va = vMultiAndDiv.front().va;
		}
		vMultiAndDiv.pop();
	}
	return va;
}

int main()
{
	#ifdef RunTime
		double tstart = (double)clock();
	#endif

	char bluecolor[] = "\e[01;34m";
	char redcolor[] = "\e[01;31m";
	char systemcolor[] = "\e[0m";
	char nocolor[] = "";

	printf("%s*%s * * * * * * * * * * * * * * * * * * * * * * %s*%s\n",bluecolor,nocolor,nocolor,nocolor);
	printf("%s*%s              no space in formula            %s*%s\n",bluecolor,redcolor,bluecolor,nocolor);
	printf("%s*%s  support plus,minus,multiply,divided,curves %s*%s\n",bluecolor,redcolor,bluecolor,nocolor);
	printf("%s*%s * * * * * * * * * * * * * * * * * * * * * * %s*%s\n",bluecolor,nocolor,nocolor,systemcolor);

	char argv[2][100];
	scanf("%s",argv[1]);
	int len = std::strlen(argv[1]);
	std::queue<Node> q;
	int loc = 0;
	char ch[100];
	memset(ch,0,sizeof(ch));
	int chloc = 0;
	while(loc<len)
	{
		if(is_operator(argv[1][loc]))
		{
			if(chloc!=0)
			{
				Node t(' ',tr_number(ch));
				q.push(t);
				memset(ch,0,sizeof(ch));
				chloc = 0;
			}
			Node t(argv[1][loc],0);
			q.push(t);
		}else
		{
			ch[chloc++] = argv[1][loc];
		}
		loc++;
	}
	if(chloc!=0)
	{
		Node t(' ',tr_number(ch));
		q.push(t);
	}
	printf("Ans: %f\n",solve(q));

	#ifdef RunTime
		double tfinish = (double)clock();
		printf("\e[01;34m Program use Time: \e[01;31m%.4f ms\e[0m\n",tfinish-tstart);
	#endif
	return 0;
}
