
// pfm luda
// 断别人兵器 & 化学效果
// create by olives@SJ
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>
int perform(object me, object target)
{
        int skill,ap,pp,damage,effect,p;
        object weapon = me->query_temp("weapon");
	object vweapon;
	string msg,dodge_skill;
        if( !target ) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用。\n");

	vweapon = target->query_temp("weapon");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「鲁达拔柳」只有拜了教主后才能用！\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 120 )
                return notify_fail("你的腾龙匕法不够娴熟，不会使用鲁达拔柳。\n");

    	if( (int)me->query("neili", 1) < 3000 )
       		return notify_fail("你现在内力不足！\n");
       	if( (int)me->query("jingli", 1) < 500 )
       		return notify_fail("你现在精力不足！\n");

    	if( (int)me->query("max_neili", 1) < 1500 )
       		return notify_fail("你内力修为不足！\n");
        if( (int)me->query_str() < 30  )
                return notify_fail("你的膂力太低，不能使用鲁达拔柳。\n");

        if(!weapon
        || me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("你现在无法使用鲁达拔柳。\n");
        if(weapon->query("sharpness")<3)
        	return notify_fail("你手中匕首不够锋利，无法使用鲁达拔柳！\n");

        skill = (int)me->query_skill("tenglong-bifa", 1);
	ap = me->query("combat_exp")/100*me->query_str();
        pp = target->query("combat_exp")/100*target->query_dex();
         if(me->query("gender") == "女性")
             return notify_fail("你是女子，如何使用鲁达拔柳？\n");

	
        me->add("neili", -350);
        me->add("jingli", -200);
        if(objectp(vweapon))
        {
		ap *= weapon->query("sharpness");
	        pp *= vweapon->query("rigidity");

 		message_vision(HIY"\n$N双腿一缩，似欲跪拜，右臂却横掠而出，急削向$n手中"+vweapon->name()+NOR,me,target);
  		if(random(ap+pp)>pp)
  		{

  			message_vision(HIY"\n结果$n手中"+vweapon->name()+HIY"应手而断！"NOR,me,target);
                	vweapon->unequip();
                	vweapon->move(environment(target));
                	vweapon->set("name", "断掉的" + vweapon->name());
                	vweapon->set("value", 49);
                	vweapon->set("weapon_prop", 0);
                	target->reset_action();
		}
	}
	msg = HIY"\n$N突然一个前滚翻，似欲向$n胯下钻过，但只一作势，左手抓向$n右脚足踝，右手兵器点向$n小腹！\n"NOR;
	ap = (int)me->query_skill("dulong-dafa",1) * (int)me->query("neili") * (int)me->query_str();
        pp = (int)target->query_skill("force", 1) * (int)target->query("neili") * (int)target->query_dex();
        ap *= (int)me->query("combat_exp")/200;
        pp *= (int)target->query("combat_exp")/200;
        ap /= 1000;
        pp /= 1000;
	if(!living(target)) pp = 1;
        me->start_busy(1);
        me->start_perform(6, "「鲁达拔柳」");
        if(random(ap+pp) > pp){
                target->start_busy(random(2));
                damage =  me->query_skill("force");
                damage += me->query("jiali") * 5;
                damage -= target->query_temp("apply/armor") * 2;
                effect = SKILL_D("dulong-dafa")->force_effect(target->query_skill_mapped("force"));
                damage *= (5-effect);
                if (damage < 0) damage = 0;
                damage = damage + random(damage / 2);
                if (damage > 2500) damage = 2500 + (damage-2500)/100;
                if(wizardp(me))
			tell_object(me,sprintf("damage = %O\n",damage));

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", random(damage), me);
                target->receive_damage("neili", damage/4);
                me->receive_damage("neili", damage/5);
                if(damage >= 2500)
                        msg += HIY"这一招乃是使上了全力，丝毫不留余地，$n的生死存亡，便决于这顷刻之间！\n"NOR;
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += damage_msg(damage, "刺伤");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg = replace_string( msg, "$l", "小腹");
                msg = replace_string( msg, "$w", weapon->name());

        }
        else {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        me->add("neili", -400);
        me->add("jingli", -100);
        message_vision(msg, me, target);
        return 1;
}
  	
