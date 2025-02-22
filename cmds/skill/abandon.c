// abandon.c
// Motify by snowman at 19/03/1999.
// 加上再确定。

#include <ansi.h>

int help();
private void delete_skill(string arg, object me, string skill, int level, int lvl);

int main(object me, string arg)
{
	int level, lvl = 0;

	if (!arg)
		return notify_fail("指令格式：abandon|fangqi <技能名称> [级数]\n");
		
	sscanf(arg, "%s %d", arg, lvl);
	  
	if (!me->query_skills() || undefinedp(me->query_skills()[arg]))
		return notify_fail("你并没有这项技能。\n");
		
	level = me->query_skill(arg, 1);

	if (!intp(lvl) || lvl < 0) 
		return notify_fail("级数不可为负数。\n");
		
	if (me->is_busy())
		return notify_fail("你正忙着呢。\n");
	me->start_busy(1);
	if (!lvl) lvl = me->query_skill(arg, 1);
	if (lvl >= level) {
		if (lvl < 60) {
			me->delete_skill(arg);
			write("\n你放弃了"+ to_chinese(arg) +"。\n\n");
		} else {
			write("\n注意！你将要放弃全部 "HIW + to_chinese(arg) + "("+arg+")"NOR" ，确定吗？[Y|N] >");
			input_to("delete_all", me, arg, lvl);
		}
	} 
	else if (level < 100)
		return notify_fail("你这项技能还没有到能收放自如的地步。\n");
	else {
		write("\n注意！你将要放弃" + chinese_number(lvl)+ "级 "HIW+to_chinese(arg)+"("+arg+")"NOR" ，确定吗？[Y|N] >");
		input_to("delete_skill", me, arg, level, lvl);
	}
	return 1;
}

private void delete_all(string arg, object me, string skill, int lvl)
{
	if( arg[0]=='y' || arg[0]=='Y' ){
		me->delete_skill(skill);
		if(userp(me) && !wizardp(me) && lvl >= 60)
			log_file("static/ABANDON", sprintf("%s(%s) 放弃了全部 %d 级 %s 在 %s\n",
				me->name(1), me->query("id"), lvl, to_chinese(skill) , ctime(time()) ));
		write("\n你放弃了"+ to_chinese(skill) +"。\n\n");
	}
	else write("\n你决定保留"+ to_chinese(skill) +"("+skill+")。\n\n");
}

private void delete_skill(string arg, object me, string skill, int level, int lvl)
{
	if( arg[0]=='y' || arg[0]=='Y' ){
		me->set_skill(skill, level - lvl);
		if(userp(me) && !wizardp(me) && lvl >= 60)
		     log_file("static/ABANDON", sprintf("%s(%s) 放弃了 %d 级 %s 在 %s\n",
			  me->name(1),me->query("id"), lvl, to_chinese(skill) , ctime(time()) ));
		write("\n你放弃了" + chinese_number(lvl)+ "级"+ to_chinese(skill) +"("+skill+")。\n\n");
	}
	else write("\n你决定保留"+ to_chinese(skill) +"("+skill+")。\n\n");
}

int help()
{
	write("
指令格式：abandon|fangqi <技能名称> [级数]

放弃一项你所学过的技能，注意这里所说的「放弃」是指将这项技能从你人物
的资料中删除，如果你以后还要练，必须从０开始重练，请务必考虑清楚。

或者可以选择放弃指定的级数，范围必须是 1 到现有级数之间的数目，大于级
数意味着全部放弃！

这个指令使用的场合通常是用来删除一些「不小心」练出来的技能，由于每个
人有着不同的天赋，所修习的武功也不会相同。如果样样都学，到头来只会样
样不精。

例： abandon dodge 10.      放弃 10 级基本轻功。
     abandon dodge.	 放弃基本轻功。
     

注意：巫师不会恢复你放弃的武功，一切后果自负！
     
\n");
	return 1;
}
