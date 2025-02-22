// riyue 日月同辉
// by leontt
// Modify by leontt 1/05/2000

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int i;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「日月同辉」只能在战斗中使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("使用「日月同辉」时必须空手！\n");
        
        if( (int)me->query_skill("xingyi-zhang", 1) < 140 )
                return notify_fail("你的星移掌不够娴熟，使不出「日月同辉」绝技。\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 140 )
                return notify_fail("你的神元功等级不够，不能使用「日月同辉」。\n");

        if (me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("你目前的内功无法支持你使用「日月同辉」进行攻击。\n");  
                        
        if( (int)me->query_int() < 30 )
                return notify_fail("你的悟性还使不出「日月同辉」绝技。\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
         || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("你现在无法使用「日月同辉」进行攻击。\n");  
                                                                                               
        if( (int)me->query("max_neili") < 1200 )
                return notify_fail("你现在内力修为太弱，不能使用「日月同辉」。\n");

        if( (int)me->query("neili") < 800 )
                return notify_fail("你目前内力太少，不能使用「日月同辉」。\n");

        if( (int)me->query("jingli") < 200 )
                return notify_fail("你现在精力太少，不能使用「日月同辉」。\n");

        if( me->query_temp("mr_riyue") )
                return notify_fail("你刚使完「日月同辉」，真气运转不畅，无法再次使用！\n");
                
        tell_object(me,CYN"\n你双掌一搓，在双掌之间形成一个耀眼的「"HIW"气旋"CYN"」！\n" NOR,me, target);
        
        i = (int)me->query_skill("xingyi-zhang", 1);

        me->add_temp("apply/damage", i/5);
        me->add_temp("apply/strike", i/6);
        me->set_temp("mr_riyue", 4);
        
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
        me->add("neili", -100);
        if(me->is_fighting(target)){
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
                me->add("neili", -100);
        }
        if(me->is_fighting(target) && me->query_skill("xingyi-zhang", 1) >= 150){
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
                me->add("neili", -100);
        }
        if(me->is_fighting(target) && random(me->query_skill("xingyi-zhang", 1)) >= 200){
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
                me->add("neili", -100);
        }
                  
        message_vision(YEL "\n$N一式「日月同辉」发挥的淋漓尽致，双掌一分，气定神闲，信心倍增。\n" NOR,me, target);
        me->add_temp("apply/damage", -i/5);
        me->add_temp("apply/strike", -i/6);
        me->delete_temp("mr_riyue");
        me->start_busy(1+random(2));
        me->start_perform( 4,"「日月同辉」");
        me->set_temp("mr_riyue", 1);      
        me->add("jingli", -100);
        me->add("neili", -200);
        if(me->query("neili") < 0) me->set("neili", 0);
        i = (int)me->query_skill("strike")/30;
        if( i > 10 ) i = 10;
        if( i < 4 ) i = 4;
        call_out("remove_effect", i, me);   
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("mr_riyue");
        tell_object(me, HIW"\n你调息片刻，觉得真气恢复了不少，又可以使用「日月同辉」了。\n"NOR); 
}
