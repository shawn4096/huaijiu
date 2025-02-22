// diqing.c 狄青降龙
// created by Olives@SJ

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

void back(object target);

int perform(object me, object target)
{
        int skill,ap,pp,time;
        object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用。\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「狄青降龙」只有拜了教主后才能用！\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 120 )
                return notify_fail("你的腾龙匕法不够娴熟，不会使用狄青降龙。\n");

    	if( (int)me->query("neili", 1) < 800 )
       		return notify_fail("你现在内力不足！\n");
       	if( (int)me->query("jingli", 1) < 500 )
       		return notify_fail("你现在精力不足！\n");

    	if( (int)me->query("max_neili", 1) < 1500 )
       		return notify_fail("你内力修为不足！\n");
        if( (int)me->query_dex() < 30  )
                return notify_fail("你的身法太低，不能使用狄青降龙。\n");

        if (!weapon
        || me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("你现在无法使用狄青降龙。\n");

        if(target->query_temp("sld/pfm/diqing")
        || target->query_temp("block_msg/all"))
                return notify_fail("他的眼睛已经瞎了，不必再用狄青降龙了！\n");
         if(me->query("gender")!="男性")
             return notify_fail("你不是男子，如何使用狄青降龙？\n");
        skill = (int)me->query_skill("tenglong-bifa", 1);

	ap = COMBAT_D->skill_power(me,"dagger",SKILL_USAGE_ATTACK);
        pp = COMBAT_D->skill_power(me,"parry",SKILL_USAGE_ATTACK);
        if(target->is_busy())
        	pp /= 2;

        me->add("neili", -350);
        me->add("jingli", -200);
        message_vision(HIY "\n$N使出一招「狄青降龙」，背脊后撞，十指向$n胸口虚抓，乘其避让之际，突然一个倒翻斛斗，身子跃起，双腿一分，跨坐在$n肩头，同时双手拇指压住$n太阳穴，食指按眉，中指按眼。\n"NOR,me,target);

        message_vision(HIY"$n一惊，忙双臂回转，想护住双眼！\n"NOR, me, target);;

  	if(random(ap+pp)>pp)
         {
                message_vision(HIR"\n只听$n惨叫一声，$N的两支手指已经插入$n的眼眶，只见$n的眼角鲜血直流！\n"NOR, me, target);
                target->set_temp("sld/pfm/diqing", skill);
                target->add_temp("apply/attack", - skill/3);
                target->add_temp("apply/defense", -skill/3);
                target->receive_damage("qi", skill*5);
                target->receive_wound("qi", skill*5/2);
                COMBAT_D->report_status(target);
                target->kill_ob(me);
                target->set_temp("block_msg/all",1);
                me->start_perform(10,"狄青降龙");
                time = 3+skill/10;
                if(time>60) time = 60;
                call_out("back", time, target);
                }

  	else {
                message_vision(HIY"$n抱头缩颈一个滚翻，总算躲开了$N这一招。\n"NOR, me, target);
                me->start_perform(2+random(3),"狄青降龙");
                me->start_busy(3);
                target->kill_ob(me);
        }

        return 1;
}

void back(object target)
{
        int lvl;
        if(!target) return;
        lvl = target->query_temp("sld/pfm/diqing");
        target->add_temp("apply/attack", lvl/3);
        target->add_temp("apply/defense", lvl/3);
        target->set_temp("block_msg/all", 0);
        if(living(target))
              tell_object(target, HIW "啊！总算双目没有被抓瞎，你又可以看见事物啦！\n" NOR);
        target->delete_temp("sld/pfm/diqing");
}
