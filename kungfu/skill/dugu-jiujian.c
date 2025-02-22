// dugu-jiujian.c 独孤九剑

inherit SKILL;
#include <ansi.h>
#include <combat.h>

#include <combat_msg.h>

string *dodge_msg = ({
        "却见$N踏前一步，剑式斜指$n的右臂，想要使$n闪身而退。\n",
        "$n以攻为守，以进为退，凝神运气向$N猛攻快打地挥出方位大异的泰山「快活三」三剑。\n",
        "$n剑法突变，剑势伸缩不定，奔腾矫夭，逆使嵩山剑法的「天外玉龙」企图迫使$N变招。\n",
        "$n不闪不避，举剑闪电般使出「叠翠浮青」反削$N，想挡过$N此招。\n",
        "$n突然使出青城派松风剑法的「鸿飞冥冥」，可是方位却有所偏差，长剑对着$N一绞，企图突破$N的攻势。\n"
        "$n挺剑一招象是「白云出岫」回刺$N，企图将$N的攻势化解。\n",
        "只见$n不退反进，身如飘风，诡异地一式「天柱云气」，动向无定不可捉摸地挡住了$N的进攻。\n",
        "$n不退反进，使出恒山剑招「绵里藏针」，森森剑气充溢四周！架开了$N的这招。\n",
});

mapping *action = ({
([
        "action" :"$N满场游走，东刺一剑，西刺一剑，令$n莫明其妙，分不出$N剑法的虚实" ,
        "force" : 190,
        "dodge" : 30,
        "parry" : 40,
        "damage": 80,
        "lvl" : 0,
        "damage_type" : "刺伤"
]),
([
        "action" :"$N突然一剑点向$n的$l，虽一剑却暗藏无数后着，$n手足无措，不知如何是好",
        "force" : 210,
        "dodge" : 30,
        "parry" : 25,
        "damage": 100,
        "lvl" : 20,
        "damage_type" : "刺伤"
]),
([      "action" : "$N反手横剑刺向$n的$l，这似有招似无招的一剑，威力竟然奇大，$n难以看清剑招来势",
        "force" : 230,
        "dodge" : 40,
        "parry" : 40,
        "damage": 100,
        "lvl" : 40,
        "damage_type" : "刺伤"
]),
([      "action" : "$N随手一剑指向$n，落点正是$n的破绽所在，端的是神妙无伦，不可思议",
        "force" : 250,
        "dodge" : 50,
        "parry" : 40,
        "damage": 120,
        "lvl" : 60,
        "damage_type" : "刺伤"
]),
([      "action" : "$N将$w随手一摆，但见$n自己向$w撞将上来，神剑之威，实人所难测",
        "force" : 270,
        "dodge" : 60,
        "parry" : 40,
        "damage": 140,
        "lvl" : 80,
        "damage_type" : "刺伤"
]),
([      "action" : "$N抱剑旋身，转到$n身后，杂乱无章地向$n刺出一剑，不知使的是什么剑法",
        "force" : 290,
        "dodge" : 50,
        "parry" : 35,
        "damage": 160,
        "lvl" : 100,
        "damage_type" : "刺伤"
]),
([      "action" : "$N剑挟刀势，大开大阖地乱砍一通，但招招皆击在$n攻势的破绽，迫得$n不得不守",
        "force" : 310,
        "dodge" : 50,
        "parry" : 40,
        "damage": 180,
        "lvl" : 120,
        "damage_type" : "刺伤"
]),
([      "action" : "$N举剑狂挥，迅速无比地点向$n的$l，却令人看不出其所用是什么招式",
        "force" : 330,
        "dodge" : 55,
        "parry" : 30,
        "damage": 200,
        "lvl" : 140,
        "damage_type" : "刺伤"
]),
([      "action" : "$N脸上突现笑容，似乎已看破$n的武功招式，胸有成竹地一剑刺向$n的$l",
        "force" : 350,
        "dodge" : 60,
        "parry" : 40,
        "damage": 220,
        "lvl" : 160,
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage)
{
	return (usage == "sword") || (usage == "parry") || (usage =="dodge");
}

int valid_learn(object me)
{
	mapping my_fam  = me->query("family");
	if(!my_fam || my_fam["master_name"] != "风清扬")
		return notify_fail("你不是风清扬的弟子，不能学习「独孤九剑」。\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_skill("dugu-jiujian",1) > 60)
		return notify_fail("这套剑法我就教到这儿，以后就要靠你自己去领悟了。\n");
	return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
//	victim->set_temp("must_be_hit", 1);
	victim->add_temp("lost_attack", random(3));
	call_out("remove_eff", me->query_skill("sword")/10, victim);
}

void remove_eff(object victim)
{
	if (!victim) return;
	victim->delete_temp("must_be_hit");
}

mapping query_action(object me,object weapon)
{
	int i, level;

	level = (int)me->query_skill("dugu-jiujian", 1);
	for(i = sizeof(action); i > 0; i--)
	if(level > action[i-1]["lvl"])
		return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	return notify_fail("独孤九剑只能通过领悟来提高。\n");
}

string perform_action_file(string action)
{
	return __DIR__"dugu-jiujian/" + action;
}
