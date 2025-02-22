// yuxue-dunxing.c 御雪遁形
// by iceland

inherit SKILL;

mapping *action = ({
([      "action" : "$n一招「雁独行」，双臂平伸，借势一个空心筋斗向后倒翻出去。\n",
        "dodge" : 15,
]),
([      "action" : "$n见状曲膝俯身以手撑地，使出一招「鱼潜」，双足一点，箭一般从$N腋下蹿了过去。\n",
        "dodge" : 30,
]),
([      "action" : "$n平地带起一阵旋风，一招「狸翻」，跃起在空中几个横滚，$N的招数被化于无形。\n",
        "dodge" : 45,
]),
([      "action" : "$n斜斜的倒退几步，突然探手在$N肩上一按，使出一招「鹰千里」，已经从$N头顶越过。\n",
        "dodge" : 60,
]),
([      "action" : "$n使出一招「蛇游」，身体左摇右摆，飘忽不定，脚下毫无章法，$N的招数却差之毫厘，一一落空。\n",
        "dodge" : 75,
]),
([      "action" : "$n纵声清啸，双掌在地下一拍，气流激动之下，一招「龙巡」冲天而起。\n",
        "dodge" : 90,
]),
});


mapping query_action(object me, object weapon)
{
	int zhaoshu, level;

	zhaoshu = sizeof(action);
	level   = (int) me->query_skill("yuxue-dunxing");

	if (level < 50 )
		zhaoshu--;

	if (level < 40 )
		zhaoshu--;

	if (level < 30 )
		zhaoshu--;

	return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
	return usage == "dodge";
}

int valid_learn(object me)
{
	return 1;
}

string query_dodge_msg(object me)
{
	object ob;
	mapping action;

	action = query_action(me, ob);

	return action["action"];
}

int practice_skill(object me)
{
	if( (int)me->query("jingli") < 40 )
		return notify_fail("你的体力太差了，不能练习御雪遁形。\n");
	me->receive_damage("jingli", 25);
	return 1;
}
