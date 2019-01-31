// luohan-quan.c �޺�ȭ

// ��Щ������������.........................................................
// 1234567890987654321234567890

inherit SKILL;

mapping *action = ({
([      "action" : "$N�����ϲ���һʽ����ݺ��ܡ��������ַֿ�����ȭΪ�ƣ�����$n��$l",
        "force" : 80,
        "dodge" : 3,
        "lvl" : 0,
        "skill_name" : "��ݺ���",
        "damage_type" : "����"
]),
([      "action" : "$N�����̤��ȫ����ת��һ�С����ﳯ�����������͵ز���$n��$l",
        "force" : 100,
        "dodge" : 6,
        "lvl" : 8,
        "skill_name" : "���ﳯ��",
        "damage_type" : "����"
]),
([      "action" : "$N˫�ִ󿪴��أ����߾٣�ʹһ�С����Ӷ�Ӧ����˫ȭ��$n��$l��ȥ",
        "force" : 120,
        "dodge" : 9,
        "lvl" : 15,
        "skill_name" : "���Ӷ�Ӧ",
        "damage_type" : "����"
]),
([      "action" : "$N����Ȧ���������⵱�أ����ڳ��ϣ�һ�С�ƫ�����ǡ�����$n��$l",
        "force" : 160,
        "dodge" : 12,
        "lvl" : 24,
        "skill_name" : "ƫ������",
        "damage_type" : "����"
]),
([      "action" : "$Nʹһ�С��ຣ��ͷ��������ǰ̽��˫�ֻ��˸���Ȧ������$n��$l",
        "force" : 100,
        "dodge" : 15,
        "lvl" : 33,
        "skill_name" : "�ຣ��ͷ",
        "damage_type" : "����"
]),
([      "action" : "$N˫�ƻ�����һ�ǡ�Юɽ���������Ƴ���磬һ�����е�$n��$l",
	"force" : 160,
        "dodge" : 18,
        "lvl" : 42,
        "skill_name" : "Юɽ����",
        "damage_type" : "����"
]),
([      "action" : "$Nʩ��������������˫ȭȭ����磬ͬʱ����$nͷ���أ�������Ҫ��",
    "force" : 180,
        "dodge" : 21,
        "lvl" : 50,
        "skill_name" : "������",
        "damage_type" : "����"
]),
([      "action" : "$N����ڿۣ�����������һʽ�������������˫�����밴��$n��$l",
	"force" : 210,
        "dodge" : 24,
        "lvl" : 58,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_combine(string combo) {
	if(this_player()->query_skill("wuxiang-zhi", 1) >= 200
                && this_player()->query_skill("luohan-quan",1)>=200
                && this_player()->query_con() > 45
        	&& this_player()->query_int() > 45)
		return combo=="wuxiang-zhi";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���޺�ȭ������֡�\n");
        if ((int)me->query_skill("yijin-jing", 1) < 10)
                return notify_fail("����׽�ڹ���򲻹����޷�ѧ�޺�ȭ��\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������̫�����޷����޺�ȭ��\n");
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
	mapping act;

        level   = (int) me->query_skill("luohan-quan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"]) {
			act = action[NewRandom(i, 20, level/5)];
			break;
		}
	if(level>=300)
		return ([
			"action": act["action"],
			"force": act["force"]+level-150+random(level),
			"dodge": act["dodge"]+random(level),
        		"damage_type": act["damage_type"]
		]);
	return act;
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("��������������޺�ȭ��\n");
        me->receive_damage("jingli", 25);
        me->add("neili", -10);
        return 1;
}
