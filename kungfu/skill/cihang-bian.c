//�Ⱥ���,
//ȡ��������ʦ<��ţͼ��>
//cool@SJ,990420

#include <ansi.h>

inherit SKILL;

string *body_name = ({ 
"������","��첲","����","ͷ��","����","����","С��","��Ž���","������","�Ҹ첲","����","�ҽŽ���",}); 

mapping *action = ({
([ "action": "$N˫�ֺ�ʲ��������ע, һʽ��δ����������$w�������ԣ�����һת������$n��$l",
   "skill_name" : "δ��",
   "damage_type":  "����",
]),
([ "action": "$N���绬��������$wһ����һʽ����������Ѹ���ޱȵطִ��������࣬$n��ʱ����֧穣������ֽ�",
   "skill_name" : "����",
   "damage_type":  "����"
]),
([ "action": "$N������ע��$w�����ʹ��һʽ�����ơ���$w��ز���裬ֱ�������ƿ�һ�����$n",
   "skill_name" : "����",
   "damage_type":  "����"
]),

([ "action": "$Nһ����Х������$wһ�С����ס������������Ӱ����ǵص���$n�������Ƶ�����֮��",
   "skill_name" : "����",
   "damage_type":  "����"
]),
([ "action": "$N������������$w��һʽ��ѱ�������ӳ�������ת������$n��ȥ ",
   "skill_name" : "ѱ��",
   "damage_type":  "����"
]),
([ "action": "$N������շ������ִ����ӳ�$w��һʽ���ް�����һ����ɽ�����ı޷�ֱ����$n",
   "skill_name" : "�ް�",
   "damage_type":  "����"
]),
([ "action": "$N��¶΢Ц��ǰһ��������$w���ʹ��һʽ�����ˡ�������ƽ������������˿������",
   "skill_name" : "����",
   "damage_type":  "����"
]),
([ "action": "$N��ǰ������˫����ס$w������ʹ��һʽ�������������Ƴ���, һ�ɾ����ƿն���",
   "skill_name" : "����",
   "damage_type":  "����"
]),
([ "action": "$N��������$w��һʽ�����ա�����������, ��������",
    "skill_name" : "����",
   "damage_type":  "����"
]),
([ "action": "$N�����������裬����$wͻȻ�ӳ���ʹ��һʽ��˫����������������������,���ƾ���",
   "skill_name" : "˫��",
   "damage_type":  "����"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_neili") < 800 )
               return notify_fail("����������㣬û�а취��ϰ�޷�, ����Щ���������ɡ�\n");

       if ((int)me->query_skill("kurong-changong", 1) < 20)
               return notify_fail("��Ŀ���������Ϊ������\n");

       if ( !objectp(weapon = me->query_temp("weapon"))
        ||( string)weapon->query("skill_type") != "whip" )
               return notify_fail("���������һ�����Ӳ������޷���\n");
       return 1;

}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level, a;
        string msg;
        level   = (int) me->query_skill("cihang-bian",1);

        if(me->query_temp("chb")){
          	switch(me->query_temp("chb")){
             		case 3: msg = MAG"����$N���γ�ǰһ�壬 ����"+ weapon->name()+MAG"�������С��" NOR; break;
             		case 2: msg =HIY"������$N����������"+ weapon->name()+ "��"+ weapon->name()+HIY"���йٱʰ����$n��ǰ��" NOR;break;
             		case 1: msg = HIW"���$N���ϸ߸�һԾ�����˷�����"+ weapon->name()+HIW "����$n���𹥻�" NOR; break;
             		default: msg = HIW"���$N���ϸ߸�һԾ�����˷�����"+ weapon->name()+HIW"����$n���𹥻�" NOR; break;
          	}
          	a = me->query_str() * 2 + random(me->query("jiali")/2);
          	me->add_temp("chb", -1);
              	return ([
                	"action":	msg,
                	"damage":	a, 
                	"damage_type": 	"����",
                	"dodge": me->query_dex(), 
                	"force": (a + me->query_skill("force", 1)) / 2,
              	]);
        }
        for(i = sizeof(action); i > 0; i--) {
        	a = NewRandom(i, 20, level/5);
              	return ([
                	"action":	action[a]["action"],
                	"damage": 	me->query_str(), 
                	"damage_type": 	"����",
                	"dodge": 	me->query_dex(), 
                	"force": 	me->query_skill("force", 1)/2,
                	"parry":	random(10),
                	"skill_name" : 	action[a]["skill_name"],
              	]);
        }
}

int practice_skill(object me)
{
       	object weapon;

       	if (!objectp(weapon = me->query_temp("weapon"))
       	|| (string)weapon->query("skill_type") != "whip")
           	return notify_fail("��ʹ�õ��������ԡ�\n");
      	if ((int)me->query_skill("kurong-changong",1) < 100)
               	return notify_fail("�Ⱥ��޷��Կ�������Ϊ����,�㲻���������,�޷������Ⱥ��ޡ�\n");
       	if ((int)me->query("jingli") < 50)
               	return notify_fail("��������������Ⱥ��޷���\n");
       	if ((int)me->query("neili") < 50)
               	return notify_fail("��������������Ⱥ��޷���\n");
       	me->receive_damage("jingli", 35);
       	me->add("neili", -(10+random(5)));
       	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object weap,weap1;
        
        weap = victim->query_temp("weapon");
        weap1 = me->query_temp("weapon");
        if( random(me->query_skill("cihang-bian", 1)) > 80
        && me->query("neili") > 100
        && random(5) > 2 ){
           	if ( weap ){
               		message_vision(HIY "ֻ��$N���ٻ���" + weap1->name() + "��ת����������СȦ�ӣ�������֮����ס�Է���" + weap->name() +"��\n" NOR, me ); 
               		if (random(me->query_skill("parry", 1)) > victim->query_skill("parry", 1)/2 ){       
                 		message_vision(HIY "$N�����ֱ�����һק��" + weap->name()
                                	+ "ȴ�޷���"+weap1->name()+"�Ĳ������ѿ����鼱֮��ֻ�÷��������еı��С�\n" NOR, victim );
                 		weap->unequip();
                 		weap->move(environment(me));
                 		victim->reset_action();
               		}
               		else {
                 		message_vision(HIY "$N�����ɾ���" + weap->name()
                                	+ "˳�ŷ��������ת���£��⿪��"+weap1->name()+"�Ĳ��ơ�\n" NOR, victim );
                 		victim->add("neili",-20);
               		}
               		me->add("neili", -30);
             	}
        }
	else {
             	if ( random(me->query_skill("parry", 1)) > victim->query_skill("parry", 1)/2 
              	&& !random(5) 
              	&& !victim->is_busy() ) {
               		victim->start_busy(random(3)+ 1);
               		me->add("neili",-80);
               		victim->receive_damage("qi", damage_bonus, me);
            		victim->receive_wound("qi", damage_bonus/2, me);     
            		message_vision(HIY "ֻ��$N�ı�ʽ�鶯�쳣��"
				+ weap1->name() + "ת����������СȦ�ӣ�������֮����ס�˶Է���"
				+ body_name[random(sizeof(body_name))] +"��\n" NOR, me);
               		message_vision(HIR "$N����һ��,�ƺ����˵��ˡ�\n" NOR, victim );    
           	}             
        }
        return;
}

string perform_action_file(string action)
{
               return __DIR__"cihang-bian/" + action;
}
