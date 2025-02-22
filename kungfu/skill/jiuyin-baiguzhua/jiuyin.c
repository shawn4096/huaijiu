// jiuyin 九阴三绝爪

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i;
        skill = (int)me->query_skill("jiuyin-baiguzhua", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「九阴三绝爪」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「九阴三绝爪」！\n");   

        if( skill < 140 )
                return notify_fail("你的九阴白骨爪还不够娴熟，使不出「九阴三绝爪」绝技。\n");

        if ( skill < 180 ) i = 3;
        if ( skill < 220 ) i = 2;
        else i = 1;

        if ( me->query_skill_mapped("claw") != "jiuyin-baiguzhua"
          || me->query_skill_prepared("claw") != "jiuyin-baiguzhua")
               	return notify_fail("你现在无法使用「九阴三绝爪」！\n");

        if( me->query_temp("huifeng/mie") )
                return notify_fail("你正在运用「灭剑」心法！\n");

        if( (int)me->query_temp("foguang"))
                return notify_fail("你正在运用「佛光普照」心法！\n");   

        if( (int)me->query("max_neili") < 400 * i  )
                return notify_fail("你现在内力太弱，使不出「九阴三绝爪」。\n");      

        if( (int)me->query("neili") < 1100 )
                return notify_fail("你现在真气太弱，使不出「九阴三绝爪」。\n");

        if( me->query("shen") > -1000000 )
        	if( me->query("GKS") < me->query("BKS") )
                	return notify_fail("你不够狠毒，无法使出「九阴三绝爪」的绝技。\n");

        me->start_perform(5, "九阴三绝爪");
        message_vision(RED"\n$N突然怪叫一声，全身骨骼如爆豆般噼啪作响，手臂突然暴涨三尺！\n"NOR,me);
        me->add("neili", -500);
        me->add("jingli", -50);

        me->add_temp("apply/attack", skill/4);       
        me->add_temp("apply/damage", skill/6);
               
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target)) 
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target)){
           	if(random(me->query("combat_exp")) > target->query("combat_exp")/2)
                	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
           	else	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        }
        me->add_temp("apply/damage", -skill/6);    
        me->add_temp("apply/attack", -skill/4);
        me->start_busy( 1 + random(i));
        return 1;
}
