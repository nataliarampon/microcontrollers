#ifndef GALILEO2IO_H
#define GALILEO2IO_H

#ifdef __cplusplus
extern "C"
{
#endif

enum BOARD_NAME
{
	BOARD_GALILEO_GEN1=1,
	BOARD_GALILEO_GEN2=2,
	BOARD_UNKNOWN=-1
};


extern int board_name(void);
extern char* pgets(char *s, int size, const char path[]);
extern int pputs(const char path[], const char s[]);

#ifdef __cplusplus
};
#endif

#endif