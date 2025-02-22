// longxiang.c 龙吟凤翔
//by xiaoyao 4/19/2k

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int i, j, focus;
        object weapon;
        i = 1;
        j = me->query_skill("sword")/10;

        if(me->query("ss/pass_deng")) {
              j = me->query_skill("sword")/8;
              i = 3;
        }

        focus = me->query_temp("ss/focus") + 1;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「龙吟凤翔」只能在战斗中对对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你必须使用剑才能使用「龙吟凤翔」。\n");

        if(me->query_skill("songshan-jian", 1) < 180 )
                return notify_fail("你的嵩山剑法还不够娴熟，使不出「龙吟凤翔」绝技。\n");

        if( (int)me->query_skill("hanbing-zhenqi", 1) < 180 )
                return notify_fail("你的寒冰真气不够高，无法使用「龙吟凤翔」。\n");        

        if( (int)me->query_skill("force") < 150 )
                return notify_fail("你的内功等级不够，使不出「龙吟凤翔」绝技。\n");

        if( (int)me->query_str() < 31)
                return notify_fail("你的膂力还不够强劲，使不出「龙吟凤翔」绝技。\n");

        if (me->query_skill_prepared("hand") != "songyang-shou"
        || me->query_skill_mapped("hand") != "songyang-shou")
                return notify_fail("「龙吟凤翔」需要用大嵩阳手辅助。\n");

        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("你现在内力太弱，使不出「龙吟凤翔」。\n");      

        if( (int)me->query("neili") < 900 )
                return notify_fail("你现在真气太弱，使不出「龙吟凤翔」。\n");

        msg = HIR"\n$N伸出左手拇指、食指、中指三根手指，握住了剑尖，右手一松，长剑突然弹起，剑柄在前，不住地晃动。\n突然$N绕着$n快速攻击，人剑合一，幻作一条金龙腾空而起，自半空中横过，剑身似曲似直，倏的罩向$n！\n\n"NOR;

        me->add_temp("apply/attack", j+focus*10);
        me->add_temp("apply/damage", j/3+5*focus);
        message_vision(msg, me, target);

        if(me->query("ss/pass_deng")) message_vision(HIY"\n$N已熟知嵩山剑法的精妙所在，剑随心走，顿时招式凌厉！\n"NOR, me);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add("neili", -150);
        me->add("jingli", -50);
        message_vision(HIR"                                                                   ※※  "HIC"龙"NOR  HIR"  ※※\n"NOR,me);       

        weapon->unequip(); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add("neili", -150);
        me->add("jingli", -50);
        message_vision(HIR"                                                                   ※※  "HIC"吟"NOR  HIR"  ※※\n"NOR,me);

        weapon->wield();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add("neili", -150);
        me->add("jingli", -50);
        message_vision(HIR"                                                                   ※※  "HIC"凤"NOR  HIR"  ※※\n"NOR,me);

        weapon->unequip(); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add("neili", -150);  
        me->add("jingli", -50);
        message_vision(HIR"                                                                   ※※  "HIC"翔"NOR  HIR"  ※※\n"NOR,me);        
        weapon->wield();
        if(random(me->query_skill("songshan-jian",)) > 200 ){
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->add("neili", -150);
        me->add("jingli", -50);
          }
        me->add_temp("apply/damage", -j/3-5*focus);
        me->add_temp("apply/attack", -j-focus*10);
        me->start_busy(1+random(2));
        target->start_busy(2);
        me->start_perform(5,"「龙吟凤翔」");
        return 1;
}

