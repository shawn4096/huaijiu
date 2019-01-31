// zhenshan-mianzhang.c ��ɽ����
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N�ͺ�һ�������ã���һ�������ݲ������������棬̤��һ��������һ�С����֡�����$n��$l��ȥ",
        "force" : 140,
        "dodge" : 5,
        "damage_type" : "����",
        "lvl" : 0,
        "skill_name" : "����"
]),
([      "action" : "$N����һ����һ����ӡ�ơ�����ɽ���Ʒ��Ȼ�縫������$n��$l",
        "force" : 150,
        "dodge" : -5,
        "damage_type" : "����",
        "lvl" : 10,
        "skill_name" : "ӡ��"
]),
([      "action" : "$N������ǰ������һ�ơ����Ƽ��ա���һ����ɽ��������������$n��$l",
        "force" : 180,
        "dodge" : 5,
        "damage_type" : "����",
        "lvl" : 15,
        "skill_name" : "���Ƽ���"
]),
([      "action" : "$N˫��һ����ʽ������ͻȻ��������ɨ��$n��$l������һ�С����ƶϷ塹",
        "force" : 210,
        "dodge" : 10,
        "damage_type" : "����",
        "lvl" : 20,
        "skill_name" : "���ƶϷ�"
]),
([      "action" : "$N����Ϊצ��ץ��$n��$l��һ�С�������ӡ�������$n��������ˤ��",
        "force" : 240,
        "dodge" : -20,
        "damage_type" : "����",
        "lvl" : 25,
        "skill_name" : "�������"
]),
([      "action" : "$Nʹ�����������������$n��ǰ����һ����Ż���Ϊָ����ʳ��˫ָ���¶��ϴ���$n���⡸����Ѩ��",
        "force" : 220,
        "dodge" : -5,
        "damage_type" : "����",
        "lvl" : 30,
        "skill_name" : "�������"
]),
([      "action" : "$N�������ƣ�һ�С��������¡������󷭹�������ת�˸�СȦ����$n��$l��ȥ",
        "force" : 210,
        "dodge" : 10,
        "damage_type" : "����",
        "lvl" : 35,
        "skill_name" : "��������"
]),
([      "action" : "$N��ת���ƣ�������ȭ��һʽ��ѩӵ���ء�����$n��$l�ͻ�",
        "force" : 230,
        "dodge" : 5,
        "damage_type" : "����",
        "lvl" : 40,
        "skill_name" : "ѩӵ����"
]),
([      "action" : "$N���̡��̹���񡹣�˫�ַ�ת���������ַ�����$n��$l��ҪѨ����",
        "force" : 260,
        "dodge" : 5,
        "damage_type" : "����",
        "lvl" : 45,
        "skill_name" : "�̹����"
]),
([      "action" : "$N���С�ԧ���ȡ�����$n��$l���漴����$n�ؿڵġ�����Ѩ��",
        "force" : 230,
        "dodge" : 5,
        "damage_type" : "����",
        "lvl" : 50,
        "skill_name" : "ԧ����"
]),
([      "action" : "$Nһ�С��ɺ����᡹��ٿ��б������$n����󣬻��ֳ��ƣ���$n��$l��",
        "force" : 200,
        "dodge" : 10,
        "damage_type" : "����",
        "lvl" : 60,
        "skill_name" : "�ɺ�����"
]),
([      "action" : "$Nʩ������¶�Ὥ���������ͻ����������ܣ�ͻȻ����ץס$n��$l���ͺ�һ������$n�������˳�ȥ",
        "force" : 170,
        "dodge" : -5,
        "damage_type" : "����",
        "lvl" : 90,
        "skill_name" : "��¶�Ὥ"
]),
([      "action" : "$N���һ�����ʹܶ����������������$n�����󣬽�������һ�С��׺���ա���ʹ��ȫ����$n��$l��ȥ",
        "force" : 240,
        "dodge" : 5,
        "damage_type" : "����",
        "lvl" : 120,
        "skill_name" : "�׺����"
]),
([      "action" : "$N����һ����ʹ��һ�С���ת���ɡ���ת��һ��Ȧ�ӣ�˫��ֱ��$n��$l",
        "force" : 210,
        "dodge" : 10,
        "damage_type" : "����",
        "lvl" : 150,
        "skill_name" : "��ת����"
]),
([      "action" : "$N�����ұۣ��������������������һ�У�һ�С���ܽ�����������������$n��$l��ȥ",
        "force" : 200,
        "dodge" : -10,
        "damage_type" : "����",
        "lvl" : 180,
        "skill_name" : "��ܽ���"
])
});

int valid_enable(string usage) { return (usage == "strike") || (usage == "parry"); }
int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����ɽ���Ʊ�����֡�\n");
        if ((int)me->query_skill("yinyun-ziqi", 1) < 100)
                return notify_fail("�����������򲻹����޷�ѧϰ��ɽ���ơ�\n");
        if ((int)me->query("max_neili") < 1200)
                return notify_fail("�������̫�����޷�����ɽ���ơ�\n");
        return 1;
}

int practice_skill(object me)
{
        if ((int)me->query_skill("yinyun-ziqi", 1) < 100)
             return notify_fail("�����������򲻹����޷���ϰϰ��ɽ���ơ�\n");
        if ((int)me->query("jingli") < 40)
                return notify_fail("��ľ���̫����,�޷���ϰ��ɽ����\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("���������������ɽ���ơ�\n");
        me->receive_damage("jingli", 35);
        me->add("neili", -10);
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
        level = (int)me->query_skill("zhenshan-mianzhang", 1);
           
        if ( random(level)/2 > 100
        && me->query_skill("strike",1) > 200 
        && me->query("neili") > 1000 
        && me->query("jingli") > 300 
        && me->query("jiali") > 5 
        && !me->query_temp("wd_hkbd")){
                me->add("neili", -20);
                return ([
                        "action": HIY "$N�������䣬˫����ƮƮ�أ��������޵��Ļ������������䵱��ѧ֮һ����ɽ���ƣ�"NOR,
                        "force": 400,
                        "dodge": -5,
                        "damage_type": "����"]);
        }

        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];


}

string perform_action_file(string action)
{
        return __DIR__"zhenshan-mianzhang/" + action;
}
