// by Tie@fy3 hehe
#include <ansi.h>
int main(object me, string str)
{
	string output;
        if(me->is_busy())
        return notify_fail("你现在正忙。\n");

        me->add("jing",-10);
        me->start_busy(2);

    output = HIR"★ "HIW"书剑II"HIR" ★"HIG" 神书榜\n" NOR; 
    output += ""HIW"─────────────────────────────────────\n"NOR"";   
    output += QUEST_D->dyn_quest_list();  
    output += ""HIW"────────────────────────────"HIW" 书剑II"HIW" ────\n\n"NOR""; 

	me->start_more(output);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式: hytask
相关文件: help tasks

这个指令是用来得知目前的所有神书.

HELP
	);
	return 1;
}
