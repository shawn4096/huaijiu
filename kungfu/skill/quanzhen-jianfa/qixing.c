// qixing. 七星绝命剑
// Modify By River 99.5.26
// Modified by darken@SJ

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg,dodge_skill;
        object weapon = me->query_temp("weapon");
        int damage, p;
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用「七星绝命剑」绝技。。\n");

        if( (int)me->query_skill("quanzhen-jianfa", 1) < 101 )
                return notify_fail("你的全真剑法不够熟练，使不出「七星绝命剑」绝技。\n");

        if ( !weapon
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "quanzhen-jianfa"
         || me->query_skill_mapped("parry") != "quanzhen-jianfa")
               return notify_fail("你现在无法使用七星绝命剑。\n");

        if((int)me->query_skill("sword", 1) < 100 )
               return notify_fail("你的基本功还不够娴熟，使不出「七星绝命剑」绝技。\n");

        if((int)me->query_dex() < 25)
               return notify_fail("你的身法还不够迅，使不出「七星绝命剑」绝技。\n");

        if((int)me->query_skill("force", 1) < 100)
               return notify_fail("你的内功修为不够，无法使用「七星绝命剑」绝技。\n");  

        if((int)me->query_temp("hebi"))
               return notify_fail("你正在施展双剑合壁，无法使用「七星绝命剑」绝技。\n"); 

        if((int)me->query("neili") < 400)
               return notify_fail("你的内力不够，无法使用「七星绝命剑」绝技。\n");

        if((int)me->query("jingli")< 300)
               return notify_fail("你的精力不够，无法使用「七星绝命剑」绝技。\n");

        msg = HIW"\n$N一声长啸，一抖手中剑，剑幕中飞出七朵寒星，既如狂风暴雨又如流星般向$n罩了过去。\n"NOR;
        if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 )
        {
           damage = 4 * (int)me->query_skill("quanzhen-jianfa", 1);
           damage = damage / 2 + random(damage / 2);
           if (damage>1500) damage=1500;
           if (me->query_skill("xiantian-gong")>100) damage *= 2;
               else message_vision(HIG"只是$N的先天功还没到家，剑气微弱。\n"NOR, me);
           me->add("neili", -damage/3);
           me->add("jingli",-100);
           target->receive_damage("qi", damage);
           target->receive_wound("qi", damage/4);
           msg += HIR"$n躲闪不及，身中七剑，“哇”的狂叫一声，鲜血狂喷而出！\n"NOR;
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           target->set_temp("last_damage_from", "被"+me->name()+"杀");
           me->start_perform(4,"「七星绝命剑」");
        } 
        else {
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
              me->add("neili", -100);
              me->start_busy(2); 
              me->start_perform(3,"「七星绝命剑」");
        }
        message_vision(msg, me, target);
        return 1;
}
