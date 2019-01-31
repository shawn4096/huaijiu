// hanbing-shenzhang.c  �������� 6/25/2000 Modifed 
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "ȴ��$N����һ�����������ֵ��Ƶ����Է������������˺������������֣����ʳ�ж�ָ��$n$l��ȥ",
        "force" : 200,
        "dodge" : -10,
        "damage_type" : "����",
        "parry" : 10,
        "lvl" : 1,
]),
([      "action" : "$N���Ƶ���$n�����Ƽ����ھ�����$p����ֱ�����£���һ�ƾӸ����£����Ӻ��磬�Ƶ��澢",
        "force" :300,
        "dodge" : 5,
        "parry" : -5,
        "damage_type" : "����",
        "lvl" : 50,
]),
([      "action" : "$N����һ�����������Ʒֱ��ĳ�����̬����̫��ȭ��ʮ���֣����漴������ȴ����������ĺ���",
        "force" : 350,
        "parry" : -15,
        "dodge" : 20,
        "damage_type" : "����",
        "lvl" : 100,
]),
([      "action" : "$N����ȫȻ�����·磬˫�۳��м��̣�������һ�߱㼴���أ�����ֻ�ز�������ͻȻ����һ�죬����$n",
        "parry" : 10,
        "force" : 420,
        "dodge" : -5,
        "damage_type" : "����",
        "lvl" : 150,
]),
([      "action" : "$N������ָ��ָ���Ƶ�$n������������������ָ��$p��������һ̧����Ȼ����$p$l�������������",
        "force" : 450,
        "dodge" : -10,
        "damage_type" : "����",
        "lvl" : 180,
]),

});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
        if (!me->query("family") || me->query("family/master_id") != "zuo lengchan")
                return notify_fail("��ֻ�ܴ�����������ѧ�ú������ơ�\n");
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ʊ�����֡�\n");
        if ((int)me->query_skill("hanbing-zhenqi", 1) < 140)
                return notify_fail("��ĺ���������򲻹����޷�ѧ�������ơ�\n");
        if ((int)me->query_skill("songyang-zhang", 1) < 140)
                return notify_fail("��Ĵ������ƻ�򲻹����޷�ѧ�������ơ�\n");
        if ((int)me->query("max_neili") < 2000)
                return notify_fail("�������̫�����޷����������ơ�\n");
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
        level = (int)me->query_skill("hanbing-shenzhang", 1);
        if (me->query_temp("ss_feiwu") == 2){
            return([      
                   "action": HIW "������$N"HIW"����һ��һ�գ���$n"HIW"��û�з�Ӧ����ʱ������ǰ�����𡸺����������������һ�ơ���"NOR,
                   "force" : 550,
                   "dodge" : 20,
                   "damage_type" : "����",
                   ]);
            }
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
//        if (lvl < 199 ) return 0;
        
        if ((int)me->query("jingli") < 70)
                return notify_fail("��ľ���̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("��������������������ơ�\n");
        me->receive_damage("jingli", 50);
        me->receive_damage("neili", 10);
        if(me->query_skill("hanbing-shenzhang", 1) > 160)
                me->receive_damage("jingli", 10);
        if(me->query_skill("hanbing-shenzhang", 1) > 190)
                me->receive_damage("neili", 5);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
     /*  if( random(me->query_skill("hanbing-shenzhang")) > 45) {
                  victim->apply_condition("cold_poison", random(3) + 2 +
                        victim->query_condition("cold_poison"));
        }
          */
       string msg;
        int lvl= me->query_skill("hanbing-shenzhang", 1);
        int j = (lvl - 100) / 5 + 1;
        if ( j > 6 ) j = 6;
        
        if(random(me->query_skill("hanbing-shenzhang", 1)) > 50
        && me->query("neili")>1000
        && random(me->query("neili"))>victim->query("neili")/4)
{
          if(victim->query("neili")/2 < me->query("neili"))
             victim->apply_condition("cold_poison", 2+victim->query_condition("cold_poison"));       
          else
             me->apply_condition("cold_poison", 1+victim->query_condition("cold_poison"));
        }
        if(random(me->query_con())>20
         && lvl >= 100
         && random(me->query_str())>20
         && me->query_skill_prepared("strike") == "hanbing-shenzhang"
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

string perform_action_file(string action)
{
        return __DIR__"hanbing-shenzhang/" + action;
}
