// songyang-bian.c ������
// Created by Numa 1999-11-22
// Modified by Numa 2000-1-25

#include <ansi.h>

inherit SKILL;

string  *msg2 = ({
HIY"\n$N��$n���г�����ǿ����������һ��������$n��\n"NOR,
HIR"\n$n���мȳ��������ջ����ǲ��ܣ���ǿ������$N���ѽ�$w����$n�Ĵ�ҪѨ��\n"NOR,
HIG"\n$N���Լ��������𽥻��ң��鼱֮�£�������շɳ���$w��ĩ��ȴ��ɨ��$n������Ѩ��\n"NOR,
HIB"\n$N���һ����������·��ֻ��ƴ��һ����������ˣ�$w���ƶ�Ȼ������$n�����м�֮����\n"NOR,
HIW"\n$n��$N������Ȼ���������а����кã�����һԽ�����������ϵ��������ű�Ӱ��ʹ$n�޴����Σ�\n"NOR,
});


mapping *action = ({
([     "action": "$N����$w������һת��$w����һ�����ߴ�Խ��������ֱ����$n",
       "dodge": 5,
       "damage": 70,
       "force": 150,
       "lvl" : 0,
       "damage_type":  "����"
]),
([     "action": "$N������������$w��˫�ֲ����趯��$n����ȫ�����������Ӱ֮�У�˿���޻���֮��",
       "dodge": 10,
       "damage": 70,
       "force": 200,
       "lvl" : 30,
       "damage_type":  "����"
]),
([     "action": "$N�����ھ�����ע��$w֮�ϣ��漴������������ԲȦ���⻷֮��һ����Ӱֱ�ܶ�������ճ���$n",
       "dodge": -20,
       "damage": 90,
       "force":  220,
       "lvl" : 45,
       "damage_type":  "����"
]),
([     "action": "$N��������һ�٣������Ͼ٣���Ҫ������������$wȴ��һ�����ߴ�����$n��ȥ",
       "dodge": 15,
       "damage": 120,
       "force": 240,
       "lvl" : 70,
       "damage_type":  "����"
]),
([     "action": "$N�粿һ�ʣ�����$w��ǰ������$wĩ���ڵ��ϻ��������ڡ��ı��죬�ͻ���$n",
       "dodge": 15,
       "damage": 120,
       "force": 260,
       "lvl" : 90,
       "damage_type":  "����"
]),
([     "action": "$N�����Ȼһ�������˸�ת��˫���Բ��϶���$w��������ҵ���������$n",
       "dodge": 10,
       "damage": 100,
       "force": 280,
       "lvl" : 110,
       "damage_type":  "����"
]),
([     "action": "$N������$w��ջ��˸���Ȧ������Χ��$n���ߣ�$n��ȫ���Ѩ����������$w֮��",
       "dodge": 15,
       "damage": 120,
       "force": 300,
       "lvl" : 125,
       "damage_type":  "����"
]),
([     "action": "$N��Хһ��������������ɽ�ڹ����̶����̤��$w����ˮ���߰㻮��$n�ĸ���ҪѨ",
       "dodge": 25,
       "damage": 140,
       "force": 320,
       "lvl" : 140,
       "damage_type":  "����"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if (!me->query("ss/pass_deng"))
               return notify_fail("����δ��ȫ��������޵İ�����ѧ�Ļᣡ\n");
       if(!me->query("family") || me->query("family/family_name")!="��ɽ��" )
               return notify_fail("�㲻����ɽ�ɵ��ӣ���������������ޣ�\n");
               
       if( (int)me->query("max_neili") < 1500 )
               return notify_fail("���������Ϊ���㣬û�а취�������ޡ�\n");

        if ((int)me->query_skill("hanbing-zhenqi", 1) < 130)
               return notify_fail("��ĺ����������̫ǳ��\n");

       if ( !objectp(weapon = me->query_temp("weapon"))
       || ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("���������һ�����Ӳ������޷���\n");

       return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
       int i, level;
     
       level   = (int) me->query_skill("songyang-bian",1);
       if (level>200) level=200+(level-200)/10;
       if( me->query_temp("ss_luan") && random(7)> 3){
       return ([
                  "action" :msg2[random(sizeof(msg2))],
                  "force" : random(150)+level,
                  "dodge": random(25)-random(10)+10,
                  "damage": ((random(3)+1)*100)/2 +level/2,
                  "damage_type":random(2)?"����":"����",
       ]);
        }

       for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{

       if ((int)me->query("jingli") < 80)
                return notify_fail("������������������ޡ�\n");
                
       if ((int)me->query("neili") < 30 )
                return notify_fail("������������������ޡ�\n");
                
       me->receive_damage("jingli",60);
       
       if((int)me->query_skill("songyang-bian",1)> 180)
            me->add("neili",-20);
            
       return 1;
}

mixed hit_ob(object me, object target, int damage)
{
        object weapon;
        if (me->query("env/songyang_auto")
         && objectp(weapon = me->query_temp("weapon"))
         && weapon->query("skill_type") == "whip"
         && me->query_skill("parry",1) > 160
         && me->query("neili") > 1500 
         && me->query("jingli") > 500 
         && me->query_skill("songyang-bian",1) > 180
         && me->query_skill("songyang-shou",1) > 160
         && me->query_skill_mapped("hand") == "songyang-shou"
         && me->query_skill_prepared("hand") == "songyang-shou"
        && random(8) > 5
         && random(me->query("combat_exp")) > target->query("combat_exp")/2)
        {
                me->add("neili", -50);
                message_vision(HIY"\n$N�������������"+weapon->name()+HIY"һ���������ֱ���һ�Ǵ������֣�\n"NOR,me);
                damage = me->query_skill("songyang-bian", 1)/8 + random(me->query_skill("songyang-bian", 1)/8);
                me->add_temp("apply/damage", damage);
                weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                weapon->wield();
                message_vision(HIC"\n$Nһ��δ�ϣ��ּ�������������"+weapon->name()+HIC"һ�����ھ�˳��"+weapon->name()+HIC"���������㳯��$nֱ�ƶ�ȥ��\n"NOR,me,target);
                me->add_temp("apply/damage", - damage);
                me->start_busy(1 + random(2));
        }
        return 0;
}
string perform_action_file(string action)
{
               return __DIR__"songyang-bian/" + action;
}
