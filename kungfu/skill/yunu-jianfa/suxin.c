// yunu-jianfa 玉女素心
// by dubei
// Modify By River 99.5.26
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, string arg)
{
      object weapon, target;
      int dex,armor,skill;       
      dex = me->query_dex()*2;
      armor = me->query_int()*3;
      skill = me->query_skill("yunu-xinjing",1)/5 + me->query_skill("yunu-jianfa",1)/5;
      if (me->query("gender") == "女性") skill *= 5/4;
      weapon = me->query_temp("weapon");

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
               return notify_fail("「玉女素心」只能在战斗中对对手使用。\n");

      if ( !weapon
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "yunu-jianfa" 
        || me->query_skill_mapped("parry") != "yunu-jianfa")
               return notify_fail("你没用玉女素心剑怎么使出「玉女素心」呢？别做梦了！\n");

      if((int)me->query_skill("yunu-jianfa", 1) < 120 )
               return notify_fail("你的玉女剑法修为不够 。\n");

      if((int)me->query_skill("sword", 1) < 120 )
               return notify_fail("你的基本功还不够娴熟，使不出「玉女素心」绝技。\n");

      if((int)me->query_dex() < 30)
               return notify_fail("你的身法还不够迅捷，使不出「玉女素心」绝技。\n");

      if((int)me->query_skill("yunu-xinjing", 1) < 110 )   
               return notify_fail("你的玉女心经修为不够，无法使用「玉女素心」绝技。\n");  

      if((int)me->query_temp("gumu_suxin")) 
               return notify_fail("你现在正在使用「玉女素心」绝技。\n"); 

        if( me->query_temp("wujian") )
                return notify_fail("你正在使用「无剑胜有剑」呢！\n");

      if((int)me->query_temp("hebi"))
               return notify_fail("你正在施展双剑合壁，无法使用「玉女素心」绝技。\n"); 

      if((int)me->query("max_neili") < 1000)
               return notify_fail("你的内力修为不够。\n");

      if((int)me->query("neili") < 700)
               return notify_fail("你的内力不够。\n");

      if((int)me->query("jingli") < 600)
               return notify_fail("你的精力不够。\n");

       me->add("neili", -300);
       me->add("jingli", -150);
       me->add_temp("apply/armor", armor);
       me->add_temp("apply/dexerity",dex);
       me->set_temp("gumu_suxin", 1); 
       message_vision(HIW"\n$N信手一剑，极尽潇洒脱逸之妙，手中"+weapon->name()+HIW"幻化出无数虹芒，向$n电掣攻去。\n"NOR,me,target);
       me->add_temp("apply/damage", 100);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
       me->add_temp("apply/damage", -100);
       me->start_perform(3,"「玉女素心」");
       call_out("check_fight", 1, me, dex, armor, skill);
       return 1;
}

void remove_effect(object me, int dex, int armor, object weapon)
{      
       me->add_temp("apply/armor", -armor);
       me->add_temp("apply/dexerity",-dex);
       me->delete_temp("gumu_suxin");
       tell_object(me, HIW"你「玉女素心」施展完毕，缓缓舒了一口气。\n" NOR); 
}

void check_fight(object me, int dex, int armor, int skill)
{
       object weapon;
       if (!me) return;
       if(!objectp(weapon = me->query_temp("weapon"))
         || me->query_skill_mapped("sword") != "yunu-jianfa"
         || me->query_skill_mapped("parry") != "yunu-jianfa"
         || me->query_skill_mapped("force") != "yunu-xinjing"
         || weapon->query("skill_type") != "sword"){
           remove_effect(me, dex, armor, weapon);
           return;
       }
       if( skill < 1 || !me->is_fighting()) {
           remove_effect(me, dex, armor, weapon);
           return;
       }
       call_out("check_fight", 1, me, dex, armor, skill-1);
}
