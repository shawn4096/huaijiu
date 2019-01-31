// yitian-tulong.c ��������������
// xQin 9/1/98
// Under Modify

#include <ansi.h>
#include <combat.h>

inherit SKILL;
//inherit F_SSERVER;

int raozhi(object me, object victim, object weapon, int damage);

nomask int parry_available() { return 1; }
string *parry_msg = ({
	"$p����һ�ɾ���Ϯ���ؿڣ�����$Wһ��������һ����Ʋ���պ÷�ס��$P$w�����ơ�\n",
	"Σ��֮�У�$p��$W��$P��$w��һ����һ�������������ɵıܹ�����һ�����ǡ��䡹�־��е�һ�ꡣ\n",
	"$p$W���ӣ�����ʹ��һ�ǡ������־�����ס$P��$w��$WһƲһ�㣬���ӽ��ƴ���\n",
	"����$p$Wʹһ�С������־��е���Ʋ������$P�����ƣ��ԼӲ�������ǧ��һ��֮�ʣ�תΣΪ����\n",
});

string query_parry_msg(object weapon, object victim)
{
        object ob;

        if (!objectp(ob = victim->query_temp("weapon")) )
                return replace_string(parry_msg[random(sizeof(parry_msg))], "$W", random(2)?"����":"����");
        else
                return replace_string(parry_msg[random(sizeof(parry_msg))], "$W", ob->name());
}

mapping *action_unarmed = ({
([      "action":"$N���Ƽ�̽����ָ��ץ�����������������$n��$l",
        "force" : 160,
        "dodge" : 40,
        "parry" : 20,
        "damage": 50,
        "damage_type":  "����"
]),
([      "action":"$N�����ĳ������ƶ����κ���������������б�����ִ�������������",
        "force" : 180,
        "dodge" : 40,
        "parry" : 20,
        "damage": 90,
        "lvl" : 112,
        "damage_type":  "����"
]),
([      "action":"$Nһ�����ֲ������������ף�������������ƽƽ��ɨ������$n��̫��Ѩ",
        "force" : 160,
        "dodge" : 40,
        "parry" : 20,
        "damage": 50,
        "damage_type":  "����"
]),
([      "action":"$Nٿ��Ծ�𣬷����ǰ������һ��һ�ӣ�ȴ�ǡ��졹�־���һƲ",
        "force" : 160,
        "dodge" : 40,
        "parry" : 20,
        "damage": 50,
        "damage_type":  "����"
]),
([      "action":"$N����һ�䣬˫�Ʒ��裬��������ѩ������಻���������õ����ǡ�Ī���־�",
        "force" : 200,
        "dodge" : 0,
        "parry" : 20,
        "damage": 100,
        "damage_type":  "����"
]),
([      "action":"$Nת����������ȭ�ͳ���ȴ�ǡ��¡��־���һֱ���ĵ�һ��������$n��$l",
        "force" : 220,
        "dodge" : 30,
        "parry" : 20,
        "damage": 100,
        "damage_type":  "����"
]),
([      "action":"$N�����㣬�������磬���������ٿ����ʹһ���������־��е�һ����ץ��$n",
        "force" : 240,
        "dodge" : 80,
        "parry" : 20,
        "damage": 120,
        "damage_type":  "ץ��",
        "post_action":  (: call_other, "/adm/daemons/weapond.c", "bash_weapon" :)
]),
([      "action":"$N˫��һ�㣬�������࣬ʹ��һ�С������־��е�һ��ֱ���������ڰ���м�������",
        "force" : 260,
        "dodge" : 10,
        "parry" : 20,
        "damage": 100,
	"weapon": "����",
        "damage_type":  "����"
]),
([      "action":"$N��Хһ��������ֱ���������������ǽ���â����ʸӦ��������Ͼ�����粻���ɣ���һֱ���ǡ��桹�ֵ�����һ��",
        "force" : 200,
        "dodge" : 40,
        "parry" : 20,
        "damage": 100,
	"weapon": "����",
        "damage_type":  "����"
])
});

