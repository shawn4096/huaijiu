// wofo.c yizhi-chan perform 皈依我佛

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	string msg;
	int exp,exp1,busy,lvl,lvl1;

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
	  return notify_fail("「皈依我佛」只能在战斗中对对手使用。\n");
	     
      if( objectp(me->query_temp("weapon")) )
	  return notify_fail("你必须空手使用「皈依我佛」！\n");
      
      if( (int)me->query_skill("yizhi-chan",1) < 100 )
	  return notify_fail("你的一指禅不够娴熟，不会使用「皈依我佛」！\n");

      if( (int)me->query_skill("yijin-jing",1) < 100 )
	  return notify_fail("你的易筋经内功等级不够，不能使用「皈依我佛」！\n");  
      
      if( (int)me->query_str() < 25 )
	  return notify_fail("你的臂力不够强，不能使用「皈依我佛」！\n");
      
      if( (int)me->query("max_neili") < 1000 )
	  return notify_fail("你的内力太弱，不能使用「皈依我佛」！\n");
      
      if( (int)me->query("neili") < 350 )
	  return notify_fail("你的内力太少了，无法使用出「皈依我佛」！\n");   
										 
      if (me->query_skill_prepared("finger") != "yizhi-chan"
       || me->query_skill_mapped("finger") != "yizhi-chan")
	  return notify_fail("你现在无法使用「皈依我佛」进行攻击。\n");										 
      if( me->query_temp("wofo"))
	  return notify_fail("你正在使用一指禅的特殊攻击「皈依我佛」！\n");

	if (target->is_busy()) return notify_fail("对方正自顾不暇，放胆攻击吧！\n");
       
      msg = HIY"$N突然身行纵向半空，右手屈指弹出，嗤的一声，一股劲气激射而出，罩向$n周身大穴。\n" NOR;
      message_vision(msg, me, target);   
//      me->start_perform(6,"「皈依我佛」");								
	exp=me->query("combat_exp");
	exp1=target->query("combat_exp");
	lvl=me->query_skill("finger");
	lvl1=target->query_skill("dodge");
	busy=3;
	busy=busy+random(lvl)/100;
	if(busy>4) busy=4;
	if(exp1==0 || lvl1==0) busy=10;
	else if( exp>exp1) busy=busy*exp/100*lvl/(exp1/100*lvl1);
	if(busy>6) busy=6;
	if( wizardp(me)) tell_object(me,sprintf("busy=%d\n",busy));
	if( random(exp/100*lvl)>exp1/100*lvl1/3){
		msg = HIW"$n只感到穴道一麻，浑身劲气立散，动弹不得。\n"NOR;
		message_vision(msg, me, target); 
		me->set_temp("wofo",1);  
		me->add("neili", -350);    
		target->start_busy(busy);
		me->start_busy(1+random(2));
		call_out("remove_effect", me->query_skill("yizhi-chan") / 20 + 2, me);
      }
      else {
		msg = HIY"$n看出$N的企图，一闪身，敏捷地躲过了$N的这一招！\n"NOR;	  
		message_vision(msg, me, target);					
		me->start_busy(2+random(3));
		me->add("neili", - 100);
      }
      return 1;
}

void remove_effect(object me)
{
	if (!me) return;
	me->delete_temp("wofo");
	message_vision(HIR"$N的「皈依我佛」运功完毕，脸色好看多了。\n"NOR, me);
}
