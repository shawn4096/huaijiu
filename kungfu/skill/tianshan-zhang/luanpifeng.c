#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

string perform_name(){ return HIC"乱劈风"NOR; }

int perform(object me, object target)
{
        object weapon;
        int skill,improve;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「乱劈风」只能对战斗中的对手使用。\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "staff" )
                return notify_fail("你手中无杖，怎能运用「乱劈风」？！\n");

        if( me->query_temp("xx_luanpifeng"))
                return notify_fail("你刚使完「乱劈风」，目前气血翻涌，无法再次运用！\n");

        if((int)me->query_skill("tianshan-zhang", 1) < 180
         ||(int)me->query_skill("staff", 1) < 180
         ||(int)me->query_str() <=30 )
                return notify_fail("你修为还不够，还未能领悟「乱劈风」！\n");

        if( me->query_skill("huagong-dafa", 1) < 180 )
                return notify_fail("你的内功修为火候未到，施展只会伤及自身！\n");

        if( me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你所用的内功与「化功大法」心法相悖！\n");

        if (me->query_skill_mapped("staff") != "tianshan-zhang"
         || me->query_skill_mapped("parry") != "tianshan-zhang")
                return notify_fail("你现在无法使用「乱劈风」进行攻击。\n");

        if( me->query("max_neili") <= 2000 )
                return notify_fail("你的内力修为不足，劲力不足以施展「乱劈风」！\n");

        if( me->query("neili") <= 600 )
                return notify_fail("你的内力不够，劲力不足以施展「乱劈风」！\n");

        if( me->query("jingli") <= 200 )
                return notify_fail("你的精力有限，不足以施展「乱劈风」！\n");

        message_vision(HIB"\n$N突然将"+weapon->name()+HIB"胡乱挥舞，更将阴狠内功注入手中所用武器中，一时攻击大增!\n" NOR, me);

        if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
           if(weapon->query("rigidity")<10)
                weapon->add("rigidity", 1);
        }
        skill = me->query_skill("staff");
      	improve = skill/5 + random(skill/5);
      	if ( improve > 100 ) improve = 100 + random(improve-100) / 5;

        me->set_temp("xx_luanpifeng", improve);
        me->add_temp("apply/damage", improve);
        me->add_temp("apply/staff", improve);
        me->add_temp("apply/strength", improve);
        call_out("remove_effect", 1,  me, weapon, skill);
        me->start_perform(5, "「乱劈风」");
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(! me->is_fighting()
         || !weapon
         || me->query_skill_mapped("staff") != "tianshan-zhang"
         || me->query_skill_mapped("parry") != "tianshan-zhang"
         || count < 1 ){
          i = me->query_temp("xx_luanpifeng");
          me->add_temp("apply/staff", -i);
          me->add_temp("apply/damage", -i);
          me->add_temp("apply/strength", -i);
          me->delete_temp("xx_luanpifeng");
	if (weapon)
		message_vision(HIB"\n$N体力不支，手中"NOR+weapon->name()+HIB"逐渐慢了下来。\n"NOR, me);
          return;
        }
        else {
          me->start_perform(1,"「乱劈风」");
          call_out("remove_effect", 1, me, weapon, count -1);
        }
}

int help(object me)
{
        write(
@HELP
乱劈风
       是星宿派－－天山杖法的特殊攻击，将一身阴狠内功注入手中所用钢杖中，
       看似胡乱挥舞，钢杖羚羊挂角,无迹可寻，攻击大增。
       使用要求：天山杖法、化功大法180等级、激发杖法、招架为天山杖法。
HELP
        );
        return 1;
}
