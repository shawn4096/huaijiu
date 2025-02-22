// zixu.c 子胥举鼎
// created by Olives@SJ
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
void remove_effect(object target, int skill);
void check_fight(object me, object target, int improve);

int perform(object me, object target)
{
        int skill,ap,pp;
        object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用。\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「子胥举鼎」只有拜了教主后才能用！\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 120 )
                return notify_fail("你的腾龙匕法不够娴熟，不会使用子胥举鼎。\n");

    	if( (int)me->query("neili", 1) < 800 )
       		return notify_fail("你现在内力不足！\n");
       	if( (int)me->query("jingli", 1) < 500 )
       		return notify_fail("你现在精力不足！\n");

    	if( (int)me->query("max_neili", 1) < 1500 )
       		return notify_fail("你内力修为不足！\n");
        if( (int)me->query_dex() < 30  )
                return notify_fail("你的身法太低，不能使用子胥举鼎。\n");
       if(target->query_temp("sld/pfm/zixu"))
              return notify_fail("你已经对"+target->name()+"使用“子胥举鼎”了！\n");

        if(!weapon
        || me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("你现在无法使用子胥举鼎。\n");
         if(me->query("gender")!="男性")
             return notify_fail("你不是男子，如何使用子胥举鼎？\n");


        skill = (int)me->query_skill("tenglong-bifa", 1);
	skill /=30;
	if(skill>7) skill = 7;
	ap = me->query("combat_exp");
        pp = target->query("combat_exp");

        me->add("neili", -350);
        me->add("jingli", -200);
  	message_vision(HIY"\n只见$N左手猛然反转，在$n左腋底搔了一把。$n格格一笑，身子软了下来。$N左手已拿住$n腋下，右手回转，抓住$n领口，举起$n身子，过了自己头顶，猛然往外摔出。\n"NOR,me,target);
	
  	if(random(ap)>pp/2)
  	{
  		message_vision("\n就在那电光火石之间，$N已经封住了$n肘后的“小海穴”和腋下“极泉穴”。$n被摔在地上，已是动弹不得。\n",me,target);
                  target->start_lost(random(skill/30)+1);
                  target->add_temp("sld/pfm/zixu",target->query_dex()/2);
		target->add_temp("apply/dexerity",-target->query_dex()/2);
		target->set_temp("sld/pfm/zixu",1);
		me->start_perform(5,"「子胥举鼎」");

	        target->start_call_out( (: call_other, __FILE__, "check_fight",  me, target, skill/5 :), 1);
		return 1;
  	}
  	else
  	{
  		message_vision("\n只见$N手指连颤，急点$n肘后的“小海穴”和腋下“极泉穴”，$n急忙闭气移穴，躲过了这几下点穴，身子刚一着地，便趟了出去，如在水面滑溜漂行。\n",me,target);
  		me->start_perform(3+random(2),"「子胥举鼎」");
  		return 1;
  	}
	return 1;
}

void check_fight(object me, object target, int improve)
{
       object weapon;

       if(!target) return;
       if(!me) {
          remove_effect(target,improve);
          return;
       }
       else
       if(!me->is_fighting(target) && target->query_temp("sld/pfm/zixu")){
          remove_effect(target, improve);
          return;
       }
       else if( (target->query_temp("qianshou"))
        && (!target->is_fighting()
        || !me->is_fighting()
        || !living(me)
        || target->is_ghost()
        || me->is_ghost()
        || !improve ))
        {
               remove_effect(target, improve);
               return;
        }
          else if(target->query_temp("sld/pfm/zixu"))
        {
        	weapon = me->query_temp("weapon");
        	if(!objectp(weapon)
        	|| weapon->query("skill_type")!= "dagger")
        	{
                	remove_effect(target, improve);
                	return;
                }
        }
        else{
            call_out("check_fight", 1, me, target, --improve);
            return;
        }
}

void remove_effect(object target, int skill)
{

          target->add_temp("apply/dexerity",target->query_temp("sld/pfm/zixu"));
        tell_object(target, HIB"你渐渐适应了这种变化，状态又恢复如常。\n"NOR);
}
