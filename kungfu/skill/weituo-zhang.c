// weituo-zhang.c Τ����

inherit SKILL;

mapping *action = ({
([	"action" : "$N˫��΢��������΢΢������˫�����ƣ�һ�С�����ٵء���һ����ɽ֮��ѹ��$n",
	"force" : 170,
        "parry" : 5,
	"lvl" : 0,
	"skill_name" : "����ٵ�",
	"damage_type" : "����"
]),
([	"action" : "$N���а����ӷ�һ�С��������ա������ƻ���$n���ţ���һ��ȴ����$n��С��",
	"force" : 200,
        "parry" : 10,
	"lvl" : 15,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N˫�ƻ������Ī�⣬һ�С�������ɫ����˲Ϣ֮����$n����������һʮ����",
	"force" : 230,
        "parry" : 15,
	"lvl" : 30,
	"skill_name" : "������ɫ",
	"damage_type" : "����",
]),
([	"action" : "$N����һ�ƣ�û�а�����ף�һ�С����ޱߡ����͵���$n��$l�����ȥ",
	"force" : 260,                                    
        "parry" : 20,
	"lvl" : 40,
	"skill_name" : "���ޱ�",
	"damage_type" : "����"
]),
([	"action" : "$N˫�ƽ����������ޣ�һ�С�˭������������ž�������$n�ļ�ͷ��ǰ��",
	"force" : 310,
        "parry" : 25,
	"lvl" : 50,
	"skill_name" : "˭�����",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С�����������������һ�ƻ�����������������һ�����$n��$l",
    "force" : 340,
        "parry" : 30,
	"lvl" : 60,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N˫���ڿ����뻮������˫�����ƣ�һ�С��ҷ�ȱ�����һ����ɽ������������ֱ��$n����",
    "force" : 380,
        "parry" : 35,
	"lvl" : 70,
	"skill_name" : "�ҷ�ȱ�",
	"damage_type" : "����"
]),
([	"action" : "$NͻȻ���м�ת��һ�С��ຣ��ͷ������Ӱ���裬��ʱ֮�佫$n����˷�����ס��",
    "force" : 410,
        "parry" : 40,
	"lvl" : 80,
	"skill_name" : "�ຣ��ͷ",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_combine(string combo) { return combo=="luohan-quan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��Τ���Ʊ�����֡�\n");
	if ((int)me->query_skill("yijin-jing", 1) < 10)
		return notify_fail("����׽�ڹ���򲻹����޷���Τ���ơ�\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷���Τ���ơ�\n");
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
	level   = (int) me->query_skill("weituo-zhang",1);
		  for(i = sizeof(action); i > 0; i--)
		  if(level > action[i-1]["lvl"])
		  return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("�������������Τ���ơ�\n");
	me->receive_damage("jingli", 25);
	me->add("neili", -10);
	return 1;
  }

