// quanzhen-jianfa ȫ�潣��
// Modify By River 99.5.26
inherit SKILL;
#include <ansi.h>
mapping *action = ({
([      "action" : "$N��Ӱ�ζ���̤���ţ���ƫ�棬һʽ���ֻ�������������$n��$l",
        "force" : 170,
        "dodge" : 20,
        "damage" : 40,
        "parry" : 10,
        "lvl" : 0,
        "skill_name" : "�ֻ�����",
        "damage_type" : "����"
]),
([      "action" : "$N��ǰԾ��һ�������ֽ��������ֽ�ʹ��һʽ������Į����ֱ��$n��$l",
        "force" : 200,
        "dodge" : 15,
        "damage" : 50,
        "parry" : 20,
        "lvl" : 10,
        "skill_name" : "����Į��",
        "damage_type" : "����"
]),
([      "action" : "$N�β�ͦ����һʽ����ɽ�����������н������ޱȣ������ӽ�ײ��$n��$l",
        "force" : 230,
        "dodge" : 15,
        "damage" : 60,
        "parry" : 20,
        "lvl" : 25,
        "skill_name" : "��ɽ����",
        "damage_type" : "����"
]),
([      "action" : "$N����΢�࣬��������һ���һ���󻡣�һʽ��˳ˮ���ۡ���ƽƽ����$n��$l��ȥ",
        "force" : 260,
        "dodge" : 10,
        "damage" : 70,
        "parry" : 10,
        "lvl" : 30,
        "skill_name" : "˳ˮ����",
        "damage_type" : "����"
]),
([      "action" : "$N����š���������鱧��Բ��һʽ�������仨�������й�ֱ��������$n��$l",
        "force" : 290,
        "dodge" : 10,
        "damage" : 80,
        "parry" : 15,
        "lvl" : 50,
        "skill_name" : "�����仨",
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ������ٵء�����������������������ֱ����Ю����֮����Ȼն��$n��$l",
        "force" : 320,
        "dodge" : 5,
        "damage" : 90,
        "parry" : 20,
        "lvl" : 70,
        "skill_name" : "����ٵ�",
        "damage_type" : "����"
]),
([      "action" : "$N����ʩ�����׵罻�ӡ�������Ƴ�һ����â��������ƿ�����$n��$l",
        "force" : 350,
        "dodge" : 5,
        "damage" : 100,
        "parry" : 15,
        "lvl" : 90,
        "skill_name" : "�׵罻��",
        "damage_type" : "����"
]),
([      "action" : "$N˫�Ȱ�����ף�һʽ�����񹲷ߡ������⻮������ԲȦ����������������",
        "force" : 380,
        "dodge" : -5,
        "damage" : 120,
        "parry" : 25,
        "lvl" : 110,
        "skill_name" : "���񹲷�",
        "damage_type" : "����"
]),
});

int valid_enable(string usage)
{
        return (usage == "sword") || (usage == "parry"); 
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        if( ! me->query_skill("xiantian-gong"))
        if ((int)me->query_skill("yunu-xinjing", 1) < 20)
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
        int i, j, level,xtg;
        level   = (int) me->query_skill("quanzhen-jianfa",1);
        xtg = (int)me->query_skill("xiantian-gong", 1);

        for(i = sizeof(action); i > 0; i--){
                if(level > action[i-1]["lvl"]){
                  j = NewRandom(i, 20, level/5);
                  if ( me->query_temp("hebi")
                    && me->query("jiali")
                    && random(2) != 1 ){ 
                  return ([  
                           "action" :random(2)? HIW+action[j]["action"]+NOR :HIY+action[j]["action"]+NOR,
                           "force" : action[j]["force"]+60,
                           "dodge": action[j]["dodge"]+ 15,
                           "damage": action[j]["damge"]+level/4,
                           "lvl" : action[j]["lvl"],
                           "parry":action[j]["parry"]+ 20,
                           "weapon" : random(2)?"����":"����",
                           "damage_type" : random(2)?"����":"����",
                         ]);
                   }
                  if( me->query_temp("sanqing")
                    && me->query("jiali")){
                  return ([  
                           "action" :HIW+action[j]["action"]+NOR,
                           "force" : action[j]["force"]+40+xtg/10,
                           "dodge": action[j]["dodge"]+random(15)+xtg/15,
                           "damage": action[j]["damge"]+ (level+xtg)/6,
                           "lvl" : action[j]["lvl"],
                           "parry":action[j]["parry"]+ random(20)+xtg/15,
                           "weapon" : random(2)?"����":"����",
                           "damage_type" : random(2)?"����":"����",
                         ]);
                   }
                return action[j];
                }
        }
}

int practice_skill(object me)
{
        object weapon;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("neili") < 10)
                return notify_fail("�������������ȫ�潣����\n");
        if ((int)me->query("jingli") < 40)
                return notify_fail("�������������ȫ�潣����\n");
        me->receive_damage("jingli", 25);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"quanzhen-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int skill= me->query_skill("quanzhen-jianfa", 1);
        if( random(me->query_skill("quanzhen-jianfa", 1)) > 60
         && me->query_temp("hebi")
         && !victim->is_busy()
         && damage_bonus > 100){
            victim->start_busy(random(skill/20) + 2 );
            call_out("check_fight", 1, me, victim);
        }
}

void check_fight(object me,object victim)
{
        if(!victim) return;
        if( ! me 
         || ! me->is_fighting(victim)
         ||   me->query_skill_mapped("sword") !="quanzhen-jianfa"
         || ! me->query_temp("weapon")
         || ! me->query_temp("hebi")){
          if( victim->is_busy()) victim->start_busy(1);
          return;
        }
        call_out("check_fight", 1, me, victim);
}
