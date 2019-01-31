// dashou-yin.c ���ڴ���ӡ
//  by iceland

inherit SKILL;

mapping *action = ({
([      "action" : "$Nʹ��һ�С���������ӡ����˫�ƺ�ʮ��ֱֱײ��$n��ǰ��",
        "skill_name" : "��������ӡ",
        "force" : 100,
        "dodge" : 0,
        "parry" : 0,
        "lvl" : 0,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����ƹ���ӡ��������Ծ��˫���繴��ץ��$n��$l",
        "skill_name" : "���ƹ���ӡ",
        "force" : 150,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 8,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С�׼���ĸӡ����������ָ��ֱȡ$n��$l",
        "skill_name" : "׼���ĸӡ",
        "force" : 210,
        "dodge" : 15,
        "parry" : -5,
        "lvl" : 16,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С���������ӡ����ŭ��һ����һ�Ƶ�ͷ����$n��$l",
        "skill_name" : "��������ӡ",
        "force" : 260,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 24,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С�ҩʦ�����ӡ�����ͳ���ǰ�����������㹥��$n",
        "skill_name" : "ҩʦ�����ӡ",
        "force" : 300,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 32,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����½��ӡ������������˫������ɨ��$n��$l",
        "skill_name" : "���½��ӡ",
        "force" : 340,
        "dodge" : 8,
        "parry" : 0,
        "lvl" : 40,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����ֽ��ӡ���������Ծ��˫��ǰ�������ץ��$n���ʺ�",
        "skill_name" : "���ֽ��ӡ",
        "force" : 390,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 48,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С������ǻ�ӡ������ʱ��������������г���������Ӱ����$n��$l",
        "skill_name" : "�����ǻ�ӡ",
        "force" : 450,
        "dodge" : 5,
        "lvl" : 56,
        "damage_type" : "����",
]),
});


int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

//int valid_combine(string combo) { return combo=="tianwang-zhua"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����ڴ���ӡ������֡�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫���ˣ����������ڴ���ӡ��\n");
	if ((int)me->query_skill("longxiang-boruo", 1) < 20)
		return notify_fail("���������������̫ǳ������ѧ���ڴ���ӡ��\n");
	if ((int)me->query_skill("force", 1) < 20)
		return notify_fail("��Ļ����ڹ����̫ǳ������ѧ���ڴ���ӡ��\n");
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
        level   = (int) me->query_skill("dashou-yin",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
//	object weapon;

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����ڴ���ӡ������֡�\n");
	if ((int)me->query("jingli") < 40)
		return notify_fail("����������������������ڴ���ӡ��\n");
	me->receive_damage("jingli", 20);
        me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"dashou-yin/" + action;
}


