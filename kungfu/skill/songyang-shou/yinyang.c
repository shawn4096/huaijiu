// Created by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

int perform(object me, object target)
{
        int i, j, damage, num, p, win=0;
        int tmp;
        string msg;
        
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target))
                return notify_fail("大阴阳手绝技只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("songyang-shou", 1) < 140 )
                return notify_fail("你的嵩阳手火候不够。\n");
 
        if( (int)me->query_skill("parry", 1) < 140 )
                return notify_fail("你的基本招架火候不够。\n");

        if( (int)me->query_skill("hanbing-zhenqi", 1) < 140 )
                return notify_fail("你的基本内功火候不够。\n");
                
        if( (int)me->query("max_neili") < 2500 )
                return notify_fail("你的内力修为不够。\n");

        if( (int)me->query("neili") < 800 )
                return notify_fail("你的真气不够。\n");

        if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力不够。\n");
                
        if (!me->query("ss/yy"))
                return notify_fail("你不会大阴阳手绝技。\n");

        if (me->query_skill_mapped("force") != "hanbing-zhenqi")
                return notify_fail("你用什么为基础来使大阴阳手绝技?\n");

        if (me->query_skill_prepared("hand") != "songyang-shou"
         || me->query_skill_mapped("hand") != "songyang-shou")
                return notify_fail("你现在无法使用嵩阳手。\n");

        if (me->query_temp("weapon"))
                return notify_fail("大阴阳手绝技只能空手使用！\n");

        if( me->query_temp("ss_yinyang"))
                return notify_fail("你正在使用大阴阳手绝技。\n");

        me->add("neili", -200);
        me->add("jingli", -50);
        message_vision(HIY "\n$N突然向后倒窜，双掌向着$n发力遥击！\n" NOR,me, target);

 
        num = me->query_skill("songyang-shou",1);
        num += random(me->query_skill("hanbing-zhenqi",1));
        num += me->query_skill("parry",1);
        num = num * (me->query_temp("ss/focus")+1) / 15;
        tmp = me->query_temp("yinyang");

        if( tmp > 0 )
        {
            me->add_temp("apply/attack", -tmp);
            me->add_temp("apply/damage", -tmp);
            me->delete_temp("yinyang");
        }
        
        me->add_temp("apply/attack", num);
        me->add_temp("apply/damage", num);
        me->set_temp("yinyang",num);

        i = (int)me->query_skill("hand")/20;
        if (i > 10) i = 10;
        if (i < 4) i = 4;

        msg = HIB "\n$N双掌一阴一阳，阳掌先出，阴力却先行着体，一股寒气直逼$n而去！\n" NOR;
        if (random(me->query("combat_exp")) > target->query("combat_exp")/2){
                msg += CYN"$n刚要闪避，只觉一股寒气袭上身来，登时机伶伶打了个冷战。\n"NOR;
                damage = (int)me->query_skill("hanbing-zhenqi") + (int)me->query_skill("songyang-shou")/2*3;
                damage = (random(damage) + damage) * (random(2)+1);
                if(damage > 2000) damage = 2000 + (damage - 2000)/100;
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                me->add("neili", -200);
                me->add("jingli", -50);
                if (wizardp(me)) tell_object(me,HIW"damage是"+damage + "。\n"NOR);
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "内伤");
                msg += "( $n" + eff_status_msg(p) + " )\n";
        }
        else{ 
                msg += "$n被这阴寒掌力打在身上，霎时间全身剧震，说不出的难受。\n";
                win = 1;
        }
        message_vision(msg, me, target);

        if (win == 1){
                me->start_busy(1+random(2));
                call_out("remove_effect", 1, me, target, i);
                return 1;
        }
        else {
           msg = HIR"$n只一呆，一股炙热的掌风跟着扑到！\n"NOR;
           if (random(me->query("combat_exp")) > target->query("combat_exp")/2){
              msg += CYN"$n意欲闪避，已是不能，身体立似火烧火燎般痛楚！\n"NOR;
              damage = (int)me->query_skill("hanbing-zhenqi") + (int)me->query_skill("songyang-shou")*2;
              damage = (random(damage) + damage) * (random(2)+1);
              if(damage > 2000) damage = 2000 + (damage - 2000)/100;
              me->add("neili", -200);
              me->add("jingli", -50);
              target->receive_damage("qi", damage);
              target->receive_wound("qi", damage/3);
              if (wizardp(me)) tell_object(me,HIW"damage是"+damage + "。\n"NOR);
              p = (int)target->query("qi") * 100 / (int)target->query("max_qi"); 
              msg += damage_msg(damage, "内伤");
              msg += "( $n" + eff_status_msg(p) + " )\n";
           }
           else {
              msg += "$n被这炙热掌力打在身上，霎时间全身剧震，说不出的难受。\n";
           }
           message_vision(msg, me, target);
        }
        me->set_temp("ss_yinyang",1);

        j = (int)me->query_skill("hand")/10;
        remove_call_out("remove_effect");
        remove_call_out("remove_effect2");
        call_out("remove_effect", 1, me, target, i);
        call_out("remove_effect2",j, me);
        me->start_perform(5,"大阴阳手");
        me->start_busy(1);
        target->start_busy(1+random(2));
        return 1;
}

void remove_effect(object me,object target,int count)
{
        int i;
        if (!me) return;
        if(!target
         || !me->is_fighting(target)
         || me->query_temp("weapon")
         || me->query_skill_prepared("hand") != "songyang-shou"
         || count < 1 ){
            i = me->query_temp("yinyang");      
            me->add_temp("apply/attack", -i);
            me->add_temp("apply/damage", -i);
            me->delete_temp("yinyang");
            return;
        }
        call_out("remove_effect", 1, me, target, count -1);
}

void remove_effect2(object me)
{
        if (!me) return;
        me->delete_temp("ss_yinyang");
        if(me->query_temp("yinyang")){
             me->add_temp("apply/attack",-me->query_temp("yinyang"));
             me->add_temp("apply/damage",-me->query_temp("yinyang")); 
             me->delete_temp("yinyang");
        }
        tell_object(me, HIG"\n你的阴阳掌力渐渐消弱了！\n"NOR);
}
