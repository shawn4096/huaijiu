//shigu.c 石鼓文
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
      string msg; 
      int i, damage,p;                                  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("你手里没有笔，无法写出石鼓文！\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("石鼓文只能在战斗中对对手使用。\n");
             
      if((int)me->query_skill("yingou-bifa",1) < 150 )
         return notify_fail("你的银钩笔法还不够娴熟，不会写石鼓文！\n");
      
      if((int)me->query_skill("literate",1) < 140 )
         return notify_fail("你的读书写字等级不够，不能写出石鼓文！\n");  

      if((int)me->query_skill("guiyuan-tunafa",1) < 160 )
         return notify_fail("你的归元吐纳法等级不够，不能写出石鼓文！\n");
      
      if((int)me->query("max_neili") < 2000 )
         return notify_fail("你的内力太弱，无法写出强劲有力的石鼓文! \n");
      
      if((int)me->query("neili") < 800 )
         return notify_fail("你的内力太少了，写出的石鼓文无刚阳之气！\n");       

      if((int)me->query("jingli") < 500 )
         return notify_fail("你的精力太少了，写出的石鼓文无刚阳之气！\n");       
         
      if(me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("你现在无法写出「石鼓文」！\n");

      i = random((int)(me->query_skill("yingou-bifa",1)/15));
      if(i < 1) i=1;
      if(i > 15) i=15;                                                                                 

      msg = HIY"$N忽然间笔法又变，运笔不似写字，却如拿了斧头在石头上凿打一般。这一路笔法是石鼓文，\n"+
               "那是春秋之际用斧凿刻在石鼓上的文字，此乃最古的大篆字。$n对这一路古篆果然只识得一两\n"+
               "个字，既不知对方书写何字，自然猜不到书法间架和笔画走势，登时难以招架。\n" NOR;

      me->add("neili", - 450);
      me->add("jingli", -100);

      if((random(me->query_skill("literate")) > target->query_skill("literate")/6)
       &&(random(me->query_skill("force")) > target->query_skill("force")/3)){
           me->start_busy(1);
           target->start_busy(3);
           damage = (int)me->query_skill("yingou-bifa", 1);
           damage = damage/2 + random(damage);
           damage = damage * i * 2 / 3;
           if (damage > 2400 ) damage = 2400;
           target->receive_damage("qi", damage);
           target->receive_wound("qi", damage/2);
           msg += MAG"$N一个字一个字篆将出来，文字固然古奥，而作为书法之基的银钩笔法也相应加强劲力。\n"+
                     "$N振笔挥舞，在空中连书三个古字，$n还想得到去认甚麽字，膝上穴道一麻，强吸一口气\n"+
                     "向膝间穴道冲去，$N笔来如电，跟著又是一点连环进招，$n不由自主地瘫倒在地上。\n"NOR;
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           msg += "( $n"+eff_status_msg(p)+" )\n";
       }
       else{
           msg += CYN"$P一字快过一字，笔锋掠过$p的身边，只觉得冷飕飕的，$p已无力去认$P所\n"+
                     "写何字，只得护住面门和身上各大要穴，突然臂上一麻，强吸一口气去冲穴道，\n"+
                     "总算勉力冲穴成功，但是手臂已酸麻无力，勉强能招架。\n"NOR;
           if( random(me->query("combat_exp", 1)) > target->query("combat_exp", 1)/ 2
            && me->is_fighting(target)
            && present(target,environment(me))){
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
              if (present(target,environment(me)) && me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
           }
           me->start_busy(2);
           if ( target->query("neili") > 400 ) target->add("neili",- random(200));
       }
       message_vision(msg, me, target);
       me->start_perform(6,"「石鼓文」");
       return 1;
}
