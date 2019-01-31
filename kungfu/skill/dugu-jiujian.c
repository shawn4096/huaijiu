// dugu-jiujian.c ���¾Ž�

inherit SKILL;
#include <ansi.h>
#include <combat.h>

#include <combat_msg.h>

string *dodge_msg = ({
        "ȴ��$N̤ǰһ������ʽбָ$n���ұۣ���Ҫʹ$n������ˡ�\n",
        "$n�Թ�Ϊ�أ��Խ�Ϊ�ˣ�����������$N�͹����ػӳ���λ�����̩ɽ���������������\n",
        "$n����ͻ�䣬�����������������ڽ�ز����ʹ��ɽ�����ġ�������������ͼ��ʹ$N���С�\n",
        "$n�������ܣ��ٽ������ʹ�������両�ࡹ����$N���뵲��$N���С�\n",
        "$nͻȻʹ��������ɷ罣���ġ����ڤڤ�������Ƿ�λȴ����ƫ���������$Nһ�ʣ���ͼͻ��$N�Ĺ��ơ�\n"
        "$nͦ��һ�����ǡ����Ƴ�ᶡ��ش�$N����ͼ��$N�Ĺ��ƻ��⡣\n",
        "ֻ��$n���˷���������Ʈ�磬�����һʽ�������������������޶�����׽���ص�ס��$N�Ľ�����\n",
        "$n���˷�����ʹ����ɽ���С�������롹��ɭɭ�����������ܣ��ܿ���$N�����С�\n",
});

mapping *action = ({
([
        "action" :"$N�������ߣ�����һ��������һ������$nĪ������ֲ���$N��������ʵ" ,
        "force" : 190,
        "dodge" : 30,
        "parry" : 40,
        "damage": 80,
        "lvl" : 0,
        "damage_type" : "����"
]),
([
        "action" :"$NͻȻһ������$n��$l����һ��ȴ�����������ţ�$n�����޴룬��֪����Ǻ�",
        "force" : 210,
        "dodge" : 30,
        "parry" : 25,
        "damage": 100,
        "lvl" : 20,
        "damage_type" : "����"
]),
([      "action" : "$N���ֺὣ����$n��$l���������������е�һ����������Ȼ���$n���Կ��彣������",
        "force" : 230,
        "dodge" : 40,
        "parry" : 40,
        "damage": 100,
        "lvl" : 40,
        "damage_type" : "����"
]),
([      "action" : "$N����һ��ָ��$n���������$n���������ڣ��˵����������ף�����˼��",
        "force" : 250,
        "dodge" : 50,
        "parry" : 40,
        "damage": 120,
        "lvl" : 60,
        "damage_type" : "����"
]),
([      "action" : "$N��$w����һ�ڣ�����$n�Լ���$wײ����������֮����ʵ�����Ѳ�",
        "force" : 270,
        "dodge" : 60,
        "parry" : 40,
        "damage": 140,
        "lvl" : 80,
        "damage_type" : "����"
]),
([      "action" : "$N��������ת��$n����������µ���$n�̳�һ������֪ʹ����ʲô����",
        "force" : 290,
        "dodge" : 50,
        "parry" : 35,
        "damage": 160,
        "lvl" : 100,
        "damage_type" : "����"
]),
([      "action" : "$N��Ю���ƣ��󿪴��ص��ҿ�һͨ�������нԻ���$n���Ƶ��������ȵ�$n���ò���",
        "force" : 310,
        "dodge" : 50,
        "parry" : 40,
        "damage": 180,
        "lvl" : 120,
        "damage_type" : "����"
]),
([      "action" : "$N�ٽ���ӣ�Ѹ���ޱȵص���$n��$l��ȴ���˿�������������ʲô��ʽ",
        "force" : 330,
        "dodge" : 55,
        "parry" : 30,
        "damage": 200,
        "lvl" : 140,
        "damage_type" : "����"
]),
([      "action" : "$N����ͻ��Ц�ݣ��ƺ��ѿ���$n���书��ʽ�����г����һ������$n��$l",
        "force" : 350,
        "dodge" : 60,
        "parry" : 40,
        "damage": 220,
        "lvl" : 160,
        "damage_type" : "����"
]),
});

int valid_enable(string usage)
{
	return (usage == "sword") || (usage == "parry") || (usage =="dodge");
}

int valid_learn(object me)
{
	mapping my_fam  = me->query("family");
	if(!my_fam || my_fam["master_name"] != "������")
		return notify_fail("�㲻�Ƿ�����ĵ��ӣ�����ѧϰ�����¾Ž�����\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("dugu-jiujian",1) > 60)
		return notify_fail("���׽����Ҿͽ̵�������Ժ��Ҫ�����Լ�ȥ�����ˡ�\n");
	return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
//	victim->set_temp("must_be_hit", 1);
	victim->add_temp("lost_attack", random(3));
	call_out("remove_eff", me->query_skill("sword")/10, victim);
}

void remove_eff(object victim)
{
	if (!victim) return;
	victim->delete_temp("must_be_hit");
}

mapping query_action(object me,object weapon)
{
	int i, level;

	level = (int)me->query_skill("dugu-jiujian", 1);
	for(i = sizeof(action); i > 0; i--)
	if(level > action[i-1]["lvl"])
		return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	return notify_fail("���¾Ž�ֻ��ͨ����������ߡ�\n");
}

string perform_action_file(string action)
{
	return __DIR__"dugu-jiujian/" + action;
}
