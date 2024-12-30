#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>

char *com, *output;
unsigned int seed, tempo, bl1, bl2, bl3, *b1, *b2, *b3, br3, alt, b, l, intro, end;

void playbeat(int beat, int repeat){
switch(beat){
case 1:
	for(int r = 0; r < repeat; r++){
	for(int i = 0; i < bl1; i++){
		char arg[53];
		sprintf(arg," synth %f sin %d fade 0 0 0.05 vol %f :",1.0f/tempo,b1[i],(1200.0f-b1[i])/1200);
		strcat(com,arg);
	}}
break;
case 2:
	for(int r = 0; r < repeat; r++){
	for(int i = 0; i < bl2; i++){
		char arg[53];
		sprintf(arg," synth %f sin %d fade 0 0 0.05 vol %f :",1.0f/tempo,b2[i],(1200.0f-b2[i])/1200);
		strcat(com,arg);
	}}
break;
case 3:
	for(int r = 0; r < repeat; r++){
	for(int i = 0; i < bl3; i++){
		char arg[53];
		sprintf(arg," synth %f sin %d fade 0 0 0.05 vol %f :",1.0f/tempo,b3[i],(1200.0f-b3[i])/1200);
		strcat(com,arg);
	}}
break;
}
}

int note(){
	return 440*pow(2,((rand()%64+1)-49)/12);
}

int main(int argc, char *argv[]){
	srand(time(NULL));

	output = malloc(25);
	strcpy(output,"out.ogg");
	seed = rand();
	tempo = 4;
	alt = 1;
	b = 0;
	l = 0;
	intro = 1;
	end = 1;

	int c;
	while((c = getopt(argc, argv, "o:l:s:t:a:b:i:e:")) != -1){
	switch(c){
	case 'o':
		output = optarg;
		break;
	case 'l':
		l = atoi(optarg);
		break;
	case 's':
		seed = atoi(optarg);
		break;
	case 't':
		tempo = atoi(optarg);
		break;
	case 'a':
		alt = atoi(optarg);
		break;
	case 'b':
		b = atoi(optarg);
		break;
	case 'i':
		intro = atoi(optarg);
		break;
	case 'e':
		end = atoi(optarg);
		break;
	case '?':
		printf("Known options are o,s,t,a,b,i,e. All options require an argument.\n");
		return 1;
	default:
		abort();
	}
	}

	srand(seed);

	if(l == 0)
		bl1 = tempo*(rand()%6+4);
	else
		bl1 = tempo*l;
	bl2 = tempo*(rand()%5+4);
	bl3 = tempo*(rand()%5+4);
	b1 = malloc(bl1*4);
	b2 = malloc(bl2*4);
	b3 = malloc(bl3*4);

	for(int i = 0; i < bl1; i++){
		b1[i] = note();
	}
	for(int i = 0; i < bl2; i++){
		b2[i] = note();
	}
	for(int i = 0; i < bl3; i++){
		b3[i] = note();
	}

	com = malloc(30+53*tempo*125+40*tempo*alt*150);
	strcpy(com,"sox -n ");
	strcat(com,output);
	
	if(alt > 0){
		br3 = (rand()%21+10)*tempo/bl3;
	}

	if(b == 0 && intro > 0)
		playbeat(2,(rand()%16+10)*tempo/bl2);
	if(b == 0){
		playbeat(1,(rand()%31+50)*tempo/bl1);
		for(int i = 0; i < alt; i++){
			playbeat(3,br3);
			playbeat(1,(rand()%21+40)*tempo/bl1);
		}
	}
	if(b == 0 && end > 0)
		playbeat(2,(rand()%16+10)*tempo/bl2);
	if(b > 0)
		playbeat(1,b);

	com[strlen(com)-1] = '\0';
	FILE *ramctmp = fopen("ramctmp","w");
	fputs(com,ramctmp);
	fclose(ramctmp);
	system("sh ramctmp");
	system("rm ramctmp");

	free(com);
	free(b1);
	free(b2);
	free(b3);
	return 0;
}
