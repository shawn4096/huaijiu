// shijiushi.c 玉女十九式

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
#define MAX_HITS    19
 
int perform(object me, object target)
{
        string weapon;
        int i;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("玉女十九式只能对战斗中的对手使用。\n");

        if( me->query_dex() < 60 )
                return notify_fail("你在身法上先天禀赋不足，不能使用玉女十九式！\n");
        
        if( me->query_skill("zixia-gong", 1) < 300 )
                return notify_fail("你的紫霞功火候未到，无法施展玉女十九式！\n");

        if( me->query_skill("dodge") < 300 )
                return notify_fail("玉女十九式需要超绝的轻功配合，方能有效施展！\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用玉女十九式！\n");

        if( me->query("neili") <= 5000 )
                return notify_fail("你的内力不够使用玉女十九式！\n");

        if( me->query("jingli") <= 3000 )
                return notify_fail("你的精力不够使用玉女十九式！\n");

        if( me->query_temp("hsj_19"))
                return notify_fail("你正在运用玉女十九式！\n");

        if( !me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("你手中无剑怎能使用玉女十九式？！\n");

        weapon = (me->query_temp("weapon"))->query("name");

        message_vision(HIC "\n$N运剑如风，精妙非常的“玉女剑十九式”一式式施展开来。" + weapon + HIC"如银龙出海,幻起道道电光！\n" +
        "顷刻之间，$N将“玉女十九剑”中那十九式的数百招一气呵成的使了出来，这数百招便如一招，剑法之快，直是匪夷所思。\n\n" NOR, me, target);
        me->set_temp("hsj_19",1);
          me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1));
 
    for( i = 0; i < MAX_HITS; i ++ ) {
        if( random( MAX_HITS ) >= i ) {
          if (me->query("gender") == "女性")
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          else
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
          me->add("neili",-100);
          }
        else {
            break;
        }
    }
        me->add("neili", -300);
          me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1));
        me->add("jingli", -100);
        me->delete_temp("hsj_19");
        me->start_perform(2+random(3));

        return 1;
}

