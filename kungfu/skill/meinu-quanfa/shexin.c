// shexin.c 摄心

#include <ansi.h>

inherit F_SSERVER;

void affectob(object ,object ,int ,int ,int);
void dohit(object,object);

int perform(object me, object target)
{
	int affect,skill,hits;
	string msg;
	
	if(!me->is_fighting())
		return notify_fail("你没在战斗中呢！\n");

	if(!target) target = offensive_target(me);

	if( (skill=(int)me->query_skill("meinu-quanfa", 1)) < 150 )
		return notify_fail("你的美女拳法还不够纯熟，无法施展「摄心」绝技。\n");

	if(me->query_skill_mapped("parry") != "meinu-quanfa")
		return notify_fail("你没有使用美女拳法作为招架！\n");
	
	if ( me->query_temp("weapon"))
		return notify_fail("你手持武器，如何使用「摄心」绝技？\n");

	if(me->query("gender")=="无性")
		return notify_fail("面对无性对手，你如何施展「摄心」绝技？\n");
		
	if(target->query("gender")==me->query("gender"))
		return notify_fail("面对同性对手，你如何施展「摄心」绝技。\n");

	if(me->query("max_neili")<1200)
		return notify_fail("你内力不够，无法使用「摄心」绝技。\n");

	affect=me->query_per()+random(me->query("per")/2);

	if (me->query("gender")=="男性") affect=affect / 2;

	if (   target->query_skill("buddhism") > (skill+random(affect/2))  //判断monk
	    || target->query_skill("dacheng-fofa") > (skill+random(affect/2))
	    || target->query_skill("taoism") > (skill+random(affect/2)) )
	{
		msg = HIY"\n$N对$n轻轻一笑，眼光之中流露出妩媚之意，想施展「摄心」绝技。\n"+
			HIW"不料$n定了定神，突然大喝一声，顿时把$N惊出一身冷汗。\n"NOR;
		message_vision(msg,me,target);
		me->start_busy(4);
	}
	else if (target->query_per()>=me->query_per())
	{
		msg = HIY"\n$N忽然对$n轻轻一笑，眼光四处流动，所经过之处似乎充满了妩媚。\n"NOR; 
		message_vision(msg, me, target);
		message_vision(HIW"但是$N沮丧地发觉，$n比自己漂亮，「摄心」绝技无法施展。\n"NOR,me,target);
		me->start_busy(2);
	}
	  else if (random(10)>5)
	{
		msg = HIY"\n$N忽然对$n轻轻一笑，眼光四处流动，所经过之处似乎充满了妩媚，$n不由得一呆。\n"NOR; 
      
		message_vision(msg, me, target);

		if ( random(skill) > target->query_skill("force",1)/2 )
		{
			target->add_temp("apply/dexerity", -affect);
			hits = skill / 10;
			me->start_perform(4,"摄心");
			target->apply_condition("no_perform", 3);
			target->set_temp("shexin", 1);
			me->start_busy(1);
			target->start_busy(1);
			me->add("jingli",-100);
			me->add("neili",-300);
			dohit(me,target);
			dohit(me,target);
			call_out("affectob",random(2)+2, me, target, affect, hits,3);
		}
		else 
		{
			message_vision(CYN"\n但见$n大喝一声，想用雄浑的内力打破$N四周这妩媚的气氛！\n"+
					"结果$n只发出两、三招，就无法忍受$N妩媚的眼光了。\n"NOR, me, target);
			me->start_busy(1);
			target->start_busy(1);
			me->add("neili",-100);
			target->add_temp("apply/dexerity", -affect);
			dohit(me,target);
			dohit(me,target);
			if (skill >= 200) dohit(me,target);
			target->add_temp("apply/dexerity", affect);
			me->start_perform(4,"摄心");
		}
	}
	else
	{
		msg = HIY"\n$N忽然对$n轻轻一笑，想施展「摄心」绝技。\n"+
			HIM"谁知$n根本就没有上当。\n"NOR; 
		message_vision(msg, me, target);
		me->start_perform(5,"摄心");
	}       
	return 1;
}

void affectob(object me,object target,int affect,int hits,int now)
{
	if( !me 
		|| !target 
		|| ( now > hits) 
		|| objectp(me->query_temp("weapon")) 
		|| target->is_ghost() 
		|| me->is_ghost()  
		|| !me->is_fighting(target) 
		|| me->query("neili") < 800 
		|| me->query_skill_prepared("cuff")!="meinu-quanfa"
		|| me->query_skill_prepared("parry")!="meinu-quanfa")
	{
		if( me ) message_vision(HIC"\n$N内力突然一顿，眼光又恢复平静。\n"NOR, me);
		if( target && target->query_temp("shexin"))
			target->delete_temp("shexin");
		if ( target )  target->add_temp("apply/dexerity", affect);
			return;
	}

	if( now > (hits/2) && target->query_temp("shexin"))
		target->delete_temp("bujue_busy");

	dohit(me,target);
	dohit(me,target);
	me->start_perform(3,"摄心");
	call_out("affectob",random(2)+2,me,target,affect,hits,now+1);
}

void dohit(object me,object target) 
{
	int neili,jiali;
	neili = me->query("neili");
	jiali = me->query("jiali");
	COMBAT_D->do_attack(me, target,0, 1);
	if (me->query("neili")<neili && jiali>0) me->set("neili",neili-jiali/3);
}
