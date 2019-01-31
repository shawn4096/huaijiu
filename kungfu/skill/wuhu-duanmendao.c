// wuhu-duanmendao.c �廢���ŵ�
// Modified By Numa@SJ 2000.7

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N������$w����һ�����漴��������һ�ݣ��ԡ��ͻ���ɽ��֮������$n",
        "force" : 140,
        "dodge" : 10,
        "parry" : 5,
        "damage" : 15,
        "damage_type" : "����",
        "lvl" : 10,
        "skill_name" : "�ͻ���ɽ"
]),
([      "action" : "$Nһ�С����絹��������$w��������ֱֱ����$nС��",
        "force" : 160,
        "dodge" : 5,
        "parry" : 10,
        "damage" : 10,
        "damage_type" : "����",
        "lvl" : 40,
        "skill_name" : "���絹��"
]),
([      "action" : "$N��������������תһ�ܣ�����$w����һ�С���ɳ��ʯ������$n",
        "force" : 200,
        "dodge" : -10,
        "parry" : 10,
        "damage" : 20,
        "damage_type" : "����",
        "lvl" : 80,
        "skill_name" : "��ɳ��ʯ"
]),
([      "action" : "$Nȫ������һԾ��ԼĪ�����ʱ�����´ܣ�һ�С����ذ���ֱȡ$n����",
        "force" : 240,
        "dodge" : 5,
        "parry" : -5,
        "damage" : 25,
        "damage_type" : "����",
        "lvl" : 120,
        "skill_name" : "���ذ�"
]),
([      "action" : "$N����һ����������������$w֮�ϣ���һ�С���ɨ���¡�ֱ��$n˫ϥ",
        "force" : 270,
        "dodge" : 5,
        "parry" : 10,
        "damage" : 70,
        "damage_type" : "����",
        "lvl" : 150,
        "skill_name" : "��ɨ����"
]),
([      "action" : "$N����ͻȻ���ȣ����ֻ��˸�ԲȦ�������Ե�����ס���ƣ�һ�С�����ɽ�ӡ���$n��ѹ��ȥ",
        "force" : 300,
        "dodge" : -5,
        "parry" : 10,
        "damage" : 120,
        "damage_type" : "����",
        "lvl" : 200,
        "skill_name" : "����ɽ��"
]),
});

int valid_enable(string usage) {return (usage == "blade") || (usage == "parry");}

int valid_learn(object me)
{
        if(me->query("mao18/pass4") && me->query_skill("wuhu-duanmendao", 1) >= 220 ){
		if( (int)me->query_skill("blade", 1) >= 220){
		
			return 1;
		}
		else return notify_fail("��Ļ���������򲻹���\n");       
	}
        return notify_fail("���廢���ŵ�����ѧֻ�ܴ��ؼ�������\n");        

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

        if( random(10) > 5
        && ((int)me->query_skill("blade", 1) >= 120 ) 
        && ((int)me->query_skill("wuhu-duanmendao", 1) >= 120 )
        && ((int)me->query_skill("force") >= 150 )
        && ((int)me->query("neili") >= 500 )
        && random( (int)me->query_skill("wuhu-duanmendao", 1)) >= 100) {
                me->add("neili", -100);
                if (me->query("mao18/pass2")) {
                        if (me->query("mao18/pass3"))
                                switch (random(6)) {
                                        case 0 :
                                        case 2 :
                                        case 4 :
                                                return ([
                                                        "action": HIY"$N�������أ�����$w����$n���裬��һʽ��"HIR"�廢����"HIY"����ѧ�ٽ�$nΧ�ڵ���֮��"NOR,
                                                        "damage": 250,
                                                        "force": 450,
                                                        "damage_type": "����"
                                                ]);
                                                break;
                                        case 1 :
                                        case 3 :
                                                return ([
                                                        "action": HIR"$N˫�ֽ�߬����$w������Բ���Ȼһʽ���ͻ���ɽ����ݺݵ�����$n"NOR,
                                                        "damage": 200,
                                                        "force": 400,
                                                        "damage_type": "����"
                                                ]);
                                                break;
                                        case 5 :
                                                return ([
                                                        "action": HIC"$NĿ¶�׹⣬��$n̤��ǰʱ��һʽ��������ʳ��������$w��$n���迪ȥ"NOR,
                                                        "damage": 160,
                                                        "force": 350,
                                                        "damage_type": "����"
                                                ]);
                                                break;
                                }
                        else
                                switch (random(3)) {
                                        case 0 :
                                        case 2 :
                                                return ([
                                                        "action": HIR"$N˫�ֽ�߬����$w������Բ���Ȼһʽ���ͻ���ɽ����ݺݵ�����$n"NOR,
                                                        "damage": 200,
                                                        "force": 400,
                                                        "damage_type": "����"
                                                ]);
                                                break;
                                        case 1 :
                                                return ([
                                                        "action": HIC"$NĿ¶�׹⣬��$n̤��ǰʱ��һʽ��������ʳ��������$w��$n���迪ȥ"NOR,
                                                        "damage": 160,
                                                        "force": 350,
                                                        "damage_type": "����"
                                                ]);
                                                break;
                                }
                }
                else
                        return ([
                                "action": HIC"$NĿ¶�׹⣬��$n̤��ǰʱ��һʽ��������ʳ��������$w��$n���迪ȥ"NOR,
                                "damage": 160,
                                "force": 350,
                                "damage_type": "����"
                        ]);
        }

        level   = (int) me->query_skill("wuhu-duanmendao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}       

int practice_skill(object me)
{       
        object weapon;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("jingli") < 50)
                return notify_fail("��������������廢���ŵ�����\n");


        if(me->query("mao18/pass4") && me->query_skill("wuhu-duanmendao", 1) >= 220 ){
		if( (int)me->query_skill("blade", 1) >= 220){
		        me->receive_damage("neili", 30);
                        me->receive_damage("jingli", 35);
			return 1;
		}
		else return notify_fail("��Ļ���������򲻹���\n");       
	}
        return notify_fail("���廢���ŵ�����ѧֻ�ܴ��ؼ�������\n");        

}

string perform_action_file(string action)
{
        return __DIR__"wuhu-duanmendao/" + action;
}
