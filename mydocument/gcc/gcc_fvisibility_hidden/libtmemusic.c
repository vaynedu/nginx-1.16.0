/*******************************************************************
*    > F-Name :  tmemusic.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Fri 26 Jul 2019 02:30:44 PM CST
*******************************************************************/


#include<stdio.h>

extern int attribute_flag;

int get_music_id()
{
	return 2222;
}

#if attribute_flag==0
void tmemusic_print()
{
#else
void  __attribute__((visibility("default"))) tmemusic_print()
{
	printf("_attribute__: %d\n", attribute_flag);
#endif
	printf("tmemusic id: %d\n", get_music_id());

	return;
}
