// wujian.c
// tiantian@sj
// modified by olives@SJ 4/31/2001
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

void remove_effect(object me, object weapon);
int perform(object me, object target)
{
	int skill;
	int i;
	object weapon;

	skill = (int)me->query_skill("xuantie-jianfa", 1);                

	if( !target ) target = offensive_target(me);

	if( !target || !me->is_fighting(target) )
		return notify_fail("「无剑胜有剑」只能在战斗中使用。\n");

	if(me->query_temp("wujian"))
		return notify_fail("你正在使用「无剑胜有剑」。\n");

	if(!objectp(weapon = me->query_temp("weapon")) 
	|| weapon->query("skill_type")!="sword")
		return notify_fail("你手中无剑，如何使的出玄铁剑法的绝技！\n");

	if(weapon->query("unique")
	|| weapon->query("rigidity")>3
	|| weapon->query("sharpness")>3 )
		return notify_fail("你如此依赖宝剑，如何能领会「无剑胜有剑」的意境?\n");

	if( (int)me->query_skill("xuantie-jianfa", 1) < 200 ) 
		return notify_fail("你的玄铁剑法不够娴熟，不会使用「无剑胜有剑」。\n");
		
	if( (int)me->query_skill("force", 1) < 200 )
		return notify_fail("你的基本内功等级不够，不能使用「无剑胜有剑」。\n");

    	if (me->query_skill_mapped("sword") != "xuantie-jianfa" )
		return notify_fail("你现在无法使用「无剑胜有剑」。\n");

	if( me->query("max_neili")<3000)
		return notify_fail("你的内力修为太差，不能使用「无剑胜有剑」。\n");
	if( (int)me->query("neili") < 3000 )
		return notify_fail("你现在内力太弱，不能使用「无剑胜有剑」。\n");

     	me->start_perform(2,"「无剑胜有剑」");

	message_vision(HIB "\n$N将内力灌注剑上，纯以意气运剑，但觉天地间无一不可为剑，渐入「无剑胜有剑」的境界。\n" NOR, me, target);
        i=(me->query_skill("xuantie-jianfa",1)+me->query_skill("force",1))/6;
	i=i+random(i);
	if(i>160) i=160+(i-160)/10;
	me->add("neili",-i*2);
/*
	weapon->unequip();
	if(!weapon->query("wujian"))
	{
		weapon->add("weapon_prop/damage",i);
		weapon->set("wujian",1);
	}
	weapon->wield();
*/
//      给兵器加damage很可能出问题的，不如加在人身上好了
	me->add_temp("apply/damage",i);
	me->set_temp("wujian",i);
	me->start_busy(1);
	call_out("check_fight",1,me,weapon);
	return 1;
}

void check_fight(object me, object weapon) 
{ 
	if(!me
	|| !living(me)
	||  me->is_ghost()
	|| !me->is_fighting()
	|| !me->query_temp("weapon")
	||  me->query_temp("weapon") != weapon) 
	{
		remove_effect(me,weapon);
		return;
	}
            call_out("check_fight", 1, me, weapon); 
} 

void remove_effect(object me, object weapon)
{
	int lvl;

	if (!me)
		return;
	lvl = me->query_temp("wujian");
	me->add_temp("apply/damage",-lvl);
	me->delete_temp("wujian");
/*	if (!weapon) {
		
                me->set_temp("last_damage_from", "作弊失败被惩罚");
		me->die(); 

//     damage已经加在人身上了，不需要如此惩罚

		return;
	} */
	message_vision(HIB"只听“砰”的一声，"+weapon->query("name")
		+HIB"不堪$N内力冲击，裂成了碎片。\n"NOR,me);
	weapon->unequip();
	weapon->move(environment(me));
	weapon->set("name", weapon->query("name")+"的碎片");            
	weapon->set("long", "这是"+weapon->name()+"的碎片。\n");
	weapon->set("value", 0);
	weapon->set("weapon_prop", 0);
}
