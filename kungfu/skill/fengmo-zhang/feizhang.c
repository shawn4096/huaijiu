// feizhang.c  螺旋飞杖
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if(!target) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("螺旋飞杖只能对战斗中的对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
                return notify_fail("你使用的武器不对。\n");
                
        if( (int)me->query_skill("fengmo-zhang", 1) < 100 )
                return notify_fail("你的疯魔杖法不够娴熟，不会使用「螺旋飞杖」。\n");
                                
        if( (int)me->query_skill("huntian-qigong", 1) < 80 )
                return notify_fail("你的混天气功不够高，不能使用飞杖伤敌。\n");
                        
        if( (int)me->query("max_neili", 1) < 800 )
                return notify_fail("你的内力修为不够，不能使用「螺旋飞杖」。\n");
        
        if ((int)me->query("neili",1)<500)
                return notify_fail("你的真气不够，无法使用飞杖。\n");   

        msg = CYN "$N一声长啸，猛吸一口气,将手中"+weapon->query("name")+"凌空掷向$n。\n"NOR;
        me->start_perform(4,"飞杖");

        if(random(me->query("combat_exp",1))>target->query("combat_exp",1)/2){
             damage = (int)me->query_skill("fengmo-zhang", 1);
             damage = damage +  (int)me->query_skill("fengmo-zhang", 1);
             damage = damage +  (int)me->query_skill("staff", 1);
                damage = damage +  (int)me->query_skill("staff", 1);

             if ( damage > 1500 ) damage = 1500;                           
             target->receive_damage("qi", damage);
             target->receive_wound("qi", damage);
             me->add("neili", -damage/3);
             msg += HIR"只见$N手中"+ weapon->query("name")+"螺旋飞出,倏的罩向$n,\n$n只觉一股大力铺天盖地般压来,登时眼前一花，两耳轰鸣,哇的喷出一口鲜血！\n只见"+weapon->query("name")+"转了一圈又飞回了$N手中。\n"NOR;
                me->start_busy(1+random(2));
        }
        else{
             msg += CYN"可是$p见事不妙，猛地向前一跃,跳出了$P的攻击范围。$P大步向前接住空中的"+weapon->query("name")+"\n"NOR;
             me->add("neili", -100);
                me->start_busy(2+random(2));
        }
        message_vision(msg, me, target);
        return 1;
}
