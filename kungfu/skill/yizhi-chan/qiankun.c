// qiankun.c
// by snowman@SJ 22/06/99

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

void remove_effect(object me);
int perform(object me, object target)
{
      string msg, dodge_skill;                                   
      int ap, dp;
      
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target)
      || environment(target)!=environment(me))
                return notify_fail("「一指乾坤」只能在战斗中对对手使用。\n");
             
      if( target->query("combat_exp") < 80000 )
                return notify_fail("杀鸡焉用牛刀？对"+target->name()+"你没必要使用一指乾坤吧。\n");
      if( me->query_temp("weapon") )
                return notify_fail("你必须空手使用「一指乾坤」！\n");
      
      if( (int)me->query_skill("yizhi-chan",1) < 180 )
                return notify_fail("你的一指禅不够娴熟，不会使用「一指乾坤」！\n");
      
      if( (int)me->query_skill("yijin-jing",1) < 180 )
                return notify_fail("「一指乾坤」需要雄厚的易筋经内功为基础。\n");
                  
      if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("你所使用的内功不对。\n");
                
      if( target->query_condition("yzc_qiankun"))
                return notify_fail("对方已经身中「一指乾坤」，你不用再费力气了。\n");
      
      if( (int)me->query("max_neili") < 3000 )
                return notify_fail("你的内力修为太次，不能使用「一指乾坤」！\n");
      
      if( (int)me->query("neili") < 700 )
                return notify_fail("你的内力太少了，无法使用出「一指乾坤」！\n");   
            
      if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力太少了，无法使用出「一指乾坤」！\n");   
                  
      if( (int)me->query_temp("yzc/qiankun"))
                return notify_fail("你刚刚用了一次「一指乾坤」，先调息调息一下吧！\n");   
                                                               
      if (me->query_skill_prepared("finger") != "yizhi-chan"
          || me->query_skill_mapped("finger") != "yizhi-chan")
                return notify_fail("你现在无法使用「一指乾坤」进行攻击。\n");                                                                                 
       
      msg = HIC"\n$N面露微笑，曲指对着$n轻轻一弹，只听嗤的一声一股劲气从$P手指激射而出，窜向$p丹田！\n" NOR;
                                           
      ap = me->query_skill("force") + me->query_skill("finger") + me->query_kar();
      dp = me->query_skill("force") + me->query_skill("dodge") + target->query_kar();   
      ap *= me->query("combat_exp")/1000;
      dp *= target->query("combat_exp")/1000;       
                      
      me->receive_damage("neili", me->query_skill("force") + me->query_skill("finger"));
//     me->start_perform(5,"一指乾坤");
      
      if( random(ap) > dp/3) {
                msg += HIW"结果$n一个不小心，被指劲点在丹田之上，顿时丹气混乱，脸色发白！\n"NOR;
                tell_object(target, "你感觉这指劲在丹田里乱窜，扰得你浑身发软，身不由己！\n");
                target->receive_damage("qi", me->query_skill("finger"), me);
                ap = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += damage_msg(me->query_skill("finger"), "内伤");
                msg += "( $n"+eff_status_msg(ap)+" )\n";
                
                target->apply_condition("yzc_qiankun", 2+me->query_kar()/5);                                                    
                }
      else {
   me->start_busy(2);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                }                    
            
      message_vision(msg, me, target);   
      me->set_temp("yzc/qiankun", 1);
      me->start_call_out( (: call_other, __FILE__, "remove_effect", me:), 15);
      return 1;
}

void remove_effect(object me)
{
        if(!me) return;
        me->delete_temp("yzc/qiankun"); 
}

