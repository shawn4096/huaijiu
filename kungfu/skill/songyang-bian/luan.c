// luan.c
// Created by Numa 2000.1.25

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int i, tmp;
        
        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("乱鞭诀只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("songyang-bian", 1) < 120 )
                return notify_fail("你的嵩阳鞭火候不够。\n");

        if( (int)me->query_skill("whip", 1) < 120 )
                return notify_fail("你的基本鞭法火候不够。\n");
        if( (int)me->query_skill("hanbing-zhenqi", 1) < 120 )
                return notify_fail("你的寒冰真气火候不够。\n");
                
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("你的内力修为不够。\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够。\n");
        if (me->query_skill_mapped("force") != "hanbing-zhenqi")
                return notify_fail("你无法使用乱鞭诀。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "whip"
         || me->query_skill_mapped("parry") != "songyang-bian"
         || me->query_skill_mapped("whip") != "songyang-bian")
                return notify_fail("你无法使用乱鞭诀。\n");

        if (me->query_temp("ss_luan"))
                return notify_fail("你正在使用乱鞭诀。\n");

        me->add("neili", -200);
        message_vision(BLU "\n$N突然脚下步伐混乱，出招呆滞，招式破绽百出，全身各大要穴均暴露无疑！\n$n一见此机，心切之下，仓促连攻几招。哪知$N此为缓招，但见手中长鞭一个倒卷，乱鞭诀随之连绵而出，其势不可挡！\n" NOR,me, target);

        tmp = (me->query_skill("songyang-bian",1) + me->query("hanbing-zhenqi",1))/15;
        tmp += random(tmp);
        me->add_temp("apply/dexerity", tmp);
        me->set_temp("ss_luan",1);
        i = me->query_skill("whip")/2;
        if (wizardp(me))
                tell_object(me,"Dexerity Add "+ tmp + "，Callout Waiting Time Is "+ i +"！\n");
        call_out("check_fight", 1, me, target, tmp, i);
        me->start_busy(2+random(3));
        return 1;
}

int check_fight(object me, object ob, int tmp, int i)
{
        object weapon;
//        int num;
//        string msg;

        if (!me)
                return 0;
        if (me->is_ghost() || !living(me) || !me->query_temp("ss_luan") || i <1)
        {
                me->add_temp("apply/dexerity", -tmp);
                call_out("remove_effect",5+random(5),me);
                return 1;
        }
        if (!me->is_fighting() || me->query("neili") <= 100)
        {
                me->add_temp("apply/dexerity", -tmp);
                message_vision(CYN"\n$N一套乱鞭诀使罢，神情若定，立于场中。\n"NOR,me);
                call_out("remove_effect",5+random(5),me);
                return 1;
        }
        if (userp(me)
        && (me->query_skill_mapped("force") != "hanbing-zhenqi"
        ||  me->query_skill_mapped("whip") != "songyang-bian"
        ||  me->query_skill_mapped("parry") != "songyang-bian"
        ||  !objectp(weapon = me->query_temp("weapon"))
        ||  weapon->query("skill_type") != "whip"))
        {
                me->add_temp("apply/dexerity", -tmp);
                message_vision(CYN"\n$N一套乱鞭诀使罢，神情若定，立于场中。\n"NOR,me);
                call_out("remove_effect",5+random(5),me);
                return 1;
        }
        if (!ob || ob->is_ghost())
        {
                me->add_temp("apply/dexerity", -tmp);
                message_vision(CYN"\n$N一套乱鞭诀使罢，神情若定，立于场中。\n"NOR,me);
                call_out("remove_effect",5+random(5),me);
                return 1;
        }

/*        
        if (me->query_skill("whip") > 200 && me->query_skill("whip") < 400)
            num = 10;
        if (me->query_skill("whip") > 400 && me->query_skill("whip") < 600)
            num = 30;
        if (me->query_skill("whip") > 600 && me->query_skill("whip") < 800)
            num = 50;
        if (me->query_skill("whip") > 800)
            num = 70;
        if (wizardp(me) && me->query("env/test"))  tell_object(me,CYN"Num为"+num+"。\n"NOR);
        if (random(me->query_skill("whip")/10)>num && random(6) > 3)
        {
                switch(random(5))
                {
                        case 0 : msg = HIY"\n$N见$n此招出势勉强，急将鞭梢一带，划向$n！\n"NOR;
                                 break;
                        case 1 : msg = HIR"\n$n此招既出，意欲收回已是不能，勉强攻出，$N早已将$w抽向$n四处要穴！\n"NOR;
                                 break;
                        case 2 : msg = HIG"\n$N见自己身形已逐渐混乱，情急之下，身体凌空飞出，$w的末梢却已扫向$n的玉堂穴！\n"NOR;
                                 break;
                        case 3 : msg = HIB"\n$N如此一来，已无退路，只有拼死一搏，念既至此，$w攻势陡然凌厉，$n已无招架之力！\n"NOR;
                                 break;
                        case 4 : msg = HIW"\n$n见$N出招已然无力，心中暗暗叫好，身形一越而出，方觉上当，但团团鞭影已使$n无处遁形！\n"NOR;
                                 break;
                }
                message_vision(msg,me,ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);
        }
*/        
        call_out("check_fight", 1, me, ob, tmp, i-1);
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("ss_luan");
}

