// huashan-jianfa.c ��ɽ����
// modified by darken@SJ

inherit SKILL;
#include <combat.h>
#include <ansi.h>
mapping *action_male = ({
([      "action" : "$Nһ�С����Ƴ�ᶡ�����һ�����ԣ���ʱ����һƬ������$w���Ե���$n��$l",
        "force" : 140,
        "dodge" : 5,
        "parry" : 3,
        "damage" : 40,                     
        "lvl" : 0,
        "skill_name" : "���Ƴ��",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�����з����ǡ������Ʒ����������ӯ�鶯��$w��˸����������$n��$l",
        "force" : 170,
        "dodge" : 4,
        "parry" : 10,
        "damage" : 60,
        "lvl" : 10,
        "skill_name" : "�з�����",
        "damage_type" : "����" 
]),

([      "action" : "$Nһ�С������������������ߣ�$w���϶��»���һ���󻡣���$n������ȥ",
        "force" : 200,
        "dodge" : 10,
        "parry" : -5,
        "damage" : 100,
        "lvl" : 30,
        "skill_name" : "������",
        "damage_type" : "����"
]),
([      "action" : "$N��ǰ����һ��������$w�������ƼȻ�����������������$NͻȻ����һת��ʹ�����׺���ա�ֱ��$n��$l",
        "force" : 240,
        "dodge" : 20,
        "parry" : 5,
        "damage" : 110,
        "lvl" : 60,
        "skill_name" : "�׺����",
        "damage_type" : "����"
]),
([      "action" : "$N���е�$wһ�Σ��������ߣ�һ������������һƬ��Ӱ��һ�С�����ӭ�͡�ֱ��$n��$l",
        "force" : 280,
        "dodge" : 10,
        "parry" : 10, 
        "damage" : 130,
        "lvl" : 80,
        "skill_name" : "����ӭ��",
        "damage_type" : "����"
]),

([      "action" : "$N����$wб�η�����һʽ���ޱ���ľ������һ�³��м��죬����������ã�ֱ��$n��$l",
        "force" : 300,
        "dodge" : 5,
        "parry" : 10,
        "damage" : 115,
        "lvl" : 100,
        "skill_name" : "�ޱ���ľ",
        "damage_type" : "����"
]),
([      "action" : "$NͻȻ���ֺ��������Ž������գ��ƺ�Ҫײ���Լ������ţ�ͻȻһʽ����ɽ������,�������$n",
        "force" : 320,
        "dodge" : 10,
        "parry" : 5,
        "damage" : 145,
        "lvl" : 120,
        "skill_name" : "��ɽ����",
        "damage_type" : "����"
]), 
([      "action" : "$N�ұ����ᣬ����$w�������ߣ�����һ̧��һ�С��Ű�ɭɭ��ֻ��$nײ������",      
        "force" : 340,
        "dodge" : 10,
        "parry" : 2,
        "damage" : 135,
        "lvl" : 150,
        "skill_name" : "�Ű�ɭɭ",
        "damage_type" : "����"
]),
});

mapping *action_famale = ({
([      "action" : "$Nʹ�����з����ǡ������Ʒ����������ӯ�鶯��$w��˸����������$n��$l",
        "force" : 120,
        "dodge" : 0,
        "parry" : 5,
        "damage" : 35,
        "lvl" : 0,
        "skill_name" : "�з�����",
        "damage_type" : "����"
]),
([      "action" : "$N��ǰ����һ��������$w�������ƼȻ�����������������$NͻȻ����һת��ʹ�����׺���ա�ֱ��$n��$l",
        "force" : 150, 
        "dodge" : 5,
        "parry" : -5,
        "damage" : 70,
        "lvl" : 16,
        "skill_name" : "�׺����",
        "damage_type" : "����"
]),
([      "action" : "$N���е�$wһ�Σ��������ߣ�һ������������һƬ��Ӱ��һ�С�����ӭ�͡�ֱ��$n��$l",
        "force" : 180,
        "dodge" : 0,
        "parry" : 10,
        "damage" : 90,
        "lvl" : 26,
        "skill_name" : "����ӭ��",
        "damage_type" : "����"
]),

([      "action" : "$N����$wб�η�����һʽ���ޱ���ľ������һ�³��м��죬����������ã�ֱ��$n��$l",
        "force" : 220,
        "dodge" : 10,
        "parry" : 5,
        "damage" : 45,
        "lvl" : 35,
        "skill_name" : "�ޱ���ľ", 
        "damage_type" : "����"
]),
([      "action" : "$N��������һʽ������ء���$w��Ȼһ��������ǧ�������۶�������������$n��$l",
        "force" : 240,
        "dodge" : 5,
        "parry" : 10,
        "damage" : 110,
        "lvl" : 54,
        "skill_name" : "�����",
        "damage_type" : "����"
]),
([      "action" : "$N��תһʽ�����両�ࡹ��ٲȻ��ǹ��ꪣ���ɳǧ�$w������������$n���������ؽ���֮��",
        "force" : 260,
        "dodge" : 5,
        "parry" : 5,
        "damage" : 130,
        "lvl" : 65,
        "skill_name" : "���両��",
        "damage_type" : "����"
]),

([      "action" : "$N��������һ�֣�����$w�����ӳ�һ�С���˫�޶ԡ�������ɭȻ����$n��$l��ȥ",
        "force" : 280,
        "dodge" : 5, 
        "parry" : 5,
        "damage" : 125,
        "lvl" : 92,
        "skill_name" : "��˫�޶�",
        "damage_type" : "����"
]),
([      "action" : "$N��̾һ��������$w����һ����һʽ���仨���⡹��$w��ȻԾ��ٿ�Ļ��������¶���һ���ƮȻ����$n��$l",
        "force" : 300,
        "dodge" : 5,
        "parry" : 10,
        "damage" : 145,
        "lvl" : 100,
        "skill_name" : "�仨����",
        "damage_type":  "����"
]),
});

