// anran-zhang.c ��Ȼ������
// By River 98.10.28
// Modified by snowman@SJ 20/06/2000
// ��river���ּ� ob_hit �ˣ��Ҹ���ɾ��... :-)

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" :"$N��Ӱ��ת������Ȱ��ǰ����˲��˲�ң�һʽ���ǻ��չȡ��Ʒ�����$n��$l",
    "force" : 250,
    "dodge" : 20,
    "lvl" : 0,
    "skill_name" : "�ǻ��չ�",
    "damage_type" : "����"
]),
([  "action" :"$N��̾һ�����������أ�һ�С��������ġ����յ�$nȫ������֮�ʣ�����ֱ��$n��$l",
    "force" : 350,
    "dodge" : 10,
    "lvl" : 30,
    "skill_name" : "��������",
      "damage_type" : "����"
]),
([  "action" :"$N��Ŀ��Ȼ����ֱ֫ͦ���������ۣ��ơ���ʬ���⡹�㣬���۽��ȣ���նֱ��$n��$l",
    "force" : 400,
    "dodge" : -20,
    "lvl" : 50,
    "skill_name" : "��ʬ����",
    "damage_type" : "����"
]),
([  "action" :"$Nһʽ��ӹ�����š������ִ��أ�һ�߻��ײ�ֹ��ٿ�����Ƶ�������Ʊ���$n��$l",
    "force" : 280,
    "dodge" :-5,
    "lvl" : 60,
    "skill_name" : "ӹ������",
    "damage_type" : "����"
]),
([  "action" :"$NͻȻͷ�½��ϣ��������ӣ��ִ����У�ֻ��һ�С�������ʩ�����������$n��$l",
    "force" : 300,
    "dodge" : -20,
    "lvl" : 70,
    "skill_name" : "������ʩ",
    "damage_type" : "����"
]),
([  "action" :"$N���ֳ��ƣ������Ƴ�һ�С�������ʳ����$nֻ��һ��ǿ�����׵��ƹܷ��ѹ����",
    "force" : 300,
    "dodge" : 0,
    "lvl" : 80,
    "skill_name" : "������ʳ",
    "damage_type" : "����"
]),
([  "action" : "$N���۸�����ĿԶ����һʽ������ֻӰ����$n��һ���ɣ�������Ϊ$N��������",
    "force" : 350,
    "dodge" : -10,
    "lvl" : 90,
    "skill_name" : "����ֻӰ",
    "damage_type" : "����"
]),
([  "action" : "$N����һ�С�������������$n�����Ʒ�֮�С�$n�������ݺ��ξ��ˣ�����$N���Ʒ�ת��",
    "force" : 300,
    "dodge" : 5,
    "lvl" : 100,
    "skill_name" : "��������",
    "damage_type" : "����"
]),
([  "action" : "ȴ��$N��������������������У�ƾ��һʽ�����񲻰�������$n���������ˣ��޷�Ӳ��",
    "force" : 300,
    "dodge" : -10,
    "lvl" : 120,
    "skill_name" : "���񲻰�",
    "damage_type" : "����"
]),
([  "action" : "$N������$n��ǰһ����һ�С���;ĩ·������$n��ǰ���֮����ͻȻת�䣬����$n��$l",
    "force" : 350,
    "dodge" : 10,
    "lvl" : 140,
    "skill_name" : "��;ĩ·",
    "damage_type" : "����"
]),
([  "action" : "$N����ϲŭ���֣���״�ٳ�����$n������������֮�ʣ�һ�С�������ɫ������$n��$l",
    "force" : 400,
    "dodge" : 10,
    "lvl" : 160,
    "skill_name" : "������ɫ",
    "damage_type" : "����"
]),
([  "action" : "$N��Ȼ��Ц��ֹ�����ֵ߿�����$n���Գ�����У�$N��һʽ������Ƿǡ�����$n��$l",
    "force" : 450,
    "dodge" : -20,
    "lvl" : 180,
    "skill_name" : "����Ƿ�",
    "damage_type" : "����"
]),
([  "action" : "ͻ��$N���λζ����ѹ���$n���ϣ�һʽ������ľ��������$n���֮ʱ������$n��$l��",
    "force" : 500,
    "dodge" : 5,
    "lvl" : 200,
    "skill_name" : "����ľ��",
    "damage_type" : "����"
]), 
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
       int skill = me->query_skill("anran-zhang", 1);
       if ((int)me->query_temp("weapon") || (int)me->query_temp("secondary_weapon"))
               return notify_fail("����Ȼ�����Ʊ�����֡�\n");
       if ((int)me->query("max_neili") < 1500)
               return notify_fail("�������������\n");
       if ((string)me->query_temp("xinjing/bonus") == "apply/strength")
               return notify_fail("����Ĭ���ľ��־����޷�����ѧϰ��Ȼ�����ơ�\n");
       if ((int)me->query_str() < 30 )
               return notify_fail("��û��ǿ���������޷�ѧ��Ȼ�����ơ�\n");
       if (( me->query("con") + me->query_skill("force", 1)/10 ) < 30 )
               return notify_fail("��û���ۺ�������޷�ѧ��Ȼ�����ơ�\n");
       if ((int)me->query_skill("yunu-xinjing", 1) < (skill-30)
        && (int)me->query_skill("anran-zhang", 1) < 230)
               return notify_fail("�����Ů�ľ����̫ǳ��\n");      
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
        int i, j, level,tmp;
        object target;         
        string msg;
        
        level = (int) me->query_skill("anran-zhang",1);
        tmp = 1 + random(level/10);
        
        if( me->query("gender") != "����")
                tmp /= 2;
                
        for(i = sizeof(action); i > 0; i--) {
                if(level > action[i-1]["lvl"]) {
                        j = NewRandom(i, 20, level/5);
                        target = offensive_target(me);    
                        if(me->query_temp("anran")){
                                switch(me->query_temp("anran")){
                                        case 2: msg = HIY"$N���������ң�û����ɵĻ��������ĳ�һ�ƣ�ֻ�����۵�һ������һ�����û���$n��ͷ"NOR; break;
                                        case 1: msg = HIR"������$N�߳�һ�š���һ�ŷ���ʱ�л��㱣�����ԼԼ���������ޡ����һ�죬��$n�ؿ�Ϯȥ"NOR; break;
                                        default: msg = HIC"$N���������ң�û����ɵĻ��������ĳ�һ�ƣ�ֻ�����۵�һ������һ�����û���$n��ͷ"NOR; break;
                                }
                                me->add_temp("anran", -1);      
                                return ([
                                        "action":msg, 
                                        "force" : action[j]["force"] + 3 * tmp,
                                        "dodge": action[j]["dodge"] + tmp,
                                        "parry": tmp,
                                        "damage_type" : "����",
                                ]);
                        }
                        if( me->query_temp("xiaohun")
                        && me->query("jiali")
                        && random(10) >= 5 ){
                                return ([
                                        "action" : random(2)? HIB+action[j]["action"]+NOR :MAG+action[j]["action"]+NOR,
                                        "force" : action[j]["force"]+ 3 * tmp,
                                        "dodge": action[j]["dodge"]+ tmp,
                                        "damage_type" : "����",
                                ]);
                        }
                        return action[j];
                }
        }
}

