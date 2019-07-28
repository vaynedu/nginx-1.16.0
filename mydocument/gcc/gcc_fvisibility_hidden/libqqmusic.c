/*******************************************************************
*    > F-Name :  qqmusic.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Fri 26 Jul 2019 02:30:44 PM CST
*******************************************************************/

#include <stdio.h>


int get_music_id()
{
	return 1111;
}

#if _ATTRIBUTE_FLAG
void __attribute__((visibility("default"))) qqmusic_print()
#else
void qqmusic_print()
#endif
{
    printf("qqmusic id: %d\n", get_music_id());
	return;
}
