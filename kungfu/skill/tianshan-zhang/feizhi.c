//by caiji@SJ
//出处：天龙八部，第3册，975页1996年11月重印版/三联出版社出版
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
string perform_name(){ return HIC"飞掷"NOR; }
int perform(object me, object target)
{
        object weapon;
        int damage,p;
        string msg,dodge_skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        ||  !living(target))
                return notify_fail("「飞掷」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("tianshan-zhang", 1) < 100 )
                return notify_fail("你的天山杖法功力太浅，别做梦了。\n");

        if( (int)me->query_skill("staff", 1) < 100 )
                return notify_fail("你的基本杖法功力太浅，别做梦了。\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 100 )
                return notify_fail("你的内功功力太浅，别做梦了。\n");
                
        if( (int)me->query("max_neili") < 500 )
                return notify_fail("你的内力太浅，别做梦了。\n");
        if( (int)me->query("neili") < 200 )
                return notify_fail("你的真气不够，别做梦了。\n");
        if (me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你用什么为内功基础来使「飞掷」?\n");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff"
            || me->query_skill_mapped("staff") != "tianshan-zhang")
                return notify_fail("你使得了「飞掷」么?\n");
                 
        me->set_temp("tsz/feizhi", 2); 

        message_vision(BLU "\n$N大喝一声，紧接着「呼」的一声猛响，$N把手中的"+weapon->name()+"掷向$n"+BLU"。\n"NOR,me,target);

        if(   random(target->query_skill("dodge"))/2<me->query_skill("dodge")
           || random(me->query("combat_exp"))>target->query("combat_exp")/3){
           damage = 4 * (int)me->query_skill("tianshan-zhang", 1);
           damage = damage / 2 + random(damage / 2) + 5*me->query("jiali");

           me->add("neili", -damage/2);
           me->add("jingli",-100);
           if(damage>1500) damage=1300+random(200);
           target->receive_damage("qi", damage);
           target->receive_wound("qi", damage/4);
           msg = HIR"$n躲闪不及，被飞来的"+weapon->name()+"重重击中！\n"NOR;
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           target->set_temp("last_damage_from", me);
           msg += damage_msg(damage, "刺伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           msg = replace_string( msg, "$l", "胸口" );
           msg = replace_string( msg, "$w", weapon->name());
		message_vision(msg, me, target);
           if (random(target->query("kar")) < 1)
                 target->die();
           weapon->move(environment(me));
        } 
        else {
		string tmp;

              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              if (stringp(tmp = SKILL_D(dodge_skill)->query_dodge_msg(target, 1)))
		      msg += tmp;
              me->add("neili", -100);
              me->start_busy(1); 
                if( weapon->unequip())
                if( random(target->query("kar"))<10
                &&(int)target->query_encumbrance() *100 / (int)target->query_max_encumbrance()<85) {
                	weapon->move(target);
                	msg = HIY"$n伸手轻轻一接，便把飞来的"+weapon->name()+"接在手中！\n"NOR;
                }
                else if(random(target->query("kar"))<5){
                        weapon->move(environment(me));
                        msg = HIY"$n运内力于掌上，对着飞来的"+weapon->name()+"一砍，"+weapon->name()+"顿时断为两端！\n"NOR;
                        weapon->set("name", "断掉的" + weapon->name());
                        weapon->set("value", 0);
                        weapon->set("weapon_prop", 0);
                }
                else weapon->move(environment(me));
                
		message_vision(msg, me, target);
        }
        me->delete_temp("tsz/feizhi"); 
        me->start_perform(1, "「飞掷」");
        return 1;
}
