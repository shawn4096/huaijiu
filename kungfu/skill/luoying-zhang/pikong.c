// pikong.c By Darken
// Modified by Numa@Sj 99-11-12 2:46

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int perform(object me, object target)
{
        int damage, p;
        string msg;
        
        if( !target ) target = offensive_target(me);
        if(!objectp(target)) return notify_fail("你想劈谁？\n");
        if (wiz_level(me) < wiz_level(target))
                return notify_fail("你不能攻击巫师等级比你高的对手。\n");
        if(target==me)
                return notify_fail("用 suicide -f 指令会比较快些。\n");
        if( !target
            || !target->is_character())
                return notify_fail("你想攻击谁？\n");


        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用劈空掌！\n");   
        if( environment(me)->query("no_fight") )
                return notify_fail("这里不能战斗。\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 150 )
                return notify_fail("你的碧海潮生功修为未到，无法打出劈空掌。\n");
        if( (int)me->query_skill("luoying-zhang",1) < 120 )
                return notify_fail("你的掌法修为不足，使不出劈空掌。\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在内力太弱，不能打出劈空掌。\n");
        if( (int)me->query("jiali") < 100 )
                return notify_fail("你现在加力太弱，不能打出劈空掌。\n");
        if (me->query_skill_prepared("strike") != "luoying-zhang"
            || me->query_skill_mapped("strike") != "luoying-zhang")
                return notify_fail("你现在无法使用劈空掌进行攻击！\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("你的碧海潮生功修为不够，无法使用劈空掌进行攻击！\n");
                
        me->start_perform(4,"劈空掌");
        msg = HIB "\n$N长啸一声，一式劈空掌向$n击到，落英神剑掌风挟带著澎湃汹涌的碧海潮生功蜂拥而至，其势殊不可挡！\n"NOR;
        if (random(me->query_skill("dodge")*2) > target->query_skill("dodge")
        && me->query("combat_exp") > random(target->query("combat_exp")/2))
        {
                me->start_busy(1);
                target->start_busy(random(4));
                damage = (int)me->query_skill("bihai-chaosheng", 1) + (int)me->query_skill("luoying-zhang", 1);
                damage += random(me->query("jiali") * 8);
                damage *= 2;
                if(target->query("neili") > me->query("neili")) damage /= 2;

                if (damage > 1500) damage = 1500;  

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                me->add("neili", -damage/2);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HIG"结果重重的打在$n的胸口，$n登时鲜血狂喷。\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
          me->kill_ob(target);   
     target->kill_ob(me);
        }
        else {
                me->start_busy(2);
                msg += CYN"$n见掌势猛烈，急忙向旁一让，$N这一掌便即落空。\n"NOR;
        }
        message_vision(msg, me, target);
        return 1;
}
