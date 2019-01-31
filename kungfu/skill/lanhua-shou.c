// lanhua-shou.c ������Ѩ��
// Modified by Numa 19990929
// Modified by Darken@SJ 20000415

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

inherit SKILL;

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

mapping *action = ({
([      "action" : "$N���ֺ�������֮�Σ���ָ��£��Ĩ������$n��������Ѩ",
        "force" : 180,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 0,
        "skill_name" : "����������ʽ",
        "damage_type" : "����"
]),
([      "action" : "$N������ҡ��������������������ԡ��㻮��$n",
        "force" : 240,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 30,
        "skill_name" : "����������ʽ",
        "damage_type" : "����"
]),
([      "action" : "$N����$n���˫�ֳ�Ȧ�������������ң��������϶��£�һ��һ����˫�ַ���$nҪѨ���ڡ�",
        "force" : 300,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 60,
        "skill_name" : "����ʽ",
        "damage_type" : "����"
]),
([      "action" : "$N����˳�ģ��Ƴ����գ������浽��˫������ֻ���������ǰ���·��ɷ���$n",
        "force" : 360,
        "dodge" : 5,
        "parry" : 2,
        "lvl" : 90,
        "skill_name" : "���ʽ",
        "damage_type" : "����"
]),
([      "action" : "$N���ƺ�����һ������������������Ʒ绢���ķ���$n",
        "force" : 420,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 120,
        "skill_name" : "��Ҷʽ",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
        object nvxu;

        if (me->query("thd/finish") == 1)
        {
        return 1;
        }
        else if (me->query("gender") == "����") {
                if (!(nvxu = find_object("/clone/npc/huang-son-in-law")))
                        nvxu = load_object("/clone/npc/huang-son-in-law");
                if (nvxu->query("winner") != me->query("id") || nvxu->query("death_count") < me->query("death_count")) 
                        return notify_fail("������Ѩ���˻Ƶ����Ҵ���ѧ���������ա�\n");
        }
        else if (me->query("gender") == "Ů��") {
                if (me->query("class") != "bonze" || me->query("family/family_name") != "������" || me->query("family/generation") > 3)
                        return notify_fail("������Ѩ���˶�������ʦ������ѧ����ͨ������ѧ�����ġ�\n");
        }
        else
                return notify_fail("������Ѩ���˻Ƶ����Ҵ���ѧ���������ա�\n");
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("ѧ������Ѩ�ֱ�����֡�\n");
        if ((int)me->query("max_neili") < 300)
                return notify_fail("�������̫�����޷�ʹ��������Ѩ�֡�\n");
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
        int i, level;

        level   = (int) me->query_skill("lanhua-shou",1);
        if (random(2) == 1 && me->query("env/lhspfm")=="˫��ʽ" && random(level) > 100 && me->query_skill("force") >= 150 && me->query("neili") >= 200) {
                me->add("neili", -50);
                me->set_temp("autopfm_lhs", 1);
                return ([
                	"action": HIR "$N˫�ֽ�����ʹ����"HIC"������˫��ʽ"HIR"������״�����������ٳ��ţ��������΢΢ҡ�ڡ�\n"CYN"$n������Щ������ȴ��Ȼ����$N��ʮָ�ѷ�����ǰ��" NOR,
                	"force": 550,
                	"dodge" : 50,
                	"parry" : 50,
                	"damage_type": "����"]);
        }
        me->delete_temp("autopfm_lhs");
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}


int practice_skill(object me)
{
        int lvl = me->query_skill("lanhua-shou", 1);
        int i = sizeof(action);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["lanhua-shou"])
                while (i--) 
                        if (lvl == action[i]["lvl"])
                                if (me->query("gender") == "Ů��")
                                        return notify_fail("�㽫�Ѿ�ѧ���������ʽ��ϰ��һ�飬���������ȥ��ʦ��ѧ�µ���ʽ���޷���ý����ˡ�\n");
                                else
                                        return notify_fail("�㽫�Ѿ�ѧ���������ʽ��ϰ��һ�飬���������ȥ������ѧ�µ���ʽ���޷���ý����ˡ�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��������Ѩ�ֱ�����֡�\n");
        if ((int)me->query("jingli") < 60)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 40)
                return notify_fail("�������������������Ѩ�֡�\n");
        me->receive_damage("jingli", 60);
        me->add("neili", -20);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int hurt, lvl = me->query_skill("hand");
        string name1,name2;
        object weapon = victim->query_temp("weapon");
        name1 = xue_name1[random(sizeof(xue_name1))];
        name2 = xue_name2[random(sizeof(xue_name2))];        

        if (victim->is_busy()) return 0;
        if ( lvl > 300) lvl = 300 + (lvl-300)/10;
        
        if (me->query_temp("autopfm_lhs")){
                if (random(lvl) > 120
                && random(me->query("neili")) > victim->query("neili")/2 ){
                        if (me->query("neili") > 40)
                                me->add("neili", -40);
                        else	me->set("neili", 0);
                        hurt = (victim->query("neili") < lvl / 6 ? victim->query("neili") : lvl / 6);
                        victim->add("neili", -hurt/2);
                        victim->receive_wound("qi", -lvl / 6);
                        victim->add("jingli", -lvl / 6);
                        me->delete_temp("autopfm_lhs");
                        return CYN "$n��$N����˫��ʽͬʱ�����ˡ�"RED + name1 + CYN"���͡�" RED + name2 + CYN"����\n$nֻ����ȫ���ʹ�������ھ������Ĵ��Ҵ�,һʱ��Ȼ�޷����ƣ�\n" NOR;
                } 
                return 0;
        } 
        else if (random(lvl) > 200 
        && random(10) > 7
        && !victim->query_temp("lhs")
        && me->query("neili") > victim->query("neili")) {
            	switch (me->query("env/lhspfm")) {
               		case "��Ҷʽ": 
                    		if (weapon){
                       			weapon->unwield();
                       			weapon->move(environment(victim));
                       			victim->add("neili", -lvl/5);
                       			return CYN "$n����Ҷʽ�����ˡ�"HIR+name2+CYN"������һ�飬"+weapon->query("name")+CYN"�ѳֲ�ס�����ڵ��ϡ�\n" NOR; 
                       		} 
                       		else {
                       			victim->add("neili", -lvl/5);
                       			return CYN "$n����Ҷʽ�����ˡ�"HIR+name2+CYN"������һ�飬����Ҳ�ܵ����񵴣�\n" NOR; 
                       		}
                       		break;
               		case "���ʽ": 
                    		victim->add_temp("apply/dexerity",-lvl/20);
                    		victim->add_temp("apply/strength",-lvl/20);
                    		victim->add_temp("apply/constitution",-lvl/20);
                    		victim->add_temp("apply/intelligence",-lvl/20);
                    		victim->set_temp("lhs", 1); 
                    		call_out("remove_effect", lvl/10, victim, lvl/20);
                    		return CYN "$n�����ʽ����������������Ѩ��ս�������\n" NOR;
                    		break;
               		case "����ʽ": 
                    		victim->start_busy(1 + random(2));
                    		victim->set_temp("lhs", 1); 
                    		if (weapon) {
                        		victim->map_skill(weapon->query("skill_type"));
                        		victim->set_temp("no_enable",1);
                        	} 
                        	else {
                        		victim->prepare_skill("leg");
                        		victim->prepare_skill("hand");
                        		victim->prepare_skill("strike");
                        		victim->prepare_skill("cuff");
                        		victim->prepare_skill("claw");
                        		victim->prepare_skill("finger");
                        		victim->set_temp("no_prepare",1);
                        	}
                    		call_out("remove_special", lvl/10, victim);
                    		return CYN "$n������ʽ�����ˡ�"HIR+name1+CYN"�����书�����������޷�ʩչ������\n" NOR;
                    		break;
            	}
        }
}

string perform_action_file(string action)
{        
        return __DIR__"lanhua-shou/" + action;
}

void remove_effect(object victim, int lvl)
{
        if (!victim) return;
        victim->delete_temp("lhs");
        victim->add_temp("apply/dexerity",lvl);
        victim->add_temp("apply/strength",lvl);
        victim->add_temp("apply/constitution",lvl);
        victim->add_temp("apply/intelligence",lvl);
        message_vision(HIW"$N��������ѨѪ���п��ˡ�\n"NOR, victim);
}

void remove_special(object victim)
{
        if (!victim) return;
        victim->delete_temp("lhs");
        victim->delete_temp("no_enable");
        victim->delete_temp("no_prepare");
}
