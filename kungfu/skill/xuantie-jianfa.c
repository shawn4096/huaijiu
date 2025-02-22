// 玄铁剑法
// Modify By River 99.05
// Modified by darken@SJ

#include <ansi.h>;

inherit SKILL;

string  *msg = ({
"$N当胸平平刺出一剑，看似毫无变化，却有轰轰之声，$n只觉一股大力由剑身直逼周身",
"$N凌空跃起，身随剑起，借助下行之势向下猛劈一剑，将$n周身笼于剑气之下",
"$N轻叹一声，随手横劈一剑，缓缓指向$n，当真平淡中蕴涵所有变化，无招胜有招",
"$N迅疾挑出一剑，此剑之快，匪夷所思，$n惊恐之际一染、已然无法分辨剑路来去",
"$N提剑顺刺，逆击，横削，倒劈，无不是剑法的入门，当真返朴归真，已不存任何破绽",
"$N仰首长啸，令风云变幻，旋及剑气弥漫于$n周身各处，$n但觉身处惊涛骇浪之中", 
"$N祭起手中之剑，左手捏成剑诀，咄喝一声，空中满是剑影，宛若千道银链，在$n身边游动",
"$N连出十余剑，一时迅疾如流星划空，一时凝重迟缓，招招无迹可寻，平淡至极又匪思至极", 
"$N剑势如虹，无可当锋，$n惊怖中更觉剑力有如海潮一般，一波一浪阵阵涌来，绵延不绝",
"$N手中$w向前挑出，看似无甚劲力，启知剑势将老，内力却如海潮一般汹涌，向$n袭去",
"$N远远挥出一剑，$n不料气劲如此之强，防范一疏，一股大力劈头而来",
"$N深吸一口气，手中$w挟带风声，平平淡淡的挥向$n。风声越来越响，竟如同暴风之中一般",
"$N一凝神，$w居然发出淡淡的一层暗青色光芒，如狂风怒潮一边，向$n卷去",
});

string *parry_msg = ({
"$p不挡不架，手中$w向$P胸口直刺，$N眼见攻击即将得手，却不得不避开$w的锋芒。\n",
"$p算准$P攻势，一剑横在胸前，$P只得变招后退。\n",
"$p力灌剑身，猛力一击，$P的招式还未近身，便尽数震开。\n",
"$p随手一点，无招无式，只是劲力强极，$P只得弃攻转守，以求自保。\n",
"$p料敌机先，$P处处受制，没一招能够使全，如同小儿习武，手忙脚乱一般。\n",
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        int i;
        i = me->query_skill("force")/2 + random(me->query_str() + me->query_con()) + me->query("max_neili")/100;
        if( i < 100) i = 100;
        if( i > 600) i = 550+random(50);
        if(me->query_temp("xtjf_pfm")){
          return ([
                "action":HIC+msg[random(sizeof(msg))]+NOR,
                "damage":(random(2)+1)* 150,
                "dodge": random(15)-5,
                "force": i,
                "parry":35-random(20),
                "damage_type":random(2)?"刺伤":"割伤",
          ]);
        }
        return ([
                "action":msg[random(sizeof(msg))],
                "damage":(random(2)+1)* 70,
                "dodge": random(10)-5,
                "force": i - random(100) - 50,
                "parry":40 - random(20),
                "damage_type":random(2)?"刺伤":"割伤",
        ]);
}

int practice_skill(object me)
{    
        object weapon;
        int lvl;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
          return notify_fail("你使用的武器不对。\n");
        if((lvl = me->query_skill("xuantie-jianfa", 1)) < 200 )
          return notify_fail("你的玄铁剑法还不够熟练，需要在山洪中继续修炼。\n");
        if ((int)me->query("jingli") < 60+ lvl/10)
          return notify_fail("你的体力不够练玄铁剑法。\n");
        if ((int)me->query("neili") < 20+lvl/10)
          return notify_fail("你的内力不够练玄铁剑法。\n");
        if(lvl>400) lvl += random(lvl)/2;
        me->receive_damage("jingli", 20+ lvl/10);
	me->add("neili", -(10+lvl/20));
        return 1;        
}

int valid_learn(object me)
{
        if (me->query_skill("xuantie-jianfa", 1) < 200 )
          return notify_fail("玄铁剑法先期只能通过在山洪中修炼来提高技艺。\n");
          return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xuantie-jianfa/" + action;
}

