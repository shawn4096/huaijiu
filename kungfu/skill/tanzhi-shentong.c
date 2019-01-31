#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";
string *xue_name1 = ({ 
        "��׶Ѩ",
        "�ٻ�Ѩ",
        "־��Ѩ",
        "�羮Ѩ",
        "�͹�Ѩ",
        "�ڹ�Ѩ",
        "���Ѩ",
        "����Ѩ",
});
string *xue_name2 = ({
        "����Ѩ",
        "����Ѩ",
        "����Ѩ",
        "�׺�Ѩ",
        "��̨Ѩ",
        "�縮Ѩ",
        "���Ѩ",
        "����Ѩ",
}); 
string *xue_name3 = ({
        "����Ѩ",
        "����Ѩ",
        "˿����Ѩ",
        "����Ѩ",
        "����Ѩ",
        "��׵Ѩ",
        "����Ѩ",
        "����Ѩ",
}); 

mapping *action_finger = ({
([      "action" : "$N��ָ΢����ͻȻ������һʽ��ָ�㽭ɽ����һ�ƾ���ֱϮ$n��$l",
        "force" : 200,
        "dodge" : 5,
        "parry" : -5,
        "lvl" : 0,
        "skill_name" : "ָ�㽭ɽ",
        "damage_type" : "����"
]),
([      "action" : "$N��������ǰһ��������ͻȻ��������ָ΢������������ָ����ֱϮ$n��$l",
        "force" : 300,
        "dodge" : 0,
        "parry" : 10,
        "lvl" : 60,
        "skill_name" : "������ָ",
        "damage_type" : "����"
]),
([      "action" : "$N�ұۻӶ�����ָ����������ǰ����һ�����ߣ����ǡ�һ�´�ˮ��������$n��ǰ��",
        "force" : 400,
        "dodge" : 8,
        "parry" : -8,
        "lvl" : 120,
        "skill_name" : "һ�´�ˮ",
        "damage_type" : "����"
]),
([      "action" : "$NԾ���ڰ�գ�˫�ּ��ӣ���ָ����������ָ���ס�����ǵذ���$nӿȥ",
        "force" : 450,
        "dodge" : -3,
        "parry" : -10,
        "lvl" : 180,
        "skill_name" : "��ָ����",
        "damage_type" : "����"
]),
});

