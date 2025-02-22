// yinyang.c
#include <ansi.h>
int exert(object me)
{       
        int improve = (int)me->query_skill("force") * 2;

        if ((int)me->query_skill("linji-zhuang", 1) < 120)
            return notify_fail("你的临济十二庄修为还不够。\n");

        if( me->query("class") != "bonze" && me->query("family/generation") > 3)
            return notify_fail("你不是出家人，无法领会临济十二庄的「阴阳」字决！\n");

        if((int)me->query("neili") < 1000 )
            return notify_fail("你的真气不够。\n");

        if((int)me->query("max_neili") < 2000 )
            return notify_fail("你的真气不够。\n");

        if( me->query_temp("ljz/yinyang")   )
            return notify_fail("你正在运用临济十二庄的「阴阳」字诀！\n");

        message_vision(HBBLU"只见$N吸取天地之间的阴阳两气，顿然气力大增！\n"NOR,me);

        me->add("max_qi", improve);
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("max_qi"));
        me->set_temp("ljz/yinyang", improve);
        me->add("neili", - 500);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), improve );
        return 1;
}

void remove_effect(object me)
{      
        int improve;
        if( !me || !me->query_temp("ljz/yinyang") ) return;
        improve = me->query_temp("ljz/yinyang");
        me->delete_temp("ljz/yinyang");
        me->add("max_qi", - improve);
        if( me->is_ghost() )
        	return;
        me->add("eff_qi", - improve);
        tell_object(me, HIR"你的临济十二庄「阴阳」字诀运功完毕，气力回复了正常。\n"NOR);
}
