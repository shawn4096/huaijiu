// songyang-shou.c  ������
// Created by Numa 2000.1.5
// Modified by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ�Ƹߣ�һ�Ƶͣ��ڳ��ˡ������֡�������ʽ--���������ס�",
        "force" : 160,
        "dodge" : 10,
        "damage_type" : "����",
        "lvl" : 0,
        "skill_name" : "��������"
]),
([      "action" : "$N����һ�ᣬ����һ�б㼴������������һ�Ƴ��֣���ʱȫ������Ԩͣ���ţ���������",
        "force" : 230,
        "dodge" : 5,
        "damage_type" : "����",
        "lvl" : 30,
        "skill_name" : "Ԩͣ����"
]),
([      "action" : "$N���һ��������С���ˣ����漴˫������Ƴ���һ�����ҵ��Ʒ�����$n�������",
        "force" : 290,
        "dodge" : 5,
        "damage_type" : "����",
        "lvl" : 60,
        "skill_name" : "����ӭ��"
]),
([      "action" : "$N�����������裬˫�ƽ���һ��$n�����ţ�һ��$n��С��",
        "force" : 340,
        "dodge" : 10,
        "damage_type" : "����",
        "lvl" : 80,
        "skill_name" : "�ɰز���",
]),
([      "action" : "$N̤ǰһ������$n��ڶ��У�˫�ֿ���硢Ѹ��磬��ͣ����$n�������ҪѨ",
        "force" : 380,
        "dodge" : 15,
        "lvl" : 100,
        "damage_type" : "����",
        "skill_name" : "��ڶ���"
]),
([      "action" : "$N���������������б��Χ��$n�����ϳ��ƣ���Ѹ����$nȫ�����ҪѨ����¶����",
        "force" : 400,
        "dodge" : 5,
        "damage_type" : "����",
        "lvl" : 120,
        "skill_name" : "��������"
]),
([      "action" : "$N������ǰ�������͵�һ�ܣ�������������ֻ��֣�˫����ֱ��$n������ѹȥ",
        "force" : 410,
        "dodge" : 10,
        "damage_type" : "����",
        "lvl" : 140,
        "skill_name" : "��Ԩ��̽"
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

/*
int valid_combine(string combo) 
{
        object me = this_player(); 

        if ((int)me->query_skill("songyang-zhang") > 100
        &&  (int)me->query_skill("songyang-shou") > 100)
                return combo=="songyang-shou";
        return notify_fail("��Ĵ��������ƺ������ֵĻ�򲻹���\n");
}
*/

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("ѧϰ�����ֱ�����֡�\n");
        if ((int)me->query_skill("hanbing-zhenqi", 1) < 20)
                return notify_fail("��ĺ���������򲻹����޷�ѧ�����֡�\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷��������֡�\n");
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
        level = (int)me->query_skill("songyang-shou", 1);
        
        if (me->query_temp("ss_yinyang") == 1 && random(me->query_skill("songyang-zhou",1)/10)>12)
        {
                switch(random(2))
                {
                        case(0) :
                                return([
                                        "action": HIW "$N"HIW"ٿ���۽�������ԶԶ����һ�ƣ���������$n"HIW"�ؿڣ����ƺ������ˣ�$n"HIW"��ʱһ�����£�"NOR,
                                        "force" : 480,
                                        "dodge" : -10,
                                        "damage_type" : "����",
                                        ]);
                                break;
                        case(1) :
                                return([
                                        "action": HIW "$N"HIW"ٿ���۽�������ԶԶ����һ�ƣ���������$n"HIW"�ؿڣ����������ޱȣ�$n"HIW"����ٸ����ܣ�"NOR,
                                        "force" : 480,
                                        "dodge" : 10,
                                        "damage_type" : "����",
                                        ]);
                                break;
                }
        }
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}


mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        string msg;
        int focus = me->query_temp("ss/focus");
        int lvl= me->query_skill("songyang-shou", 1);
        int j = (lvl - 100) / 5 + 1;

        if (me->query_temp("ss/hb") && !victim->is_busy()) {
            victim->apply_condition("cold_poison", victim->query_condition("cold_poison")*120/100 + focus);
            victim->start_busy(2);
            victim->add("neili",-me->query_skill("force"));
            if (victim->query("neili") < 0) victim->set("neili",0);
            msg = HIW"$n��$N��һ�ƻ��У���Ȼһ���£��ƺ�ȫ���ѪҺ��������һ�㣡\n"NOR;
            message_vision(msg, me, victim);
        }
        if ( j > 6 ) j = 6;
        
        if(random(me->query_con())>20
         && lvl >= 100
         && random(me->query_str())>20
         && me->query_skill_prepared("hand") == "songyang-shou"
         && me->query("neili") > 1000
         && me->query("max_neili") > 1500 
         && me->query("jiali")){
           me->add("neili", -50);
   switch(random(7)){
            case 0 :
               msg = HIB"$N���𺮱���������������һ���������ֵİ�����ʹ�����������еġ�"HIW"�캮�ض� "HIB"����˫��һ�ɸ���֮����$n��ȥ��\n"NOR;
               victim->apply_condition("cold_poison", j + victim->query_condition("cold-poison"));
               break;  
            case 1 :
               msg =HIB"$N���𺮱���������������һ���������ֵİ�����������ʹ�����������еġ�"HIW"����̹�"HIB"��������Ʈ��������$n��ʱ�о�һ����ɭ֮��ӭ�������\n"NOR;
               victim->receive_damage("jing", lvl);
               victim->receive_wound("jing", lvl);
               break;
            case 2 :
               msg =HIB"$N���ƽ���ʹ�����������еġ�"HIW"����ѩ��"HIB"�������Ʊ��ѩ�ף���$n��ȥ��\n"NOR;
               victim->add("jingli",-lvl);
               break;
            case 3 :
               msg =HIB"$N���𺮱���������������һ���������ֵİ�����ʹ�����������еġ�"HIW"��ѩ����"HIB"����˫�Ʊ��ѩ�ף����һ�ɺ��쳺��֮������$n��ȥ��\n"NOR;
               victim->add("neili", -lvl*3);
               if( victim->query("neili") < 0) 
                victim->set("neili", 0);
               break;
            case 4 :
               msg =HIB"$N��������ʹ�����������еġ�"HIW"ǧ�����"HIB"����˫����������������һ������֮��ֱ��$n��ȥ��\n"NOR;
               victim->start_busy(2 + random(2));
               break;
            case 5:
               msg =HIB"$N�������˿�����ʹ�����������еġ�"HIW"����ѩƮ"HIB"������$n�ͳ�һ���溮�ޱȵ�������\n"NOR;
               victim->receive_damage("qi", lvl*3);
               victim->receive_wound("qi", lvl*3);
               break;
            case 6:
               msg =HIB"$N���𺮱���������������һ���������ֵİ�����ʹ����������֮���衸�򺮹�һ��������˫��������������ͬ���ȣ�����$n��\n"NOR;
                victim->apply_condition("no_perform", 1);
               break;
           }   
           if (me->query_temp("ss_feiwu"))
                  victim->apply_condition("cold_poison", 30 +
                        victim->query_condition("cold_poison"));      
           msg +=HIW"$nֻ����$N��һ�Ƽ����溮�ޱȵ���������ðٶˣ���������㣬ע��ȫ��Ѩ��, ���ܶ�����\n"NOR;
           message_vision(msg, me, victim);
        } 
}

int practice_skill(object me)
{
       
        if ((int)me->query("jingli") < 50)
                return notify_fail("��ľ���̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("������������������֡�\n");
        me->receive_damage("jingli", 30);
        me->receive_damage("neili", 5);
        if(me->query_skill("songyang-shou", 1) > 170)
                me->receive_damage("jingli", 10);
        if(me->query_skill("songyang-shou", 1) > 190)
                me->receive_damage("neili", 5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"songyang-shou/" + action;
}

