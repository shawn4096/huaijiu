// pixie-jian.c ��а����
// by snowman 22/11/98
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
"ͻȻ֮�䣬��Ӱ���ϣ�$n��󻬳����࣬��ʱ�ֻص���ԭ�أ������$N��һ�С�\n",
"$n�ֱۻ�ת����$N������һ�ƣ�˳������һ�ԡ�\n",
"$n�����������$N������Ѹ���ޱȵ�һ����˳������һ�ԡ�\n",
"$n����Ʈ����������ȣ�ת�˼�ת���Ʋ���$N����󣬶����$N��һ�С�\n",
"$Nֻ����ǰһ�����ƺ�����$n����һ�ϣ����漴�ּ�$n�ص�ԭ�أ�ȴ�ƴ�δ�뿪��\n",
"$N�۾�һ����$n��û����Ӱ��ͻȻ$n���������һ��$N��ͷ������Ծ����\n",
"$n��ȻһЦ������֮����$N����֪����Ǻã�ͣס�˹�����\n",
"$n��һ������һ������һ������һ������$N���������������������²����������ް��������\n",
"$n���ִ�Ĵָ��ʳָ��סһ���廨�룬����һ�٣���ס���ƣ�$N����ʽ��ʹ����ȥ��\n",
"$n��������������ʳָ��������$N����Ŀ���̣��������ܾ��˵Ĵ򷨣�\n",
"$n���ҵ���أ�Ժ�����Ͼ��������$N���ޣ����ù��򣬺ù��򣡡�\n",
});


string  *msg = ({
"$N����һ�䣬��������۵�$n��ǰ����಻��һ�ߣ�����$w�Ѿ��̵�$n��$l",
"������Ӱ������$N���е�$w��$n��$lֱ�����������籼�ף��ܲ��ɱ�",
"$N������ϣ�������$n�ļ���һ���ٺ�ɳ�ȥ�������е�$wȴָ��$n��$l",
"$NͻȻԾ�����࣬$nһ̧ͷ�����ֿ��в���$N����Ӱ����һ�ɺ���ȴ�����Ϯ��",
"$N��һ������һ������һ������һ������$n��������������������һת������$n",
"�����$N���������ϣ�˫�����õ��ģ���������֮������$n����֮�ʵ���$w����$n",
"$N����Ʈ����������ȣ�ת�˼�ת���Ʋ�������һ������$n������֮��֮�죬ֱ�Ƿ�����˼",
"$N����һ�٣�վ��Ƭ�̣�����$n����󷽻������࣬���ſ������׵Ļص�ԭ��",
"$NǱ���������������ˣ�����$n������ת������$w��ʹ����Ҳ��������һ�㣬Խ��Խ��",
"ͻȻ$N����$w����һ�ã�����$n΢һ����֮��ֱȡ$n��$l���Ƶ���������",
"����$nһ��֮�ʣ�$N����Ծ�����ߣ���������أ����Ӹ�������ˢˢ��������$n��ȥ",
"$N��Ȼ����Ϊ�����ó�����������Ӱ���ٻ���$n������$w�û����������н���$n��$l",
"$nֻ����ǰһ�����ƺ�����$N����һ�ϣ����漴�ּ�$N�ص�ԭ�أ�ȴ�ƴ�δ�뿪",
"$Nһ����У����������ڰ����һת������ޱȵķ�������������$w�ƿ�ֱ��$n$l",
"$N������������ȣ�Ʈ����ȥ��ֱ�����̣����е�$wȴ���Ƕ���$n����",
"$Nһ����Ц������Ｒ����ǰ�������Ƕ������ã�һ˲֮�䣬��$n����Ѳ���һ�ߣ����˵ı��Ӽ���Ҫ����һ��",
"$N�����������$n������Ѹ���ޱȵ�һ���������ֱۻ�ת������$n������һ��",
"$Nһ��ͦ�̣��������ţ���̬֮�У������л�ɽ��Ů������ѧ����Ů��ʮ��ʽ���ķ��ˣ�ֻ�Ǵ���������ɭɭ��а��",
"$N����һȦ����ת$w����ش̳���ˢˢˢ������ʽ�����о���ָ��$n��Ҫ��"
});


