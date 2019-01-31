// tianwang-zhua.c �������צ
//  by iceland
inherit SKILL;

mapping *action = ({
([	"action" : "$N����̽��һʽ�����ơ�����������ǰ��צ�黤����צֱ̽$n������",
	"force" : 200,
        "dodge" : -5,
        "parry" : 10,
	"lvl" : 0,
	"skills_name" : "����",
	"damage_type" : "ץ��"
]),
([	"action" : "$Nһʽ����ơ���������������׷�����б������$n��࣬���ֿ���$n����",
	"force" : 240,
        "dodge" : 0,
        "parry" : -5,
	"lvl" : 10,
	"skills_name" : "���",
        "damage_type" : "ץ��"
]),
([	"action" : "$N�੹�Х���������ǣ�һʽ�����������ڽ�$n���У�˫צ���ۣ�����$n",
	"force" : 280,
        "dodge" : 10,
        "parry" : 10,
	"lvl" : 20,
	"skills_name" : "����",
        "damage_type" : "����"
]),
([	"action" : "$N�ڿ�Ծ��ʹһʽ�����֡���˫צǰ�󽻴������һץ����һץ���Ƶ�$n��������",
	"force" : 320,
        "dodge" : 5,
        "parry" : 0,
	"lvl" : 30,
	"skills_name" : "����",
        "damage_type" : "ץ��"
]),
([	"action" : "$N˫Ŀ������գ����������дʣ�һʽ��ײ�ӡ������ִ�������֮�ϣ���צ��˫��֮��ֱ����$n��$l",
	"force" : 360,
        "dodge" : -10,
        "parry" : 5,
	"lvl" : 50,
	"skills_name" : "ײ��",
        "damage_type" : "����"
]),
([	"action" : "$N����������һʽ�����㡹��˫צ����ǰ�鰴���ó�����צӰ��ָ�������ƿ�˿˿���죬ңң����$nȫ��",
	"force" : 400,
        "dodge" : 15,
        "parry" : -10,
	"lvl" : 70,
	"skills_name" : "����",
        "damage_type" : "ץ��"
])
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }

//int valid_combine(string combo) { return combo=="dashou-yin"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���������צ������֡�\n");
	if ((int)me->query_skill("longxiang-boruo", 1) < 30)
		return notify_fail("��������������򲻹�������ѧ�������צ��\n");
	if ((int)me->query_skill("force", 1) < 30)
		return notify_fail("��Ļ����ڹ���򲻹�������ѧ�������צ��\n");
	if ((int)me->query("max_neili") < 150)
		return notify_fail("�������̫���������˽������צ��\n");
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
	level   = (int) me->query_skill("tianwang-zhua",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("��������������������צ��\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -10);
	return 1;
}
 
