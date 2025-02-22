 // sandou 灵蛇三抖

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      int lv;
      object weapon;

      weapon = me->query_temp("weapon");
      lv = me->query_skill("lingshe-bianfa",1);
 
      if( !target ) target = offensive_target(me);
     
      if( !target
       || !me->is_fighting(target) )
            return notify_fail("「灵蛇三抖」只能在战斗中对对手使用。\n");

      if(!weapon
       || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "lingshe-bianfa")
            return notify_fail("你手里没有鞭，无法使用「灵蛇三抖」！\n");             

      if((int)me->query_skill("lingshe-bianfa",1) < 120 )
            return notify_fail("你的灵蛇鞭法不够娴熟，不能使用「灵蛇三抖」！\n");


      if((int)me->query_skill("dulong-dafa", 1) < 120 )
            return notify_fail("你的毒龙大法等级不够，不能使用「灵蛇三抖」！\n");

        if((int)me->query("neili") < 300 )
            return notify_fail("你的内力太少，不能使用「灵蛇三抖」！\n");
      
      if(me->query_skill_mapped("force") != "dulong-dafa")
            return notify_fail("你现在使用的内功与毒龙大法相抵触，不能使用「金蛇缠丝」。\n");

      message_vision(HIY"\n$N连续抖动手中鞭子，"+weapon->query("name")+HIY+"循着诡异的途径向$n袭去！\n"NOR, me,target);
      me->add("neili", -200);
      me->add("jingli", -100);
      me->set_temp("sandou",1);
      me->add_temp("apply/strength", lv/5);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  

      if (present(target,environment(me)) && me->is_fighting(target))
	      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  

      if(present(target,environment(me))
      && me->is_fighting(target)
      && lv > 150 )
      {
      	 if(random(20)>10) 
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
      else
         	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      }
      me->add_temp("apply/strength", -lv/5);
      me->delete_temp("sandou");        
      me->start_perform(4,"「灵蛇三抖」");
      return 1;
}
