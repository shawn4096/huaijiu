inherit F_SSERVER;
#include <ansi.h>
int perform(object me, object target)
{
        string msg;
        int neili, qi;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("「乾坤一指」只能对战斗中的对手使用。\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 150 )
                return notify_fail("你的碧海潮生功修为未到，无法使出乾坤一指。\n");
        if( (int)me->query_skill("suibo-zhuliu", 1) < 150 )
                return notify_fail("你的随波逐流修为未到，无法使出乾坤一指。\n");
        if( (int)me->query_skill("tanzhi-shentong", 1) < 150 )
                return notify_fail("你的弹指神通修为未到，无法使出乾坤一指。\n");
        if( (int)me->query_skill("finger",1) < 120 )
                return notify_fail("你的指法修为不足，使不出乾坤一指。\n");
        if( (int)me->query("neili") < 3000 )
                return notify_fail("你现在内力太弱，不能出乾坤一指。\n");
        if (target->query_temp("thd/qiankun"))
                return notify_fail("他已经被击中了，放心攻击吧。\n");
                
        me->start_perform(4,"乾坤一指");
        neili = target->query("max_neili");
        qi = target->query("max_qi");
        msg = HIG"\n$N手指一伸，一股劲风随之向$n袭去！\n"NOR;
        if (random(me->query("dex") + me->query_skill("dodge", 1)/ 10) > (target->query("dex")+target->query_skill("dodge", 1)/10))
        {
                msg += HIR"$n被这一指重重点中气海穴，结果檀中、玉堂穴气息再也无法顺畅通行。\n"NOR;
                me->start_busy(2);
                target->start_busy(random(4)+1);
                target->set_temp("thd/qiankun",1);
                target->set("max_qi",qi/2);
                target->set("eff_qi",qi/2);
// set for condition
                target->set("qiankun/qi",qi);
                target->set("qiankun/neili",neili);
                if (target->query("qi")>target->query("eff_qi")) 
                       target->set("qi",target->query("eff_qi"));
                target->set("max_neili",neili/2);
                if (target->query("neili")>target->query("max_neili"))
                       target->set("neili",target->query("max_neili"));
                target->apply_condition("qiankun_wound",(int)me->query_skill("finger")/50);
        }
        else {
                me->start_busy(3);
                msg += HIY"$n身形拔起，在$N肩头一点，便闪过了这一招。\n"NOR;
        }
        me->add("neili",-(300+random(100)));
        message_vision(msg, me, target);
        return 1;
}

