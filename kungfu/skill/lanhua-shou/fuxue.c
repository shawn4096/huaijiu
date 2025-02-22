// fuxue.c 兰花拂穴
// Created by Numa 19990927

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h"

inherit F_SSERVER;

string *xue_name = ({
        "曲池穴",
        "冲阳穴",
        "臂儒穴",
        "白海穴",
        "灵台穴",
        "风府穴",
        "神风穴",
        "玉书穴",
}); 

void remove_effect(object me);

int perform(object me, object target)
{
      string msg,name;
      int cp,ap, dp;
      
      if( !target ) target = offensive_target(me);
     
      if( !target
       || !me->is_fighting(target)
       || !living(target)
       || environment(target)!=environment(me))
                return notify_fail("「兰花拂穴」只能在战斗中对对手使用。\n");
             
      if( me->query_temp("weapon") )
                return notify_fail("你必须空手使用「兰花拂穴」！\n");
      
      if( (int)me->query_skill("lanhua-shou",1) < 180 )
                return notify_fail("你的兰花拂穴手还不够娴熟，恐怕做不到「兰花拂穴」的「准」字。\n");
      
      if( (int)me->query_skill("suibo-zhuliu",1) < 180 )
                return notify_fail("你的随波逐流还不够娴熟，恐怕做不到「兰花拂穴」的「快」字。\n");

        if( (int)me->query_skill("qimen-bagua",1) < 180 )
                return notify_fail("你的奇门八卦还不够娴熟，恐怕做不到「兰花拂穴」的「奇」字。\n");
                  
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("你所使用的内功不对。\n");
                
        if( target->query_condition("lanhua-fuxue"))
                return notify_fail("对方已经身中「兰花拂穴」，你不用再费力气了。\n");

        if( (int)me->query("neili") < 700 )
                return notify_fail("你的内力太少了，无法使出「兰花拂穴」！\n");
            
        if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力太少了，无法使出「兰花拂穴」！\n");
                  
        if( (int)me->query_temp("lanhua-fuxue"))
                return notify_fail("你刚刚使用过「兰花拂穴」，先休息一下吧！\n");   
                                                               
        if (me->query_skill_prepared("hand") != "lanhua-shou"
         || me->query_skill_mapped("hand") != "lanhua-shou")
                return notify_fail("你现在无法使用「兰花拂穴」进行攻击。\n");                                         

        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
                
	me->start_perform(5, "兰花拂穴");
        name = xue_name[random(sizeof(xue_name))];
// 符合 清              
        if (me->query("eff_qi")>=me->query("max_qi") / 2)
        {
                msg = HIC"\n$N右手挥出，拇指与食指扣起，余下三指略张，手指如一枝兰花般伸出，拂向$n，姿势美妙已极。\n" NOR;
                                           
                ap = me->query_skill("force") + me->query_skill("dodge") + me->query_skill("hand") + me->query_skill("qimen-bagua");
                cp = me->query_skill("force") + me->query_skill("dodge") + me->query_skill("hand") + me->query_skill("qimen-bagua");
                dp = target->query_skill("force") + target->query_skill("dodge") +me->query_skill("parry")+target->query_skill("literate");
                ap *= me->query("combat_exp")/1000;
                dp *= target->query("combat_exp")/1000;       
                if (cp>1000) cp=1000;            
                if( random(ap) > dp / 2 )
                {
                        msg += CYN"$n只感「"RED + name + CYN"」上一麻，被$N拂中穴道。\n"NOR;
                        target->receive_damage("qi", random(cp), me);
                        ap = (int)target->query("qi")*100/(int)target->query("max_qi");
                        msg += damage_msg(me->query_skill("hand"), "内伤");
                        msg += "( $n"+eff_status_msg(ap)+" )\n";

                        me->add("neili",-cp/3);
                        me->add("jingli",-100);
                        target->start_busy(random(2));
                }
                else
                {
                        msg += CYN"$n只感「"RED + name + CYN"」上一麻，手臂疾缩，总算变招迅速，没给$N拂中穴道。\n"NOR;
                        me->add("neili",-100);
                        me->add("jingli",-40);
                        me->start_busy(1);
                }                    
                message_vision(msg, me, target);   
                me->set_temp("lanhua-fuxue", 1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me:), 10);
                return 1;
        }
// 不符合 清
        else
        {
                msg = HIC"\n$N右手挥出，拇指与食指扣起，余下三指略张，手指歪歪斜斜地拂向$n。\n" NOR;
                                           
                ap = me->query_skill("force") + me->query_skill("dodge") + me->query_skill("hand") + me->query_skill("qimen-bagua");
                cp = me->query_skill("force") + me->query_skill("dodge") + me->query_skill("hand") + me->query_skill("qimen-bagua");
                dp = target->query_skill("force") + target->query_skill("dodge") +target->query_skill("parry")+target->query_skill("literate",1);
                ap *= me->query("combat_exp")/1000;
                dp *= target->query("combat_exp")/1000;       
                if (cp>1000) cp=1000;      
                if( random(ap) > dp/2 )
                {
                        msg += CYN"$n只感「"RED + name + CYN"」上一麻，被$N拂中穴道。\n"NOR;
                        target->receive_damage("qi", random(cp), me);
                        ap = (int)target->query("qi")*100/(int)target->query("max_qi");
                        msg += damage_msg(me->query_skill("hand"), "内伤");
                        msg += "( $n"+eff_status_msg(ap)+" )\n";

                        me->add("neili",-300);
                        me->add("jingli",-100);
                        target->start_busy(2);
                }
                else
                {
                        msg += CYN"$n只感「"RED + name + CYN"」上一麻，手臂疾缩，总算变招迅速，没给$N拂中穴道。\n"NOR;
                        me->add("neili",-100);
                        me->add("jingli",-40);
                        me->start_busy(1);
                }                    
                message_vision(msg, me, target);   
                me->set_temp("lanhua-fuxue", 1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me:), 10);
                return 1;
        }
}

void remove_effect(object me)
{
        if(!me) return;
        me->delete_temp("lanhua-fuxue");
}
