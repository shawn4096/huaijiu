// jinyan-gong.c ���㹦

inherit SKILL;

mapping *action = ({
([	"action" : "$n΢һ����������ǰһ�ݣ�һʽ�������Ϸɡ������赭д�ض��$N��һ����\n",
	"lvl" : 0,
 	"skill_name" : "�����Ϸ�",
	"dodge"  : 15
]),
([	"action" : "$nһʽ����ȥ�޺ۡ����������ƮȻ���ˣ�$Nһ�����У�$n����������֮�⡣\n",
	"lvl" : 5,
	"skill_name" : "��ȥ�޺�",
	"dodge"  : 25
]),
([	"action" : "$n�鲽ǰ�磬�Ų����Ƿ�λ������������⣬һ�С���ת���ơ���Ȼ�Ƶ�$N���\n",
	"lvl" : 10,
	"skill_name" : "��ת����",
	"dodge"  : 35
]),
([	"action" : "$n΢΢һЦ���㲻�������ڣ�һʽ������̫�项�����̰�ȽȽ���𣬻���$N��ࡣ\n",
	"lvl" : 20,
	"skill_name" : "����̫��",
	"dodge"  : 45
]),
([	"action" : "$n����ͻ�䣬ʹ����Ⱥ�ǲ��á���Χ��$N�Ĵ����߶�ʱ�û���������Ӱ��$NĿ���۴���֪����δ���\n",
	"lvl" : 30,
	"skill_name" : "Ⱥ�ǲ���",
	"dodge"  : 55
]),
([	"action" : "$nһʽ�������ë��������Ʈ���벻��������һƬ��ë���������������$N��籩���Ĺ��ơ�\n",
	"lvl" : 40,
	"skill_name" : "�����ë",
	"dodge"  : 65
]),
([	"action" : "$n���������ݰ㼱����ת������һ�С���ճ�������$N�Ĺ���ͳͳ���⡣\n",
	"lvl" : 55,
 	"skill_name" : "��ճ���",
	"dodge"  : 75
]),
([	"action" : "$nһʽ����Ӱ���С�������ƮƮ������$N�����ƶ�������$N��֮��$n��ƮȻ������\n",
	"lvl" : 80,
	"skill_name" : "��Ӱ����",
	"dodge"  : 85
]),
([	"action" : "$nʹ���������ݡ����嶷Ȼ����Խ��Խ�ߣ�����΢һת����������֮�⣬��$N�Ĺ��ƾ����������Σ�\n",
	"lvl" : 99,
	"skill_name" : "������",
	"dodge"  : 99
])

});


string query_skill_name(int level)
{
	int i;

	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;

	level   = (int) me->query_skill("jinyan-gong",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) 
			return action[NewRandom(i, 20, level/5)];
}

int valid_enable(string usage)
{
	return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
	return 1;
}

string query_dodge_msg(object me)
{
	int i, level;

	level   = (int) me->query_skill("jinyan-gong",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) 
			return action[NewRandom(i, 20, level/5)]["action"];
}

int practice_skill(object me)
{
	int lvl = me->query_skill("jinyan-gong", 1);
	int i = sizeof(action);
	mapping learned = me->query_learned();

	if (!mapp(learned)) learned = ([]);
	if (!learned["jinyan-gong"])
		while (i--) 
			if (lvl == action[i]["lvl"])
				return notify_fail("�㽫�Ѿ�ѧ���������ʽ��ϰ��һ�飬���������ȥ��ʦ��ѧ�µ���ʽ���޷���ý����ˡ�\n");;

	if( (int)me->query("jingli") < 40 )
		return notify_fail("��ľ���̫���ˣ�����������㹦����\n");
	me->receive_damage("jingli", 30);
	return 1;
}
