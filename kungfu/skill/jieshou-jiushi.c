// jieshou-jiushi���־�ʽ

inherit SKILL;

mapping *action = ({
([	"action" : "$N���ƽ�������ǰ̽��һ�С���ʽ�ֽ𡹣��Ʒ�ֱ����$n��$l",
	"force" : 170,
        "dodge" : 5,
	"lvl" : 0,
	"skill_name" : "��ʽ�ֽ�",
	"damage_type" : "����"
]),
([	"action" : "$N���ж�ת��һ�С�������ɽ�������ֻ��⣬����ֱ��$nǰ��",
	"force" : 230,
        "dodge" : 5,
	"lvl" : 20,
	"skill_name" : "������ɽ",
	"damage_type" : "ץ��"
]),
([	"action" : "$N���һ����һ�С�˳ˮ���ۡ������в��䣬������Ѹ�仯�ƣ�б��$n�ĺ�����",
	"force" : 380,
        "dodge" : 15,
	"lvl" : 40,
	"skill_name" : "˳ˮ����",
	"damage_type" : "����",
]),
([	"action" : "$N˫�������������룬һ�С������Ὥ����ȥ����죬��$n��$l��ȥ��",
	"force" : 220,
        "dodge" : 20,
	"lvl" : 60,
	"skill_name" : "�����Ὥ",
	"damage_type" : "����"
]),
([	"action" : "$N�������,�����Ϸ⣬������ѹ������������$n��$l",
	"force" : 250,
        "dodge" : -5,
	"lvl" : 80,
	"skill_name" : "����С��",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С�����������������ǰһ��͵�������ֻ�����ǰ����,����˳�Ʒ���$n������",
	"force" : 300,
        "dodge" : 5,
	"lvl" : 100,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([	"action" : "$N�Ų����ţ���ȻԾ��$n������,һ�С�����ãã�������ִ���$n��$l",
	"force" : 300,
        "dodge" : -10,
	"lvl" : 110,
	"skill_name" : "����ãã",
	"damage_type" : "����"
]),
([	"action" : "$N��ָ΢΢���죬һ�С���ɽ��ˮ������Ӱ������ٰ㽫$n����������",
        "force" : 350,
        "dodge" : 0,
	"lvl" : 120,
	"skill_name" : "��ɽ��ˮ",
	"damage_type" : "����"
]),
([	"action" : "$NͻȻ��ü��������̬��ɢ�����ַ��飬$n��һ���ȣ���Ȼ�е�һ����ɽ�������Ʒ�Ϯ��",
        "force" : 460,
        "dodge" : 5,
	"lvl" : 150,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���־�ʽ������֡�\n");
	if (me->query_skill_mapped("force") != "linji-zhuang")
		return notify_fail("���־�ʽ�������ټ�ׯΪ������\n");
	if ((int)me->query_skill("linji-zhuang", 1) < 120)
		return notify_fail("����ټ�ׯ����û��ã�������ѧ���־�ʽ��\n");
        	if ((int)me->query_skill("sixiang-zhang", 1) < 100)
		return notify_fail("��������Ƹ���û��ã�������ѧ���־�ʽ��\n");
	if ((int)me->query("max_neili") < 1200)
		return notify_fail("�������̫�����޷������־�ʽ��\n");
	return 1;
}

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
	level   = (int) me->query_skill("jieshou-jiushi",1);
		  for(i = sizeof(action); i > 0; i--)
			 if(level > action[i-1]["lvl"])
				return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	int lvl = me->query_skill("jieshou-jiushi", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("����������������־�ʽ��\n");
	me->receive_damage("jingli", 50);
	me->add("neili", -20);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jieshou-jiushi/" + action;
}