int practice_skill(object me)
{
        int lvl = me->query_skill("anran-zhang", 1);
        int i = sizeof(action);
        while (i--) if (lvl == action[i]["lvl"]) return 0;
        if ((int)me->query("jingli") < 50)
                return notify_fail("���������������Ȼ�����ơ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("���������������Ȼ�����ơ�\n");
        me->receive_damage("jingli", 40);
        me->add("neili", -15 );
        return 1;
} 

string perform_action_file(string action)
{
        return __DIR__"anran-zhang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string msg;
        int j;
        
        if( damage_bonus < 100 ) return 0;
        j = me->query_skill("anran-zhang", 1);
        
          if ( (random(10)>6)
        && !victim->is_busy()
        && j > 140
        && me->query("neili") > victim->query("neili")
        && me->query_skill_mapped("parry") == "anran-zhang"
        && me->query("neili") > 1000 
        && me->query("max_neili") > 1500 
        && j > random(victim->query_skill("dodge",1))){
                switch(random(3)){
                        case 0 :
                                  msg = "$Ņͷ���죬��������������һ����ͷ���տ��ĳ�������б�£��������ɻ��Σ���ɢ���£�\n";
                                  msg += "���$n����һ�С�������졹���ñ�˵����������վ���Ų�Ҳ�ǲ��ܡ�\n"; 
                                break;
                        case 1 :
                                  msg = "$N��������Ʈ����������ˮ������ȴ����֮�������ƴ��ż�ǧ����ɳһ�㣡\n";
                                  msg += "���$n����һ�С������ˮ�������������ݺ��ξ��ˣ�����ײײ��\n";
                                break;
                        case 2 :
                                  msg = "ͻȻ��$N�����붯���������䡢˫��ͷ���������ر�������������ʽ������\n";
                                  msg += "���$n����һ�С��������С���������ȫȻ�������ľ��ء�\n";
                                break;               
                }        
                  victim->start_busy(2+random(2)); 
                message_vision(msg, me, victim);
        }
}

int help(object me)
{
        write(WHT"\n��Ȼ�����ƣ�"NOR"\n\n");
        write(@HELP
        ����Ժ�С��Ů�ھ���ȶϳ���ǰ���֣����ñ����������ں���֮��������
        ����֮�󣬳����ڹ�ѭ�򽥽�֮�⣬����޿��������������ռ�˼��С��Ů��
        ����������������������Ȥ��һ���ں�����Ȼ���ã���������֮������ȭ���
        �ߣ���ʱ���ڹ�����ѵ���һ���־��߼�������������һ�ƣ�����̲��һֻ��
        ����ı��Ǵ�÷��顣���ɴ���˼��������һ���������Ʒ���������Ѱ���书
        ���죬����֮����ȫ��������һ����һʮ���С�����ƽ�ܹ�������ѧ���ҵ�ָ
        �㣬��ȫ���ѧ�����������ڹ��Ŀھ�����С��Ůѧ�á���Ů�ľ������ڹ�Ĺ
        �м����������澭����ŷ�����Ը�󡹦����ת���������߹���������Դ򹷰�
        ������ҩʦ���Ե�ָ��ͨ�����｣��������һ��ָ֮�⣬��а����������ؤ��
        ����ͨ����ѧ��������������Ĺ�ɵ���ѧ����������֮����辶����ʱ��
        ���ͨ������׿Ȼ�ɼҡ�ֻ������ʣһ�ۣ����Բ��������仯ȡʤ����������
        ����ѧͨ���෴�����������Ƴ�����Ϊ����Ȼ�����ơ���ȡ���ǽ��͡��𸳡�
        ����һ�䡰��Ȼ�����ߣ�Ψ������ӡ�֮�⡣
        
�书���ƣ�
        ��Ȼ������(anran-zhang)
             
���⹥����   
        ��Ȼ����(Perform anran)��      
        �������(Perform xiaohun)��
        ��������(Perform jishi)
        
Ҫ��
        ������� 1500;
        ������� 30;
        �������� 30;
        ��Ȼ������ 230 ��ǰ������Ů�ľ� 30 ����

HELP
        );
        return 1;
}