mapping *action_throwing = ({
([      "action" : "$N��ָ΢����ͻȻ������һʽ��ָ�㽭ɽ����$w�ƿ�֮��������ֱϮ$n��$l",
        "force" : 130,
        "dodge" : -5,
        "parry" : -10,
        "damage" : 60,
        "lvl" : 0,
        "skill_name" : "ָ�㽭ɽ",
        "damage_type" : "����",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
([      "action" : "$N��������ǰһ��������ͻȻ��������ָ΢������������ָ����$w��Х��ֱϮ$n��$l",
        "force" : 170,
        "dodge" : 5,
        "parry" : -15,
        "damage" : 80,
        "lvl" : 60,
        "skill_name" : "������ָ",
        "damage_type" : "����",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
([      "action" : "$N�ұۻӶ�����ָ����������$w����ǰ����һ�����ߣ����ǡ�һ�´�ˮ��������$n��ǰ��",
        "force" : 240,
        "dodge" : -5,
        "parry" : -6,
        "damage" : 110,
        "lvl" : 120,
        "skill_name" : "һ�´�ˮ",
        "damage_type" : "����",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
([      "action" : "$NԾ���ڰ�գ�˫�ּ��ӣ���ָ����������ָ���ס���������ǵص�$w����$nӿȥ",
        "force" : 320,
        "dodge" : 0,
        "parry" : -10,
        "damage" : 150,
        "lvl" : 180,
        "skill_name" : "��ָ����",
        "damage_type" : "����",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="throwing" || usage=="parry"; }

int valid_learn(object me)
{
        object weapon;
        if (weapon = me->query_temp("weapon"))
        if ((string)weapon->query("skill_type") != "throwing")
                return notify_fail("ѧ��ָ��ͨ������ֻ��ְֳ�����\n");
	if ((int)me->query_skill("bihai-chaosheng", 1) < 100)
		return notify_fail("��ı̺���������򲻹����޷�ѧ��ָ��ͨ��\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("��ϰ��ָ��ͨ�����б̺���������ϡ�\n");
        if ((int)me->query("max_neili") < 200)
                return notify_fail("�������̫�����޷�����ָ��ͨ��\n");
        return 1;
}


string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action_finger)-1; i >= 0; i--)
                if(level >= action_finger[i]["lvl"])
                        return action_finger[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("tanzhi-shentong",1);
        if ( level > 150
         && me->query_skill("force") > 250
         && me->query("neili") >= 200 && random(3)== 1) {
                me->add("neili", -20);
                if (!weapon)
                   	return ([
                     		"action": HBRED "$Nһ���Ϻȣ����ο�ʼ���ٻζ�������$n���ߡ�$nһ��㵼䣬ֻ�������͡�֮�����죬���������������˷�Ϯ��$n��" NOR,
                     		"force": 500,
                     		"dodge" : 10,
                     		"parry" : 10,
                     		"damage_type": "����"
                   	]);
                else	return ([
                     		"action": HIR "$Nһ���Ϻȣ����ο�ʼ���ٻζ�������$n���ߡ�$nһ��㵼䣬ֻ�������͡�֮�����죬����" + weapon->query("unit") + weapon->query("name") + "������˷�Ϯ��$n��" NOR,
                     		"damage": 200,
                     		"force": 380,
                     		"dodge" : 8,
                     		"parry" : 4,
                     		"damage_type": "����"
                   	]);
        }
        if (!weapon) {
                for(i = sizeof(action_finger); i > 0; i--)
                        if(level >= action_finger[i-1]["lvl"])
                                return action_finger[NewRandom(i, 20, level/5)];
        }
        else
                for(i = sizeof(action_throwing); i > 0; i--)
                        if(level > action_throwing[i-1]["lvl"])
                                return action_throwing[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("tanzhi-shentong", 1);
        int i = sizeof(action_finger);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["tanzhi-shentong"])
         while (i--) 
           if (lvl == action_finger[i]["lvl"])
              return notify_fail("�㽫�Ѿ�ѧ���������ʽ��ϰ��һ�飬���������ȥ��ʦ��ѧ�µ���ʽ���޷���ý����ˡ�\n");;
        if (weapon = me->query_temp("weapon"))
        if ((string)weapon->query("skill_type") != "throwing")
              return notify_fail("����ָ��ͨ������ֻ��ְֳ�����\n");
        if ((int)me->query("jingli") < 50)
              return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
              return notify_fail("���������������ָ��ͨ��\n");
        me->receive_damage("jingli", 45);
        me->add("neili", -20);
        return 1;
}

string perform_action_file(string action)
{
      	return __DIR__"tanzhi-shentong/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl = me->query_skill("finger");
        string name1,name2, name3;
        
        if ( lvl > 200 
        && me->query("neili") > 600
        && userp(me)
        && me->query("combat_exp") > victim->query("combat_exp") /3 *2
        && !victim->is_busy()
        && random(10) > 6 && random(lvl) > random( victim->query("dodge") ) ){
        	name1 = xue_name1[random(sizeof(xue_name1))];
        	name2 = xue_name2[random(sizeof(xue_name2))];
        	name3 = xue_name3[random(sizeof(xue_name3))];
              	message_vision(HIR "$n��$N�����ˡ�"HIC + name1 + HIR"������Ϣ���ң�\n" NOR,me,victim);
              	victim->start_busy(random(3)+1);
           	if (random(lvl) > 230) {
              		message_vision(HIY "$N��ָ΢�����ֵ�����$n�ġ�"HIC + name2 + HIY"����\n" NOR,me,victim);
              		message_vision(HIY "$nֻ����ͷ΢΢��ѣ�������ܼ��У�\n" NOR,me,victim);
              		victim->add("jingli",- lvl); 
              	}
           	if (random(lvl) > 300) {
              		message_vision(HIG "$N�����ٵ���$n�ġ�"HIC + name3 + HIG"����\n" NOR,me,victim);
              		message_vision(HIG "$n����һ���ʹ�������޷����ۣ�\n" NOR,me,victim);
              		victim->add("neili",- lvl*2); 
              	}
        }
}

