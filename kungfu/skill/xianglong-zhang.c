// xianglong-zhang.c ����ʮ����

#include <ansi.h>
inherit SKILL;


string *parry_msg = ({
"$p�����������С�������β�������Ʒ�����$P���������׺ݣ�����Ӳ�ӣ�����ܿ���\n",
"ֻ��$p����Բ��������ֱ�ƣ�������ǰ��һ�д��Ƿ�����ȴ����˫��֮�䲼��һ����ڡ�\n",
"$p���²��ҵ�����˫�Ƶ���ƽ�ƣ����Լ�ȫ������������֮�¡��ص�����Ԩͣ���ţ�ֱ�ް��������\n",
});

string query_parry_msg(object weapon, object victim) 
{ 
        if ( victim->query_temp("weapon") || victim->query_skill("xianglong-zhang", 1) < 100
        || victim->query_skill_prepared("strike") != "xianglong-zhang" )
                return SKILL_D("parry")->query_parry_msg(weapon);
        else
                return parry_msg[random(sizeof(parry_msg))];
}

mapping *action = ({
([      "action": "$N˫��΢����˫��ƽƽ�ᵽ��ǰ���ұۻ���ԲȦ������һ�����ý���ʮ���Ƶĵ�һ�С������лڡ�����$n",
        "dodge": 10,
        "force": 250,
        "lvl" : 0,
        "skill_name": "�����л�",
        "damage_type": "����"
]),
([      "action": "$NͻȻһԾ�����գ����μ�����ת���Ӹ����£�˫��ʹ��һ�С��������졹����������ӿ�����ֱ�����µ�$nѹȥ",
        "dodge": -5,
        "force": 270,
        "lvl" : 10,
        "skill_name": "��������",
        "damage_type": "����"
]),
([      "action": "����$Nһ��δ�꣬һ���������ƻ��ջ��أ��������Һ��ƶ���������һ�С����������Ѹ���ޱȵ�����$n��$l",
        "dodge": -10,
        "force": 290,
        "lvl" : 20,
        "skill_name": "��������",
        "damage_type": "����"
]),
([      "action": "$N�������������˫������ƽ�ƣ�ʩ�����轥��½�������������ƽ����ʵ����������ȴ���������ķ���������ѹ��$n",
        "dodge": -5,
        "force": 310,
        "lvl" : 30,
        "skill_name": "�轥��½",
        "damage_type": "����"
]),
([      "action": "$N���ƾ۳�ȭ״��һʽ�ڴ���$n���ֱۣ����Ž�����ǰ����Ѹ���Ƴ�������һ�С�Ǳ�����á��������ۻ�ӿ��$n",
        "dodge": -10,
        "force": 330,
        "lvl" : 40,
        "skill_name": "Ǳ������",
        "damage_type": "����"
]),
([      "action": "��������$N������ǰ�������������������һ�С�����󴨡����⽵�����Ʒ��絶���У�Ѹ���ޱȵؿ���$n��$l",
        "dodge": 5,
        "force": 350,
        "weapon" : "�������Ʒ�",
        "skill_name": "�����",
        "lvl" : 50,
        "damage_type": "����"
]),
([      "action": "$N˫���ಢ������ͻȻǰԾ��ʹ����ͻ�����������У�������ɽ��������$n�����Ƴ������޿ɱ�",
        "dodge": -5,
        "force": 350,
        "skill_name": "ͻ������",
        "lvl" : 60,
        "damage_type": "����"
]),
([      "action": "ͻ��$N��Ȼ���һ�����й����Ŵ󿪣�˫��һ��һ�������������˵ľ�������һ�е�ն��$n������һ�С��𾪰��",
        "dodge": -25,
        "force": 370,
        "skill_name": "�𾪰���",
        "lvl" : 70,
        "damage_type": "����"
]),
([      "action": "$N��ǰһ����һ�С���Ծ��Ԩ��������˫����$n�����ĳ���һ�˽���һ�ˣ��Ʒ�������������ɳʯ",
        "dodge": -10,
        "force": 370,
        "skill_name": "��Ծ��Ԩ",
        "lvl" : 70,
        "damage_type": "����"
]),
([      "action": "$N������ǰ�ƶ���˫�Ʒ�ʹ��ʽ��˫��ȡˮ�����������Ʒ�һ��һ�ң���ȴ�����Ⱥ�ͬʱѹ��$n$l",
        "dodge": -10,
        "force": 390,
        "skill_name": "˫��ȡˮ",
        "lvl" : 80,
        "damage_type": "����"
]),
([      "action": "$N���΢�������η����ڰ�����ĳ�����Ծ��Ԩ����˫����������һ����ƾ�����$n��$l����",
        "dodge": -5,
         "force": 390,
        "weapon" : "����",
        "skill_name": "��Ծ��Ԩ",
        "lvl" : 90,
        "damage_type": "����"
]),
([      "action": "$N��������ʹ��һ�С�ʱ����������˫��һ��һ����һ��һ�£�һǰһ����$n���������������ҿ�������",
        "dodge": -10,
        "force": 410,
        "skill_name": "ʱ������",
        "lvl" : 100,
        "damage_type": "����"
]),
([      "action": "$Nʹ��һ�С����Ʋ��꡹�����ƽ����������ĳ������������ס$n�˵���·�����Ƹ���бб������$n��$l",
        "dodge": -10,
          "weapon" : "����������",
        "skill_name": "���Ʋ���",
        "force": 410,
        "lvl" : 110,
        "damage_type": "����"
]),
([      "action": "$N������ǰ��ʹ��һ�С��������ڡ���˫�ƿ��������������$n�����������������ϵ�ɳʯ�������裬��ʵǱ����С",
        "dodge": -15,
        "force": 430,
        "skill_name": "��������",
        "lvl" : 120,
        "damage_type": "����"
]),
([      "action": "$N����һת��ͻȻ����$n��ǰ������бת��סȫ�������˾�һ�С���ս��Ұ������Ȼ����$n��$l",
        "dodge": -5,
        "weapon" : "��Ե",
        "skill_name": "��ս��Ұ",
        "force": 430,
        "lvl" : 130,
        "damage_type": "����"
]),
([      "action": "$Nһ�����ȣ���ǰ�Ż��󿪣�˫���ಢ������$n�͵���ȥ������һ�����յġ���˪�����������Լ������ض�����",
        "dodge": -25,
        "force": 480,
        "skill_name": "��˪����",
        "lvl" : 140,
        "damage_type": "����"
]),
([      "action": "$N���Ƶʹ�������̧�ߣ�ʹ��һ�С�����ެ���������ۻ�����������һ��һ��ͬʱ���м��$n��ѹ��ȥ",
        "dodge": 5,
        "force": 500,
        "skill_name": "����ެ",
        "lvl" : 150,
        "damage_type": "����"
]),
([      "action": "����$N���ƻ��أ�����һ�࣬��ת����$n�����ƽ�����һ�ڣ�һ�С�������β����������$n",
        "dodge": 15,
        "force": 500,
        "skill_name": "������β",
        "lvl" : 160,
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("������ʮ���Ʊ�����֡�\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 100)
                return notify_fail("��Ļ���������򲻹����޷�������ʮ���ơ�\n");
        if( me->query("gender") == "����")
                return notify_fail("��һ�����в�Ů֮������ѧϰ�����ƣ�\n");
        if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷�ѧ����ʮ���ơ�\n");
        if ((int)me->query_str() < 27 )
                return notify_fail("��û����׳�ı����޷�ѧ����ʮ���ơ�\n");
        if ((int)me->query_con() < 26)
                return notify_fail("��û���ۺ�������޷�ѧ����ʮ���ơ�\n");

        return 1;
      }

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, j, level, tmp; 
            
        level   = (int) me->query_skill("xianglong-zhang",1);
    
        if (me->query_temp("slbw")) {   
                me->delete_temp("slbw");             
                return ([  
                        "action" : HIC"����$NӲ����$p��һ�У����ƽ��������һ�ڣ�һ�С�������β�����䲻��ذ�����$n��$l�ϣ�"NOR,
                        "force" : me->query("gender")=="����"?600:450,
                        "dodge": me->query("gender")=="����"?30:20,
                        "parry": me->query("gender")=="����"?30:20,
                        "damage_type" : "����",
                        ]);
                }
    
        else if ( me->query_temp("xlz/hanglong")){
                me->delete_temp("xlz/hanglong");
                tmp = 2 + random(level/10);
                return ([
                        "action": YEL"\n$N�е��������У�������΢�������ƻ��˸�ԲȦ��ƽ�Ƴ�ȥ�����ǽ���ʮ�����еġ������лڡ���"+
                        "���Ƴ�ȥ�������赭д����һ��������ɲʱ֮������"+ chinese_number(tmp)+ "���ᾢ��һ��ǿ��һ�������ص�����ֱ����"+
                        "�᲻�ݣ���ǿ���ƣ�"NOR,
                        "dodge": -30 + 10 * tmp,
                        "parry": -25 + 10 * tmp,
                        "force": 500 + 40 * tmp,        
                        "damage": 50 + 10 * tmp,
                        "damage_type": random(2)?"����":"����" ]);
                }
                
        for(i = sizeof(action); i > 0; i--) {
                if(level > action[i-1]["lvl"]) {
                        j = NewRandom(i, 20, level/5);       
                        if (me->query_temp("xlz/xiao") && me->query("jiali") >= 50 )                 
                                return ([  
                                "action" : HIY+action[j]["action"]+NOR,
                                "force" : (me->query("gender")=="����"?action[j]["force"]:action[j]["force"]/2)+me->query_str()*5,
                            "dodge":(me->query("gender")=="����"?action[j]["dodge"]:action[j]["dodge"]+10)+random(10),
                                "parry": me->query("gender")=="����"?30:10,
                                "lvl" : action[j]["lvl"],
                                "weapon" : action[j]["weapon"],
                                "damage_type" : action[j]["damage_type"],
                                ]);
                      
                else return ([  
                        "action" : action[j]["action"],
                        "force" : me->query("gender")=="����"?action[j]["force"]:action[j]["force"]/2,
                        "dodge":me->query("gender")=="����"?action[j]["dodge"]:action[j]["dodge"]+20,
                        "parry": me->query("gender")=="����"?10:5,
                        "lvl" : action[j]["lvl"],
                        "weapon" : action[j]["weapon"],
                        "damage_type" : action[j]["damage_type"],
                        ]);
                }
        }
}       

int practice_skill(object me)
{
        int lvl = (int)me->query_skill("xianglong-zhang", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("jingli") < 100)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 40)
                return notify_fail("�����������������ʮ���ơ�\n");

        me->receive_damage("jingli", 60);
        me->receive_damage("neili", 20);
        if(lvl > 150) 
                me->receive_damage("jingli", 10);
        if(lvl > 200) 
                me->receive_damage("neili", 10);
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"xianglong-zhang/" + action;
}


int ob_hit(object ob, object me, int damage)
{
        int i, neili;
        if(living(me) &&
        userp(me) &&
        random(me->query_str()) > ob->query_str()/4 &&
        random(me->query("combat_exp")) > ob->query("combat_exp")/10 &&
        me->query_skill("xianglong-zhang", 1) >= 180 && 
        me->query("neili") > 600 &&
        me->query("eff_qi") < me->query("max_qi")/2 &&
        !me->query_temp("slbw_hit") &&
        !ob->query("env/invisibility"))
        {
                me->set_temp("slbw", 1);
                ob->set_temp("slbw_hit", 1);
                i = me->query("jiali");
                neili = me->query("neili");
                me->set("jiali", me->query_skill("force") + 100);
                me->add_temp("apply/attack", me->query_skill("xianglong-zhang", 1)/2);
                me->add_temp("apply/strength", i/2);
                
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);
                
                if(me->query("neili") < neili) me->set("neili", neili-100);
                me->set("jiali", i);
                ob->delete_temp("slbw_hit");
                me->add_temp("apply/attack", -me->query_skill("xianglong-zhang", 1)/2);
                me->add_temp("apply/strength", -i/2);
        }
        
        return 1;
}
