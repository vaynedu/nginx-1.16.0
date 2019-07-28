/*******************************************************************
*    > F-Name :  tmemusic.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Fri 26 Jul 2019 02:30:44 PM CST
*******************************************************************/


#include<stdio.h>

int get_music_id()
{
	return 2222;
}

#if _ATTRIBUTE_FLAG
void  __attribute__((visibility("default"))) tmemusic_print()
#else
void tmemusic_print()
#endif
{
    printf("tmemusic id: %d\n", get_music_id());

	return;
}
