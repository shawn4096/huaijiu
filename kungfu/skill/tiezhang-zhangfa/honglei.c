// by darken@SJ
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

string perform_name(){ return HBBLU"轰雷双掌"NOR; }
int perform(object me, object target)
{
        int p, j;
        string msg;
        j = me->query_skill("tiezhang-zhangfa", 1);

        if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !living(target)
          || environment(target)!= environment(me))
                return notify_fail("「轰雷双掌」只能在战斗中对对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「轰雷双掌」！\n");

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 200 )
                return notify_fail("你的铁掌不够娴熟，使不出「轰雷双掌」绝技。\n");

        if( (int)me->query_skill("guiyuan-tunafa", 1) < 200 )
                return notify_fail("你归元吐纳法不够，使不出轰雷双掌绝技。\n");

        if( (int)me->query("jiali") < 120 )
                return notify_fail("你加力不够，使不出「轰雷双掌」绝技。\n");

        if (me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("你所使用的内功不对。\n");

        if( (int)me->query_skill("force") < 250 )
                return notify_fail("你的内功等级不够，不能使用「轰雷双掌」。\n");

        if( (int)me->query_str() < 50 )
                return notify_fail("你的膂力还不够强劲，使不出「轰雷双掌」来。\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("你现在无法使用「轰雷双掌」！\n");

        if( (int)me->query("max_neili") < 4000)
                return notify_fail("你现在内力太弱，使不出「轰雷双掌」。\n");

        if( (int)me->query("neili") < 3000 )
                return notify_fail("你现在真气太弱，使不出「轰雷双掌」。\n");

        msg = HBBLU "\n$N蓦地里转身，使出铁掌掌法中的“轰雷双掌”对$n胸口双掌推出！\n"NOR;
        if (random(me->query_dex()) > target->query_dex()/2) {
             msg += HIR"\n结果一击命中，$n向后飞出足足三四丈远，口中鲜血狂喷！\n"NOR;
             j *= 10;
             j += me->query("jiali")*10;
             j -= target->query_con()*20;
             j = j*2/3 + random(j/3);
             target->receive_damage("qi", j);
             target->receive_wound("qi",j/2);
             p = (int)target->query("qi")*100/(int)target->query("max_qi");
             msg += "( $n"+eff_status_msg(p)+" )\n"; 
        } else
             msg += HIR"\n$n见来势猛恶，急忙远远避开。\n"NOR;

        me->add("neili", -2500-random(500));
        me->start_busy(1+random(2));
        message_vision(msg, me, target);
        me->start_perform(5,"「轰雷双掌」");
        return 1;
}

