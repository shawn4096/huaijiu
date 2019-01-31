// lianhua-zhang.c ������
// By Looklove 2000/10/18

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([	"action" : "$N���﷢�����������һʽ������������˫�Ʋ���ƽƽ����$n����",
	"force" : 100,
	"parry" : 2,
        "dodge" : 5,
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "��������"
]),
([	"action" : "$N��¶΢Ц��һ�С��ص���ɡ���������һ�ڣ����ƻ���һ������Ļ��ߣ�ֱ��$n����",
	"force" : 150,
        "dodge" : 5,
	"parry" : 5,
        "damage_type" : "����",
	"lvl" : 10,
	"skill_name" : "�ص����"
]),
([	"action" : "$Nʹ����˫�����ޡ���$nȦ���Ʒ�֮�ڣ�$nֻ�����ۻ����ҷֲ���������ʵ��������",
	"force" : 200,
        "dodge" : 5,
	"parry" : -5,
        "damage_type" : "����",
	"lvl" : 20,
	"skill_name" : "˫������"
]),
([	"action" : "$N���ڿ��У�һʽ�����������˫�ƿ��������������",
	"force" : 250,
        "dodge" : 5,
	"parry" : 10,
        "damage_type" : "����",
	"lvl" : 30,
	"skill_name" : "�������"
]),
([	"action" : "$Nʹһʽ����ź���������ƻ��أ���������ǰһ�Σ�ͻ�ش�Ҹ�´�����ֱ��$n����",
	"force" : 270,
        "dodge" : 10,
	"parry" : 15,
        "damage_type" : "����",
	"lvl" : 40,
	"skill_name" : "��ź����"
]),
([	"action" : "$Nһʽ����Ұ���㡹����ֻ�����紩�����������·���",
	"force" : 300,
        "dodge" : 5,
	"parry" : 10,
        "damage_type" : "����",
	"lvl" : 50,
	"skill_name" : "��Ұ����"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������Ʊ�����֡�\n");
	if ((int)me->query_skill("huntian-qigong", 1) < 30)
		return notify_fail("��Ļ���������򲻹����޷�ѧϰ�����ơ�\n");
	if ((int)me->query("max_neili") < 150)
		return notify_fail("�������̫�����޷��������ơ�\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level, neili, htqg, lhz, strike;
        neili = me->query("neili");
        lhz = me->query_skill("lianhua-zhang", 1);
        htqg = me->query_skill("huntian-qigong", 1);
 	strike = me->query_skill("strike", 1);
        if (htqg > 80 && lhz > 80 && strike > 80 && neili > 600 
            && random(me->query_int()) > 24 ){
                me->add("neili", -60);
                if(random(10) < 2 )
                return ([
                "action":HIY
		"ͻȻ$N��¶����΢Ц��$n�о�����֮���������ⶨ��ȴ����$Nʹ����"HIC"�����ƾ���"HIR"�����������"NOR,
	        "weapon" : HIY"�������"NOR,
                "force": 500,
                "dodge": -15,
                "parry": 15,
                "damage_type": "����"]);
	}

        level   = (int) me->query_skill("lianhua-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query_skill("lianhua-zhang",1) < 30)
		return notify_fail("��������������̶Ȼ������������Լ���ϰ��\n");
	if ((int)me->query("jingli") < 30)
		return notify_fail("��ľ���̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("������������������ơ�\n");
	me->receive_damage("jingli", 15+random(10));
	me->add("neili", -5+random(5));
	return 1;
}
int help(object me)
{
        write(
@HELP
������
    ؤ��ǰ�����˺��߹������һ�Ź�����Ϊ�������Ӵ����������ʱ�����������������ơ�
    ����ؤ�����Ź��򣬳����ŵĵ��ӣ���ѧ�����ơ����ż������ߣ�������������ǿ��
    ѧϰҪ�󣺻�����������30����������150��ؤ����Ӱݰ����������ѧ����
    �Զ����������������
    ���Դ���24�����������������Ʒ���������ȫ������80����������600ս�������������
HELP
        );
        return 1;
}
