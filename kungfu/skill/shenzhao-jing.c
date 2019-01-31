// shenzhao-jing.c
// written by Xiaoyao 98.7.25

inherit FORCE;
#include <ansi.h>
int valid_enable(string usage) { return usage == "force"; }

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
        return valid_public(me);
}

int practice_skill(object me)
{
        if((int)me->query_skill("shenzhao-jing", 1) >= 220 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("shenzhao-jing", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高神照经。\n");       
	}
        return notify_fail("神照经只能通过学习来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return SKILL_D("shenzhao-jing/") + func;
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIW + me->name()+"双手摆于胸前，头顶白气越来越浓。"NOR,
    "start_my_msg" : "你慢慢盘膝而坐，双手摆于胸前，体内一股暖流随经脉缓缓流转。\n",
    "start_other_msg" :HIW + me->name()+"缓缓坐下，弯曲双手摆于胸前，头上白雾缓缓升起。\n"NOR,
    "halt_msg" : HIW "$N猛的睁开双眼，双手迅速回复体侧，仔细打量四周。\n"NOR,
    "end_my_msg" : "你一个周天行将下来，精神抖擞的站了起来。\n",
    "end_other_msg" : HIW "只见盘旋在"+me->name()+"头顶的白气慢慢消散，"+me->name()+"睁开双眼，站了起来。\n"NOR
     ]);
}
