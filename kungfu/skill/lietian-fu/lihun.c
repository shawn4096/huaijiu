// lihun.c 离魂斩

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      int lvl;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = (int)me->query_skill("lietian-fu", 1)/4;
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
        return notify_fail("「离魂斩」只能在战斗中对对手使用。\n");

      if (!weapon || weapon->query("skill_type") != "axe"
       || me->query_skill_mapped("axe") != "lietian-fu")
        return notify_fail("你使用的兵刃不正确，无法使用「离魂斩」！\n");             

      if( (int)me->query_skill("lietian-fu",1) < 120 )
        return notify_fail("你的裂天斧法不够娴熟，不能使用「离魂斩」！\n");
      
      if( (int)me->query_skill("axe",1) < 100 )
        return notify_fail("你的基本斧法等级不够，不能使用「离魂斩」！\n");  
     
      if( (int)me->query_skill("guiyuan-tunafa", 1) < 100 )
        return notify_fail("你的归元吐纳法等级不够，不能使用「离魂斩」！\n");

      if( (int)me->query("max_neili") < 1000 )
        return notify_fail("你的内力太弱，不能使用「离魂斩」！\n");
      
      if( (int)me->query("neili") < ( me->query_skill("force")+ lvl ))
        return notify_fail("你的内力太少了，无法使用出「离魂斩」！\n");   
                                                                                 
      message_vision(RED"\n$N使出「离魂斩」，每一式中都带着奇异的韵律，似乎时间都被这韵律所凝结，猛然间斧影如闪电似惊虹，如海浪般卷来。\n"NOR, me,target);
      me->add("neili", - 300);
      me->add("jingli", -50);      
      lvl=random(lvl/2)+lvl/2;
      me->add_temp("apply/strength", lvl);
      me->add_temp("apply/attack", lvl);
      me->set_temp("lihun", 1);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
 if (present(target,environment(me)) && me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
      if (present(target,environment(me)) && me->is_fighting(target))
 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);  
      if (present(target,environment(me))
       && me->is_fighting(target)
       && me->query_skill("lietian-fu", 1) > 150)
 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      me->add_temp("apply/strength", -lvl);
      me->add_temp("apply/attack", -lvl);
      me->delete_temp("lihun");
 me->start_busy(2);
      me->start_perform(4,"「离魂斩」");
      return 1;
}
