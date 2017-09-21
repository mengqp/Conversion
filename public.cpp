/*******************************************************************************
 * 文件名:public.cpp
 * 文件描述:全局共用的一些函数
 * 作者:mengqp
 * 创建日期:2017/09/21 20:04:46
 * 公司：
 * 版本：Ver1.0
 *
 * 历史版本：
 * 修改人                修改时间                修改版本        修改内容
 *
 *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>

// void itoa(int value,char *str,int radix, int first )	//将整型装换成字符型
// {
//     if( 1 == first )
//     {
//         memset( str, 0, strlen(str));
//         first =0;
//     }

//     char temp[2]=" ";
//     if ( value!=0 )
//     {
//         itoa( value/radix , str , radix, first);
//         temp[0] = char(value%radix+'0');
//         strcat(str,temp);
//     }
// }
char *public_itoa(int num,char *str,int radix)
{
    const char table[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *ptr = str;
    bool negative = false;
    if(num == 0)
    {              //num=0
        *ptr++='0';
        *ptr='\0';                // don`t forget the end of the string is '\0'!!!!!!!!!
        return str;
    }
    if(num<0)
    {               //if num is negative ,the add '-'and change num to positive
        *ptr++='-';
        num*=-1;
        negative = true;
    }
    while(num){
        *ptr++ = table[num%radix];
        num/=radix;
    }
    *ptr = '\0';            //if num is negative ,the add '-'and change num to positive
    // in the below, we have to converse the string
    char *start =(negative?str+1:str); //now start points the head of the string
    ptr--;                           //now prt points the end of the string
    while(start<ptr)
    {
        char temp = *start;
        *start = *ptr;
        *ptr = temp;
        start++;
        ptr--;
    }
    return str;
}
