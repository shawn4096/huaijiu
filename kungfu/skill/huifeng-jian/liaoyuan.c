// liaoyuan.c 燎原百击

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      int lvl;
      object weapon;
      string name;
      weapon = me->query_temp("weapon");
      if (weapon) name = weapon->query("name");

      if( !target ) target = offensive_target(me);
     
      if( !target
       || !me->is_fighting(target) )
           return notify_fail("燎原百击只能在战斗中对对手使用。\n");

      if (!weapon
       || weapon->query("skill_type") != "sword"
       || me->query_skill_mapped("sword") != "huifeng-jian")
           return notify_fail("你手里没有剑，无法使用燎原百击！\n");             

      if( (int)me->query_skill("huifeng-jian",1) < 120 )
           return notify_fail("你的回风拂柳剑不够娴熟，不能使用燎原百击！\n");
      
      if( (int)me->query_skill("sword",1) < 120 )
           return notify_fail("你的基本剑法等级不够，不能使用燎原百击！\n");  

      if( (int)me->query_skill("jieshou-jiushi", 1) < 120 )
           return notify_fail("你的截手九式等级不够，不能使用燎原百击！\n");
      
      if( (int)me->query_skill("linji-zhuang", 1) < 120 )
           return notify_fail("你的临济十二庄等级不够，不能使用燎原百击！\n");

      if (me->query_skill_mapped("force") != "linji-zhuang")
           return notify_fail("你所使用的内功不对。\n");

      if( (int)me->query("max_neili") < 1000 )
           return notify_fail("你的内力太弱，不能使用燎原百击！\n");
      
      if( (int)me->query("neili") < 500 )
           return notify_fail("你的内力太少了，无法使用出燎原百击！\n"); 
   
      if (me->query_skill_prepared("hand") != "jieshou-jiushi"
       || me->query_skill_mapped("hand") != "jieshou-jiushi")
           return notify_fail("你不会截手九式，现在无法使用燎原百击进行攻击。\n");

      lvl = ((int)me->query_skill("huifeng-jian", 1) + (int)me->query_skill("jieshou-jiushi", 1) ) /10;

      message_vision(HIW"\n$N长啸一声，身子往高空升去，刚好拦住$n，右手中"+name+HIW"刹那间填满空间。\n"NOR, me,target);
      message_vision(HIW"左手使出截手九式，带起无数小气旋，威力顿然加强。\n"NOR, me,target);
      me->add("neili", -350); 
      me->add("jingli", -150);      
      if( !me->query_temp("huifeng")){
        me->add_temp("apply/attack", lvl); 
        me->add_temp("apply/damage", lvl/2);
        me->set_temp("liaoyuan", 1);
      }
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

      if (present(target,environment(me)) && me->is_fighting(target))
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
      weapon->unequip(); 

      if (present(target,environment(me))
       && me->is_fighting(target)
       && me->query_skill("jieshou-jiushi",1) > 150)
      COMBAT_D->do_attack(me, target, 0, 1);  

      if (present(target,environment(me))
       && me->is_fighting(target)
       && random(me->query_skill("jieshou-jiushi", 1)) > 200)
      COMBAT_D->do_attack(me, target, 0, 0);

      if( me->query_temp("liaoyuan")){
        me->add_temp("apply/attack", -lvl);
        me->add_temp("apply/damage", -(lvl/2));
        me->delete_temp("liaoyuan");
      }
      weapon->wield();
      me->start_busy(2);
      me->start_perform(5, "燎原百击");
      return 1;
}
