// songyangjue.c by darken@SJ

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("嵩阳诀只能对战斗中的对手使用。\n");

        if( me->query_skill("hanbing-zhenqi", 1) < 60 )
                return notify_fail("你的寒冰真气不够，无法施展嵩阳诀！\n");

        if( me->query_skill("sword") < 90 )
                return notify_fail("你的剑法程度还不能使用嵩阳诀！\n");

        if( me->query_skill("hand") < 90 )
                return notify_fail("你对大嵩阳手认识还不够！\n");

        if( me->query("neili") < 500 )
                return notify_fail("你的内力不够使用嵩阳诀！\n");

        if( me->query("jingli") < 300 )
                return notify_fail("你的精力不够使用嵩阳诀！\n");

        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "songshan-jian")
                return notify_fail("你必须使用嵩山剑法！\n");

        message_vision(HIW "\n$N剑法突转，竟然用剑施展出大嵩阳手中的招数！\n" NOR, me);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add("neili", -300);
        me->add("jingli", -100);
        me->start_perform(2);

        return 1;
}

