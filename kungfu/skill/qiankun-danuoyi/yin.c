#include <ansi.h>
inherit F_SSERVER;
int check_fight(object me);

int perform(object me,object target,string arg)
{
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
              return notify_fail("「引」字诀只能对战斗中的对手使用。\n");

        if(!me->is_fighting())
                return notify_fail("你没在战斗中呢！\n");

        if(me->query_skill("qiankun-danuoyi", 1) < 210 )
                return notify_fail("你的乾坤大挪移还未练到第七层。\n");

        if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("你没有使用乾坤大挪移作为招架！\n");

        if((int)me->query("neili") < 500)
                return notify_fail("你目前的内力不够。\n");

        if((int)me->query_temp("qkdny/yi") )
                return notify_fail("你正在施展「移」字诀呢！\n");

        if((int)me->query_temp("qkdny/yin") )
                return notify_fail("你正在施展「引」字诀呢！\n");

        if((int)me->query_temp("qkdny/xu") )
                return notify_fail("你正在施展「蓄」字诀呢！\n");

        if((int)me->query_temp("qkdny/hua") )
                return notify_fail("你正在施展「化」字诀呢！\n");

        if(target->query_temp("qkdny/yin"))
                return notify_fail( target->query("name") +"正在使用「引」字诀呢。\n");

        me->add("neili", -400-random(100));
        tell_object(me,HIG"\n你运起乾坤大挪移心法，停下了攻击，凝神专注牵引。\n"NOR);
        me->set_temp("qkdny/yin", 1);
	me->set_temp("lost_attack", 1);
        me->add_temp("apply/dodge",-200);
        me->add_temp("apply/parry",-200);
        check_fight(me); 
        return 1;
}

int check_fight(object me)
{    
       if (!me || !me->query_temp("qkdny/yin")) return 0;

       else if(me->is_ghost() || !living(me)
         || !me->is_fighting()
         || me->query("jingli") < 500 
         || me->query("neili") < 500 
         || me->query("jing")<500){
           tell_object(me, HIG"\n你的招数恢复了平常。\n"NOR);
           me->delete_temp("qkdny/yin");
           me->add_temp("apply/dodge",200);
           me->add_temp("apply/parry",200);
       }
       else call_out("check_fight", 1, me);
	me->set_temp("lost_attack", 1);
       return 1;
}
