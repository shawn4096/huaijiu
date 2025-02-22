// yinfeng.c 阴风刀
// by snowman
// Modify By River@SJ 增加有9阳后的效果 2000.2.22
#include <ansi.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int exert(object me, object target)
{        
        object weapon;
            int damage, p, force, lvl;
        string msg;
        weapon = me->query_temp("weapon");

        if( !objectp(target)) target = offensive_target(me);
        if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("阴风刀只能在战斗中对对手使用。\n");   
       
        if (me->query_skill_mapped("dagger") != "shenghuo-lingfa")
                return notify_fail("你必须先将圣火令法功和圣火神功相互配合。\n");

        if(!weapon)
                return notify_fail("你必须使用武器来传递阴风刀内劲！\n");   

        if( weapon->query("skill_type") != "dagger" )
                return notify_fail("你必须使用匕法传递阴风刀内劲！\n");     

        if( (int)me->query_skill("shenghuo-shengong",1) < 130 )
                return notify_fail("你的圣火神功等级不够，不能施展阴风刀内劲！\n");

        if( (int)me->query_skill("shenghuo-lingfa",1) < 130 )
                return notify_fail("你的圣火令法等级不够，不能施展阴风刀内劲！\n");

        if( (int)me->query_skill("force", 1) < 130 )
                return notify_fail("你的基本内功等级不够，不能施展阴风刀内劲！\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不足，不能施展阴风刀内劲！\n");

        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("你的内力不足，不能施展阴风刀内劲！\n");

        if( (int)me->query("jingli") < 300 )
                return notify_fail("你的精力不足，不能施展阴风刀内劲！\n");

        me->start_exert(4, "阴风刀");
        me->start_perform(4, "阴风刀"); 

        force = me->query_skill("force") + me->query_skill("jiuyang-shengong", 1)/10;
        lvl = me->query_skill("jiuyang-shengong", 1);

        tell_object(me, HIW"\n你悄悄使出"BLU"阴风刀"HIW"，运起一股无形无质的阴寒之气，直插"+target->name()+"胸口玉堂要穴！\n"NOR); 

   if( random(force)*(me->query_temp("yinfeng/time")+1) > target->query_skill("force")/2
         && me->query("combat_exp")/2 *(me->query_temp("yinfeng/time")+1) > random(target->query("combat_exp")/2)){

                me->delete_temp("yinfeng/time");
                damage = force;
                damage += random(damage);                
               
                if(target->query_skill("force")-100 > force)
                           damage /= 2;                  
                if(target->query_skill("force") > force * 2)
                           damage = random(50);
                if( force > target->query_skill("force")*2)
                           damage *= 2;
                if(me->query("neili")+ lvl*2 > target->query("neili")*2)
                           damage *= 2;
                else
                 if(me->query("neili")+ lvl*2 > target->query("neili"))
                           damage += random(damage/2);
                else
                 if(target->query("neili") > me->query("neili")*2 + lvl*4)
                           damage /= 2;
                               
                if(target->query("combat_exp") > me->query("combat_exp")*2 + lvl* 2000 )
                           damage /=2;
                   
                else
                 if(me->query("combat_exp")+ lvl* 1000 > target->query("combat_exp")*2)
                           damage *= 2; 
                          
                else
                 if((me->query("combat_exp")+ lvl)/3*2 > target->query("combat_exp"))
                           damage += random(damage/2); 
                damage += (me->query_skill("jiuyang-shengong")+random(me->query_skill("jiuyang-shengong",1)));

                if (damage > 2000) damage = 2000 +(damage - 2000)/100;

                if (damage > 1500){
                           tell_object(target, HIB"\n突然之间，一股无形无质、利如钢刃的阴寒之气直插入你胸口的“玉堂穴”中！\n"+
                                               HIR"你霎时之间闭气窒息，全身动弹不得！\n"NOR);
                           target->start_busy(3+random(2));
                }
                else if(damage <= 50){
                           damage = 10;
                           tell_object(target, HIY"\n突然之间，一股利如钢刃般的阴寒之气直插你胸口的玉堂穴！\n"+
                                                  "幸好你护体神功遍护全身，这股阴风刀虽利，却也伤你不得！\n"NOR);
                           tell_object(me, HIY"你连运阴风刀的内劲，但见对方竟是毫不费力的抵挡了下来！\n"NOR);
                }
                else{
                           tell_object(target, HIB"\n突然之间，一股阴劲如刀、如剑、如匕、如凿，直插入你胸口的“玉堂穴”中！\n"+
                                               HIR"你霎时之间闭气窒息，全身冰冷！\n"NOR);
                           target->receive_wound("qi", damage/6, me);
                           target->start_busy(1+random(2));
                }
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                target->receive_damage("neili", damage/3, me); 
           
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                tell_room(environment(target), HIR + target->name()+"突然全身猛地一震，面如金纸，震退了数步，彷佛被什么人在胸口处猛击了一下似的！\n" NOR, ({ target })); 
                msg = damage_msg(damage, "内伤");
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
                message_vision(msg, me, target);          
//                if(!target->is_killing(me->query("id"))) target->kill_ob(me);
                me->start_busy(random(2));
                me->receive_damage("neili", -damage/3);
                me->receive_damage("jingli", 70);
                }
         
        else {       
                me->add_temp("yinfeng/time",1);
                if(me->query_temp("yinfeng/time")>3) me->set_temp("yinfeng/time",3);
                me->receive_damage("neili", 100);
                me->receive_damage("jingli", 15);
                tell_object(me, HIY"结果阴风刀内劲还没触到"+target->name()+"的身体便已经散了。\n"NOR);
                me->start_busy(2); 
        }
        return 1;
}
