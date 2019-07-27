/*******************************************************************
*    > F-Name :  qqmusic.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Fri 26 Jul 2019 02:30:44 PM CST
*******************************************************************/

#include<stdio.h>

extern int attribute_flag;

int get_music_id()
{
	return 1111;
}

#if attribute_flag==0
void qqmusic_print()
{
#else
void __attribute__((visibility("default"))) qqmusic_print()
{
	printf("__attribute__ = %d\n",attribute_flag);

#endif
	printf("qqmusic id: %d\n", get_music_id());

	return;
}
