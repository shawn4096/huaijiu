// zhixin.c

#include <ansi.h>

int exert(object me)
{       
        int improve;

        if ((int)me->query_skill("linji-zhuang", 1) < 60)
             return notify_fail("你的临济十二庄修为还不够。\n");

        if( me->query("class") != "bonze" && me->query("family/generation") > 3)
             return notify_fail("你不是出家人，无法领会临济十二庄的「之心」字决！\n");

        if( (int)me->query("neili") < 300 )
             return notify_fail("你的真气不够。\n");
        
        if( me->query_temp("yun_zhixin"))
             return notify_fail("你正在运用临济十二庄的「之心」字决！\n");

        write(MAG"你微一凝神，运动之心两庄，去浊气出体外，收清气入心中，只觉灵台清明，领悟力有所增加。\n"NOR, me);
        message_vision(MAG"只见$N微一凝神，吞吐几口长气，一对眼眸灵动晶亮，神采弈弈。\n"NOR, me);
        improve = (int)me->query("int");
        me->add_temp("apply/intelligence", improve/2);
        me->set_temp("yun_zhixin", 1);  
        me->add("neili", - 150);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, improve :), (int)me->query_skill("literate", 1)/2);
        return 1;
}

void remove_effect(object me, int improve)
{
        if(!me) return;
        me->add_temp("apply/intelligence", -improve/2 );    
        me->delete_temp("yun_zhixin");
        tell_object(me, HIR"你体内已积过多浊气，似乎领悟力又归于寻常。\n"NOR);
}
