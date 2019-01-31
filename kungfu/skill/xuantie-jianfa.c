// ��������
// Modify By River 99.05
// Modified by darken@SJ

#include <ansi.h>;

inherit SKILL;

string  *msg = ({
"$N����ƽƽ�̳�һ�������ƺ��ޱ仯��ȴ�к��֮����$nֻ��һ�ɴ����ɽ���ֱ������",
"$N���Ծ�����潣�𣬽�������֮����������һ������$n�������ڽ���֮��",
"$N��̾һ�������ֺ���һ��������ָ��$n������ƽ�����̺����б仯������ʤ����",
"$NѸ������һ�����˽�֮�죬������˼��$n����֮��һȾ����Ȼ�޷��ֱ潣·��ȥ",
"$N�ὣ˳�̣�������������������޲��ǽ��������ţ����淵�ӹ��棬�Ѳ����κ�����",
"$N���׳�Х������Ʊ�ã���������������$n���������$n���������κ���֮��", 
"$N��������֮����������ɽ������ͺ�һ�����������ǽ�Ӱ������ǧ����������$n����ζ�",
"$N����ʮ�ལ��һʱѸ�������ǻ��գ�һʱ���سٻ��������޼���Ѱ��ƽ�������ַ�˼����", 
"$N������磬�޿ɵ��棬$n�����и����������纣��һ�㣬һ��һ������ӿ�������Ӳ���",
"$N����$w��ǰ����������������������֪���ƽ��ϣ�����ȴ�纣��һ����ӿ����$nϮȥ",
"$NԶԶ�ӳ�һ����$n�����������֮ǿ������һ�裬һ�ɴ�����ͷ����",
"$N����һ����������$wЮ��������ƽƽ�����Ļ���$n������Խ��Խ�죬����ͬ����֮��һ��",
"$Nһ����$w��Ȼ����������һ�㰵��ɫ��â������ŭ��һ�ߣ���$n��ȥ",
});

string *parry_msg = ({
"$p�������ܣ�����$w��$P�ؿ�ֱ�̣�$N�ۼ������������֣�ȴ���ò��ܿ�$w�ķ�â��\n",
"$p��׼$P���ƣ�һ��������ǰ��$Pֻ�ñ��к��ˡ�\n",
"$p���ལ������һ����$P����ʽ��δ�����㾡���𿪡�\n",
"$p����һ�㣬������ʽ��ֻ�Ǿ���ǿ����$Pֻ������ת�أ������Ա���\n",
"$p�ϵл��ȣ�$P�������ƣ�ûһ���ܹ�ʹȫ����ͬС��ϰ�䣬��æ����һ�㡣\n",
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        int i;
        i = me->query_skill("force")/2 + random(me->query_str() + me->query_con()) + me->query("max_neili")/100;
        if( i < 100) i = 100;
        if( i > 600) i = 550+random(50);
        if(me->query_temp("xtjf_pfm")){
          return ([
                "action":HIC+msg[random(sizeof(msg))]+NOR,
                "damage":(random(2)+1)* 150,
                "dodge": random(15)-5,
                "force": i,
                "parry":35-random(20),
                "damage_type":random(2)?"����":"����",
          ]);
        }
        return ([
                "action":msg[random(sizeof(msg))],
                "damage":(random(2)+1)* 70,
                "dodge": random(10)-5,
                "force": i - random(100) - 50,
                "parry":40 - random(20),
                "damage_type":random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{    
        object weapon;
        int lvl;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
          return notify_fail("��ʹ�õ��������ԡ�\n");
        if((lvl = me->query_skill("xuantie-jianfa", 1)) < 200 )
          return notify_fail("�������������������������Ҫ��ɽ���м���������\n");
        if ((int)me->query("jingli") < 60+ lvl/10)
          return notify_fail("�����������������������\n");
        if ((int)me->query("neili") < 20+lvl/10)
          return notify_fail("�����������������������\n");
        if(lvl>400) lvl += random(lvl)/2;
        me->receive_damage("jingli", 20+ lvl/10);
	me->add("neili", -(10+lvl/20));
        return 1;        
}

int valid_learn(object me)
{
        if (me->query_skill("xuantie-jianfa", 1) < 200 )
          return notify_fail("������������ֻ��ͨ����ɽ������������߼��ա�\n");
          return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xuantie-jianfa/" + action;
}

