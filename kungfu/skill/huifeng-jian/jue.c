#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        object weapon;
        string msg;
        int i;

        weapon = me->query_temp("weapon");

        if(!me->is_fighting() )
                return notify_fail("绝剑只能在对战斗中使用。\n");

        if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
                return notify_fail("你手中无剑，怎能运用「绝剑」心法？！\n");

        if( (int)me->query_skill("linji-zhuang",1) < 150 )
                return notify_fail("你的临济十二庄不够火候，使不出绝剑。\n");  

        if( me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("你现在不能使用「绝剑」心法。\n");

        if( (int)me->query_skill("huifeng-jian",1) < 150 )
                return notify_fail("你的回风拂柳剑不够火候，使不出绝剑。\n");  

        if( me->query_temp("huifeng/jue"))
                return notify_fail("你已经在使用了。\n");
 
        if(me->query_temp("emei/parry"))
            return notify_fail("你正在使用诸天化身步。\n");
 
        if( (int)me->query("jingli", 1) < 500 )
                return notify_fail("你现在精力不够。\n");

        if( (int)me->query("neili", 1) < 500 )
                return notify_fail("你现在内力不够。\n");

        me->start_perform(3,"「绝剑」");
        msg = HIW"$N深吸一口气，运起峨嵋临济十二庄使出「绝剑」！";
        me->add("neili", -200+random(100));
        me->add("jingli", -100);
        me->start_busy(1+random(2));
        i = me->query_skill("linji-zhuang",1) + me->query_skill("huifeng-jian", 1);
        i /= 10;
        me->add_temp("apply/parry", i);
        me->add_temp("apply/dodge", i);
        me->set_temp("huifeng/jue", i);
// 灭、绝互相配合
        if (me->query_temp("huifeng/mie"))
        {
               msg += "灭剑、绝剑互相配合，威力大增！\n"NOR;
               me->add_temp("apply/damage",i/2);
               me->add_temp("apply/defence", i/2);
               me->set_temp("huifeng/miejue",i);
        }
        else msg +="\n"NOR;
        message_vision(msg, me);
        call_out("check_fight", 1, me, weapon, i);
        call_out("remove_effect", (int)me->query_skill("linji-zhuang",1)/4, me, i);
        return 1;
}

void remove_effect(object me, int i)
{
        if (!objectp(me)) return;
        if( !me->query_temp("huifeng/jue")) return;
        me->delete_temp("huifeng/jue", 1);
        me->add_temp("apply/parry", -i);
        me->add_temp("apply/dodge", -i);
        if (me->query_temp("huifeng/miejue")){
               me->add_temp("apply/damage",-(i/2));
               me->add_temp("apply/defence", -(i/2));
               me->delete_temp("huifeng/miejue");
        }
        message_vision(HIW"$N「绝剑」运使完毕，恢复了平常的攻击。\n"NOR, me);
}

void check_fight(object me,object weapon,int i)
{
        if(!me) return;
        if(!me->query_temp("huifeng/jue")) return;
        if(!me->is_fighting()
         || me->query_skill_mapped("sword") !="huifeng-jian"
         ||! weapon
         || weapon->query("skill_type") != "sword"){
            me->delete_temp("huifeng/jue", 1);
            me->add_temp("apply/parry", -i);
            me->add_temp("apply/dodge", -i);
            if (me->query_temp("huifeng/miejue")) {
               me->add_temp("apply/damage",-(i/2));
               me->add_temp("apply/defence", -(i/2));
               me->delete_temp("huifeng/miejue");
            }
            return;
        }
        call_out("check_fight", 1, me, weapon, i);
}
