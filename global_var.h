#ifndef GLOBAL_VAR
#define GLOBAL_VAR

extern int random1;			//1st block rand var
extern int random2;			//2nd block rand var


extern int position;			//current cookie height

extern int num_life;			//life count
extern int score;				//current score

extern int Miss;
extern int Perfect;
extern int my_clear;

extern unsigned short (* Fb_ptr)[480];	//lcd0 buffer

extern int start_x1;			//block1 current Xposition
extern int start_x2;			//block2 current Xposition
extern int start_x3 ;	

extern int hit_check1;			//block1 hit check var
extern int hit_check2;			//block2 hit check var
extern int hit_check3 ;	


extern int temp_start_x1;		//block1 & block2 distance store var
extern int temp_start_x2;


extern int d_min;
extern int d_sec;



extern int level;		//current game level var

extern char ptr[10][10];	//current life string

extern int high_low;





#endif
