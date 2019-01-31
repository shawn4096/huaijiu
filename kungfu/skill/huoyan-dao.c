// huoyan-dao.c ���浶
// by snowman@SJ

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N��Ϣת�����˾���˫�ۣ�ȫ��ǽ�һ���죬����һʽ��ʾ��������$n��������$nȫ�������ڳ��ȵ��Ʒ���",
        "skill_name" : "ʾ����",
        "force" : 250,
        "lvl" : 0,
        "dodge" : 15,
        "parry": 10,
        "damage_type" : "����",
]),
([      "action" : "$N�����Ц��һ�С�ʼ�ľ��������浶�ھ����ڼ�������ӿ����$P˫���籦���ʮ����ǰ������$n����һ��",
        "skill_name" : "ʼ�ľ�",
        "force" : 280,
        "lvl" : 20,
        "dodge" : 10, 
        "parry": 5,
        "damage_type" : "����",
]),
([      "action" : "$N˫�ƺ�ʮ���ִ򿪣����С��ֱ������Ի��浶���Ϲ����۳�һ�������ʢ���Ļ��������ת��������$n����",
        "skill_name" : "�ֱ���",
        "force" : 340,
        "lvl" : 50,
        "dodge" : 5,
        "weapon" : "��������",
        "damage_type" : "����",
]),
([      "action" : "$N�������࣬˫�ƴ�Բ��ʹ�������ȵĵ�����ۣ����С��Ʒ�ִ������һֻ�޴�����ƣ������$n��ץ����",
        "skill_name" : "�Ʒ�ִ",
        "force" : 320,
        "lvl" : 70,
        "dodge" : 10,
        "damage_type" : "����",
]),
([      "action" : "$N����һ������Ȼʹ����ħ���ϵġ�����Բ����������쫷��Χ��$P������������$nһ��������$P��������",
        "skill_name" : "����Բ",
        "force" : 400,
        "lvl" : 120,
        "dodge" : -10,
        "damage_type" : "����",
]),
([      "action" : "$N�����ħ�澭��˫��������������$n����������֮�£����絶�и����ġ����泣�������ƺ�Ҫ��$p��������",
        "skill_name" : "���泣",
        "force" : 350,
        "lvl" : 140,
        "dodge" : -5, 
        "weapon" : "���ε���",
        "damage_type" : "����",
]),
([      "action" : "$N�ֱ��࣬�����������֡����淨�������ĳ�������е������᲻ɢ�����������Ƶ�����ȴ��ɽ�������ӿ��$n",
        "skill_name" : "���淨",
        "force" : 430,
        "lvl" : 160,
        "dodge" : -15, 
        "parry": 5,
        "damage_type" : "����",
]),
([      "action" : "$N�������ƣ�һʽ�������š���������ת������ȫ�������޷��Զ���$P����΢�㣬��������һ����ն��$n$l",
        "skill_name" : "������",
        "force" : 500,
        "lvl" : 180,
        "dodge" : 5, 
        "parry": 10,
        "weapon" : "��������",
        "damage_type" : "����",
]),
});

 
int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����浶������֡�\n");
        if ((int)me->query("max_neili") < 1500) 
                return notify_fail("�����������Ϊ������������ϰ���浶��\n");
        if ((int)me->query_con() < 30) 
                return notify_fail("��ĸ���̫�ͣ����ܼ������浶��\n");
        if ((int)me->query_skill("longxiang-boruo", 1) < 100)
                return notify_fail("���浶��Ҫ������������ڰ˲����ϵĻ�����ѧϰ��\n");
        if ((int)me->query_skill("force") < 100)
                return notify_fail("��Ļ����ڹ����̫ǳ������ѧ���浶��\n");
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
        level = (int) me->query_skill("huoyan-dao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����浶������֡�\n");
        if ((int)me->query("jingli") < 50 || (int)me->query("neili") < 20)
                return notify_fail("������������������˻��浶��\n");
        me->receive_damage("jingli", 40);
        me->add("neili",-10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huoyan-dao/" + action;
}

int ob_hit(object ob, object me, int damage)
{
        string msg;
        int j, skill, neili, neili1;

        skill = me->query_skill("huoyan-dao", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");

        if( random(skill) > ob->query_skill("parry", 1)/2
        && me->query("combat_exp") > ob->query("combat_exp")/2
        && me->query_skill_mapped("parry") == "huoyan-dao"
        && me->query_skill("longxiang-boruo", 1) > 150
        && neili > 1000 
        && skill > 150 
        && random(neili) > random(neili1)/2
        && living(me)
        && !me->query_temp("weapon")
        && !ob->query_temp("weapon")
        && !ob->is_visible(me)) {       
        	if( me->query_temp("dazhuan_npc") ) neili += neili/2;
        	    
                msg = "ֻ����$N��ǰ�������죬�����浶�����ƴ�ʢ��";            
                if(neili >= neili1+random(neili1)+damage*2){
                        msg += "��$n��ʽ�ϵ��������ƽ�������\n", 
                        j = -8000;
                }
                else if(neili >= neili1+damage){
                        msg += "$P�����ﴦ����ס��һЩ$n������������\n", 
                        j = -(damage/2+random(damage/2));               
                }
                else{
                        msg += "$Pչ�����浶������ס��һЩ$n�Ĺ�����\n", 
                        j = -damage/3; 
                }        
                if(wizardp(me)) tell_object(me, "Target damage = "+damage+" ��\n");   
                message_vision(msg, me, ob);
                return j;
       }          
}

int help(object me)
{
	write(HIR"\nѩɽ�ؼ������浶����"NOR"\n");
	write(@HELP
	
	Ҫ��	������� 1500 ���ϣ�
		������� 30 ���ϣ�
		����������ȼ� 100 ���ϣ�
		�ڹ��ȼ� 100 ���ϡ�     
HELP
	);
	return 1;
}
