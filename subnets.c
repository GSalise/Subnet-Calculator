#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
	int prefix;
	int subreq;
	int hostreq;
}subnet;

typedef struct{
	int oct1;
	int oct2;
	int oct3;
	int oct4;
	subnet sub;
}ipAdd;

typedef struct{
	int binz[8];
}binary;

typedef struct{
	int deptNO;
	int hosts;
}hostVLSM;


binary* getbinary(ipAdd);
void subfind(ipAdd);
void findreqsub(ipAdd);
void vlsm(ipAdd);
ipAdd print(ipAdd, int, int, int,int);
int flagnumber(int);

int main(){
	
	ipAdd input;
	char choice, choice1, choice2, choice3;
	
	printf("Enter the 1st octet: ");
	scanf("%d", &input.oct1);
	printf("Enter the 2nd octet: ");
	scanf("%d", &input.oct2);
	printf("Enter the 3rd octet: ");
	scanf("%d", &input.oct3);
	printf("Enter the 4th octet: ");
	scanf("%d", &input.oct4);
	printf("Enter the prefix: /");
	scanf("%d", &input.sub.prefix);
	
	binary *InputBIN=getbinary(input);
	
	printf("Does it need a subnet requirement or host requirement? Y/N: ");
	scanf("  %c", &choice);
	
	if(choice=='Y'){
		printf("Is it a subnet requirement? Y/N: ");
		scanf("  %c", &choice1);
		if(choice1=='Y'){
			printf("\n\nEnter subreq: ");
			scanf("%d", &input.sub.subreq);
			findreqsub(input);
		}else if(choice1=='N'){
			printf("Host req not available");
		}
	}else {
		printf("VLSM? Y/N: ");
		scanf("  %c", &choice2);
		
		if(choice2=='Y'){
			vlsm(input);
		}else{
			subfind(input);
		}
		
	}
	
	
	input.oct1=192;
	input.oct2=0;
	input.oct3=0;
	input.oct4=0;
	input.sub.prefix=8;
	
//	vlsm(input);
	
	
	
	
	
	
	
	return 0;
}

binary* getbinary(ipAdd inp){
	int octet[8]={128,64,32,16,8,4,2,1};
	
	binary *BIN=calloc(4,sizeof(binary));
	

	int catcher=0;
	
	do{
		for(int i=0; i<8; i++){
			if(catcher+octet[i]<inp.oct1 || catcher+octet[i]==inp.oct1){
				catcher+=octet[i];
				BIN[0].binz[i]=1;
			}
		}
	}while(catcher!=inp.oct1);
	catcher=0;
	
	do{
		for(int i=0; i<8; i++){
			if(catcher+octet[i]<inp.oct2 || catcher+octet[i]==inp.oct2){
				catcher+=octet[i];
				BIN[1].binz[i]=1;
			}
		}
	}while(catcher!=inp.oct2);
	catcher=0;
	
	do{
		for(int i=0; i<8; i++){
			if(catcher+octet[i]<inp.oct3 || catcher+octet[i]==inp.oct3){
				catcher+=octet[i];
				BIN[2].binz[i]=1;
			}
		}
	}while(catcher!=inp.oct3);
	catcher=0;
	
	do{
		for(int i=0; i<8; i++){
			if(catcher+octet[i]<inp.oct4 || catcher+octet[i]==inp.oct4){
				catcher+=octet[i];
				BIN[3].binz[i]=1;
			}
		}
	}while(catcher!=inp.oct4);
	catcher=0;
	
	
	return BIN;
}

