// hamagong.c ��󡹦
// Modified by snowman 01/08/2000


#include <ansi.h>
#include <combat.h>

inherit FORCE;

#include <combat_msg.h>

mapping *action = ({
([      "action": "$N����������һ�ֳŵأ����Ӻ�ͦ��ֻ��һ����$n��$l�ĳ�",
        "dodge": 10,
        "force": 200,
        "lvl" : 0,
        "damage_type": "����"
]),
([      "action": "$N˫���ڵ���һ�ţ����Ӻ��ذ���һԾ���ߣ�����$n����ǰ��������$pֱ������",
        "weapon" : "��Ե",
        "dodge": 15,
        "force": 230,
        "damage" : 20,
        "lvl" : 0,
        "damage_type": "����"
]),
([      "action": "$N��Ȼ�����Ծ��˫����$n�������ߣ�$Pֻ������װ�裬����ȴ�����ʱ��������",
        "dodge": 25,
        "force": 340,
        "lvl" : 20,
        "weapon": "����",
        "damage_type": "����"
]),
([      "action": "$NͻȻ�������Լ�������ץһ�ѣ��ַ������Լ����Ϻ���һ�ţ�һ�ƻ�������;����ر䣬ʵ��֪����δ�",
        "dodge": 15,
        "force": 350,
        "lvl" : 50,
        "damage_type": "����"
]),
([      "action": "ͻȻ֮�䣬$N������������ȫȻ���أ�΢΢��ͷ��һ����ĭ��$n$l��ȥ",
        "weapon" : "��Һ",
        "dodge": 10,
        "force": 290,
        "damage" : 40,
        "lvl" : 70,
        "damage_type": "����"
]),
([      "action": "$N˿��������ɫ��˫��΢��������ƽ�죬���ƻ��������󡹦�ľ���������һ������$n",
        "dodge": 15,
        "force": 380,
        "lvl" : 90,
        "damage_type": "����"
]),
([      "action": "$NĬ��ھ�����������ֻ����ת����˳�죬����һ������Ծ�𣬹���һ���к���˫�ƶ���$n�ĳ�",
        "dodge": 11,
        "force": 350,
        "lvl" : 110,
        "damage_type": "����"
]),
([      "action": "$N΢΢��ͷ������һЦ��һ��ҧ��$n",
        "dodge": 15,
        "force": 150,
        "damage": 100,
        "lvl" : 130,
        "weapon": "����",
        "damage_type": "����"
]),
([      "action": "����$N˫��΢����˫�ƻ��գ�Ȼ����$nһ��һ�£�һ��һ�գ���Ȼ����",
        "dodge": 10,
        "force": 330,
        "lvl" : 140,
        "damage_type": "����"
]),
([      "action": "ͻȻ֮�䣬$N������������ȫȻ���أ��������ף���Ȼ������$n$l��ץһ��",
        "dodge": 17,
        "force": 300,
        "damage": 40,
        "lvl" : 110,
        "damage_type": "ץ��"
]),
([  	"action": "$N���۱�ס����������Ƭ�̣���Ծ�����۾�Ҳ����������˫�Ʊ���$n�ķ������˳�ȥ",
        "dodge": 10,
        "force": 450,
        "lvl" : 190,
        "damage_type": "����"
]),
([  	"action": "$N�Ų�ҡҡ�ϻϵĿ���ȥ���Ͼͻ��������Ȼ˫��һ�䡢һ�ǣ����и��һ���кȣ�������$n��Ȼ�Ƴ�",
        "dodge": 15,
        "force": 440,
        "lvl" : 220,
        "damage_type": "����"
]),
});

int valid_enable(string usage) 
{ 
	return usage == "force" || usage=="strike" || usage =="parry"; 
}

mapping exercise_msg(object me)
{
  	return ([
    		"status_msg" : HIW + me->name()+"����ڵ��ϣ���ð����" NOR,
    		"heal_msg" : HIW"$Nȫ����ɣ�����ڵ��Ͽ�ʼ�˹����ˡ���\n"NOR,
    		"heal_finish_msg" : HIW"$N���ۣ����Ĵ��һ����ȫ��İ���������ɢ��\n"NOR,
    		"heal_unfinish_msg" : "$N���ۣ����Ĵ��һ����վ������������ɫ�԰ף���������������\n",
    		"heal_halt_msg" : "$N��ð���������ۣ����Ĵ��һ����վ��������\n",
    	]);
}

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
        
        level   = (int) me->query_skill("hamagong",1);
        if ( me->query_temp("hmg_super_hit")
        && random(me->query_str()) > 35 
        && random(level) > 150 
        && me->query("max_neili") > 3000 
        && me->query("neili") > 1300 ) {
                me->add("neili", -50);
                me->delete_temp("hmg_super_hit");
                return ([
                	"action": HIC "$N�׵����ӣ�����΢�գ����й������Ľ���������˫����$n�����Ƴ������û�����������������" NOR,
                	"dodge" : 15,
                	"force": 750,
                	"damage_type": "����"
                ]);
        }
        
        if( random(10) == 5 )
        	me->add_temp("hmg_super_hit", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int valid_learn(object me)
{
	if( me->query_skill("hamagong", 1) < 100 )
        	return notify_fail("��󡹦�������ʲô�ط���������ϰ�ġ�\n");
        return 1;
}

string exert_function_file(string func)
{
       	return __DIR__"hamagong/" + func;
}

string perform_action_file(string action)
{
        return __DIR__"hamagong/" + action;
}

void skill_improved(object me)
{
	int skill = me->query_skill("hamagong", 1);
	
	if( skill > me->query("hmg/lian_level") )
		me->set("hmg/lian_level", skill);
	else return;
	
	if( skill % 2 == 0 ){
		me->add("max_jingli", random(8)+1);
		tell_object(me, "��ĸ�󡹦��������ľ�����Ϊ��\n");
	}
	else	{
		me->add("max_neili", random(8)+1);
		tell_object(me, "��ĸ�󡹦���������������Ϊ��\n");
	}
}

int practice_skill(object me)
{
       	if((int)me->query_skill("hamagong", 1) >= 100 ){
           	if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
                   	me->improve_skill("hamagong", (int)me->query_int());
                   	me->add("neili", -(20+random(30))); 
                   	me->add("potential", -1*(1+random(3)));
                   	return 1;
           	}
           	else return notify_fail("�����ڵ���Ϊ��������߸�󡹦�ˡ�\n");
       	} 
       	else return notify_fail("��󡹦���������ϰ��\n");
}


