// guifei 贵妃回眸
// created by olives@SJ
/*
     洪夫人身子微曲，纤腰轻扭，右足反踢，向教主小腹踹去。教主后缩相避，
洪夫人顺势反过身来，左手搂住教主的头颈，右手竟已握住了匕首，剑尖对准了
教主后心，笑道：“这是第一招，叫做‘贵妃回眸’，你记住了。”

*/
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me, object target)
{
        object weapon;
        string msg;
  
        if(!target) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("「贵妃回眸」只能在战斗时使用！\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「贵妃回眸」只有拜了教主后才能用！\n");

        if(!objectp(weapon=me->query_temp("weapon"))
        || weapon->query("skill_type") != "dagger")
             return notify_fail("你手上没有匕首，如何使用「贵妃回眸」。\n");
	
        if((int)(me->query("dex")+me->query_skill("dodge",1)/10) < 30 )
                return notify_fail("你身法不够，使用「贵妃回眸」，恐怕会伤到自己！\n");

        if((int)me->query_skill("tenglong-bifa", 1) < 150 )
                return notify_fail("你的腾龙匕法还不够熟练，不能使用「贵妃回眸」！\n");
	if((int)me->query_skill("shenlong-tuifa",1) < 150)
		return notify_fail("你的神龙腿法不够熟练，不能使用「贵妃回眸」！\n");
	
        if(me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("只有使用腾龙匕法时才能使用「贵妃回眸」！\n");

	if(me->query_skill_mapped("leg") != "shenlong-tuifa"
	|| me->query_skill_prepared("leg") != "shenlong-tuifa")
		return notify_fail("你现在没有做好准备，无法使用「贵妃回眸」！\n");
		
        if( (int)me->query_skill("dulong-dafa", 1) < 150 )
                return notify_fail("你的毒龙大法功力不足，不能用「贵妃回眸」。\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用「贵妃回眸」！\n");

        if((int)me->query("neili", 1) < 1500)
                return notify_fail("你现在内力不足，不能使用「贵妃回眸」！\n");

        if(me->query("gender") == "男性" )
                return notify_fail("不是女人怎么能使用「贵妃回眸」呢！\n");

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你现在所使用的内功同毒龙大法相互抵触，不能使用「贵妃回眸」。\n");

        
        msg = HIR"$N乘$n稍稍走神之机，拼尽全力使出苏夫人不传之绝技－－「贵妃回眸」"NOR;
        msg += MAG"\n$N身子微曲，纤腰轻扭，右足反踢，向$n小腹踹去。\n"NOR;
  	me->receive_damage("neili",500);
  	me->receive_damage("jingli",200);
        message_vision(msg,me,target);
        me->set_temp("sld/pfm/guifei",1);
        weapon->unequip();
        COMBAT_D->do_attack(me,target,0,TYPE_SUPER);
        weapon->wield();
        me->delete_temp("sld/pfm/guifei");
        me->start_busy(2+random(2));
        me->start_perform(2+random(2),"「贵妃回眸」");
	return 1;
}

