//hanshasheying ��ɳ��Ӱ
// 1997-2-14

inherit SKILL;

string  *msg = ({
"$N��һ�ʹһʽ������׷�¡���ֻ��������������ö$wǰ��������$n��$l���",
"$N���κ��ظ߸�Ծ��ʹһʽ����Ůɢ������������ö$w��$n�������",
"$Nһʽ��ȥ������������һ������ö$w��$n�����ӹ�������$n����Ȼתͷ��$n���ķ�ȥ",
"$N����ͻ�ص������������һ����ʹһ�С��ճ������������а��۵���ö$w��Ѹ�ײ����ڶ�֮������$n����",
"$N����һ��������$n��󣬷���һʽ��������񡹣�������ö$w��$n�ĺ���Ҫ����ȥ",
"$Nһʽ��������꡹��ͻȻ˫���������£�ʮ��ö$w�������ط���$n��ǰ��",
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
               return notify_fail("���������������ɳ��Ӱ��\n");
       me->receive_damage("jingli", 30);
       return 1;
}

int valid_learn(object me)
{
       if ((int)me->query("max_neili") < 300)
               return notify_fail("�������������\n");
       if ((int)me->query_skill("dulong-dafa", 1) < 50)
               return notify_fail("��Ķ����󷨻��̫ǳ��\n");
               return 1;
}

string perform_action_file(string action)
{
       string * cs;
       object me=this_player();
       int hg;
    
       hg=strsrch(action,"xiangyin");
       cs=explode(action,"xiangyin");
       if(hg!=-1 && sizeof(cs)>0)
           me->set_temp("xydir",cs[0]);
       return __DIR__"hansha-sheying/xiangyin";
}

