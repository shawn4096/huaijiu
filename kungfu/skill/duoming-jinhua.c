//duoming-jinhua ������
// 1997-2-14

inherit SKILL;

string  *msg = ({
"$Nһʽ����ö�ˡ������������������ƹ�������$w��$n��$l���",
"$wٿ��ٿ�ң�����˷�������$n��ȴ��$N��һʽ��ٿ��ٿ�ҡ���$n������ö$w",
"$N�ͺ�һ����һʽ����Ůɢ�������İ�$w��$n��������������һʮ��֮��",
"$nֻ���������죬ȴ��$Nһ�С��������꡹��ʮ��ö$w��$n����Ѩ��ȥ",
"ͻȻ�ƹ�һ����$Nһʽ��ǧ��׷�꡹����ö$w��$n���ؿ�Ҫ����ȥ",
"$Nһʽ����ͷ���¡���ͻȻ����������ö$w������$n�ĺ���",
"$Nһ�С�������ס�����ö$w�������䣬�Ʒ������������$n���ܿ�����Ӱ",
"$Nһ�С��𻨶�������ȫ����˶��������ַ����ö$w����$n���ز�",
"$N�������һ�С�÷�����֡���$wһöö�Ĵ�$N���зɳ�������÷������$n"
});

int valid_enable(string usage)
{
        return usage == "throwing" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        return ([
                "action":msg[random(sizeof(msg))],
                "damage":(random(3)+1)*50,
                "damage_type":random(2)?"����":"����",
                "dodge":random(30),
                "force":random(200)+100,
                "post_action":
                  (: call_other, WEAPON_D, "throw_weapon" :)
                ]);
}

int practice_skill(object me)
{
       object weapon;
       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "throwing")
               return notify_fail("��ʹ�õ��������ԡ�\n");
       if ((int)me->query("jingli") < 50)
               return notify_fail("������������������𻨡�\n");
       me->receive_damage("jingli", 30);
       return 1;
}

int valid_learn(object me)
{
       if ((int)me->query("max_neili") < 500)
               return notify_fail("�������������\n");
       if ((int)me->query_skill("shenghuo-shengong", 1) < 50)
               return notify_fail("���ʥ���񹦻��̫ǳ��\n");
               return 1;
}

string perform_action_file(string action)
{
       return __DIR__"duoming-jinhua/" + action;
}
