// shenghuo-lingfa ʥ���
// 1997-5-14
inherit SKILL;
#include <ansi.h>
string  *msgl = ({
"$Nһʽ���������󡹺��ط��֣�$w��β�����ϵ��������벻����λ������$n��ȥ",
"$Nƽƽһ�������һʽ�����·ת����$w�ڰ�չŹŹֵֹ�ת�˸��䣬����$n��$l",
"$NͻȻһ����Х��˫��һ�С�������ʵ������ʵʵ�����Ƕ��ǵĻ���$n��$l",
"$N��Ȼ��ͷ��һʽ��ͷͷ�ǵ�����һ��ͷ����$nײȥ������$wȴ���е���$n��$l��ȥ",
"$NͻȻ�������һʽ�����������������������Ľ���׹������$w��$n��$l��ȥ",
"$N���ش��أ�һʽ������������������صĿ޺ţ�ͻȻ����߷�ɳ�����$w��$n����",
"$NĬ��ھ���$wһ�С�Ӧ����󡹣���ָǰ�أ�ͻ��һת�䣬��$n�ı��Ĵ�Ѩ��ȥ",
"$Nʹ������ʥ�����е�һ�С�������ǰ����������$n�ұۣ�$wȴ��Է���ǰ��Ѩ��ȥ",
"$Nһ�С��������С�����֪��Σ������Ѿ����$w������һ�ڣ������ޱȵĴ���$n��$l",
"$N���е�$w����һ������Ȧ�ӣ����С��췽��԰��һ������ʱ����$n�ۻ����ң���֪����"
});
string  *msgc = ({
"$N����Ϊ����һ�С�������ʤ��������б�ɣ���������$n�߳��Ľ�",
"$Nһʽ��������ȫ���������ڵ���һ�������ֱ���$n��$l�����ֻ����ж���Ѩ",
"$NͻȻ��һʽ���Խ�Ϊ�ˡ���������ǰһ�����Ľ��������£�˫����$n$l��ȥ",
"$N����һ����һʽ��������ա��������շ��˼������Ľ�������$n��$lץȥ",
"$Nһ�����һʽ���������ڡ������ڰ�գ�����ʱ�ҽŵ�ϥ����$n�ض�һ��",
"$N��ǰһ����һʽ��Ͷ���ͱ�����ײ��$n�Ļ��У�˫����$n$l��Ѩ��ײȥ",
"$N���ش��أ�һʽ����ɳ��ʯ�����������صĿ޺ţ�ͻȻ����߷�ɳ��������$n����"
});

string  *msg2 = ({
HIW"$Nֱ����ǰ������һ�٣���Ȼһ���ˤ�˹�ȥ��˫��$w"HIW"ȴ����$n�ؿ����˹�ȥ"NOR,
HIR"$Nƽƽһ�������$w"HIR"�ڰ�;�ŹŹֵֹ�ת�˸��䣬�ĵ�һ�죬����$n��$l"NOR,
MAG"$N��$w"MAG"���뻳�У�����һ̽����ץס$n��ţ�Ӳ������$n�ڰ�������˻���"NOR,
HIY"$N˫��$w"HIY"���Ӻ�ɨ��$n����һת������ܿ��������ĵ�һ�죬$l�ѱ�$w"HIY"����"NOR,
YEL"$n����ٿ��ץס��$N���ֵ�$w"YEL"����֪��$w"YEL"β�����ϵ����ĵ�һ�죬���ô���$n����"NOR,
GRN"$N�����ڵأ�˫ȭ�ʹ��Լ����ţ���$n����ͻȻ����߷�ɳ�����$w"GRN"��$n��$l����"NOR,
HIG"$N����΢б���ұ������$w"HIG"��Ī������ķ�λת�˹������ĵ�һ������$n��$l���ش�ȥ"NOR
});

int valid_enable(string usage)
{
        return usage == "dagger" || usage== "cuff" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        int level;
        string msg;
        level = (int)me->query_skill("shenghuo-lingfa",1);
        if (level > 300) level= 300+(level-300)/10;
        
        if(me->query_temp("tisha")){
           	switch(me->query_temp("tisha")){
            		case 4: msg = CYN"$Nֱ����ǰ������һ�٣���Ȼһ���ˤ�˹�ȥ��˫������$n�ؿ����˹�ȥ"NOR; break;
            		case 3: msg = CYN"$N�����ڵأ�˫ȭ�ʹ��Լ����ţ���$n����ͻȻ����߷�ɳ�����$w"CYN"��$n��$l����"NOR;break;
            		case 2: msg = CYN"$n����ʱ֮�䣬������ѩ���棬˫�۲��ܼ��ãȻ��֪���룬$N������"YEL"�粿"CYN"�ӱ�����$nײȥ"NOR; break;
            		case 1: msg = CYN"$N����$n��ȥʽ������"HIR"Ǭ����Ų����"CYN"���굽$n����ǰ��������$w"CYN"��$n��$l��ȥ"NOR;break;
            		default: msg = CYN"$Nֱ����ǰ������һ�٣���Ȼһ���ˤ�˹�ȥ��˫������$n�ؿ����˹�ȥ"NOR; break;
           	}  
           	me->add_temp("tisha", -1);
           	return ([
                        "action":msg, 
                        "force" :level * 2,
                        "dodge": random(30)-random(10),
                        "damage": level,
                        "parry": 20+random(20),
                        "damage_type" : me->query_temp("type")? "����":"����",
           	]);
        }
        if (!weapon)
       	 	return ([
                	"action":msgc[random(sizeof(msgc))],
                	"damage_type":"����",
                	"dodge":random(20)-random(8),
                	"force":random(250)+ 200,
        	]);
        if( me->query_temp("ling") && random(10)> 4)
          	return ([
                  	"action" :msg2[random(sizeof(msg2))],
                  	"force" : random(300)+level,
                  	"dodge": random(35)-random(10)+10,
                  	"damage": ((random(3)+1)* 80) +level,
                  	"damage_type":random(2)?"����":"����",
          ]);
        return ([
                "action":msgl[random(sizeof(msgl))],
                "damage":(random(3)+1)* 100,
                "damage_type":random(2)?"����":"����",
                "dodge":random(35)-random(10),
                "force":random(250)+200,
                "post_action":
                (: call_other, WEAPON_D, "bash_weapon" :)
        ]);
}

int practice_skill(object me)
{    
       	object weapon = me->query_temp("weapon");
       	int i;
       
       	if (!weapon)
               	return notify_fail("��û��ʹ�õ�������\n");
       	if(weapon->query("id") == "shenghuo ling")
            	i = 35;
       	else if(weapon->query("id") == "tieyan ling")
            	i = 40;
       	else if(weapon->query("id") == "tie ling")
            	i = 50;
       	else i = 55;
       	
       	if ((int)me->query("jingli") < 60)
               	return notify_fail("�������������ʥ�����\n");         
       	if ((int)me->query("neili") < 60)
               	return notify_fail("�������������ʥ�����\n");
       	me->receive_damage("jingli", i);
       	me->receive_damage("neili", 15);
       	return 1;
}

int valid_learn(object me)
{
       int skill = me->query_skill("shenghuo-lingfa", 1);
       if ((int)me->query("max_neili") < 1000)
               return notify_fail("�������������\n");
       if ((int)me->query_skill("shenghuo-shengong", 1) < (skill-10)
           && me->query_skill("shenghuo-shengong", 1) < 200)
               return notify_fail("���ʥ���񹦻��̫ǳ��\n");      
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shenghuo-lingfa/" + action;
}
