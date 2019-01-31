// chousui-zhang.c, ������
// by pishou

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N�߶�����������Ӷ���˫��Ю��һ���ȳ�֮��һǰһ������$n��$l",
        "dodge": 10,
        "force": 230,
        "lvl" : 0,
        "damage_type": "����"
]),

([      "action": "$N˫��һ��һ�䣬������ת����, ͻȻ��˫�Ʒ���������$n��$l",
        "dodge": 20,
           "force": 280,
        "lvl" : 0,
        "damage_type": "����"
]),

([      "action": "$N����Ʈ����Χ��$nһȦȦ���ߣ�ͬʱ˫�����ģ��������󾢷紵��$n",
        "dodge": 30,
        "force": 330,
        "lvl" : 30,
        "damage_type": "����"
]),

([      "action": "$NͻȻ������ȣ�Ծ�ڰ�գ������縫������������$n������������",
        "weapon" : "�Ʒ�",
        "dodge": 10,
           "force": 400,
        "lvl" : 50,
        "damage_type": "����"
]),

([      "action": "$N����΢����ǰһ��������ʮ�ɹ��������һ�����뷢��ţ�����һ������$n��ȥ",
        "dodge": -7,
           "force": 450,
        "lvl" : 70,
        "damage_type": "����"
]),

([      "action": "$N��¶�����Ц�ݣ��͵���ǰ�������׼$n��$l����һ�������ޱȵġ������ơ�",
        "dodge": 15,
           "force": 470,
        "lvl" : 95,
        "damage_type": "����"
]),

([      "action": "$N����һת������������һ�С��������צ�������������������ץ��$n��$l",
        "weapon" : "��צ",
        "dodge": 25,
           "force": 480,
        "lvl" : 120,
        "damage_type": "ץ��"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
/*
int valid_combine(string combo)  
{
         object me = this_player();
         mapping myfam = (mapping)me->query("family");
         if ((int)me->query_str() > 25 && myfam && myfam["master_name"] == "������")
                 return combo=="sanyin-zhua";
}
*/
string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level;

        level   = (int) me->query_skill("chousui-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
        return notify_fail("�����ֲ����������ơ�\n");
        if ((int)me->query_skill("huagong-dafa", 1) < 10)
        return notify_fail("�㻹�������û����󷨰ɡ�\n");
        if ((int)me->query("max_neili") < 100)
        return notify_fail("����������̫��, �����˳����ơ�\n");
        return 1;
}

int practice_skill(object me)
{
       if(!me->query_skill("huagong-dafa", 1))
               return notify_fail("����������Ҫ�л����󷨵�֧�֡�\n");
       if ((int)me->query("jingli") < 30)
               return notify_fail("�������̫���ˡ�\n");
       if ((int)me->query("neili") < 40)
               return notify_fail("������������������ơ�\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -10);
       return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int poison, extra;
        poison = (me->query_skill("poison", 1) - victim->query_skill("poison", 1))/2 + victim->query_condition("xx_poison");
        extra = (me->query_skill("huagong-dafa") + me->query_skill("poison",1))/10;
        if(random(me->query_skill("huagong-dafa", 1)) > 30 &&
            me->query_skill("poison", 1) > 50 && 
            me->query("env/xx_poison") != "����" && 
            me->query_skill("poison", 1)+20 > victim->query_skill("poison", 1)) {
              if (me->query("env/xx_poison") == "ɢ��") {
                 poison += extra;
                 me->add("neili",-100-random(50));
                 me->add("jingli",-20-random(30));
                 message_vision(BLU"$N����һ�ߣ�����������ʢ��\n"NOR, me);
              }
              victim->apply_condition("xx_poison", poison);
              message_vision(BLU"$Nһ���ƣ�����һ�Σ������Ѿ����˶���\n"NOR, victim);
              if (victim->query_condition("xx_poison") > 200)
                  message_vision(HBRED"$N���ڻ����������������Σ�գ�\n"NOR, victim);
              if (userp(me) && userp(victim) && me->query_condition("killer") < 15 && 
		  me->query_temp("kill_other/"+victim->query("id")) && victim->query_temp("other_kill/"+me->query("id")))
                 me->apply_condition("killer", 15);
        }
}

string perform_action_file(string action)
{
        return __DIR__"chousui-zhang/" + action;
}

