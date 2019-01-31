#include <ansi.h>
 inherit FORCE;
#include "/kungfu/skill/eff_msg.h";
string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",}); 

mapping *action = ({
([      "action": "$N�����������������޳���,������ת�����ƴ�в�������$w�����ľ�����$n��ȥ",
        "weapon" : "��Ե",
        "dodge": 10,
        "parry": 10,
        "force": 100,
        "lvl" : 0,
        "skill_name" : "�����޳�",
        "damage_type": "����"
]),
([      "action": "$N˫���������У��Ϻȣ����������ҡ�����������һ�����ݳ������һ����ǽֱ����$n",
        "dodge": 5,
        "parry": -15,
        "force": 100,
        "lvl" : 40,
        "skill_name" : "��������",
        "damage_type": "����"
]),
([      "action": "$N˫�ƽ�����հ���,����һ�𣺡��������֡���һ����$n��$l��ȥ",
        "dodge": 10,
        "parry": -15,
        "force": 150,
        "lvl" : 60,
        "skill_name" : "��������",
        "damage_type": "����"
]),

([      "action": "$NĴָ�������ģ�Ĭӽ���������޾���,������̧��������$n��$l��ȥ",
        "dodge": 10,
        "parry": -5,
        "force": 200,
        "lvl" : 80,
        "skill_name" : "�����޾�",
        "damage_type": "����"
]),

([      "action": "$Nһ����ȣ����Ǽٷǿա�,�����ĳ�һ����ɽ����������",
        "dodge": 10,
        "parry": 0,
        "force": 250,
        "lvl" : 100,
        "skill_name" : "�Ǽٷǿ�",
        "damage_type": "����"
]),
 ([     "action": "$N��Ц��Ц������һ�ƣ�����һ����һ����ת��������$n���Ű�Χ",
        "weapon" : "�Ʒ�",
        "dodge": -10,
        "parry": 10,
        "force": 300,
        "lvl" : 120,
        "skill_name" : "�ǿݷ���",
        "damage_type": "����"
]),

([      "action": "$N˫�ֺ�ʲ����������������١���˫�ƽ�������Ƴ����������ص�����ֱ����$n",
        "dodge": 15,
        "parry": 10,
        "force": 350,
        "lvl" : 140,
        "skill_name" : "�������",
        "damage_type": "����"
]),
});

int valid_enable(string usage) 
{ return usage == "force" || usage=="strike" || usage =="parry"; }

void skill_improved(object me)
{
      	int skill = me->query_skill("kurong-changong", 1);
      	int skill1 = me->query_skill("qiantian-yiyang", 1);
      	if(skill >= 200 && !me->query("kr_add")){
         	me->set("kr_add", 1);   
         	tell_object(me, GRN"\n��Ȼ�������һ�������ɵ���������:\n
         ��һ����Ϊ�������λ���Ӱ��\n
         ����¶����磬Ӧ�����ǹۡ�\n
         ���������Ϊ����һ���µľ��磡\n
         ������������ˣ�\n��ı�����ǿ�ˣ�\n"NOR);
        	me->add("max_neili", skill+random(skill1));
     	 }
}

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level;
        level = (int) me->query_skill("kurong-changong",1);
        
	i = NewRandom(sizeof(action), 20, level/5);
        if( me->query_temp("pf_rong")
        && me->query("jiali")
        && random(10) >= 5 ){
            	return ([
               		"action" : RED+action[i]["action"]+NOR,
               		"force" : action[i]["force"]+ random(2*me->query("jiali")),
               		"dodge": action[i]["dodge"],
               		"damage_type" : "����",
               	]);
       	} 
       	for(i = sizeof(action); i > 0; i--)
               	if(level > action[i-1]["lvl"])
               		return action[NewRandom(i, 20, level/5)];
}

