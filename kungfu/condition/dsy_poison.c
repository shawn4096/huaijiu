// dsy_poison.c

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{
   if( !living(me) ) {
      message("vision", HIG+me->name() + "眉眼歪斜，舌头不由自主地吐了出来，一串串黑泡沫顺着舌尖往下淌。\n"NOR, environment(me), me);
   }

      if(me->query("eff_jing") > me->query("max_jing")/2) {
      tell_object(me, CYN "你感觉中掌之处犹如火灼，全身乏力，犹如散架。\n" NOR );
      }
      else if(me->query("eff_jing") > me->query("max_jing")/4) {
      tell_object(me, CYN "你中掌之处开始溃烂发臭，招来了几只苍蝇，四肢渐渐肿了起来。\n" NOR );
      }
      else {
      tell_object(me, CYN "掌毒已经侵入五脏六腑，你神智逐渐迷失，感到对这个世界无限地留恋。。。\n" NOR );
      message("vision", HIG+me->name() + "突然象烂泥似地瘫倒在地，全身流脓，发出一阵阵的恶臭，头发一束束地脱落，随风飘散。\n"NOR,
            environment(me), me);
      }

        me->receive_damage("qi", 20, "毒发全身而死");
        me->apply_condition("dsy_poison", duration - 1);
        me->receive_wound("jing", 25, "毒发全身而死");

     if( duration < 1) return 0;
   return CND_CONTINUE;
}
