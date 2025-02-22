// huanying.c
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;
        if( !target ) target = offensive_target(me);

        if(!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "blade")
            return notify_fail("你使用的武器不对。\n");

        if( !target
         || !me->is_fighting(target) )
            return notify_fail("「幻影」只能在战斗中对对手使用。\n");

        if((int)me->query_skill("linji-zhuang", 1) < 100 )
            return notify_fail("你的临济十二庄等级不够，不能呼唤幻影。\n");       

        if(me->query_skill_mapped("force") != "linji-zhuang")
            return notify_fail("你所使用的内功不对。\n");

        if((int)me->query_skill("yanxing-daofa", 1) < 100 )
            return notify_fail("你的雁行刀法等级不够，不能呼唤鬼魂！\n");    

        if((int)me->query_skill("blade", 1) < 100 )
            return notify_fail("你的基本刀法极不够娴熟，不能呼唤出你的幻影！\n");    

        if( me->query_skill_mapped("blade") != "yanxing-daofa"
         || me->query_skill_mapped("parry") != "yanxing-daofa")
            return notify_fail("你现在无法呼唤出幻影进行攻击！\n"); 

        if((int)me->query("neili") < 300 )
            return notify_fail("你现在真气太弱，不能呼唤幻影！\n");

        if((int)me->query("max_neili") < 1000 )
            return notify_fail("你现在内力太弱，不能呼唤幻影！\n");

        if ((int)me->query_temp("幻影", 1) ) 
            return notify_fail("你已经呼唤出了自己的幻影！\n");
    
        message_vision(HIY"$N前后游走，身形闪动，手中钢刀越使越快，幻起无数刀光化出数个身形。\n"+
                          "$n被此雁行刀法之「无形幻影」所迷惑，手足无措，不知哪个$N是真，哪个是假。\n"NOR, me, target);
        me->start_busy(2);
        me->add("neili", -(int)me->query_skill("yanxing-daofa", 1) *3/2);    
        skill = me->query_skill("yanxing-daofa", 1)/3;
        me->set_temp("幻影", 1);
        me->start_perform(3,"「无形幻影」");
        call_out("remove_effect", 1, me, target, weapon, skill+1);
        return 1;
}

void remove_effect(object me,object target,object weapon, int count)
{
        if(! me) return;
        if( !target
         || !me->is_fighting(target)
         || me->query_skill_mapped("blade") != "yanxing-daofa"
         || !weapon
         || me->query_temp("weapon") != weapon
         || count < 1){
           message_vision("那个"HIY"幻影"NOR"于半空徘徊了一阵，就消失在地底了！\n", me);
           me->delete_temp("幻影");
           return;
        }
        else {
          call_out("remove_effect", 1, me, target, weapon, count -1);
          me->start_perform(1,"「无形幻影」");
        }
}
