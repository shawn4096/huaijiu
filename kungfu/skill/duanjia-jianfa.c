//�μҽ���
//cool@SJ,990528
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
        "action" : "$N�������˸�����������$wƽƽ�ݳ���һʽ�������Ͻ�ֱ��$n��ǰ��",
        "damage_type" : "����"
]),
([
        "action" : "$N������ǰ��$w��һ���벻���ĽǶ�ͻȻ������һʽ���̼�������ֱ��$n������",
        "damage_type" : "����"
]),
([
        "action" : "$Nһ�С������ڿա�������Ծ�ڰ�գ�$w��������� ��ֱ��$n��ͷ��",
        "damage_type" : "����"
]),
([
        "action" : "$N����б�ӣ�����ָ��$n�ĸ�����һ�С���Ԩ���ԡ������¶��ϣ�����$n",
        "damage_type" : "����"
]),
([
         "action" : "$N˫����أ�б�ɶ�����$w����$n��$l,��һ�С�Цָ���ϡ�",
         "damage_type" : "����"
]),
([ 
        "action" : "$N��Хһ�����ὣ�������͸������֮�⣬���ǶμҲ���֮�ء���¹��ԭ����������ס$n��ȫ��",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
            return notify_fail("�������������\n");
        if ((int)me->query_skill("qiantian-yiyang", 1) < 20)
            return notify_fail("���Ǭ��һ�����̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i,level;
		string msg;
        level   = (int) me->query_skill("duanjia-jianfa",1);
        if (level > 200) level = 200 + (level- 200)/10;
      
	     if(me->query_temp("fenglei")){
          switch(me->query_temp("fenglei")){
           case 4: msg = HIW"$Nʩչ���������裢��һ��Ծ���ڿ��У�����Χ����$n��ͣ��ת���������ĸ���λ��$n�̳��Ľ�������ޱȣ�\n" NOR;break;
			 case 3: msg = HIW"$N����$n�ľ����ڿ���һ����˫���ս���һ���̳�������ӥ�����գ����ˣ���һ����������һ����������$n��\n" NOR;break;
             case 2: msg = HIW"$N���ƻ��Ļ���������$n��ע�⣬���ֽ�ת���Σ���������������������һ�����ģ���������Ϯ��$n��ȫ��\n" NOR; break;
			 case 1: msg = HIW"$N�����³���ͻȻ����һ������ĳ���ͷ�½��ϣ����ӽ������������һƮ�����ǿ����ޱȵĴ̳�������ֱ��$n��\n"NOR;break;
             default: msg = HIW"$N�����³���ͻȻ����һ������ĳ���ͷ�½��ϣ����ӽ������������һƮ�����ǿ����ޱȵĴ̳�������ֱ��$n��\n" NOR; break;
          }
             me->add_temp("fenglei", -1);
              return ([
                "action":msg,
                "damage":150+random(50), 
                "damage_type":"����",
                "dodge": random(15)+15, 
                "force": random(50)+level/2+200,
                "parry": 5+random(5),
                "skill_name" : "��������",
              ]);
        }
		
	for(i = sizeof(action); i > 0; i--) {
            if(level > action[i-1]["lvl"]) {
               return ([
                "action":action[NewRandom(i, 20, level/5)]["action"],
                "damage":random(80)+80,
                "damage_type": action[NewRandom(i, 20, level/5)]["damage_type"],
                "dodge": random(15),
                "force": 150+random(200),
                "parry": 20+random(10),
               ]);
            }
        }
}

int practice_skill(object me)
{
        object weapon;
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("jingli") < 40)
                return notify_fail("��������������μҽ�����\n");
        if((int)me->query("neili") < 30)
                return notify_fail("��������������μҽ�����\n");
        me->receive_damage("jingli", 15);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"duanjia-jianfa/" + action;
}
