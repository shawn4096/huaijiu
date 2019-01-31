// baituo-shezhang.c ��������

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N�߸�Ծ�𣬻��������е�$wһ�С�һ�����졹����һ����������$n��ͷֱ�����",
        "dodge": -10,
        "force": 110,
        "damage" : 50,
        "lvl" : 0,
        "damage_type": "����"
]),

([  "action": "$Nһ�����ȡ���ɨǧ��������$w��������һ�ã�˫����ס$wβ��ת���͵ú�ɨ����$n��$l",
        "dodge": -15,
        "force": 150,
        "lvl" : 0,
        "damage": 60,
        "damage_type": "����"
]),
([      "action": "$N��Ȼ����һ�䣬ʹ�������߳��������ȷ��Ե�����֮��������$w����������Ӱ����$n",
        "dodge": 5,
        "force": 200,
        "lvl" : 29,
        "damage": 30,
        "damage_type": "����"
]),
([  "action": "$N���ȴ�����$w�й�ֱ��������һ����̳�������$n��$l�������С����߻�����",
        "dodge": -15,
        "force": 200,
        "lvl" : 59,
        "damage": 70,
        "damage_type": "����"
]),
([  "action": "$Nһʽ��һ�ȶ���������ͷһ$w������������ͷδ����һ�ɷ��ѽ�$n�Ƶ����Դ���",
        "dodge": -5,
        "force": 240,
        "lvl" : 79,
        "damage": 80,
        "damage_type": "����"
]),
([  "action": "$N���С�Ⱥ�߿��衹��$wɨ��һ������Ӱ������˷�Χ��$n��Ҫ��$n��û��ʳ",
        "dodge": 10,
        "force": 240,
        "lvl" : 89,
        "damage": 90,
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="staff" || usage=="parry"; }

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        object target, weapon; 
        int i, level, lvl;     
        
        target = offensive_target(me);    
        if (target->query_temp("weapon"))
             weapon = target->query_temp("weapon");
    
        lvl = random((int)me->query_skill("baituo-shezhang",1));
      
        if (me->query_skill("baituo-shezhang",1) > 100 &&
            me->query("neili") > 1000 && random(5) > 3 &&
            random(me->query("combat_exp")) > (int)target->query("combat_exp")/2){
            me->add("neili", -20);            
//            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
            return ([
                "action": HIC"������ʽ���ϣ�$N������$w˳��һ�Σ��ȼ�ֱ�����£�����һ����������$n��"NOR,
                "force" : 300,
                "dodge" : -20,
                "damage": 110,
                "damage_type":  "����"]);  
           }     
            
      
        if (objectp(weapon) && weapon->query("skill_type") == "stick" &&
            target->query_skill_mapped("stick") == "dagou-bang" &&
            lvl > target->query_skill("bagou-bang",1)/2 &&            
            me->query("neili") > 100 && lvl >= 140 &&
            me->query("oyf_hamagong") > 2) {                                                    
               me->add("neili", -100);
               return ([
                "action": HIC"$N��������ֱͦ�����۹��������ϣ��������Ʈ�ڣ����ȼ�������籩��Ҳ���ƶ���
����ֱָ$n�Ŀڣ����Ǵ򹷰�����ʮ��·�����������޹����ĵ�����İ������ڣ�"NOR,
                "force" : 290,
                "dodge" : 0,
                "damage":(random(8)+1)*50,
                "damage_type":  "����"]);
               }   
            

        level   = (int) me->query_skill("baituo-shezhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "staff")
               return notify_fail("��ʹ�õ��������ԡ�\n");
       if ((int)me->query_skill("hamagong", 1) < 30)
               return notify_fail("�㻹û������󡹦��������ϰ�������ȡ�\n");
       if ((int)me->query("jingli") < 50)
               return notify_fail("������������ˡ�\n");
       me->receive_damage("jingli", 5);
       return 1;
}

int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_neili") < 500 )
               return notify_fail("����������㣬û�а취����������, ����Щ���������ɡ�\n");

       if (!me->query_skill("hamagong", 1) ||
            me->query_skill("hamagong", 1) < 50)
               return notify_fail("��ĸ�󡹦���̫ǳ��\n");

       if ( !objectp(weapon = me->query_temp("weapon"))
       || ( string)weapon->query("skill_type") != "staff" )
               return notify_fail("�����ʹ�����������ȷ���\n");

       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baituo-shezhang/" + action;
}