mapping *action_19 = ({
([      "action":HIW"\n$Nʹһʽ������˳��Ȼ��������$w"+HIW"����΢�񣬻ó�һ���׹����$n��$l"NOR,
        "force" : 120,
        "dodge" : -10,
        "damage": 15,
        "lvl" : 0,
        "skill_name" : "����˳��Ȼ",
        "damage_type":  "����"
]),
([      "action":HIC"\n$N����ǰ��ʹ������ȥ�����С��������������ޣ�$w"+HIC"��������$n��$l��ȥ"NOR,
        "force" : 140,
        "dodge" : -10,
        "damage": 20,
        "lvl" : 8,
        "skill_name" : "��ȥ������",
        "damage_type":  "����"
]),
([      "action":HIM"\n$Nһʽ��־�����Զ��������Ʈ�����ߣ��˷�����������$w"+HIM"ңҡָ��$n��$l"NOR,
        "force" : 160,
        "dodge" : 5,
        "damage": 30,
        "lvl" : 15,
        "skill_name" : "־�����Զ",
        "damage_type":  "����"
]),
([      "action":HIG"$N��������Ծ��һʽ�������γ�����������ˮ��һкǧ�����$nȫ��"NOR,
        "force" : 180,
        "dodge" : 10,
        "damage": 35,
        "lvl" : 20,
        "skill_name" : "�����γ�",
        "damage_type":  "����"
]),
([      "action":HIY"$N����$w"+HIY"�й�ֱ����һʽ�����Ǳ��ҹ����������Ϣ�ض�׼$n��$l�̳�һ��"NOR,
        "force" : 220,
        "dodge" : 15,
        "damage": 40,
        "lvl" : 30,
        "skill_name" : "���Ǳ��ҹ",
        "damage_type":  "����"
]),
([      "action":HIR"$N����$w"+HIR"һ����һʽ������ϸ��������������Ϣ�ػ���$n��$l"NOR,
        "force" : 250,
        "dodge" : 15,
        "damage": 40,
        "lvl" : 40,
        "skill_name" : "����ϸ����",
        "damage_type":  "����"
]),
([      "action":WHT"\n$N����$w"+WHT"бָ���죬��â���£�һʽ������������������׼$n��$lбб����"NOR,
        "force" : 280,
        "dodge" : 25,
        "damage": 45,
        "lvl" : 50,
        "skill_name" : "����������",
        "damage_type":  "����"
]),
([      "action":RED"$N��ָ�����㣬����$w"+RED"�Ƴ�����ѩ����â��һʽ������һ��졹����$n���ʺ�"NOR,
        "force" : 320,
        "dodge" : 15,
        "damage": 55,
        "lvl" : 60,
        "skill_name" : "����һ���",
        "damage_type":  "����"
]),
([      "action":CYN"$N���Ƶ�����һʽ�����Ļ���������$w"+CYN"�Ի���Ծ�����缲�������$n���ؿ�"NOR,
        "force" : 380,
        "dodge" : 15,
        "damage": 60,
        "lvl" : 70,
        "skill_name" : "���Ļ�����",
        "damage_type":  "����"
]),
([      "action":HIC"\n$N����һ���εض���һʽ��������ͬ�ԡ���$w"+HIC"�ó������Ӱ����$n����Χס"NOR,
        "force" : 420,
        "dodge" : 15,
        "damage": 70,
        "lvl" : 80,
        "skill_name" : "������ͬ��",
        "damage_type":  "����"
]),
([      "action":MAG"$N�������Ʈ�䣬һʽ�����֪���⡹������$w"+MAG"ƽָ����������$n����"NOR,
        "force" : 450,
        "dodge" : 15,
        "damage": 80,
        "lvl" : 90,
        "skill_name" : "���֪����",
        "damage_type":  "����"
]),
([      "action":GRN"$N����΢����������һ�С��ߴ���ʤ�������йǽ�����쫷�����$nȫ��"NOR,
        "force" : 500,
        "dodge" : 15,
        "damage": 90,
        "lvl" : 100,
        "skill_name" : "�ߴ���ʤ��",
        "damage_type":  "����"
]),
([      "action":YEL"$Nļ��ʹһ�С���Ҷ����ɽ������ʱ�����м���Ѫ������$nȫ��"NOR,
        "force" : 500,
        "dodge" : 25,
        "damage": 100,
        "lvl" : 110,
        "skill_name" : "��Ҷ����ɽ",
        "damage_type":  "����"
]),
});

