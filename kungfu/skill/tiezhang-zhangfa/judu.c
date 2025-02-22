// tianlei.c 铁掌--聚毒

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

string perform_name(){ return HBBLU"聚    毒"NOR; }
int perform(object me, object target)
{
        int damage,p;
        string msg,dodge_skill;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
              return notify_fail("「聚毒」只能对战斗中的对手使用。\n");

        if( objectp(me->query_temp("weapon")))
              return notify_fail("你必须空手才能使用「聚毒」！\n");

        if((int)me->query_skill("guiyuan-tunafa", 1) < 100 )
              return notify_fail("你的归元吐纳法还未练成，不能使用「聚毒」！\n");
                
        if((int)me->query("neili", 1) < 800 )
              return notify_fail("你现在内力不足，不能使用「聚毒」！\n");       

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("你现在无法使用「聚毒」！\n");                                                                                 

        if(me->query_temp("tzzf"))
              return notify_fail("你正在使用掌刀。\n");

        if((int)me->query_skill("tiezhang-zhangfa", 1) < 120 )
              return notify_fail("你的铁掌掌法不够娴熟，不能使用「聚毒」。\n");

        msg = HIB"\n$N微微凝神向$n缓缓的推出一掌,只见一道黑气向前冲去！\n"NOR;

        if (random(me->query("combat_exp", 1)) > target->query("combat_exp", 1)/3){
                damage = me->query_skill("tiezhang-zhangfa",1);
                damage *= 3;
                if (damage > 1000) damage = 1000 + (damage - 1000)/100;
                target->receive_damage("jing", damage);
                target->receive_wound("jing", damage/2);
                target->receive_damage("jingli", damage+me->query_skill("poison",1));
                msg += BLU"$n惊慌失措之间，闪躲不开，一股黑气只奔$n的眉宇之间袭取！\n"NOR;
                p = (int)target->query("jing")*100/(int)target->query("max_jing");
                msg += "( $n"+eff_status_msg(p)+" )\n";
        }
        else {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
        me->add("neili", -300);
        me->add("jingli", -50);
        me->start_busy(2);
        me->start_perform(4,"「聚毒」");
        return 1;
}

int help(object me)
{
        write(WHT"\n铁掌掌法「聚毒」："NOR"\n");
        write(@HELP
        这是裘千仞铁掌功的绝招之一，叫作「聚毒」，使用铁掌的特有毒性来袭击对方。
        
        要求：  内力 800 以上；      
                精力 50 以上；  
                铁掌掌法等级 120 以上；
                归元吐纳法等级 120 以上；    
                且手无兵器。
HELP
        );
        return 1;
}
