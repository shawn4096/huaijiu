// leiting 雷霆万钧
// Created by Numa@Sj 19991118

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, damage, p, p1, p2, p0;
        int focus = me->query_temp("ss/focus");
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「雷霆万钧」只能在战斗中使用。\n");
        
        if( (int)me->query_skill("songshan-jian", 1) < 160 )
                return notify_fail("你的嵩山剑法还不够娴熟，无法使出「雷霆万钧」。\n");
        if( (int)me->query_skill("hanbing-zhenqi", 1) < 160 )
                return notify_fail("你的寒冰真气等级还不够，无法使出「雷霆万钧」。\n");
        if (me->query_skill_mapped("force") != "hanbing-zhenqi")
                return notify_fail("你目前的内功无法使出「雷霆万钧」。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "songshan-jian")
                return notify_fail("你无法使出「雷霆万钧」。\n");
        if (me->query_temp("ss/leiting"))
                return notify_fail("你刚使用完「雷霆万钧」，休息一下吧。\n"); 
                
        if( (int)me->query("max_neili") < 2500)
                return notify_fail("你的内力修为太差，无法使出「雷霆万钧」。\n");
                
        if( (int)me->query("neili") < 500)
                return notify_fail("你现在真气太弱，使不出「雷霆万钧」。\n");
         me->start_perform(4,"雷霆");
        msg = YEL"\n$N右手衣袖鼓了起来，犹似吃饱了风的帆篷一般，全身劲力都集中到了右臂之上，全力向着$n刺出。\n"NOR;
        
        p1 = me->query_skill("sword") + me->query_skill("force");
        p0 = me->query_skill("songshan-jian",1);
        p0 = p0/2 + random(p0/2);
        p0 *= (focus+2)/2;
        p2 = target->query_skill("parry") + target->query_skill("dodge");
        p1 *= me->query("combat_exp")*(focus+1)/1000;
        p2 *= target->query("combat_exp")/1000;
        
        if( p1 + p0 > random(p2/3)+p2/2 )
        {
                msg += CYN"$n被这招乾坤一掷的猛击当胸一撞，立时口中鲜血狂喷而出！\n"NOR;
                damage = (int)me->query_skill("sword") + (int)me->query_skill("force");
                damage = damage*(focus+1);
                if( damage > 3000) damage = 2800 + random(300);
//                me->add_temp("apply/strength", p0);
//              me->add_temp("apply/attack", p0/2);
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                me->add("neili",-damage/3);
                if (wizardp(me))
                        tell_object(me,HIW"damage是"+damage+"，p0是"+p0+"，p1是"+p1+"，p2/2是"+p2/2+"。\n"NOR);
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "内伤");
                msg += "( $n" + eff_status_msg(p) + " )\n";
//                me->add_temp("apply/strength", -p0);
//              me->add_temp("apply/attack", -p0/2);
        } 
        else
        {
                me->add("neili", -100);
                msg += "突然之间，白影急晃，$n向后滑出丈余，立时又回到了原地。\n" NOR;
        }
        message_vision(msg, me, target);
       
        me->start_busy(1);
        me->set_temp("ss/leiting",1);
        i = 20 - p0/20;
        if (i<5)    i = 5;
        if (i>5)    i = 10;
        call_out("remove_effect", i, me);
        return 1;
}

void remove_effect(object me)
{
        if(!me) return;
        me->delete_temp("ss/leiting"); 
}
