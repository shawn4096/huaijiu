// kuaijian.c 狂风快剑
// by darken@SJ
// modified olives@SJ
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
 
int perform(object me, object target)
{
        if( !target || target == me) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("狂风快剑只能对战斗中的对手使用。\n");

        if( me->query_dex() < 60 )
                return notify_fail("你在身法上先天禀赋不足，不能使用狂风快剑！\n");
        
        if( me->query_skill("zixia-gong", 1) < 300 )
                return notify_fail("你的紫霞功火候未到，无法施展狂风快剑！\n");

        if( me->query_skill("dodge") < 300 )
                return notify_fail("狂风快剑需要超绝的轻功配合，方能有效施展！\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用狂风快剑！\n");

        if( me->query("neili") <= 5000 )
                return notify_fail("你的内力不够使用狂风快剑！\n");

        if( me->query("jingli") <= 3000 )
                return notify_fail("你的精力不够使用狂风快剑！\n");

        if( me->query_temp("hsj_kf",))
                return notify_fail("你正在运用狂风快剑！\n");

          if(!me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("你手中无剑怎能使用狂风快剑？！\n");

        message_vision(HIG"$N仰天一声清啸，斜行而前，长剑横削直击，迅捷无比，未到五六招，
剑势中已发出隐隐风声。$N出剑越来越快，风声也是渐响。剑招一剑
快似一剑，所激起的风声也越来越强。一百零八式“狂风快剑”顷刻间
全向$n身上招呼！\n"NOR, me, target);
        me->set_temp("hsj_kf",1);
        me->add("neili",-1000);
        me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/6);
        me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/10);
        call_out("kuangfeng", 0, me, target);
        me->start_perform(999);
        return 1;
}

void kuangfeng(object me, object target)
{
        int i;
        object weapon;
        
        if (!me) return;
        weapon= me->query_temp("weapon");
       
        if (me->is_fighting(target) &&
           !me->is_busy()          &&
            me->query("jingli") > 300 &&
            me->query("neili") > 500 &&
           objectp(target) && 
           !target->is_ghost() &&
           !me->is_ghost() && 
           me->query_temp("hsj_kf")<10 &&
           environment(me) == environment(target) &&
           weapon &&
           weapon->query("skill_type") == "sword"  
            ) {
          message_vision(HIG"旁观众人只觉寒气逼人，脸上、手上被疾风刮得隐隐生疼，不由自主的后退。\n"NOR, me);
          for (i = 0; i < 3; i++) {
           if (me->is_fighting(target)) {
            if (me->query("gender") == "男性")
               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
            else
               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
          }}
          me->add("neili", -200-random(50));
          me->add("jingli", -100-random(30));
          me->add_temp("hsj_kf",1);
          call_out("kuangfeng", 2, me, target);
          return;
        }
        message_vision(HIG"$N的“狂风快剑”委实快极，一百零八招片刻间便已使完。\n"NOR, me);
        me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/10);
        me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/6);
        me->delete_temp("hsj_kf");
        me->start_busy(3+random(3));
        me->start_perform(2+random(3));
}

