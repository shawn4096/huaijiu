#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon = me->query_temp("weapon");
        object *ob;
        int i, skill, bang_jue,damage;

        if( !target ) target = offensive_target(me);
        if (!weapon || weapon->query("skill_type") != "stick"
        || me->query_skill_mapped("stick") != "dagou-bang")
                return notify_fail("你现在无法使用天下无狗攻击。\n");

        if( !me->is_fighting())
                return notify_fail("你现在没有在战斗中！\n");                          

        if( me->query("gender") == "无性")
                return notify_fail("你一个不男不女之人如何能用天下无狗？\n");

        if( (int)me->query("con") < 20 )
                return notify_fail("太遗憾了! 你先天体质不够, 这辈子无望使用天下无狗。\n");

        if( (int)me->query("max_neili") < 2000 )
                return notify_fail("你内力不雄厚不能使用天下无狗攻击。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你现在没有足够的内力使用天下无狗。\n");

        if ((int)me->query("jingli") < 100)
                return notify_fail("你现在没有足够的精力使用天下无狗。\n");

        if( (int)me->query_skill("dagou-bang", 1) < 120 )
                return notify_fail("你的打狗棒法火侯还没到，天下无狗使不出来。\n");

        if( (int)me->query_skill("bangjue", 1) < 100 )
                return notify_fail("你对诀窍心法的领会还不够, 无法天下无狗。\n");

        if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");

        skill = me->query_skill("dagou-bang", 1);
        bang_jue=me->query_skill("bangjue",1);

        me->add("neili", -500);
        me->receive_damage("jingli", 100);

        me->start_busy(2);
        message_vision(HIY "$N使出「天下无狗」的第六变，刹时四面八方是棒，。\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || ob[i]==me ) continue;
                if( !ob[i]->is_fighting(me)) continue;
                if (userp(ob[i]) && me->query_condition("killer") > 100) continue;
                if(strsrch(file_name(environment(me)),"/d/wuguan/") >= 0 && !ob[i]->query_condition("killer")) continue;
                if (random(me->query("combat_exp",1)) > (ob[i]->query("combat_exp",1))/3
            && random(bang_jue) > (ob[i]->query_dex() )){
                        damage = skill * (int)me->query("combat_exp") / (int)ob[i]->query("combat_exp");
                        damage = damage / 2 + (random(damage)+(1+random(bang_jue/10))*(bang_jue/2));
                        damage = damage / 2 + random(damage);
                        if( damage > 1500 ) damage = 1501;
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_damage("neili", damage/2 , me);
                        tell_object(ob[i], "你觉得眼前一阵棒雨，挨了不少下。\n");       
    target->start_busy( 2+random(3));         
target->receive_wound("qi",damage/3,me);
                        if( !ob[i]->is_killing(me->query("id")) ) me->kill_ob(ob[i]);
                }
                else  message_vision( "$n急忙后跳，逃出$N漫天棒雨之外。\n",me,ob[i]);
                me->start_busy(random(2)+ 2); 
        }
       me->start_perform(6,"「天下无狗」");
        return 1;
}
