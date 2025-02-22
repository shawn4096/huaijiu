// 断魂夺魄
// by Looklove@SJ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int i,j;
        i = me->query_skill("cuff", 1)/3;
        j = me->query_skill("qishang-quan", 1)/4;

        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("「断魂夺魄」只能在战斗中对对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「断魂夺魄」！\n");

        if( (int)me->query_skill("qishang-quan", 1) < 180 )
                return notify_fail("你的七伤拳还不够娴熟，使不出「断魂夺魄」绝技。\n");
        if( (int)me->query_skill("shenghuo-shengong", 1) < 180 )
                return notify_fail("你的圣火神功等级还不够，使不出「断魂夺魄」绝技。\n");
        if( (int)me->query_skill("force") < 200 )
                return notify_fail("你的内功等级不够，不能使用「断魂夺魄」。\n");

        if( (int)me->query_str() < 40 )
                return notify_fail("你的膂力还不够强劲，使不出「断魂夺魄」来。\n");

        if( me->query_skill_prepared("cuff") != "qishang-quan"
            || me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("你现在无法使用「断魂夺魄」！\n");                                                                                 
     
        if (target->query_temp("qishang"))
                return notify_fail("对方已经身中七伤拳内伤了。\n");

        if( (int)me->query("max_neili") < 3000)
                return notify_fail("你的内力太弱，使不出「断魂夺魄」。\n");      

        if( (int)me->query("neili") < 1200 )
                return notify_fail("你现在真气太弱，使不出「断魂夺魄」。\n");

        message_vision(HIR"\n$N口中念起七伤断魂夺魄歌诀，将七伤拳意发挥得淋漓尽致，大喝一声全力打出！\n"NOR,me);

        me->add_temp("apply/cuff", i);
        me->add_temp("apply/attack", j);
        me->set_temp("qsq/duanhun",7);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        if(me->is_fighting(target)&&me->query_skill("cuff")>350
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        
        if(me->is_fighting(target)&&me->query_skill("cuff")>400
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        
        if(me->is_fighting(target)&&(me->query_skill("cuff"))>450
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        
        if(me->is_fighting(target)&&random(me->query_skill("cuff"))>500
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        
        if(me->is_fighting(target)&&random(me->query_skill("cuff"))>550
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        
        if(me->is_fighting(target)) 
        {
        if( random(me->query("combat_exp"))>target->query("combat_exp")/3
          &&me->query_skill("qishang-quan")>300)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        else
                {
                if ( random(me->query("combat_exp"))>target->query("combat_exp")/4
                   &&me->query_skill("qishang-quan")>300)
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                else
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                }
        }
        me->add_temp("apply/cuff", -i);
        me->add_temp("apply/attack", -j);
        me->delete_temp("qsq/duanhun");
        me->add("neili", -1200);
        me->add("jingli", -200);
        me->start_busy(1);
        target->start_busy(1);
        me->start_perform(4,"「断魂夺魄」");
        return 1;
}
