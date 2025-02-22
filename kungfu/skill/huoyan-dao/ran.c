// by darken@SJ

#include <ansi.h>
inherit F_SSERVER;
int perform(object me)
{
        string msg;
        object target;
        int hs, ls;

        target = me->select_opponent();
        hs = me->query_skill("huoyan-dao",1);
        ls = me->query_skill("longxiang-boruo",1);

        if( !(me->is_fighting() ))
                return notify_fail("「燃」只能对战斗中的对手使用。\n");
        if (objectp(me->query_temp("weapon")))
                return notify_fail("你只能空手运用「燃」的绝技。\n");
        if( hs < 60)
                return notify_fail("你的「火焰刀」等级不够, 不能使出「燃」的绝技！\n");
        if( ls < 60)
                return notify_fail("你的「龙象般若功」功力不够, 不能使出「燃」的绝技！\n");
        if( me->query("neili") < 1000 )
                return notify_fail("你的内力即将用尽，发不出「燃」了！\n");
        if( me->query("jingli") < 1000 )
                return notify_fail("你的精力即将用尽，发不出「燃」了！\n");
        if( me->query("max_neili") < 500 )
                return notify_fail("你的内力不够，不能催动内力发出「燃」绝技！\n");
        if( me->query_skill_mapped("strike") != "huoyan-dao"
         || me->query_skill_prepared("strike") != "huoyan-dao")
                return notify_fail("你必须使用「火焰刀」，才能使出「燃」的绝技！\n");
        if( me->query_skill_mapped("force") != "longxiang-boruo")
                return notify_fail("你现在所使用的内功同「龙象般若功」向抵触，不能使出「燃」的绝技！\n");
 
        msg = HIR "\n$N双掌一聚气，挟著一股热气向$n击出！\n"NOR;
        if(random(me->query_skill("force")) >  target->query_skill("force")*2/5){
                msg+= HIR "$n只觉得全身燥热，内息乱冲！"NOR;
                target->set("qi", target->query("qi")*(ls+hs)/1000);
                target->set("eff_qi", target->query("eff_qi")*(ls+hs)/1000);
                target->set("neili", target->query("neili")*(ls+hs)/1000);
                me->start_busy(2);
                me->add("neili",-400);
        } 
        else {
                msg += HIY "可是$n看破了$N的企图，当即运起全身内力将这股热气反震了回去。\n" NOR;
                msg+= HIR "$N只觉得全身燥热，内息乱冲！"NOR;
                me->set("qi", target->query("qi")*(ls+hs)/1000);
                me->set("eff_qi", target->query("eff_qi")*(ls+hs)/1000);
                me->add("neili",-400);
                target->add("neili",-800);
                target->start_busy(2);
        }
        me->start_perform(5, "燃字诀");
        message_vision(msg, me, target);
        return 1;
}