void subfind(ipAdd inp){
	
	int octet[8]={128,64,32,16,8,4,2,1};

	
	if(inp.sub.prefix>=8 && inp.sub.prefix<16){
		int flag=0;
		for(int i=8; i<(inp.sub.prefix); i++){
			flag++;
		}
		int subnetNO=pow(2,flag);
		int hosts=pow(2,(32-(8+flag)));
		int submask=0;
		for(int i=0; i<flag; i++){
			submask+=octet[i];
		}
		//re
		printf("\nThe total number of Subnets is %d\nThe total number of usable hosts is %d\nThe Subnet Mask is 255.%d.0.0\n\n", subnetNO, hosts-2,submask);

		
		for(int i=0; i<subnetNO; i++){
			printf("[%d] - %d.%d.%d.%d\n\n", i, inp.oct1,inp.oct2,inp.oct3,inp.oct4);
			inp.oct2+=octet[flag-1];
			if(inp.oct2>255){
				(inp.oct1)++;
				inp.oct2=256-inp.oct2;
				if(inp.oct2<0){
					inp.oct2*=-1;
				}
			}
		}
		
		
	}else if(inp.sub.prefix>=16 && inp.sub.prefix<24){
		int flag=0;
		for(int i=16; i<(inp.sub.prefix); i++){
			flag++;
		}
		int subnetNO=pow(2,flag);
		int hosts=pow(2,(32-(16+flag)));
		int submask=0;
		for(int i=0; i<flag; i++){
			submask+=octet[i];
		}
		
		printf("\nThe total number of Subnets is %d\nThe total number of usable hosts is %d\nThe Subnet Mask is 255.255.%d.0\n\n", subnetNO, hosts-2,submask);

		
		for(int i=0; i<subnetNO; i++){
			printf("[%d] - %d.%d.%d.%d\n\n", i, inp.oct1,inp.oct2,inp.oct3,inp.oct4);
			inp.oct3+=octet[flag-1];
			if(inp.oct3>255){
				(inp.oct2)++;
				inp.oct3=256-inp.oct3;
				if(inp.oct3<0){
					inp.oct3*=-1;
				}
			}
		}
		
	}else if(inp.sub.prefix>=24 && inp.sub.prefix<=32){
		int flag=0;
		for(int i=24; i<(inp.sub.prefix); i++){
			flag++;
		}
		int subnetNO=pow(2,flag);
		int hosts=pow(2,(32-(24+flag)));
		int submask=0;
		for(int i=0; i<flag; i++){
			submask+=octet[i];
		}
	
		
		printf("\nThe total number of Subnets is %d\nThe total number of usable hosts is %d\nThe Subnet Mask is 255.255.255.%d\n\n", subnetNO, hosts-2,submask);

		
		for(int i=0; i<subnetNO; i++){
			printf("[%d] - %d.%d.%d.%d\n\n", i, inp.oct1,inp.oct2,inp.oct3,inp.oct4);
			inp.oct4+=octet[flag-1];
			if(inp.oct4>255){
				(inp.oct3)++;
				inp.oct4=256-inp.oct3;
				if(inp.oct4<0){
					inp.oct4*=-1;
				}
			}
		}
	}
	
	
}

void findreqsub(ipAdd inp){
	int octet[8]={128,64,32,16,8,4,2,1};

	int test=2;
	int flag=0;
	
	for(int i=1; test<inp.sub.subreq; i++){
		test=pow(2,i);
		flag++;
	}
	
	//printf("%d-%d", test, flag);
	
	int subnetNO=inp.sub.prefix+flag;
	int range=pow(2,(32-subnetNO));
	//printf("%d", subnetNO);
	
	if(subnetNO>=8 && subnetNO<16){
		for(int i=0; i<test; i++){
			printf("[%d] - %d.%d.%d.%d\n\n", i, inp.oct1,inp.oct2,inp.oct3,inp.oct4);
			inp.oct2+=range;
			if(inp.oct2>255){
				(inp.oct1)++;
				inp.oct2=256-inp.oct2;
				if(inp.oct2<0){
					inp.oct2*=-1;
				}
			}
		}
	}else if(subnetNO>=16 && subnetNO<24){
		for(int i=0; i<test; i++){
			printf("[%d] - %d.%d.%d.%d\n\n", i, inp.oct1,inp.oct2,inp.oct3,inp.oct4);
			inp.oct3+=range;
			if(inp.oct3>255){
				(inp.oct2)++;
				inp.oct3=256-inp.oct3;
				if(inp.oct3<0){
					inp.oct3*=-1;
				}
			}
		}
	}else if(subnetNO>=24 && subnetNO<=32){
		for(int i=0; i<test; i++){
			printf("[%d] - %d.%d.%d.%d\n\n", i, inp.oct1,inp.oct2,inp.oct3,inp.oct4);
			inp.oct4+=range;
			if(inp.oct4>255){
				(inp.oct3)++;
				inp.oct4=256-inp.oct4;
				if(inp.oct4<0){
					inp.oct4*=-1;
				}
			}
		}
	}
	
}

