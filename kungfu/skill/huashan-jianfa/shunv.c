#include <ansi.h>

inherit F_SSERVER;
private int remove_effect(object me, int amount);
int perform(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("「淑女剑法」只能在战斗中使用。\n");

        if((int)me->query_skill("zixia-gong", 1) < 130 )
                return notify_fail("你的内功等级不够，不能使用「淑女剑法」。\n");
    
        if ((int)me->query_skill("huashan-jianfa", 1) < 130 )
                return notify_fail("你的华山剑法不够娴熟，不能真正发挥「淑女剑法」。\n");
    
        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("parry") != "huashan-jianfa"
         || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("你现在无法使用「淑女剑法」来提高命中率。\n");
    
        if ((int)me->query("neili") < 500 )
                return notify_fail("你现在内力太弱，不能使用「淑女剑法」。\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("你现在精力太少，不能使用「淑女剑法」。\n");

        if ((int)me->query_temp("hsj_junzi"))
                return notify_fail("你正在使用「君子剑法」绝技。\n"); 

        if ((int)me->query_temp("hsj_shunv"))
                return notify_fail("你正在使用「淑女剑法」绝技。\n"); 
    
        if ( (int)me->query_temp("hsj_xiyi") ) 
                return notify_fail("你正在使用「淑女剑法」。\n");

    
        if (me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("你的内功有误，无法使用「淑女剑法」。\n");

        message_vision(HIC "$N这时一声清喝，手中"+weapon->name()+HIC"招数一变,使出华山气宗嫡传的淑女剑法，\n"+
                           "这宁女侠亲传神技好生了得。但见"+weapon->name()+HIC"幻起道道飞虹，不论对手腾挪闪跃，竭力招架，却始终脱不出$N的剑气笼罩，\n"NOR, me);
        me->start_perform(1,"「淑女剑法」");
        me->add("neili", -200);          
        me->add("jingli", -100);
    
        skill = me->query_skill("huashan-jianfa", 1)/5;
        me->add_temp("apply/dexerity",  skill);
        me->set_temp("hsj_shunv", skill);

        call_out("check_fight", 1, me, weapon);
        return 1;
}

void check_fight(object me, object weapon)
{  
        object wep;
        int i;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if( !me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || !wep
         || weapon != wep ){
	   i = me->query_temp("hsj_shunv");
           me->add_temp("apply/dexerity", -i);
           me->delete_temp("hsj_shunv");
           if(living(me) && !me->is_ghost())
              message_vision(HIW"一套淑女剑法演毕，$N凝神收式,淑女剑法的剑气渐渐消失。\n"NOR, me);
           return;
        } 
        call_out("check_fight", 1, me, weapon);
}
