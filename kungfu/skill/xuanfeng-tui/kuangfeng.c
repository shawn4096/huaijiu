// kuangfeng.c  狂风绝技

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int lvl;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("狂风绝技只能对战斗中的对手使用。\n");

        if (!(me->query("thd/perform") & 4))
                return notify_fail("你虽然听说过“狂风绝技”是桃花岛看门神技，可是却未获黄岛主传授。\n");

        if( objectp(me->query_temp("weapon")) )
               return notify_fail("你必须空手使用「狂风绝技」！\n");

        if( (int)me->query_skill("luoying-zhang", 1) < 100 )
                return notify_fail("你的落英神剑掌不够娴熟，无法施展出狂风绝技。\n");

        if( (int)me->query_skill("xuanfeng-tui", 1) < 100 )
                return notify_fail("你的旋风扫叶腿不够娴熟，无法施展出狂风绝技。\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 100)
                return notify_fail("你的碧海潮生功火候不够，无法施展出狂风绝技。\n");
        if ( (int)me->query("max_neili") < 1000)
                return notify_fail("你的内力不够，无法施展出狂风绝技。\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法施展出狂风绝技。\n");
       if (me->query_temp("thd/is_fast"))
                return notify_fail("你正在使用奇门五转。\n");

        if (me->query_skill_prepared("leg") != "xuanfeng-tui"
            || me->query_skill_mapped("leg") != "xuanfeng-tui"
            || me->query_skill_mapped("strike") != "luoying-zhang" )
                return notify_fail("你现在无法使用狂风绝技进行攻击！\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("你的碧海潮生功修为不够，无法使用狂风绝技进行攻击！\n");
                
        me->start_perform(4, "狂风绝技");
        lvl = (me->query_skill("xuanfeng-tui",1) + me->query_skill("luoying-zhang",1) )/2;
        lvl = lvl*5/7 + random(lvl*3/7);
        message_vision(HIG "$N一声清啸，拳脚齐施，使出桃花「狂风绝技」迅捷无伦地攻向$n！\n"NOR,me, target);
 me->add_temp("apply/attack",lvl/6);
 me->add_temp("apply/leg",lvl/8);
        me->add("neili", -(200 +random(100)) );
        me->prepare_skill("leg");
        me->prepare_skill("strike","luoying-zhang");
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->prepare_skill("strike");
        me->prepare_skill("leg","xuanfeng-tui");
        if(me->is_fighting(target)){
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                me->prepare_skill("leg");
                me->prepare_skill("strike","luoying-zhang");
        }
        if(me->is_fighting(target) && me->query_skill("luoying-zhang", 1) > 150)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->prepare_skill("strike");
        me->prepare_skill("leg","xuanfeng-tui");
        if(me->is_fighting(target) && (me->query_skill("xuanfeng-tui",1)) > 180 ){
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                me->prepare_skill("leg");
                me->prepare_skill("strike","luoying-zhang");
        }
        if(me->is_fighting(target) && random(me->query_skill("luoying-zhang", 1)) > 200)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->prepare_skill("strike");
        me->prepare_skill("leg","xuanfeng-tui");
        if(me->is_fighting(target) && random(me->query_skill("xuanfeng-tui", 1)) > 220)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

        me->prepare_skill("leg","xuanfeng-tui");
        me->start_busy(random(2) + 1);
me->add_temp("apply/attack",- lvl/6);
me->add_temp("apply/leg",- lvl/8);
        return 1;
}