mapping *action = ({
([      "action":"ͻȻ֮�䣬��Ӱ���ϣ�$N��󻬳����࣬��ʱ�ֻص���ԭ��",
        "force" : 90,
        "dodge" : 50,
        "damage": 70,
        "lvl" : 0,
        "skill_name" : "��Ӱ����",
        "damage_type":  "����"
]),
([      "action":"$N�����������$n������Ѹ���ޱȵ�һ����$n��Щ�����Լ�С��",
        "force" : 100,
        "dodge" : 50,
        "damage": 60,
        "lvl" : 10,
        "skill_name" : "�Լ�С��",
        "damage_type":  "����"
]),
([      "action":"�����$N�����ϣ��ڵ�$n�����̳�һ��������˲��Ծ��ԭ��",
       "force" : 120,
        "dodge" : 45,
        "damage": 70,
        "lvl" : 20,
        "skill_name" : "������",
        "damage_type":  "����"
]),
([      "action":"$nֻ����ǰһ�����ƺ�����$N����һ�ϣ����漴�ּ�$N�ص�ԭ�أ�ȴ�ƴ�δ�뿪",
        "force" : 145,
        "dodge" : 45,
        "damage": 75,
        "lvl" : 30,
        "skill_name" : "��ǰһ��",
        "damage_type":  "����"
]),
([      "action":"$NͻȻ���з�һ�䣬һ�С�����Ū�ѡ���$w�����������ʽ������ס�$n����֮�з������",
        "force" : 150,
        "dodge" : 43,
        "damage": 90,
        "lvl" : 40,
        "skill_name" : "�з�һ��",
        "damage_type":  "����"
]),
([      "action":"$N����ˣ�$n��׷������ͻȻ��$N����$n��ǰ��һ�С��������𡹣�����$wֱָ$n��$l",
        "force" : 140,
        "dodge" : 50,
        "damage": 100,
        "lvl" : 50,
        "skill_name" : "�����",
        "damage_type":  "����"
]),
([      "action":"$N����Ʈ����������ȣ�ת�˼�ת��һ�С��������������Ʋ���$n�����",
        "force" : 170,
        "dodge" : 45,
        "damage": 95,
        "lvl" : 60,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$Nһ����Ц��һ�С����Ǹ��¡�������Ｒ����ǰ��һ˲֮�䣬��$n����Ѳ���һ�ߣ�$w�漴�ݳ�",
        "force" : 140,
        "dodge" : 35,
        "damage": 110,
        "lvl" : 70,
        "skill_name" : "������ǰ",
        "damage_type":  "����"
]),
([      "action":"$N�ȵ������ã������㼴�γ�$w��һ�С����ഩ���������ִ̳�������ת����ȥ",
        "force" : 205,
        "dodge" : 35,
        "damage": 120,
        "lvl" : 80,
        "skill_name" : "���ִ̳�",
        "damage_type":  "����"
]),
([      "action":"$N��س嵽$n��ǰ��һ�С���ظ��Ŀ��������$wֱ��$n���ۣ�$n��æ�мܣ�����$N��$wͻȻת��",
        "force" : 240,
        "dodge" : 50,
        "damage": 145,
        "lvl" : 90,
        "skill_name" : "ֱ������",
        "damage_type":  "����"
]),
([      "action":"$N����Ծ��$ņ��һ����������$Nһ�С����Ƿɶ项������ֱ����£�����$w����$n��$l",
        "force" : 270,
        "dodge" : 60,
        "damage": 170,
        "lvl" : 100,
        "skill_name" : "����Ծ��",
        "damage_type":  "����"
]),
([      "action":"$Nһ�С�Ⱥа���ס�����֦�Ͱڣ�$n��ǰ�·�ͻȻ�������߰˸�$N���߰�ֻ$wһ�����$n",
        "force" : 300,
        "dodge" : 75,
        "damage": 200,
        "lvl" : 110,
        "skill_name" : "Ⱥа����",
        "damage_type":  "����"
]),
});


int valid_enable(string usage) 
{ 
    return usage == "sword" || usage == "dodge" || usage == "parry"; 
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
        int i, level, neili, force;
        level   = (int) me->query_skill("pixie-jian",1);
        force = me->query_skill("force");
        neili = me->query("neili");

        if (level > 120 && force > 180 && neili > 300 
            && me->query("max_neili") > 1200
            && random(me->query_dex()) > 25){
            return([      
                   "action": msg[random(sizeof(msg))],                   
                   "force" : force+random(force),
                   "dodge" : 20+random(60),
                   "parry" : 20+random(60),
                   "damage": me->query_temp("cimu")?force/2+random(force):force,
                   "damage_type" : "����",
                   ]);
            }
           for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

string query_parry_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
       if (me->query_skill("pixie-jian",1) >= 180) return 1;
        return notify_fail("��а����ֻ��ͨ����ϰ���������䡷��ѧϰ��\n");
}

string perform_action_file(string action)
{
        return __DIR__"pixie-jian/" + action;
}


int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("��ľ���������\n");
       if (me->query_skill("pixie-jian",1) < 180) return 0;
        me->receive_damage("jingli", 30);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
   	object weapon = me->query_temp("weapon");

    	if (!weapon) return;
   	if(((string)weapon->query("id")=="xiuhua zhen" || (string)weapon->query("id")=="qijue zhen")  
      	&& random(me->query_str()) > victim->query_str()/2){
		victim->receive_wound("qi", me->query_str()+random(80));
		if (random(5) > 3) return HIR "ֻ�����͡�һ����һ��Ѫ˿��"+victim->name()+"���̵���״������\n" NOR;
	}
}

int double_attack(object me)
{	
   	if ( me->query_skill("pixie-jian", 1) >= 60
     	&& me->query_skill_mapped("sword") == "pixie-jian"
     	&& me->query("gender") == "����")
             	return 1;
}
	