mapping *action_weapon = ({
([      "action" : "$N�������飬������磬$w�������������һ��������б��$n",
        "force" : 100,
        "dodge" : 15,
        "parry" : 20,
        "damage" : 50,
        "damage_type" : "����",
        "post_action":  (: call_other, "/adm/daemons/weapond.c", "bash_weapon" :)
]),
([      "action" : "$N������������»����������磬$wһת������$n��$l�����¿���֮�ʣ���Ʈ��������",
        "force" : 150,
        "dodge" : -10,
        "parry" : 20,
        "damage" : 70,
        "damage_type" : "����"
]),
([      "action" : "$N��������̤�ϣ��������֣�����ʵʵ�������Ϲ�â��˸�������͵ķ�����΢����",
        "force" : 150,
        "dodge" : -10,
        "parry" : 20,
        "damage" : 70,
        "damage_type" : "����"
]),
([      "action" : "$Nٿ��Ծ�𣬷����ǰ��$wһ��һ�ӣ�ȴ�ǡ��졹�־���һƲ",
        "force" : 100,
        "dodge" : 15,
        "parry" : 20,
        "damage" : 50,
        "damage_type" : "����"
]),
([      "action" : "$N$wһ��ʹһ�С�˭���־������������Ҳ�����ʱ����绯Ϊ��ǧ�����⣬��ס$n����",
        "force" : 170,
        "dodge" : 0,
        "parry" : 20,
        "damage" : 90,
        "damage_type" : "����"
]),
([      "action" : "$Nת��������$w�ͳ���ȴ�ǡ��¡��־���һֱ������$n��$l",
        "force" : 200,
        "dodge" : 10,
        "parry" : 20,
        "damage" : 120,
        "damage_type" : "����"
]),
([      "action" : "ͻȻ��$N$wʹ�С������־��е�һ�����͵�һ�죬����$n$l",
        "force" : 250,
        "dodge" : -15,
        "parry" : 20,
        "damage" : 140,
        "damage_type" : "����"
]),
([      "action" : "$N˫��һ�㣬�������࣬ʹ��һ�С������־��е�һ��ֱ������$w�ڰ���м�������",
        "force" : 200,
        "dodge" : 10,
        "parry" : 20,
        "damage" : 120,
        "damage_type" : "����"
]),
([      "action" : "$N����$w����ʯ��������������$n��̨Ѩһ·˳��ֱ�£�ʹ���ǡ��桹�־�������һ��һֱ�������鷨�еĲ��ʣ������ǻ�����ţ��",
        "force" : 250,
        "dodge" : -15,
        "parry" : 20,
        "damage" : 140,
        "damage_type" : "����"
])
});

//������ :) just an example
string  *special_msg = ({
HIY"$N������������»����������磬$wһת������$n��$l�����硰�족�ֵ�һ��"NOR,
HIY"����$N˫��һ�㣬�������࣬һ�С��족�־��еĵڶ��ᣬ��$w�ڰ���м�������"NOR,
HIY"$Nٿ��Ծ�𣬷����ǰ��$wһ��һ�ӣ�ȴ�ǡ��족�־���һƲ"NOR,
HIY"$N˳��ʹ�����족�ֵ�һ�࣬$wɨ��$n$l����������֮��"NOR,
});


int valid_enable(string usage) 
{ 
    return usage == "cuff" || usage == "parry" || usage == "sword"; 
}

