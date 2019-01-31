// riyue-bian.c ���±޷�

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([     "action": "$N����������һʽ�������ɴ̡���������̧��$w�������裬���������Ҳ���ǰ�����ƣ�����մճ��ɢ",
       "dodge": 5,
       "damage": 60,
       "force": 150,
       "lvl" : 0,
       "skill_name" : "�����ɴ�",
       "damage_type":  "����"
]),
([     "action": "$Nһʽ��Ŀ�����̡�������$w�ж��ñ�ֱ�������ڡ�������$n���̶�������Ю��������$nһ������",
       "dodge": 10,
       "damage": 70,
       "force": 230,
       "lvl" : 30,
       "skill_name" : "Ŀ������",
       "damage_type":  "����"
]),
([     "action": "$N�ھ���������$w����ת������ԲȦ��һʽ��������̡���Ծ��Ӱ������$n$l����",
       "dodge": -10,
       "damage": 80,
       "force":  270,
       "lvl" : 60,
       "skill_name" : "�������",
       "damage_type":  "����"
]),
([     "action": "$N����������һʽ����¥�Ǵ̡���$w��$n��ǰ��Ȧ�¹���������ת��������������ʽ����Ȼ��$n$l����������",
       "dodge": 10,
       "damage": 90,
       "force": 310,
       "lvl" : 90,
       "skill_name" : "��¥�Ǵ�",
       "damage_type":  "����"
]),
([     "action": "$Nһ���ߺȣ�����������һʽ�������Ӵ̡���$w����ת������Ӱ�ݺᣬֱ����Բ��Բ����ֱ�������ƻã�����$n",
       "dodge": -5,
       "damage": 110,
       "force": 300,
       "lvl" : 120,
       "skill_name" : "�����Ӵ�",
       "damage_type":  "����"
]),
([     "action": "$N���ذα�������׹�⣬һʽ�������̡ܴ��������鶯���ͣ���ʵ����������������˷���$n��ѹ��ȥ",
       "dodge": 5,
       "damage": 130,
       "force": 320,
       "lvl" : 150,
       "skill_name" : "�����ܴ�",
       "damage_type":  "����"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if(!me->query("family") || me->query("family/family_name")!="������" )
               return notify_fail("�㲻�����ֵ��ӣ�������������±޷���\n");
               
       if ((int)me->query_skill("ranmu-daofa",1) || (int)me->query_skill("weituo-chu",1) || me->query("pass_xin"))
               return notify_fail("������д�Ħ�������Ϊ������ͬʱѧϰ������������\n");
               
       if( (int)me->query("max_neili") < 1500 )
               return notify_fail("���������Ϊ���㣬û�а취�����±޷���\n");

        if ((int)me->query_skill("yijin-jing", 1) < 130)
               return notify_fail("����׽�񹦻��̫ǳ��\n");

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

mapping query_action(object me, object target)
{
        int i, level;
     
        i = random(me->query_skill("force"));
        if( i < 100) i = 100;
        
        if(me->query_temp("ryb_riyue"))
                return ([
                        "action":HIR+action[random(sizeof(action))]["action"]+NOR,
                        "damage":50+(random(2)+me->query_temp("ryb_riyue"))* 40,
                        "dodge": random(15)-10,
                        "force": i + random(i),
                        "parry":35-random(20),
                        "damage_type":"����",
                ]);
      
        if(me->query("env/���±޷�") 
        && me->query_skill("parry",1) > 120 
        && me->query("neili") > 1000 
        && me->query("jingli") > 300 
        && me->query("jiali") > 5
        && random(me->query_str()) >= 40 
        && random(me->query_skill("riyue-bian",1)) > 140){
                me->add("neili", -10);
                target->start_busy(random(3));
                if (random(me->query_str()) >= 45 
                && me->query_skill("riyue-bian",1)> 200) {           
                        me->add("neili", -10);
                        return ([
                             "action": HIR "$N������$w������Ȧ������$nԽתԽ����ԽתԽ�죬$p��ʱ�����������׵���ת�˼����ۿ���Ҫˤ����"NOR,
                             "force": 350,
                             "dodge": 5,
                             "damage" : 250,
                             "damage_type": "ˤ��"]);
                        }     
                return ([
                "action": HIR "$N����һ�������������$w������º�$n����һ��һ����ɽ�������ھ�����Ϣ����$n�ؿ�ײȥ��"NOR,
                "force": 250,
                "dodge": 10,
                "damage" : 350,
                "damage_type": "����"]);
        }
        
       level   = (int) me->query_skill("riyue-bian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{

       if ((int)me->query("jingli") < 80)
                return notify_fail("����������������±޷���\n");
                
       if ((int)me->query("neili") < 30 )
                return notify_fail("����������������±޷���\n");
                
                me->receive_damage("jingli",30);
       
       if((int)me->query_skill("riyue-bian",1)> 200)
                me->add("neili",-10);
            
       return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        object weapon, weapon1;    
        int  wp, wp1, wp2,we1,we2;  
        weapon=me->query_temp("weapon");
        weapon1=victim->query_temp("weapon");
        
        if(objectp(weapon) && objectp(weapon1)){
                wp = weapon->query("rigidity");
                wp1 = weapon1->query("sharpness");
                wp2 = weapon1->query("rigidity");
                if (random(me->query_skill("riyue-bian",1)<100))
                        return 0;
                if (random(10)>4) return 0;    
                if(wp > 10) wp = 10;
                if(wp1 > 10) wp1 = 10;
                if(wp2 > 10) wp2 = 10;
                if( wp > 0 && wp > wp1 && wp > wp2 &&
                random(me->query("str")) > victim->query("str")/2){
                        message_vision(HIY "ֻ������ৡ���һ�����죬$N���е�"+weapon1->name()+WHT"�Ѿ���"+weapon->name()+WHT"��Ϊ���أ�\n"NOR, victim );
                        weapon1->broken("�ϵ���");
                } 
                if (wp==0)  {
                        we1=me->query_str()+(int)me->query("jiali")+(int)me->query_skill("parry")/3;         
                        we2=victim->query_str()+(int)victim->query("jiali")+(int)victim->query_skill("parry")/3;
                        if (random(we1)>random(we2)){
                                message_vision(HIY "ֻ�������������죬$N���е�"+weapon1->name()+HIY"�Ѿ���"+weapon->name()+"����һ���ѳֲ������ַɳ���\n"NOR, victim );
                                if (!victim->is_busy()) victim->start_busy(random(6));
                                weapon1->move(environment(victim));
                                victim->reset_action();
                        }
                }      
        }
        return 0;
}
string perform_action_file(string action)
{
        return __DIR__"riyue-bian/" + action;
}
