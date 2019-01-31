// shenzhao.c yun shenzhao 可以在战斗中增加相当的防御

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
	int skill;

	if (!me->is_fighting())
		return notify_fail("你只能在战斗中使用神照经。\n");

	skill = me->query_skill("force") + random(50);
	
	if( (int)me->query_skill("shenzhao-jing",1) < 120 )
		return notify_fail("你目前尚不能使用神照经。\n");

	if( (int)me->query("neili") < skill  )
		return notify_fail("你的内力不够。\n");
 
	if( (int)me->query_temp("shenzhao") ) 
		return notify_fail("你已经在运用神照经了。\n");

	me->add("neili", -1 * skill);
	me->add_temp("apply/parry", skill/4);
	me->add_temp("apply/dodge", skill/4);
        if(me->query("szj2")) 	me->add_temp("apply/attack", skill/5);

	message_vision(HIW"\n$N深吸一口气，内息缓缓而动，劲力随着增加，顿时感觉精神力气勃然而兴，沛然而至！\n\n" NOR, me);

	me->set_temp("shenzhao", 1);
	call_out("remove_effect", 1, me, skill);

	me->start_exert(1, "神照经");
	me->start_busy(1);

	return 1;
}

void remove_effect(object me, int skill)
{
	if (objectp(me)) {
	  if (me->is_fighting()){
	      call_out("remove_effect", 1, me, skill);
	      return;
	  }
	  me->delete_temp("shenzhao");
	  me->add_temp("apply/parry", -1 * skill/4);
	  me->add_temp("apply/dodge", -1 * skill/4);
          if(me->query("szj2")) 	me->add_temp("apply/attack", -1 * skill/5);
	}
	return;
}


int help(object me)
{
        write(WHT"\n神照经「神照」："NOR"\n");
        write(@HELP
        这是铁骨墨萼梅念笙老先生曾经教丁典的一套内功的秘经
        丁典习得此内功，后又传授狄云，狄云苦心多年，神照经
        已习得第二境界。巧遇机缘得到狄云指点，可更上一层楼
        
        要求:   等级 120 以上；
        效果:   效果一增加防御、躲避。
                效果二增加攻击效果。
        
HELP
        );
        return 1;
}