mapping query_action(object me, object weapon)
{
        object victim;
        string *limbs, *msg, limb, msg1, msg2;

        if( !victim && me->is_fighting() ) victim = offensive_target(me);
        limbs = victim->query("limbs");
        limb = limbs[random(sizeof(limbs))];

	msg = ({
		HIW "ͻȻ��$N$w"HIW"�ƿգ�����$n"+limb+"��������;������΢������Ȼ���˹�ȥ��б��$p$l" NOR,
		HIY "$N�������Ž���������$w"HIY"��ס������ͻȻƽ�̣����⼱��������������δ�����һ��������$n�����ߴ�ҪѨ" NOR,
		HIC "$N����$w"HIC"������ǰ�������������һ�����Ρ�$n����һ��ɭɭ������ֱ�ƹ���" NOR,
	});

        msg1 = "�����һ�����죬$w����������ֱ����$p��$l";
        msg2 = "����$P�������֣�����һ�����������׵���$p$l����";

        if(me->query_temp("raozi_attack")){
                me->add("neili", -(me->query("jiali")));
		me->add("jingli", -(me->query("jiajin")));
                return ([
        	"action": me->query_temp("raozi_attack")==1?msg1:msg2,
        	"force" : 350+random(100),
        	"dodge" : 10,
        	"parry" : 20,
        	"damage" : 100+random(50),
        	"damage_type": me->query_temp("raozi_attack")==1?"����":"����",
		]);
                }
        if(me->query_temp("tian") > 4) me->delete_temp("tian");
        if(me->query_temp("tian")){
                me->add_temp("tian", 1);
                me->add("neili", -20);
        	return ([
        	"action": special_msg[me->query_temp("tian")-2],
        	"force" : 350+random(100),
        	"dodge" : 10,
        	"parry" : 20,
        	"damage" : 100+random(50),
        	"damage_type":"����",
		]);
		}
	 if (random(me->query_temp("raozhi")) > 100 ) {
		me->add("neili", -50);
        	return ([
        	"action": msg[random(sizeof(msg))],
        	"force" : 350+random(100),
        	"dodge" : 10,
        	"parry" : 20,
        	"damage" : 100+random(50),
        	"damage_type":"����",
		"post_action": (: raozhi :)
		]);
		}

        if (!weapon)
		return action_unarmed[random(sizeof(action_unarmed))];
        else
		return action_weapon[random(sizeof(action_weapon))];
       
}

int valid_learn(object me)
{
        if (me->query_skill("yitian-tulong",1) > 199) return 1;
        return notify_fail("������ͷ��һƬ���ң�������ᡸ�������������ľ������ڡ�\n");
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 40)
		return notify_fail("���������������ϰ����������������\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("���������������ϰ����������������\n");
	me->add("jingli", -30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yitian-tulong/" + action;
}

int raozhi(object me, object victim, object weapon,int damage)
{
	int sword, force, ap, dp;
	string type;

	sword = me->query_skill("sword");
	force = me->query_skill("force");
        ap = (sword + force + me->query("combat_exp")/2000) * (99+random(5));
        dp = (victim->query_skill("dodge") + victim->query_skill("parry") + victim->query("combat_exp")/2000) * 100;

//        limbs = victim->query("limbs");
//        limb = limbs[random(sizeof(limbs))];
        type = random(2)?"����":"����";
        
	if( damage < 0 && ap > dp ) 
	{
/*
           	damage = me->query_temp("apply/damage") + me->query_str() + me->query("jiali") + me->query("jiajin");
		damage = damage + random(force + sword) /10 ;
		if(me->query("neili") > random(victim->query("neili")*2) ) damage = damage + random(damage);
           	victim->receive_damage("qi", damage, me);
                if( random(damage) > (int)victim->query_temp("apply/armor"))
		victim->receive_wound("qi", damage - (int)victim->query_temp("apply/armor"), me); 

                me->add("neili", -(me->query("jiali")));
		me->add("jingli", -(me->query("jiajin")));
*/

		if (type == "����") me->set_temp("raozi_attack", 1);
                else me->set_temp("raozi_attack", 2);
                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 2);
                me->delete_temp("raozi_attack");

/*
		message_vision("�����һ�����죬"+weapon->name()+"����������ֱ����$p"+limb+"����\n",me,victim);
		else 
		message_vision("����$P�������֣�����һ�����������׵���$p"+limb+"��������\n",me,victim);

           	result = COMBAT_D->damage_msg(damage, type);
           	result = replace_string( result, "$l", limb);
           	result = replace_string( result, "$w", weapon->name());
           	str = COMBAT_D->status_msg((int)victim->query("qi") * 100 /(int)victim->query("max_qi"));

           	message_vision(result, me, victim);
           	message_vision("( $N"+str+" )\n", victim);
*/
		return 1;
	}

	return 1;
}
