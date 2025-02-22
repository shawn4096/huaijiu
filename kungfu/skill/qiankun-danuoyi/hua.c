#include <ansi.h>
inherit F_SSERVER;
int check_fight(object me);

int perform(object me, object target)
{
        if(!me->is_fighting())
                return notify_fail("你没在战斗中呢！\n");

        if(!target) target = offensive_target(me);

        if(me->query_skill("qiankun-danuoyi", 1) < 210 )
                return notify_fail("你的乾坤大挪移还未练到第七层。\n");

        if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("你没有使用乾坤大挪移作为招架！\n");

        if((int)me->query("neili") > me->query("max_neili"))
                return notify_fail("你目前的内力太强，无法使用化字诀！\n");

        if((int)me->query("jiali") >= 10)
                return notify_fail("你目前的加力太重，无法使用化字诀！\n");

        if((int)me->query_temp("qkdny/hua") )
                return notify_fail("你正在施展「化」字诀呢！\n");

        if((int)me->query_temp("qkdny/yi") )
                return notify_fail("你正在施展「移」字诀呢！\n");

        if((int)me->query_temp("qkdny/xu") )
                return notify_fail("你正在施展「蓄」字诀呢！\n");

        if((int)me->query_temp("qkdny/yin") )
                return notify_fail("你正在施展「引」字诀呢！\n");

        me->add("neili", -100-random(100));
        tell_object(me,HIW"你深深的吸了口气，招数变的轻柔缓慢。\n"NOR);
        me->set_temp("qkdny/hua", 1);
        target->apply_condition("no_perform",random(3)+1);
        check_fight(me); 
        return 1;
}

int check_fight(object me)
{    
        if (!me || !me->query_temp("qkdny/hua")) return 0;

        if(me->is_ghost() || !living(me))
            me->delete_temp("qkdny/hua");
        
        if(!me->is_fighting() 
         || me->query("jiali") > 9 
         || me->query("jingli") < 500
         || me->query("jing")<500){
           tell_object(me, HIW"\n你的招数恢复了平常。\n"NOR);
           me->delete_temp("qkdny/hua");
        }
        else call_out("check_fight", 1, me);
        return 1;
}