string *parry = ({
"$PͻȻ����һ�ã�΢΢��ͷ��һ����ĭ��$p$l�³���ȥ�����ң�",
"$P��Ȼ�ſڼ�ҧ�������ƺ������������ſڿ�ݣ��������Զ�����",
"$P��Ȼ�ϵл��ȣ����ƻ���$p�ķ�λ��ͬʱ����һ��Ũ̵�½�������",
"����$p����������಻��һ�磬$P����ſڣ�һ������һ��������$p����ҧ�䣡",
"$P����һ����ĭ���£�����̵����ĭҲ�����˹�������������ȭ��֮��ʹ�ã�",
"$P��󡹦��ת���ã�������֮��������֮��һ���Ļ�$p��",
"$P�����������$p����������������$p��ץ���£�",
"$p���иմ���$P��$N΢΢��ͷ��һ��ҧ��$p��",
"$P�䵹�о�������Ŀ��ֻ֫�б�ƽʱ��Ϊ�������ۼ�$p����Ĩ�����������ƻ�����",
"$P���˾�����������������$p����������°�ĭ����ͷ��ײ��",
});

int ob_hit(object ob, object me, int damage)
{
        string msg, *limbs;
        mapping prepare;
        int ap, dp, j = 0;
        
        
      	if( me->query_temp("fanzhen")){
         	me->delete_temp("fanzhen");
         	return 1;
        }
        
        if( ob->query("env/invisibility") ) return 0;
        
        if (!me->query_temp("hmg_nizhuan") 
        || me->query_skill_mapped("force") != "hamagong"
        || me->query_skill_mapped("strike") != "hamagong"
        || me->query_skill_mapped("parry") != "hamagong"
        || me->query("combat_exp") < ob->query("combat_exp")/2
        || ob->query_temp("weapon")
        || me->query_temp("weapon") ) return 0;
      
        prepare = ob->query_skill_prepare();
        if (!sizeof(prepare)) msg = "unarmed";
        else msg = keys(prepare)[0];
        
        ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
        dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
        if ( ob->query("neili") > me->query("neili") * 2 ) ap *= 2;
        if ( random(10) < 3 ) me->set_temp("fanzhen", 1);   

	ap = ABS(ap);
        dp = ABS(dp);
	        
        if ( random( dp * 2 ) > ap ) { 
        	me->add_temp("fanzhen",1);
        	if ( random(me->query_skill("hamagong", 1)) < ob->query_skill("parry")/2 )
        		msg = "ֻ��������ʵ����$n���ϣ���$pãȻδ����ȫ����ᣡ\n";
        	else {
        		limbs = ob->query("limbs");
        		msg = parry[random(sizeof(parry))];
        		msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
         		msg += "���$N����֮�⣡\n";
         		if( random(10) < 8 ){
         			ob->receive_damage("qi", damage/2 , me);
              			ob->receive_wound("qi", damage/4 , me);
              			j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              			msg += damage_msg(damage, "�˺�") + "( $n"+eff_status_msg(j)+" )\n";
              		}
              		
              		else{
              			msg += "�Ҷ�$P˳�Ƶ���������ÿ�δ�����ˣ����������飬һʱ֮�����޷����ϡ�\n";
              			ob->receive_damage("qi", damage/4 , me);
              			ob->receive_wound("qi", damage/8 , me);
              			j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              			msg += damage_msg(damage, "�˺�") + "( $n"+eff_status_msg(j)+" )\n";
              			ob->start_busy(2);
              		}
         	}
         	message_vision(msg, ob, me);
              	return -8000;
        }
        
        else if( random(ap + dp) > ap ) {
        	msg = parry[random(sizeof(parry))];
        	msg += "$n��Ȼ�䱻$N����һ���������в��ɵ����˼��֣�\n";
        	ob->start_busy(1);
              	message_vision(msg, me, ob);
        	return -damage/2;           
        }
        
        else return 0;
}

int help(object me)
{
	write(HIC"\n��󡹦��"NOR"\n");
	write(@HELP
	��󡹦Ϊ����ʱ���¸���ŷ�����������˹���ͬ���������գ�����ƫ�ţ���
	�ٽݾ�����ʹ�˷���ʤ����ŷ��������һ�η���ʧ���ʱ�ڣ�Ҳʹ��������
	���˾������ֿ���ٵص��书���͸�󡹦�໥��ϣ��ɳƵ��������µ�һ��
	����
	
HELP
	);
	return 1;
}

