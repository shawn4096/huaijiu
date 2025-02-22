// bingdi.c 花开并蒂

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      int lvl,jiali;

      if(objectp(me->query_temp("weapon")))
           return notify_fail("「花开并蒂」只能空手使用。\n");

      lvl = (int)me->query_skill("zhenshan-mianzhang", 1);

      if( !target ) target = offensive_target(me);

      if( !target
       || !me->is_fighting(target) )
           return notify_fail("「花开并蒂」只能在战斗中对对手使用。\n");

      if( lvl < 120 )
           return notify_fail("你震山绵掌修为尚不纯熟,无法使用「花开并蒂」！\n");             

      if((int)me->query_skill("yinyun-ziqi",1) < 120 )
           return notify_fail("你的氤氲紫气修为尚浅无法使用「花开并蒂」！\n");
 
      if((int)me->query_skill("strike",1) < 120 )
           return notify_fail("你的基本掌法等级不够，不能使用「花开并蒂」！\n");  

      if((int)me->query("max_neili") < 2000 )
           return notify_fail("你的内力修为太弱，不能使用「花开并蒂」！\n");
     
      if((int)me->query("neili") < 700 )
           return notify_fail("你的内力太少了，无法使用出「花开并蒂」！\n");   

      if((int)me->query("jingli") < 500 )
           return notify_fail("你的精力太少了，无法使用出「花开并蒂」！\n");

      if(me->query_skill_prepared("strike") != "zhenshan-mianzhang"
       || me->query_skill_mapped("strike") != "zhenshan-mianzhang"
       || me->query_skill_mapped("parry") != "zhenshan-mianzhang"
       || me->query_skill_mapped("force") != "yinyun-ziqi")
           return notify_fail("你现在无法使用「花开并蒂」进行攻击。\n");

      if( me->query_temp("wd_hkbd"))
              return notify_fail("你刚使完「花开并蒂」，目前气血翻涌，无法再次运用！\n");

      message_vision(HIC"\n$N深深吸一口气，左手挥掌猛击$n右颊，右手出指疾点$n左肩“缺盆穴”，\n"
                       +"跟着右掌击$n左颊，左手食指点$n右肩后“缺盆穴”。连续三式，便如暴风\n"
                       +"骤雨般使出，这一招叫作“花开并蒂”，名称好听，招数却十分厉害。\n"NOR,me,target);

        jiali = (int)me->query("jiali");
        me->add("neili",-( 300 + random(jiali)));
        me->add("jingli", -80);

        lvl /= 6;
        me->add_temp("apply/strike", lvl);
        me->add_temp("apply/attack", lvl);
        me->set_temp("wd_hkbd",1);
        COMBAT_D->do_attack(me, target, 0, 1);  

        if (present(target,environment(me)) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, 0);  

        if(me->query_skill("zhenshan-mianzhang", 1) > 150
        && present(target,environment(me))
        && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, 0);  

        me->start_busy(2);
        me->add_temp("apply/strike", -lvl);
        me->add_temp("apply/attack", -lvl);

        me->start_perform(5,"花开并蒂");
        lvl /= 2;
        if ( lvl < 4 ) lvl = 4;
        if ( lvl > 10 ) lvl = 10;
        call_out("remove_effect", lvl, me);
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("wd_hkbd");
        tell_object(me, GRN"\n你经过一段时间调气养息，又可以使用「花开并蒂」了。\n"NOR); 
}
