// canglang-goufa.c ���˹���
// by aug   99.9.10
// �������֣�����sld�Ĺ��Ӻ���Ҳ����ô����
// �ĳ�dagger�������֣�olives����
// tenglong-dagger ����ذ��????����ôԽ������Խ��......
// modified by Olives@SJ 4/18/2001
// ������򽫼���6��pfm
// ������ν���������У�Ӣ����ʽ
// �ֱ��ڲ�ͬ��������ò�ͬ��pfm
inherit SKILL;
#include <ansi.h>
#include <combat.h>


void post_action(object me,object victim,object weapon,int damage)
{
	int ap,dp,pp;
	
	if(!victim->is_fighting(me)
        ||  victim == me
        ||  victim->is_ghost()
        || !living(victim)
        ||  victim->query_temp("sld/pfm")
        ||  victim->query_temp("sld/post_action"))
        	return;
        victim->set_temp("sld/post_action",1);
        if( damage > 0 )
        {
        	
                if( objectp(me) )
                {
                 ap = COMBAT_D->skill_power(me,"dagger",SKILL_USAGE_ATTACK);
		 dp = COMBAT_D->skill_power(victim,"dodge",SKILL_USAGE_DEFENSE);
		 pp = COMBAT_D->skill_power(victim,"parry",SKILL_USAGE_DEFENSE);
	         if(random(ap+dp)>dp
                 && random(ap+pp)>pp
                   && random(ap+dp+pp)>(pp+dp+ap/2))
                	{
                        	message_vision(GRN"$N�����������ٳ���������ϸ���¾�Ȼû�а�㣬$n����Ƭ�̣������޴����֡�\n"NOR,me,victim);
                        	message_vision(GRN"$N�û�����һ�У�\n"NOR,me,victim);
 				if(objectp(weapon)
 				&& weapon->query("skill_type")=="dagger")
 					COMBAT_D->do_attack(me,victim,weapon,TYPE_QUICK);
                	}
                  else if(random(ap+dp+pp)>(dp+pp))
                	{
                		message_vision(GRN"$N����"+weapon->name()+GRN+"��̼��£�$nһ��������ͱ�$N���̼��¡�\n"NOR,me,victim);
                		if(objectp(weapon) 
             		    	&& weapon->query("skill_type")== "dagger")
             		    		{
             		    			COMBAT_D->do_attack(me,victim,weapon,TYPE_QUICK);
             		    			if(random(me->query("combat_exp"))>victim->query("combat_exp")/2)
             		    				COMBAT_D->do_attack(me,victim,weapon,TYPE_RIPOSTE);
                        		}
                	}
                        else if(random(ap+dp)>dp && random(ap+pp)>pp)
                	{
	                         message_vision(GRN"$N���������ٳ���"+weapon->query("name")+"���Ʋ�������$nһ�����С�\n"NOR,me,victim);
	                         message_vision(GRN"��$N����$n��ͬʱ��$nҲͬʱ����$N��Ҫ����$N��ɫ�Ұף�ҡҡ��׹��\n"NOR,me,victim);
                        	 me->receive_wound("qi",damage/4);
                        	 if(objectp(weapon) 
             		    	 && weapon->query("skill_type")== "dagger")
             		    		{
             		    			COMBAT_D->do_attack(me,victim,weapon,TYPE_QUICK);
             				}
                        	 COMBAT_D->report_status(me,1);
                		}
                }
        }
        victim->delete_temp("sld/post_action");
}