mapping *action_kf = ({
([      "action":HBCYN"$N����$w"+HBCYN"���������ͻȻ���ڿ���һ����һ�С�Ȫ��ܽ�ء������а�������֮����$w"+HBCYN"��·������ȣ���̼侹Ȼ���Ƶ���$n����",
        "force" : 160,
        "dodge" : 5,
        "parry" : 5,
        "damage": 15,
        "lvl" : 0,
        "skill_name" : "Ȫ��ܽ��",
        "damage_type":  "����"
]),
([      "action":HBCYN"$Nȫ�����Է�������·��ʹ��һ�С������ϸǡ����仯Ī��ع���$n�����ƾ���˿�������Ѱ",
        "force" : 200,
        "dodge" : 5,
        "parry" : 5,
        "damage": 25,
        "lvl" : 10,
        "skill_name" : "�����ϸ�",
        "damage_type":  "����"
]),
([      "action":HBCYN"$N����$w"+HBCYN"�ζ�����ʯ��������ʹ��������������������$n���Ƶ��ľ���ѣ����֪$N�������˶�����",
        "force" : 260,
        "dodge" : 8,
        "parry" : 8,
        "damage": 30,
        "lvl" : 20,
        "skill_name" : "ʯ������",
        "damage_type":  "����"
]),
([      "action":HBCYN"$N$w"+HBCYN"������仯������һ�С���������������������֮���£������޶�������׽����$n����һ���ۻ����ң��ٸ����Ӧ��",
        "force" : 330,
        "dodge" : 10,
        "parry" : 15,
        "damage": 40,
        "lvl" : 30,
        "skill_name" : "��������",
        "damage_type":  "����"
]),
([      "action":HBCYN"$NͻȻ��������б��ܳ���ʹ�������ף�ڡ�������$w"+HBCYN"�����Ȼ֮���������⻷��ת����ʱ֮���ѽ�$n����һ�Ž���֮��",
        "force" : 410,
        "dodge" : 10,
        "parry" : 10,
        "damage": 50,
        "lvl" : 50,
        "skill_name" : "���ף��",
        "damage_type":  "����"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili", 1) < 100)
                return notify_fail("�������������\n"); 
        if ((int)me->query_skill("zixia-gong", 1) < 20)
                return notify_fail("�����ϼ�񹦻��̫ǳ��\n");
        if( (int)me->query_skill("sword", 1) < 10 )
                return notify_fail("��Ļ���������������죬�޷�ѧϰ��ɽ������\n");
        if ((int)me->query_skill("poyu-quan", 1) < 15)
                return notify_fail("�������ȭ̫�����޷�ѧϰ����ɽ�����ľ��衣\n");
        return 1;
}


mapping query_action(object me, object weapon)
{
        int i, level;

	level=me->query_skill("huashan-jianfa",1);

        if( me->query_temp("hsj_19")) {
        for(i = sizeof(action_19); i > 0; i--) 
                if(level >= action_19[i-1]["lvl"])
                        return action_19[NewRandom(i, 20, level/5)];
        }
        if( me->query_temp("hsj_kf")) {
        for(i = sizeof(action_kf); i > 0; i--) 
                if(level >= action_kf[i-1]["lvl"])
                        return action_kf[NewRandom(i, 20, level/5)];
        }
        if( me->query("gender") != "Ů��" ) {
        for(i = sizeof(action_male); i > 0; i--)
                if(level >= action_male[i-1]["lvl"])
                        return action_male[NewRandom(i, 20, level/5)];
        }
        for(i = sizeof(action_famale); i > 0; i--) 
		if(level >= action_famale[i-1]["lvl"]) return action_famale[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("jingli") < 30)
                return notify_fail("���������������ɽ������\n");
        me->receive_damage("jingli", 30);
        return 1;
}

string perform_action_file(string action)
{
               return __DIR__"huashan-jianfa/" + action;
}

int ob_hit(object ob, object me, int damage)
{
        object weapon = me->query_temp("weapon");
        int p;
        string msg;

        p = (int)me->query("qi")*100/(int)me->query("max_qi");
	if (p < 20 &&
	me->query_skill_mapped("sword") == "huashan-jianfa" &&
	me->query_skill_prepared("cuff") == "poyu-quan" &&
	(20 - p) > random(10) &&
	weapon && !me->is_busy() &&
	me->query("env/zhijian")) {
		msg = "$N���г�����$nһ�������ַɳ���\n"NOR;
		weapon->move(environment(me));
		msg += HIW"$N���һ����������ָ���̣�����ָʹ��һ�С��������á���\n"NOR;
		if (random(me->query_int()) > ob->query_int()/5) {
			msg += HBRED"�������$n������Ѩ��\n"NOR;
			ob->start_busy(5+random(4));
		} else {
			msg += HBGRN"���$n�����ϵ�������������\n"NOR;
			me->start_busy(3+random(3));
		}
		message_vision(msg, me, ob);
		return -damage;
        }
        return 0;
}