int valid_learn(object me)
{       
        
        int i, l;        
        int t = 1, j;
        mapping myfam = (mapping)me->query("family");
        for (j = 1; j < i / 10; j++) t *= 2;        
        i = (int)me->query_skill("kurong-changong", 1);       
        l = (int)me->query_skill("buddhism", 1);       
        
        if (i > 120 && i <180 && l < i - 10)
        	return notify_fail("����������Ҫ���ķ�ѧ���裬��ķ�ѧ������\n");

        if (me->query_skill("qiantian-yiyang",1) < 140)
                return notify_fail("���Ǭ��һ������򻹲������޷�������������\n");

        if ( me->query("gender") != "����" )
                return notify_fail("���ͯ��֮�壬������ϰ���������ڹ���\n");

        if (me->query("class") != "bonze" || me->query("menggu"))
               	return notify_fail("����ҷ���ӣ�������ϰ����������\n");
       
        if (me->query_skill("yiyang-zhi",1) < 140)
               	return notify_fail("����������Ҫһ��ָ����Ϊ��ܡ�\n");
 
        if ((int)me->query_skill("kurong-changong", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("kurong-changong", 1) >= 200 )
               	return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");
               
        if ( !mapp(myfam) || myfam["master_name"] != "���ٳ���")
               	return notify_fail("�㱲�ֲ�������������ϰ����������\n");
        return 1;
}

int practice_skill(object me)
{
       if((int)me->query_skill("kurong-changong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("kurong-changong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ��������߿��������ˡ�\n");
       } else return notify_fail("�����������������ϰ��\n");
}

string exert_function_file(string func)
{
        return __DIR__"kurong-changong/" + func;
}

mapping exercise_msg(object me)
{
        return ([
          "status_msg" : HIG + me->name()+"�����ɬ֮����˫Ŀ�ʹ����ӡ�" NOR,
          "start_my_msg" : "����ϥ���£���Ŀ��ʲ��Ĭ�˿���������ֻ����������������ʼ�����ڻ����ζ���\n",
          "start_other_msg" : me->name()+"��ϥ���£���Ŀ��ʲ�������ƺ�������һ������֮�С�\n",
          "halt_msg" : "$N˫��һ�֣�������ȭ����������Ѹ�ٽ������ڡ�\n",
          "end_my_msg" : "������������������һ�����죬�����������ڵ������̧�����۾���\n",
          "end_other_msg" : "ֻ��"+me->name()+"���������۾����������ֵ���������ȥ��\n"
        ]);
}

string perform_action_file(string action)
{
        return __DIR__"kurong-changong/" + action;
}

int ob_hit(object ob, object me, int damage)
{
        string msg;
        int j, neili, neili1;
        
        if( damage < 40) return 0;

        if(me->query_temp("kurong-changong")){
            	me->delete_temp("kurong-changong");
           	return 0;
        }
	
        neili = me->query("neili");
        neili1 = ob->query("neili");
        
        if( random(me->query_skill("parry")) > ob->query_skill("parry")/3*2
        && me->query_skill_mapped("parry") == "kurong-changong"
        && me->query_skill_mapped("force") == "kurong-changong"
        && neili > 400
        && me->query_skill("parry") > 300
        && !ob->query_temp("weapon")
        && random(10) > 5){ 
          	me->add_temp("kurong-changong", 1);    
          	msg = GRN "$NĬ�˿��������ġ��ݡ��ִ󷨣�������ӵ�����͸������������ȫ��������$N���������ϡ�\n" NOR;
          	tell_object(ob, HIR "��ֻ������ͻȻ����һ�࣬���������ӭ��������\n" NOR);
          	msg += "$nһ�д���$N�����ϣ�ֻ���ƺ�����һ����ľ�ϡ�\n";
          	if(neili >= neili1*2 + random(damage)){
              		msg += "���$n�Ĺ�����$N�Ŀ������������ˣ�\n", 
              		j = -8000;
          	}
          	else if( neili > neili1 + random(damage) ){
              		msg += "���$n�Ĺ�����$N������һ�룡\n", 
              		j = -damage/2;               
          	}
          	else{
              		msg += "���$Nֻ������$n��һС��������\n", 
              		j = -damage/4; 
          	}           
          	message_vision(msg, me, ob);
          	return j;
        }        
}

