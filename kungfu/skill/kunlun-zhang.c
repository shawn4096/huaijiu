// kunlun-zhang.c ������

inherit SKILL;

mapping *action = ({
([      "action" : "$N�Ʒ缤����˫�ƴ��䣬���������޷���һ�С������ɽ��������$n��$l",
        "force" : 200,
                  "dodge" : -5,
                  "parry" : 5,
        "lvl" : 0,
        "skill_name" : "�����ɽ",
        "damage_type" : "����"
]),
([      "action" : "$N˫������һ�С������Ƶ�����һ�ƻ���$n���ţ���һ��ȴ����$nС��",
        "force" : 230,
                  "dodge" : 5,
                  "parry" : 10,
        "lvl" : 20,
        "skill_name" : "�����Ƶ�",
        "damage_type" : "����"
]),
([      "action" : "$N˫�ƻ������Ī�⣬һ�С���粻������ǰ�����ң�˲Ϣ֮����$n����������һʮ����",
        "force" : 300,
                "dodge" : -10,
                  "parry" : 0,
        "lvl" : 38,
        "skill_name" : "��粻��",
        "damage_type" : "����",
]),
([      "action" : "$Nһ����Х������һ�ƣ�һ�С�ɽ��·ת��������ת׾��ȴ��ȥ����죬��$n��$l�ͻ���ȥ��",
        "force" : 280,
                  "dodge" : 0,
                  "parry" : 5,
        "lvl" : 55,
        "skill_name" : "ɽ��·ת",
        "damage_type" : "����"
]),
([      "action" : "$N˫�ƽ����������ޣ�һ�С������޷졹������$n��$l",
        "force" : 350,
                  "dodge" : 5,
                  "parry" : 5,
        "lvl" : 72,
        "skill_name" : "�����޷�",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С���ɽ�Ϻӡ�������һȭ���������ƽ���������ȭ��һ����˫������������$n��$l",
       "force" : 400,
                  "dodge" : -5,
                  "parry" : 10,
        "lvl" : 120,
        "skill_name" : "��ɽ�Ϻ�",
        "damage_type" : "����"
]),
([      "action" : "$N˫���뻮������˫�����ƣ�һ�С������ء���һ����ɽ������������ֱ��$n����",
        "force" : 450,
                  "dodge" : 10,
                  "parry" : -5,
        "lvl" : 160,
        "skill_name" : "������",
        "damage_type" : "����"
]),
([      "action" : "$NͻȻ�������ת��һ�С���ɽѩƮ������Ӱ���裬��ʱ֮�佫$n����˷�����ס��",
        "force" : 500,
                  "dodge" : 5,
                  "parry" : 0,
        "lvl" : 180,
        "skill_name" : "��ɽѩƮ",
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
      mapping fam  = me->query("family");
    if (fam["family_name"] != "������" || fam["generation"] != 2)
         return notify_fail("������ֻ�ܴӺ������ѧ����\n");
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʊ�����֡�\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 120)
                return notify_fail("��������޼�����򲻹����޷��������ơ�\n");
    if(me->query("gender")!="Ů��"){
        if ((int)me->query_skill("zhentian-quan", 1) < 80)
                return notify_fail("�����ع����򲻹����޷��������ơ�\n");
               } else {
     if ((int)me->query_skill("chuanyun-tui", 1) < 80)
                return notify_fail("�����ع����򲻹����޷��������ơ�\n");
               }
        if ((int)me->query("max_neili") < 800)
                return notify_fail("���������Ϊ�������޷��������ơ�\n");
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
        level   = (int) me->query_skill("kunlun-zhang",1);
        
          for(i = sizeof(action); i > 0; i--)
                                 if(level > action[i-1]["lvl"]) 
               return action[NewRandom(i, 20, level/5)];
                              
}

int practice_skill(object me)
{

        int lvl = me->query_skill("kunlun-zhang", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("jingli") < 50)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("������������������ơ�\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"kunlun-zhang/" + action;
}
