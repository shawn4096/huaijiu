// beauty 飞燕回翔
// 19991002001

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>


int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int dex,urdex,damage;

        if(!target) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("「飞燕回翔」只能在战斗时使用！\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「飞燕回翔」只有拜了教主后才能用！\n");

        if(!objectp(weapon=me->query_temp("weapon"))
        || weapon->query("skill_type") != "dagger")
             return notify_fail("你手上没有匕首，如何使用「飞燕回翔」。\n");

        if( (int)(dex=me->query("dex")+me->query_skill("dodge",1)/10) < 30 )
                return notify_fail("你身法不够，使用「飞燕回翔」，恐怕会伤到自己！\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 150 )
                return notify_fail("你的腾龙匕法还不够熟练，不能使用「飞燕回翔」！\n");

        if (me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("只有使用腾龙匕法时才能使用「飞燕回翔」！\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 150 )
                return notify_fail("你的毒龙大法功力不足，不能用「飞燕回翔」。\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用「飞燕回翔」！\n");

        if((int)me->query("neili", 1) < 1500)
                return notify_fail("你现在内力不足，不能使用「飞燕回翔」！\n");

        if(me->query("gender") == "男性" )
                return notify_fail("不是女人怎么能使用「飞燕回翔」呢！\n");

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你现在所使用的内功同毒龙大法相互抵触，不能使用「飞燕回翔」。\n");

        damage = 4 * (int)me->query_skill("tenglong-bifa", 1);
        damage = damage / 2 + random(damage / 2) + 5*me->query("jiali");
        damage *=2;
        if(damage >4000) damage = 4000+random(damage-4000)/5;
	if(wizardp(me))
		tell_object(me,sprintf("damage = %O\n",damage));
        msg = HIR"$N乘$n稍稍走神之机，拼尽全力使出苏夫人不传之绝技－－「飞燕回翔」"NOR;
        msg +=MAG "\n$N使出一招「飞燕回翔」，右足顺势一勾，在兵器上一点，兵器陡地向$N咽喉射了过去。\n"NOR;
	me->receive_damage("jingli",200+random(100));
	me->receive_damage("neili",400+random(200));
	if(userp(target) && userp(me) && !random(dex))
		{
			msg+= MAG"\n$N一个不留神，竟然没有躲过插向自己咽喉的匕首，只见匕首正中$N咽喉。\n";
			message_vision(msg,me);
			me->set("eff_qi",-1);
			COMBAT_D->report_status(me,1);
			return 1;
		}
	urdex = target->query("dex")+target->query_skill("dodge",1)/10;
        if(random(dex+urdex)>urdex  )
        {
 		msg += MAG"$N身子向下一缩，那兵器急射$n"NOR;
 		if(random(me->query("kar")+me->query("pur")+me->query("per"))>target->query("kar")+target->query("pur")+target->query("per"))
 		{
 			target->set("eff_qi",-1);
 			msg += MAG"咽喉，$n躲闪不及，结果被一下扎中咽喉，$n咽喉中发出几声痛苦的呻吟，两眼翻白就倒在地上。\n"NOR;
                	message_vision(msg,me,target);
 			COMBAT_D->report_status(target,1);
 			me->start_busy(3+random(3));
 			me->start_perform(3+random(4),"「飞燕回翔」");
 			return 1;
 		}
 		else
 		{
                	target->receive_damage("qi",damage,me);
                	target->receive_wound("qi",damage/2-target->query_temp("apply/armor"),me);
                	msg += MAG"胸口，$n躲闪不及，结果正中胸口。\n"NOR;
                	result = damage_msg(damage,"刺伤");
	                result = replace_string( result, "$l", "胸口" );
	                result = replace_string( result, "$w", weapon->name() );
        	        msg += result;
	               	message_vision(msg,me,target);
                	COMBAT_D->report_status(target,1);
                	me->start_busy(1);
                	me->start_perform(2+random(3),"「飞燕回翔」");
                	return 1;
                }
        }
        else {
                msg += "\n$n被$N制住，但临危不乱，以内力护住要害，同时高高跃起，翻身以头撞地，把$N撞了出去！\n";
                message_vision(msg,me,target);
                me->start_busy(2);
                me->start_perform(1+random(3),"「飞燕回翔」");
        }
        return 1;
}

