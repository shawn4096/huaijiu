// meinu-quan 美女拳法
// Modify By River
// Modified by darken@SJ
#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「貂禅拜月」，右手一挥，向$n的$l绕去，掌缘在$n的$l一斩",
        "force" : 150,
        "dodge" : 30,
        "skill_name" : "貂禅拜月",
        "lvl" : 0,
        "damage_type" : "斩伤"
]),
([      "action" : "$N双拳抱胸，忽地右手使一招「西施捧心」，向$n的$l插去",
        "force" : 250,
        "dodge" : 25,
        "skill_name" : "西施捧心",
        "lvl" : 10,
        "damage_type" : "击伤"
]),
([      "action" : "$N右手五指弹起，仿似弹习琵琶一般，一招「昭君出塞」五指轮番向$n弹去", 
        "force" : 300,
        "dodge" : 20,
        "skill_name" : "昭君出塞",
        "lvl" : 20,
        "damage_type" : "搓伤"
]),
([      "action" : "$N侧身一闪，双手合拳向上抬去，一招「麻姑献寿」击向$n的$l",
        "force" : 320,
        "dodge" : 15,
        "skill_name" : "麻姑献寿",
        "lvl" : 30,
        "damage_type" : "撞伤"
]),
([      "action" : "$N施出「天女织梭」，右手挥左，做投梭织布之状，一挥一送，击向$n的$l",
        "force" : 370,
        "dodge" : 10,
        "skill_name" : "天女织梭",
        "lvl" : 50,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N施出「则天垂帘」，身子前扑，双掌以垂帘之势削将下来，斩向$n的$l",
        "force" : 150,
        "dodge" : 30,
        "skill_name" : "则天垂帘",
        "lvl" : 70,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N脸露微笑，伸手往头上一梳，手指如「丽华梳妆」，软软挥将出去，拍向$n的$l",
        "force" : 250,
        "dodge" : 25,
        "skill_name" : "丽华梳妆",
        "lvl" : 90,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双手互拍，闪电般击出，俨然一招「红玉击鼓」，轮番击向$n$l",
        "force" : 300,
        "dodge" : 20,
        "skill_name" : "红玉击鼓",
        "lvl" : 110,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N一招「弄玉吹箫」，一指擎天，一指对地，闭目垂首，忽手腿齐出，攻向$n的$l",
        "force" : 400,
        "dodge" : 5,
        "skill_name" : "弄玉吹箫",
        "lvl" : 120,
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("空手方能练习美女拳法。\n");
        if ((int)me->query_skill("yunu-xinjing", 1) < 10)
                return notify_fail("玉女心经领悟不够，无法修习美女拳法。\n");
        if ((int)me->query_skill("dodge", 1) < 20)
                return notify_fail("你的轻功太差，无法练美女拳法。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon,object ob)
{
        int i, j, level;
        level = (int) me->query_skill("meinu-quanfa",1);         
        for(i = sizeof(action); i > 0; i--) {
           if(level > action[i-1]["lvl"]) {
              j = NewRandom(i, 20, level/5);
                  return ([
                     "action" : action[j]["action"],
                     "force" : me->query("gender")=="女性"?action[j]["force"]*5/4:action[j]["force"],
                     "dodge": me->query("gender")=="女性"?action[j]["dodge"]+30+random(10):action[j]["dodge"],
                     "parry": me->query("gender")=="女性"?action[j]["dodge"]+30+random(10):action[j]["dodge"],
                     "lvl" : action[j]["lvl"],
                     "damage_type" : action[j]["damage_type"],
                  ]);
           }
        }
}

string perform_action_file(string action)
{
        return __DIR__"meinu-quanfa/" + action;
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 30)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练美女拳法了。\n");
        me->receive_damage("jingli", 25);
        me->add("neili", -5);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	// 这个hit_ob显然不对头，可以连续不停的出，连续不停的降对方的防御
	// olives@SJ 4/30/2001
        int extra,level;
        if ( damage_bonus < 300 ) return 0;
        extra = (me->query("gender") == "女性"? 2:1);
        level= (int) me->query_skill("meinu-quanfa",1);
        
        if(me->query("per") > 24 
        && random(10) > 5
        && random(level) > 200// 大概是random(level)>200
        && random(me->query("combat_exp")) > victim->query("combat_exp")/2
        && me->query("neili") > 500 
        && !victim->is_busy())
        {
           message_vision(MAG"\n$N悄退数步，右手支颐，左手轻轻挥出，长叹一声，脸现寂寥之意。\n"NOR,me);
          if( random(me->query_per()*extra) > victim->query_per()/2
           && me->query("gender") != victim->query("gender"))
           {             
//             victim->add_temp("apply/attack", -level);
//             victim->add_temp("apply/defense", -level);
//             victim->add_temp("apply/dodge", -level);
//             victim->set_temp("yunu/beauty", level);
             me->add("neili", -50);
             victim->start_busy(1+random(2));
             message_vision(CYN"\n$n不由得呆了，用充满爱慕的的眼光看着$N。\n\n"NOR,me,victim);
//             call_out("reset_temp", beauty, me, victim);
         }
        }
        return;
}

int help(object me)
{
        write(WHT"\n美女拳法："NOR"\n\n");
        write(@HELP
武功名称：
        美女拳法(meinu-quanfa)
             
特殊攻击：   
        摄心绝技(perform shexin)。
        
要求：
        美女拳法>300;
        最大内力>5000;
        如果对手是无性之人，或者和自己同为女性，则无法使用摄心绝技。
        男弟子和公公无法使用。
HELP
        );
        return 1;
}

