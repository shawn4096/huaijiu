//嫉世愤俗
//按照new system要求，命中率为A+
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
int perform(object me, object target)
{
          int lvl;

              lvl = me->query_skill("anran-zhang", 1)/8 ;
	 if (me->query("gender")=="女性") lvl/=2;

        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target) )
                return notify_fail("「嫉世愤俗」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「嫉世愤俗」！\n");   

        if( (int)me->query_skill("anran-zhang", 1) < 150 )
                return notify_fail("你的黯然销魂掌还不够娴熟，使不出「嫉世愤俗」绝技。\n");

        if( (int)me->query_skill("yunu-xinjing", 1) < 150 )
                return notify_fail("你的玉女心经等级还不够，使不出「嫉世愤俗」绝技。\n");

        if ( me->query_skill_mapped("strike") != "anran-zhang"
         || me->query_skill_mapped("parry") != "anran-zhang"
         || me->query_skill_prepared("strike") != "anran-zhang")
                return notify_fail("你现在无法使用「嫉世愤俗」绝技！\n");

        if((int)me->query_temp("xinjing")) 
                return notify_fail("你正在使用「心经」字诀。\n");

        if((int)me->query("max_neili") < (me->query_skill("force")+lvl+100) )
                return notify_fail("你现在内力太弱，使不出「嫉世愤俗」。\n");      

        if((int)me->query("neili") < (me->query_skill("force")+lvl) )
                return notify_fail("你现在真气太弱，使不出「嫉世愤俗」绝技。\n");


        if((int)me->query_temp("xiaohun")) 
                return notify_fail("你现在正在使用「消魂」绝技。\n"); 

        if((int)me->query("eff_qi") == 0 )
                return notify_fail("你现在无法使用「嫉世愤俗」绝技。\n");

        me->set_temp("jishi", 1);

          message_vision(HIY"$N突然一阵恶意涌上心头，所打出的掌力竟然威力大增！\n"NOR,me,target);
        me->add_temp("apply/damage", lvl/2);
        me->add_temp("apply/attack", lvl);

          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if (present(target,environment(me)) && me->is_fighting(target))
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        me->add_temp("apply/damage", -lvl/2);
        me->add_temp("apply/attack", -lvl);

        me->add("neili", -(me->query_skill("force") + random(lvl)));
        me->add("jingli", -50);
        me->delete_temp("jishi");
          me->start_perform(4,"嫉世愤俗");
        target->start_busy(1);
       me->start_busy(1+random(2));
        return 1;
}

