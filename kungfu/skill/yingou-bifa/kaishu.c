//kaishu.c 楷书
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      string msg; 
      int i;                                  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("你手里没有笔，无法写出楷书！\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("楷书只能在战斗中对对手使用。\n");
             
      if((int)me->query_skill("yingou-bifa",1) < 80 )
         return notify_fail("你的银钩笔法还不够娴熟，不会写出楷书！\n");
      
      if((int)me->query_skill("literate",1) < 80 )
         return notify_fail("你的读书写字等级不够，不能写出房玄龄碑文！\n");

      if((int)me->query_skill("guiyuan-tunafa",1) < 100)
         return notify_fail("你的归元吐纳法等级不够，不能写出房玄龄碑文！\n");  
      
      if((int)me->query("max_neili") < 1000 )
         return notify_fail("你的内力太弱，写不出刚劲有力的楷书! \n");
      
      if((int)me->query("neili") < 300 )
         return notify_fail("你的内力太少了，写出的楷书柔弱无力！\n"); 

      if( target->is_busy() )
         return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

      if (me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("你现在无法写出「楷书」！\n");

      i = random((int)(me->query_skill("yingou-bifa",1)/20));
      if(i < 1) i=1;
      if(i > 10) i=10;                                                                                 
      msg = HIC"$N一转身，手中笔摇幌，凌空写起「房玄龄碑」碑文，书法之中有点穴，点穴之中有书法，\n"+
               "当真是银钩铁划，劲峭凌厉，而雄伟中又蕴有一股秀逸的书卷气，招招法度严谨，宛如楷书\n"+
               "般的一笔不苟！\n" NOR;
      me->add("neili", - 200);
      if((random(me->query_skill("literate", 1)) > target->query_skill("literate", 1)/5)
       && (random(me->query_skill("force")) > target->query_skill("force")/3)){
            me->start_busy(1);
            target->start_busy(i+2);
            msg += HIR"$n对书法只是入门，哪懂得碑文的意境，只见$N手中的笔满天在自己身上各大要穴附近\n"+
                      "飞舞，只得勉力护住面门胸口要害，突感膝头一麻，原来已被$N倒转笔口，点中了穴道。\n"NOR;
      }
      else {
            me->start_busy(2);
            msg += HIY"哪知$p曾临写过「房玄龄碑」，预计得到$P那一横之後会跟著写那一直，倒也守得井井有条，\n"+
                      "丝毫不见败象。\n"NOR;
//          if (!(target->query("neili")<0)) target->add("neili",- 100);
      }
      message_vision(msg, me, target);
      me->start_perform(3,"「楷书」");
      return 1;
}
