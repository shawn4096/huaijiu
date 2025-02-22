// tougu.c 透骨针
// by snowman
// Modify By River@SJ 增加有9阳后的效果 2000.2.22
#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int exert(object me, object target)
{        
        object weapon;
        int damage,p,force;
        string msg, *limbs;
        weapon = me->query_temp("weapon");

        if( !target) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("透骨针只能在战斗中对对手使用。\n");

        if(!weapon)
                return notify_fail("你必须使用武器来传递透骨针内劲！\n");        

        if( (int)me->query_skill("jiuyang-shengong",1) < 100 )
                return notify_fail("你的九阳神功等级不够，不能施展透骨针内劲！\n");

        if( (int)me->query_skill("force", 1) < 100 )
                return notify_fail("你的基本内功等级不够，不能施展透骨针内劲！\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不足，不能施展透骨针内劲！\n");

        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力不足，不能施展透骨针内劲！\n");

        if( (int)me->query("jingli") < 300 )
                return notify_fail("你的精力不足，不能施展透骨针内劲！\n");

        if( target->is_busy()) 
                 return notify_fail("对方正自顾不暇呢，你不忙施展透骨针内劲！\n");

        me->start_exert(3, "透骨针");  
        me->start_perform(3, "透骨针");

        force = me->query_skill("force") + me->query_skill("jiuyang-shengong", 1)/10;
        tell_object(me,HIW"你悄悄运起"HIB"透骨针"HIW"，将一股极阴寒的内力积贮于一点，从"+weapon->name()+"上传出，直刺"+target->name()+"！\n"NOR);
        if(random(force) > target->query_skill("force")/2){
           damage = force;
           damage += random(damage);
           if(target->query_skill("force") - 50 > force)
             damage = damage/2;
           if(target->query_skill("force") > (force)*2)
              damage = random(10);
           if((force) > target->query_skill("force")*2)
              damage = damage+random(damage);
             if (damage > 1500) damage = 1500;
           if(damage > 300)
              tell_object(target, HIB"\n突然之间，你胸口一痛，似乎被一枚极细的尖针刺了一下。这一下刺痛\n"+
                                     "突如其来，似有形，实无质，一股寒气突破你的护体神功，直钻入心肺！\n"NOR);
              else if(damage <= 10){
                damage = 10;
                tell_object(target, HIY"\n突然之间，你胸口一痛，似乎被一枚极细的尖针刺了一下。幸好你护体神功遍\n"+
                                       "护全身，这阴劲虽是凝聚如丝发之细，倏钻陡戳，难防难当，却也伤你不得！\n"NOR);
                tell_object(me, HIY"你连运“透骨针”的内劲，但见对方竟是毫不费力的抵挡了下来！\n"NOR);
              }
           else tell_object(target, HIB"\n突然之间，你胸口被尖针刺了一下。刺痛似有形，实无质，一股寒气突破你的\n"+
                                       "护体神功，直侵内脏！阴劲入体，立即消失，但这一刺可当真疼痛入骨！\n"NOR);
           target->receive_damage("qi", damage, me);
           target->receive_wound("qi", damage/3, me);
           me->receive_damage("neili", damage/3);
           limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"突然全身一颤，如同被尖针刺了一下！\n" NOR, ({ target }));  
           msg = damage_msg(damage, "内伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           message_vision(msg, me, target);
           me->start_busy(1);
           me->add("jingli", -20);
           target->start_busy(2+random(4));
           return 1;
        }        
        else {
           me->add("neili", -50);
           me->add("jingli", -5);
           tell_object(me, HIY"结果透骨针内劲还没触到"+target->name()+"便已经散了。\n"NOR);
           me->start_busy(2);         
        }
        return 1;
}
