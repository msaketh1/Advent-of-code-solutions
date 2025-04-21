#include <limits.h>
#include <complex.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//int digits(unsigned long long val) {
//	return (int)log10(val)+1;
//}


int digits(unsigned long long val) {
    int d = 0;
    do {
        ++d;
        val /= 10;
    } while (val);
    return d;
}
void proc(unsigned long long val,unsigned long long* bf) {
	if(val==0) {
		*bf=1;
		*(bf+1)=ULLONG_MAX;
	} else if(digits(val)%2==0) {
		*bf=val/(unsigned long long)pow(10,digits(val)/2);
		*(bf+1)=val%(unsigned long long)pow(10,digits(val)/2);
	} else {
		*bf=val*2024;
		*(bf+1)=ULLONG_MAX;
	}
}
	



unsigned long long search(unsigned long long*p, unsigned long long val, int size) {
	int i=0;
	for(i=0;i<size;++i) {
		if(val==*(p+i)) {
			break;
		}
	}
	if(i!=size) {return i;}
	else return ULLONG_MAX;
}

void print(unsigned long long* q,int size) {
	printf("list=");
	for(int i=0;i<size;++i) {
		printf("%llu ",*(q+i));
	}
}
void prInt(int* q,int size) {
	printf("list=");
	for(int i=0;i<size;++i) {
		printf("%d ",*(q+i));
	}
}
void transfer(unsigned long long* q, unsigned long long*p, int size) {
	for(int i=0;i<size;++i) {
		p[i]=q[i];
	}
}
void transferI(int* q, int*p, int size) {
	for(int i=0;i<size;++i) {
		p[i]=q[i];
	}
}

int main(int argv, char** argc) {
	int datal=1000000; //optional, 10000 should be sufficient.
	unsigned long long* w= (unsigned long long*)malloc(datal*sizeof(unsigned long long));
	unsigned long long* bw= (unsigned long long*)malloc(datal*sizeof(unsigned long long));
	unsigned long long* p = (unsigned long long*) malloc(datal*sizeof(unsigned long long));
	unsigned long long* q= (unsigned long long*) malloc(datal*sizeof(unsigned long long));
	unsigned long long tmp[]={ULLONG_MAX,ULLONG_MAX};
//	unsigned long long init=atoll(argc[1]);
	unsigned long long M=8;
//	p[0]=init;
	p[0]=8435; p[1]=234; p[2]= 928434; p[3]=14; p[4]=0; p[5]=7; p[6]=92446; p[7]=8992692;
//	p[0]=125; p[1]=17; p[2]= 928434; p[3]=14; p[4]=0; p[5]=7; p[6]=92446; p[7]=8992692;
	transfer(p,q,M);
//	p[1]=17;
//	q[1]=17;
	w[0]=1;w[1]=1;w[2]=1;w[3]=1;w[4]=1;w[5]=1;w[6]=1;w[7]=1;
	transfer(w,bw,M);
//	w[1]=1;
//	w[1]=1;
	int steps=atoi(argc[1]);
	int count=0;
	while(count<steps) {
		int nM=M;
		unsigned long long sft=0;
		for(unsigned long long i=0;i<M;++i) {
//			printf("\n loop head \n");
//			print(p,M);
			proc(p[i],tmp);
			unsigned long long pw=bw[i];
			unsigned long long loc=search(q,*tmp,i+sft);
			if(loc==ULLONG_MAX) {
				q[i+sft]=*tmp;
				w[i+sft]=pw;
			} else {
				w[loc]+=pw;
				--nM;
				--sft;
			}
			if(*(tmp+1)!=ULLONG_MAX) {
				++nM;
				++sft;
				unsigned long long loc2=search(q,*(tmp+1),i+sft);
				if(loc2==ULLONG_MAX) {
					q[i+sft]=*(tmp+1);
					w[i+sft]=pw;
				} else {
					w[loc2]+=pw;
					--nM;
					--sft;
				}
			}
		}
		M=nM;
		transfer(q,p,M);
		transfer(w,bw,M);
		++count;
	}	
	unsigned long long sum=0;
	for(unsigned long long i=0;i<M;++i) {
		sum+=w[i];
	}
	printf("total number of stones after %d steps = %llu \n",steps,sum);
//	printf("\n list of stones\n");
//	print(q,M);
//	printf("list of weights\n");
//	print(w,M);
	printf("size = %llu\n",M);
	
	

    	printf("%llu\n", ULLONG_MAX);
}