mapping *action = ({
([     "action":   "$N���β�����һ�С��������项������$wֱ��$n��˫Ŀ��ȥ",
        "force" : 50,
        "dodge" : 10,
        "parry" : -10,
        "damage": 140,
        "lvl" : 0,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([     "action":   "$Nһ�С��������������$w��Ӱ���Σ���$n��$l��ȥ",
        "force" : 60,
        "parry" : -5,
        "damage": 145,
        "lvl" : 40,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([     "action": "$N�͵ظ���ǰ�壬һ�С�����������������$wֱ�ö��ϣ�ֱ��$n��ͷ����ȥ",
        "force" : 70,
        "dodge" : 5,
        "parry" : 10,
        "damage": 155,
        "lvl" : 80,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$Nһ����ʹһ�С����ڻ�Ծ����$w����һ�е�����$n��$l",
        "force" : 90,
        "dodge" : 15,
        "damage": 165,
        "lvl" : 100,
        "skill_name" : "��;ͬ��",
        "damage_type" : "����"
]),
([      "action" : "$N����$w��󳷣�����ǰƽƽ����һ�С�����������$n��$l",
        "force" : 80,
        "dodge" : 20,
        "damage": 180,
        "lvl" : 140,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action" : "$Nһת��$w���б����һ�С������鳲��������$n��$l",
        "force" : 95,
        "dodge" : 15,
        "damage": 190,
        "lvl" : 160,
        "skill_name" : "�����鳲",
        "damage_type" : "����"
]),
([      "action" : "$N�ҽ���ǰһ������ϥ����һ�С�����Ϸ���$w��ǰ�Ϸ�����$n��$l",
        "force" : 90,
        "dodge" : 20,
        "damage": 210,
        "lvl" : 180,
        "skill_name" : "����Ϸ��",
        "damage_type" : "����"
]),

([      "action" : "$N���λζ��������ϣ�����$n�Ļ��У�һ�С�������衹����$w�ݺݴ���$n���ؿڡ�",
        "force" : 120,
        "dodge" : 25,
        "damage": 250,
        "lvl" : 200,
        "skill_name" : "�������",
        "damage_type" : "����",
	"post_action" : (: call_other, __FILE__, "post_action" :),
]),
});

int valid_enable(string usage) { return usage == "dagger" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("dulong-dafa", 1) < 10)
                return notify_fail("��Ķ����󷨻��̫ǳ���޷�ѧϰ����ذ����\n");
        return 1;
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
        int i, level,temp;
        object target;
        object *enemy;

        level = me->query_skill("tenglong-bifa",1);

        enemy = me->query_enemy();
        if(sizeof(enemy)>0)
        {
       		target = enemy[random(sizeof(enemy))];
	        temp = target->query_skill("dodge");
        	if (!temp)
        		temp=1;  
        	i = 100*me->query_skill("dagger")/temp;
        	i = (i>100?100:(i<50?50:i));
        	if(random(450)<(50+i) 
          	&& me->query("neili")>500
          	&& me->query("jingli")>500
          	&& target->is_busy()
          	&& living(target)
          	&& !target->query_temp("sld/post_action") 
          	&& !me->query_temp("sld/pfm"))
          	{
                	if(me->query_skill_prepared("leg") == "shenlong-tuifa" 
                  	&& me->query_skill("dulong-dafa",1)>300 
                  	&& me->query_skill_mapped("force") == "dulong-dafa" )
                        	call_out("autopfm",1,me,target);
                }
        }
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

void autopfm(object me,object target)
{
        object weapon;
        
        if(!me || !target ) return;
        
        me->add("neili",-500);
        me->add("jingli",-200);	
        weapon = me->query_temp("weapon");      
        if(!weapon 
        || weapon->query("skill_type")!="dagger") 
        	return;
        if(target->query_temp("weapon")) 
        {
                message_vision(HIC"\n$N����"+weapon->query("name")+HIC"�������ġ�������У�$nһ��û����͸���ס�˱�����\n$N�˻������������ȣ�"NOR,me,target);
	        weapon->unequip(); 
                if(me->is_fighting(target)
                && living(target))
                	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
                if(me->is_fighting(target)
                && living(target)) 
                 	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);       
                if(me->is_fighting(target) 
                && random(me->query("combat_exp")+target->query("combat_exp"))>target->query("combat_exp")
                && living(target))
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
                weapon->wield(); 
	 }
        else {
                message_vision(HIC"\n$N����"+weapon->query("name")+HIC"�������ġ�������У�$nһ��û����͸�$N��ס���ֽţ�\n$N�˻���������$n���ţ�"NOR,me,target);
                weapon->unequip(); 
                if(me->is_fighting(target)
                && living(target))
                  	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);       
                if(me->is_fighting(target) 
                && random(me->query("combat_exp")+target->query("combat_exp"))>target->query("combat_exp")
                && living(target))
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
                weapon->wield(); 
        }               
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "dagger")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("jingli") < 20)
              return notify_fail("��ľ�������������ذ����\n");
        if ((int)me->query("neili") < 5)
                return notify_fail("�����������������ذ����\n");
        me->receive_damage("jingli", 20);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tenglong-bifa/" + action;
}

