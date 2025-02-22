// xixue.c 吸血青蝠
// By River
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;
int perform(object me,object target)
{
        string msg;
        int skill,damage,p;
        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target))
             return notify_fail("你只能对战斗中的对手使用「吸血青蝠」。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「吸血青蝠」！\n");   
        skill = me->query_skill("hanbing-mianzhang",1);
        if( skill < 121 )
             return notify_fail("你的「寒冰绵掌」等级不够, 还不能使用「吸血青蝠」！\n");
        if( me->query_skill_mapped("strike") != "hanbing-mianzhang" && userp(me))
             return notify_fail("你现在无法使用「吸血青蝠」！\n");
        if( me->query_skill_mapped("parry") != "hanbing-mianzhang" && userp(me))
             return notify_fail("你现在无法使用「吸血青蝠」！\n");
        //add by caiji
        if (me->query_skill_prepared("strike") != "hanbing-mianzhang")
             return notify_fail("你现在无法使用「吸血青蝠」！\n");
        //
        if( me->query_skill("dodge", 1) < 120 )
             return notify_fail("你的轻功不够，无法熟练运用「吸血青蝠」！\n");
        if( me->query_skill("shenghuo-shengong", 1) < 120)
             return notify_fail("你的圣火神功等级不够，无法使用「吸血青蝠」！\n");
        if((int)me->query("neili") < 400)
             return notify_fail("你的内力不够使用「吸血青蝠」。\n");
        if((int)me->query("jingli") < 200)
             return notify_fail("你的精力不够使用「吸血青蝠」。\n");
        me->start_perform(4,"吸血");
        msg = HIC"\n$N突然如同一只吸血青蝠，欺近$n的身前，张嘴便向$n的咽喉咬去。\n"NOR;
        if( random(me->query("combat_exp"))> target->query("combat_exp")/2 
          || !living(target)){
             if(userp(me)) me->add("neili",-200);
             me->add("jingli", -100);
             msg += HIR"$n只觉得咽喉一阵剧痛，$N正在狂吸$n的鲜血！\n"NOR;
             damage = skill;
             damage = damage + (int)me->query_skill("strike");
             damage = damage + (int)me->query_skill("shenghuo-shengong", 1);
             damage = damage/2 + random(damage);
             if(target->query("neili") >= skill)
                  target->add("neili", - random(skill) );
             
             target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
             target->apply_condition("hb_poison",target->query_condition("hb_poison")+skill/5);
                target->start_busy(4);
             me->start_busy(random(2)+1);
             p = (int)target->query("qi")*100/(int)target->query("max_qi");
             msg += "( $n"+eff_status_msg(p)+" )\n";
        }
        else{
             msg += CYN"只见$n不慌不忙，轻轻一闪，躲过了$N的利齿！\n"NOR;
             if(userp(me))
             me->add("neili",-100);
             me->add("jingli",-50);
             me->start_busy(3);
        }
        message_vision(msg, me, target);
        return 1;
}
