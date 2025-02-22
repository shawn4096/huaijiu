#include <ansi.h>

inherit F_SSERVER;
private int remove_effect(object me, int amount);
int perform(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("「希夷剑法」只能在战斗中使用。\n");

        if((int)me->query_skill("zixia-gong", 1) < 120 )
                return notify_fail("你的内功等级不够，不能使用「希夷剑法」。\n");
    
        if ((int)me->query_skill("huashan-jianfa", 1) < 120 )
                return notify_fail("你的华山剑法不够娴熟，不能真正发挥「希夷剑法」。\n");
    
        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "huashan-jianfa"
         || me->query_skill_mapped("parry") != "huashan-jianfa")
                return notify_fail("你现在无法使用「希夷剑法」来提高防御力。\n");
    
        if ((int)me->query("neili") < 500 )
                return notify_fail("你现在内力太弱，不能使用「希夷剑法」。\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("你现在精力太少，不能使用「希夷剑法」。\n");

        if ((int)me->query_temp("hsj_junzi"))
                return notify_fail("你正在使用「君子剑法」绝技。\n"); 

        if ((int)me->query_temp("hsj_shunv"))
                return notify_fail("你正在使用「淑女剑法」绝技。\n"); 
    
        if ( (int)me->query_temp("hsj_xiyi") ) 
                return notify_fail("你正在使用「希夷剑法」。\n");

    
        if (me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("你的内功有误，无法使用「希夷剑法」。\n");

        message_vision(HIC "$N这时一声清喝，手中"+weapon->name()+HIC"招数一变,使出华山气宗嫡传的希夷剑法，\n"+
                           "守御立时严密无缝。"+weapon->name()+"暴出道道凌厉剑气，层层叠叠护在身前，任敌人全力变招抢攻，却根本无隙可入。\n"NOR, me);
        me->start_perform(1,"「希夷剑法」");
        me->add("neili", -200);          
        me->add("jingli", -100);
    
        skill = me->query_skill("huashan-jianfa", 1)/4;
        me->add_temp("apply/armor",  skill*2);
        me->add_temp("apply/parry",  skill*3);
        me->add_temp("apply/dodge",  skill*3);
        me->add_temp("apply/damage",  -skill);
        me->set_temp("hsj_xiyi", 1);

        me->start_call_out( (: call_other, __FILE__, "check_fight", me, skill, weapon :), 1);
        return 1;
}

void check_fight(object me, int amount, object weapon)
{  
        object wep;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if(!me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || !wep
         || weapon != wep )
           remove_effect(me, amount);
        else call_out("check_fight", 1, me, amount, weapon);
}

private int remove_effect(object me, int amount)
{         
        int skill;
        skill = me->query_skill("huashan-jianfa", 1)/4;
 
        me->add_temp("apply/parry", -skill*3);
        me->add_temp("apply/dodge", -skill*3);
        me->add_temp("apply/armor",  -skill*2);
        me->add_temp("apply/damage",  skill);
        me->delete_temp("hsj_xiyi");
        if(living(me) && !me->is_ghost())
           message_vision(HIW"一套希夷剑法演毕，$N凝神收式,希夷剑法的剑气渐渐消失。\n"NOR, me);
        return 0;
}

