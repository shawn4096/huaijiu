// by darken@SJ
// Modify By River@SJ 2001.6.18

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill = me->query_skill("quanzhen-jianfa", 1);
        object weapon = me->query_temp("weapon");  
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("一剑化三清只能对战斗中的对手使用。\n");

        if( me->query_skill("force", 1) < 100 )
                return notify_fail("你的内功火候未到，无法施展一剑化三清！\n");

        if( me->query_skill("dodge") < 150 )
                return notify_fail("一剑化三清需轻功配合，方能施展！\n");

        if( me->query_skill("sword") < 150 )
                return notify_fail("你剑法火候未足，无法使用一剑化三清！\n");

        if( me->query("neili") < 500 )
                return notify_fail("你的内力不够使用一剑化三清！\n");

        if( me->query("jingli") < 150 )
                return notify_fail("你的精力不够使用一剑化三清！\n");

        if((int)me->query_temp("hebi"))
               return notify_fail("你正在施展双剑合壁，无法使用「一剑化三清」绝技。\n"); 

        if(!me->query_skill("xiantian-gong"))
          if(me->query_skill("yunu-xinjing", 1) < 100)
                return notify_fail("你的内功火候不够，无法使用一剑化三清。\n");

        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "quanzhen-jianfa")
                return notify_fail("你手中无剑怎能使用一剑化三清？！\n");

        msg = HIW"\n$N一声清啸，使出全真剑法中的一剑化三清，剑尖分成数点，刺向$n！\n" NOR;
        message_vision(msg , me, target);
        me->add_temp("apply/attack", 50);
        me->add_temp("apply/damage", me->query_skill("xiantian-gong")/10);
        me->add("neili", -300);
        me->add("jingli", -100);
        me->set_temp("sanqing", 1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->start_perform(3,"一剑化三清");
        me->delete_temp("sanqing");
        call_out("check_fight", 3, me, target, weapon, skill/20);
        return 1;
}

void check_fight(object me,object target,object weapon,int count)
{
        if(!me) return;
	if(!target
	 || !me->is_fighting(target)
         || !weapon
         || me->query_skill_mapped("sword") != "quanzhen-jianfa"
         || count < 3 ){
                message_vision(HIW"\n这几剑一气呵成，剑意连环，剑势沉稳，取意道家三清，乃是全真剑法中的精髓所在。\n\n"NOR, me);
                me->delete_temp("sanqing");
                me->add_temp("apply/attack", -50);
                me->add_temp("apply/damage", -me->query_skill("xiantian-gong")/10);
                return;
         }
         else {
           me->set_temp("sanqing", 1);
           if (me->query_skill("xiantian-gong", 1) > 100) {
             if (me->is_fighting(target))
             	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
             if (me->is_fighting(target) && random(2))
             	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),2);
           }
           if (me->is_fighting(target))
           	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
           if (me->is_fighting(target))
           	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
           me->delete_temp("sanqing");
           me->start_perform(3,"一剑化三清");
         }
         call_out("check_fight", 3, me, target, weapon, count - 3);  
}
