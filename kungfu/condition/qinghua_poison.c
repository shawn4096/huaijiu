// qinghua_poison.c 情花毒
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
if(me->query("class")!="bonze"){
      tell_object(me, HIM"你的手指上刺损处突然剧痛，伤口微细，痛楚竟然厉害之极。\n"NOR);
      tell_room(environment(me), MAG + me->name()+"宛如胸口蓦地给人用大铁锤猛击一下，忍不住「啊」的一声叫了出来，\n" NOR,({ me }));
      me->receive_damage("qi", 15);
      me->receive_wound("jing", 15);
	me->add_busy(1+random(2));
      me->set_temp("last_damage_from", "中情花毒");
      me->apply_condition("qinghua_poison", duration - 1);
}
else me->apply_condition("qinghua_poison", duration - 1);
      if( duration < 1 ) return 0;
      return CND_CONTINUE;
}

