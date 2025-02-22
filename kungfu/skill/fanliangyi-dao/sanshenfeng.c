// shenfeng.c 华岳三神峰
// by look
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int lvl;
        object weapon = me->query_temp("weapon");
        lvl = ( (int)me->query_skill("fanliangyi-dao", 1)/4 + (int)me->query_skill("poyu-quan", 1) ) /4;

        if( !target ) target = offensive_target(me);
     
        if( !target || !me->is_fighting(target) )
                return notify_fail("「华岳三神峰」只能在战斗中对对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "blade"
        || me->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("你手里没有刀，无法使用「华岳三神峰」！\n");             

        if( (int)me->query_skill("fanliangyi-dao",1) < 100 )
                return notify_fail("你的反两仪刀不够娴熟，不能使用「华岳三神峰」！\n");
      
        if( (int)me->query_skill("blade",1) < 100 )
                return notify_fail("你的基本刀法等级不够，不能使用「华岳三神峰」！\n");  

        if( (int)me->query_skill("poyu-quan", 1) < 100 )
                return notify_fail("你的破玉拳法等级不够，不能使用「华岳三神峰」！\n");
      
        if( (int)me->query_skill("zixia-gong", 1) < 80 )
                return notify_fail("你的紫霞神功等级不够，不能使用「华岳三神峰」！\n");

        if( (int)me->query("max_neili") < 800 )
                return notify_fail("你的内力太弱，不能使用「华岳三神峰」！\n");
      
        if( (int)me->query("neili") < 400 )
                return notify_fail("你的内力太少了，无法使用出「华岳三神峰」！\n");   
                                                                                 
        if (me->query_skill_prepared("cuff") != "poyu-quan"
          || me->query_skill_mapped("cuff") != "poyu-quan")
                return notify_fail("你现在无法使用「华岳三神峰」进行攻击。\n");

        if (me->query_skill_prepared("strike") == "hunyuan-zhang")
                return notify_fail("你现在无法使用「华岳三神峰」进行攻击。\n");


        message_vision(HIC"\n$N仰天一声清啸，运足内力使出「华岳三神峰」，向$n雷霆般地击出两拳一刀！\n"NOR, me,target);
        me->add("neili", -(300+random(100))); 
        me->add("jingli", -100);      
        me->add_temp("apply/attack", lvl);
        weapon->unequip(); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        weapon->wield();
        if(me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target)){ 
              weapon->unequip();
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
              weapon->wield();
        }
        me->start_busy(1);
        me->add_temp("apply/attack", -lvl);
	me->start_perform(4 , "「华岳三神峰」");
        return 1;
}
