// tiezhang-zhangfa �����Ʒ�
// BY BOBO@SJ 
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N����һ������һ�С��ƴ����¡��������Բ����������򣬵�ʱ��$n��������б������һ�ӣ�����$p$l",
        "dodge": 15,
        "force": 240,
        "parry": 40,
        "lvl": 0,
        "damage_type": "����"
]),
([      "action": "$Nʹһ�С���ˮ���������ұ�ͻ��ץ��$n�����ƶ�Ȼ�����쳤���ұۣ��ɿ��һ��������ն��$n��$l",
        "dodge": 20,
        "force": 280,
        "parry": 25,
        "lvl": 10,
        "damage_type": "����"
]),
([      "action": "$NͻȻʹһʽ�����ƻ��衹��˫��������һ��һ����裬����һ����ת�����ˣ�����һ�ƣ�ѹ��$n",
        "dodge": 25,
        "force": 320,
        "parry": 0,
        "lvl": 25,
        "damage_type": "����"
]),
([      "action": "$Nһ�С�����Ǭ������һ���ĳ��Ժ��͵ز���������ұ��������¼���������Ĵ������ָ��Ȧ�͵�$n��$l",
        "dodge": 20,
        "force": 280,
        "parry": 15,
        "lvl": 40,
        "damage_type": "����"
]),
([      "action": "$Nһ�С����ո��¡�������һ��һ�գ�һ����˿��������һ��֮�䣬һ�������ޱȵ������Ŷ�Ȼ����",
        "dodge": 35,
        "force": 320,
        "parry": 20,
        "lvl": 65,
        "damage_type": "����"
]),
([      "action": "$N���б���һʽ������Ϊ������˫�ƺ���г�����Ե�ŵݳ������غ�Х֮������������֮�����ɴ˶���",
        "dodge": 10,
        "force": 350,
        "parry": 35,
        "lvl": 80,
        "damage_type": "����"
]),
([      "action": "$Nһ�С����޵����������ƴ�Ȧ����������СȦ�������������������һ��֮�£��޴���ھ�ѹ��$n��$l",
        "dodge": 5,
        "force": 400,
        "parry": 20,
        "lvl": 100,
        "damage_type": "����"
]),
([      "action": "$Nһ�С���ָ��ɽ������һ�����������������ţ���һ��ȴ��Ѹ���ޱȵ�һ�Ƽ��գ�˫����һ��ȥ���绢",
        "dodge": 20,
        "force": 450,
        "parry": 15,
        "lvl": 120,
        "damage_type": "����"
]),
});


int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level, j;

	switch(me->query_temp("tz/heyi")){
		case 1:
			return ([
 				"action": CYN"$NͻȻ����һ�Σ��۽�$n������һ�����������������������$p����ֱ�Ķ��£�"NOR,
                  		"force": 450,
                  		"parry": 10,
                  		"dodge": 20,
                  		"damage": 30,
                  		"damage_type": "����"
                	]);
                	break;
                case 2:
                	return ([
 				"action": HIG"������$N����һת������$n���ԣ�����˳���ĳ�����һ�п���ƽ�ͣ�ʵ���ں�����������ޱȣ�"NOR,
                  		"force": 450,
                  		"parry": 10,
                  		"dodge": 20,
                  		"damage": 30,
                  		"damage_type": "����"
                	]);
                	break;
        }
                
        if (random(me->query_skill("strike", 1)) > 100 
        && random(me->query_skill("tiezhang-zhangfa", 1)) > 100 
        && me->query_skill("force") > 100
	&& random(10)>4
        && me->query("neili") > 30 
        && !me->query_temp("tzzf") ) {
                me->add("neili", -20);
                return ([
 			"action": HIB"$NͻȻ���һ�������м��ɶ���˫�Ʒ��ɣ���������������$nֱ�˶��£������б������ء���һ���̶���Х��"NOR,
                  	"force": 550,
                  	"parry": 10,
                  	"dodge": 40,
                  	"damage": 30,
                  	"damage_type": "����"
                ]);
        }
        
        level = me->query_skill("tiezhang-zhangfa",1);
     	for(i = sizeof(action); i > 0; i--) {
                if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);      
 			if (me->query_temp("tzzf") )      
 				return ([  
					"action" : WHT+action[j]["action"]+NOR,
 					"force" : action[j]["force"] + me->query_str() * 2,
 					"damage": 10,
 					"dodge": action[j]["dodge"]+random(20),
 					"parry": 15+random(10),
					"lvl" : action[j]["lvl"],
 					"weapon" : "����",
					"damage_type" : action[j]["damage_type"],
  				]);
  			return action[NewRandom(i, 20, level/5)];
		}
	}
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʒ�������֡�\n");
        if ((int)me->query_skill("guiyuan-tunafa", 1) < 15)
                return notify_fail("��Ĺ�Ԫ���ŷ���򲻹����޷��������Ʒ���\n");
        if ((int)me->query("max_neili") < 40)
                return notify_fail("�������̫�����޷��������Ʒ�");
        return 1;
}


int practice_skill(object me)
{
        int lvl = me->query_skill("tiezhang-zhangfa", 1);
        int i = sizeof(action);
        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("jingli") < 40)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("������������������Ʒ���\n");

        if (me->query_skill("tiezhang-zhangfa", 1) < 50)
                me->receive_damage("jingli", 20);
        else
                me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tiezhang-zhangfa/" + action;
}

