// shenyuan.c yun shenyuan 可以在战斗中增加相当的防御

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
	int skill;

	if (!me->is_fighting())
		return notify_fail("你只能在战斗中使用神元功。\n");

	skill = me->query_skill("force") + random(50);
	
	if( (int)me->query_skill("shenyuan-gong",1) < 60 )
		return notify_fail("你目前尚不能使用神元功。\n");

	if( (int)me->query("neili") < skill  )
		return notify_fail("你的内力不够。\n");
 
	if( (int)me->query_temp("shenyuan") ) 
		return notify_fail("你已经在运用神元功了。\n");

	me->add("neili", -1 * skill);
	me->add_temp("apply/parry", skill/3);
	me->add_temp("apply/dexerity", skill/5);

	message_vision(HIY "$N运起慕容绝学神元功，似乎熟知武功路数，攻守上轻松多了。\n" NOR, me);

	me->set_temp("shenyuan", 1);
	call_out("remove_effect", 1, me, skill);

	me->start_exert(1, "神元功");
	me->start_busy(random(2)+1);

	return 1;
}

void remove_effect(object me, int skill)
{
	if (objectp(me)) {
	  if (me->is_fighting()){
	      call_out("remove_effect", 1, me, skill);
//	    me->start_exert(1, "神元功"); 
	      return;
	  }
	  me->delete_temp("shenyuan");
	  me->add_temp("apply/parry", -1 * skill/3);
	  me->add_temp("apply/dexerity", -1 * skill/5);
//	tell_object(me, "对手逐渐适应了你的防守招式，渐渐加强了攻势。\n");
	}
	return;
}
