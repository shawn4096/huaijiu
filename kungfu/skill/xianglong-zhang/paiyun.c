// 排云双掌
// by snowman@SJ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int i,j,jl;
        i = me->query_skill("strike", 1)/3;
        j = me->query_skill("xianglong-zhang", 1)/3;
        jl= me->query("jiali");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("「排云双掌」只能在战斗中对对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「排云双掌」！\n");

        if( (int)me->query_skill("xianglong-zhang", 1) < 150 )
                return notify_fail("你的降龙十八掌还不够娴熟，使不出「排云双掌」绝技。\n");
        if( (int)me->query_skill("huntian-qigong", 1) < 150 )
                return notify_fail("你的混天气功等级还不够，使不出「排云双掌」绝技。\n");
        if (me->query_skill_mapped("force") != "huntian-qigong")
                return notify_fail("你所使用的内功不对。\n");
        if( (int)me->query_skill("force") < 230 )
                return notify_fail("你的内功等级不够，不能使用「排云双掌」。\n");

        if( (int)me->query_str() < 36 )
                return notify_fail("你的膂力还不够强劲，使不出「排云双掌」来。\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang"
        || me->query_skill_mapped("strike") != "xianglong-zhang"
        || me->query_skill_mapped("parry") != "xianglong-zhang")
                return notify_fail("你现在无法使用「排云双掌」！\n");                                                                                 

        if( (int)me->query("max_neili") < 2000)
                return notify_fail("你现在内力太弱，使不出「排云双掌」。\n");      

        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出「排云双掌」。\n");
//        if(me->query_temp("htqg/powerup"))
//                return notify_fail("你正在使用混天气功。\n");
        if((int)me->query_temp("xlz/xiao") && userp(me)) 
                return notify_fail("你正在使用降龙啸。\n");

        message_vision(WHT"\n$N一声断喝，双掌齐出，挟起满天飞沙！使的正是萧峰的得意功夫「排云双掌」！\n"NOR,me);
        if( jl < 200) me->set("jiali", 200);

        me->add_temp("apply/strike", i);
        me->add_temp("apply/damage", (j/3+i/3));
        me->add_temp("apply/attack", j);
        me->add_temp("apply/strength", j/5);
        me->set_temp("xlz/py");
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        if(me->is_fighting(target)) 
        {
        if( random(me->query("combat_exp"))>target->query("combat_exp")/3
          ||me->query_skill("xianglong-zhang")>350)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        else
                {
                if ( random(me->query("combat_exp"))>target->query("combat_exp")/4
                   ||me->query_skill("xianglong-zhang")>300)
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                else
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                }
        }
        me->add_temp("apply/strike", -i);
        me->add_temp("apply/damage", -(j/3+i/3));
        me->add_temp("apply/attack", -j);
        me->add_temp("apply/strength", -j/5);
        me->delete_temp("xlz/py");
        me->add("neili", -800);
        me->add("jingli", -100);
        me->start_busy(1+random(2));
        me->start_perform(5,"「排云双掌」");
        me->set("jiali", jl);
        return 1;
}