void vlsm(ipAdd inp){
	int dept;
	
	printf("How many departments/subnets do you need?: ");
	scanf("%d", &dept);

	
	ipAdd *VLSM=malloc((dept+1)*sizeof(ipAdd));
	


	int vlsmhost[dept];
	
	for(int i=0; i<dept; i++){
		printf("Enter the number of hosts (in order): ");
		scanf("%d", &vlsmhost[i]);
	}
	
	
	vlsmhost[dept]=-1;

	
	
	
	VLSM[0]=inp;
	
	for(int j=0; vlsmhost[j]!=-1; j++){
		int power=2;
	
		for(int i=1; power-2<vlsmhost[j]; i++){
			power=pow(2,i);
		}
		
		int flag=flagnumber(vlsmhost[j]);
		
		int subnetNO=inp.sub.prefix+((32-inp.sub.prefix)-flag);

		int range=pow(2,(32-subnetNO));
		power=pow(2,((32-inp.sub.prefix)-flag));
		
		VLSM[j+1]=print(VLSM[j],subnetNO,range,power,vlsmhost[j]);
		
		
		if(flag!=flagnumber(vlsmhost[j+1])){
			VLSM[j+1].sub.prefix=subnetNO;
		}
		
		
	}
	
	
	
	

	
	free(VLSM);
}

int flagnumber(int vlsmhost){
	int power=2;
	int flag=0;
	
		for(int i=1; power-2<vlsmhost; i++){
			power=pow(2,i);
			flag++;
		}
	
	return flag;
}

ipAdd print(ipAdd inp, int subnetNO, int range, int power,int host){
	int octet[8]={1,2,4,8,16,32,64,128};
	int count=0;
	int p;

	
	if(host>256 && host<65536){
		p=256;
    	while(p<host){ 
            p*=2; 
            count++; 
        }
        range=octet[count];
    }else if(host>65536 && host<16777216){
    	p=65536;
    	while(p<host){
    		p*=2;
    		count++;
		}
		range=octet[count];
	}
	
	
	//printf("%d-%d-%d", range,p,host);
	
	
	if(subnetNO>=8 && subnetNO<16){
		for(int i=0; i<1 ;i++){
			printf("[%d-%d-%d] - %d.%d.%d.%d\n\n", subnetNO, range,power, inp.oct1,inp.oct2,inp.oct3,inp.oct4);
			inp.oct2+=range;
			if(inp.oct2>255){
				(inp.oct1)++;
				inp.oct2=256-inp.oct2;
				if(inp.oct2<0){
					inp.oct2*=-1;
				}
			}
		}
	}else if(subnetNO>=16 && subnetNO<24){
		for(int i=0; i<1; i++){
			printf("[%d-%d-%d] - %d.%d.%d.%d\n\n", subnetNO, range,power, inp.oct1,inp.oct2,inp.oct3,inp.oct4);
			inp.oct3+=range;
			if(inp.oct3>255){
				(inp.oct2)++;
				inp.oct3=256-inp.oct3;
				if(inp.oct3<0){
					inp.oct3*=-1;
				}
			}
			if(inp.oct2>255){
				(inp.oct1)++;
				inp.oct2=256-inp.oct2;
				if(inp.oct2<0){
					inp.oct2*=-1;
				}
			}
		}
	}else if(subnetNO>=24 && subnetNO<=32){
		for(int i=0; i<1; i++){
			printf("[%d-%d-%d] - %d.%d.%d.%d\n\n", subnetNO, range,power, inp.oct1,inp.oct2,inp.oct3,inp.oct4);
			inp.oct4+=range;
			if(inp.oct4>255){
				(inp.oct3)++;
				inp.oct4=256-inp.oct4;
				if(inp.oct4<0){
					inp.oct4*=-1;
				}
			}
			if(inp.oct3>255){
				(inp.oct2)++;
				inp.oct3=256-inp.oct3;
				if(inp.oct3<0){
					inp.oct3*=-1;
				}
			}
		}
	}
	
	
	
	
	
	
	
	
	return inp;
}
