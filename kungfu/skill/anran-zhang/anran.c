// 黯然销魂
// By River 
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
int perform(object me, object target)
{
        int lvl, i;

        lvl = me->query_skill("anran-zhang", 1) /4;

        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target) )
                return notify_fail("「黯然销魂」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「黯然销魂」！\n");   

        if( (int)me->query_skill("anran-zhang", 1) < 150 )
                return notify_fail("你的黯然销魂掌还不够娴熟，使不出「黯然销魂」绝技。\n");

        if( (int)me->query_skill("yunu-xinjing", 1) < 150 )
                return notify_fail("你的玉女心经等级还不够，使不出「黯然销魂」绝技。\n");

        if ( me->query_skill_mapped("strike") != "anran-zhang"
         || me->query_skill_mapped("parry") != "anran-zhang"
         || me->query_skill_prepared("strike") != "anran-zhang")
                return notify_fail("你现在无法使用「黯然销魂」绝技！\n");

        if((int)me->query_temp("xinjing")) 
                return notify_fail("你正在使用「心经」字诀。\n");

        if((int)me->query("max_neili") < (me->query_skill("force")+lvl+100) )
                return notify_fail("你现在内力太弱，使不出「黯然销魂」。\n");      

        if((int)me->query("neili") < (me->query_skill("force")+lvl) )
                return notify_fail("你现在真气太弱，使不出「黯然销魂」绝技。\n");

        if((int)me->query("eff_qi") >= (int)me->query("max_qi"))
                return notify_fail("你现在心情很好，怎么使得出「黯然销魂」绝技。\n");

        if((int)me->query_temp("xiaohun")) 
                return notify_fail("你现在正在使用「消魂」绝技。\n"); 

        if((int)me->query("eff_qi") == 0 )
                return notify_fail("你现在无法使用「黯然销魂」绝技。\n");

        me->add_temp("anran", 2);
        i = (int)me->query("max_qi") / (int)me->query("eff_qi");

        if( i > 3 ) i = 3;
        if( i < 1 ) i = 1;

        if( i > 1 ){
           me->add_temp("apply/strength",lvl/6);
           me->set_temp("hurt", 1);
        } 
        
        me->add_temp("apply/damage", lvl/2);
        me->add_temp("apply/attack", -lvl);
        me->add_temp("apply/strike", lvl);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        if (present(target,environment(me)) && me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);

        me->add_temp("apply/damage", -lvl/2);
      me->add_temp("apply/attack",lvl);
        me->add_temp("apply/strike", -lvl);

        if(me->query_temp("hurt")){
            me->add_temp("apply/strength", -lvl/6);
            me->delete_temp("hurt");
        }
        me->add("neili", -(me->query_skill("force") + random(lvl)));
        me->add("jingli", -50);
        me->delete_temp("anran");
        me->start_perform(5,"黯然销魂");
        target->start_busy(1);
        me->start_busy(1+random(2));
        return 1;
}
