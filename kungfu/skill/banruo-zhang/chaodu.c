//chaodu.c  般若掌超度连环诀

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("超度连环诀只能对战斗中的对手使用。\n");

        if( me->query_temp("lianhuan") )
                return notify_fail("你已在使用超度连环诀了！\n");

        weapon = me->query_temp("weapon");
        if( objectp(weapon) )
                return notify_fail("你手中拿着家伙，如何能够施展连环诀？\n");

        if( me->query_skill_mapped("force") != "yijin-jing" )
                return notify_fail("你所用的并非易筋经神功，无法配合掌法施展连环诀！\n");

        if( me->query_skill("force") < 120 )
                return notify_fail("你的易筋经气功火候未到，无法配合施展连环诀！\n");

/*
        if( me->query_skill("banruo-zhang") < 120 )
                return notify_fail("你掌法修为不足，还不会使用超度诀！\n");
*/

        if( me->query_skill("strike") < 120 )
                return notify_fail("你掌法修为不足，还不会使用连环诀！\n");

        if( me->query("neili") <= 300 )
                return notify_fail("你的内力不够施展连环诀！\n");
        if( me->query("jingli") <= 200 )
                return notify_fail("你的精力不够施展连环诀！\n");

        skill = me->query_skill("strike");
        
        message_vision(HIR "\n$N大喝一声，运掌如电,掌风霍霍，招招连环，正式佛门伏魔功超度决！\n\n" NOR, me, target);

        me->set_temp("lianhuan", 1);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill/5);
        me->add("neili", -300);
        me->add("jingli", -100);

        return 1;
}

void remove_effect(object me, int amount)
{
        me->delete_temp("lianhuan");

        if ( me->is_fighting() ) {
                message_vision(HIR "\n$N的易筋经神功运行完毕，将内力收回丹田，手上招数也逐渐慢了下来。\n\n" NOR, me);
        }
        else {
                tell_object(me, HIR "\n你的易筋经功运行完毕，将内力缓缓收回丹田。\n\n" NOR);
        }
}
