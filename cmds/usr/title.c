// title.c (Mon  09-04-95)
 
#include <ansi.h>
inherit F_CLEAN_UP;
 
int main(object me, string str)
{
	write(sprintf(BOLD "%s" NOR "%s\n", RANK_D->query_rank(me), me->short(1)));
	return 1;
}
 
int help(object me)
{
	write(@HELP
ָ���ʽ: title
 
��ʾ��Ŀǰ�Ľ׼���ͷ�Ρ�
 
HELP
	);
}
