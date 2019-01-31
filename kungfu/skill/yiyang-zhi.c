//cool@SJ,19990628
// Modified by snowman@SJ 20/08/2000
// Modified by Cool@SJ 09/10/2000,change autopfm and yyz_hurt as qishang-quan.

#include <ansi.h>
#include <skill.h>

inherit SKILL;

#include "yiyang-zhi/liumai_skill_msg.h"

string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
"ӿȪѨ","��׶Ѩ","�縮Ѩ",
}); 

mapping *action_finger = ({
([
        "action" : "�����������죬һ����͵�������$N��ָӿ��������һ�С�����ů�ڡ�����������$n$l",
        "weapon" : "һ��ָ��",
        "force": 200,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "����ů��",
	"lvl": 0,
        "damage_type" : "����"
]),
([
        "action" : "$N����ʳָ΢�㣬���С������������һ���ۻ��һ��ָ������$n�����ֳ��ȣ���������",
        "weapon" : "һ��ָ��",
        "force": 150,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "�������",
	"lvl": 20,
        "damage_type" : "����"
]),
([
        "action" : "$Nһָ���ճ�ϼ�⡹��������һ�����ӿ��$n���������´�ƽ�ͣ�����Ȼ����޿��뿹",
        "weapon" : "һ��ָ��",
        "force": 180,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "�ճ�ϼ��",
	"lvl": 30,
        "damage_type" : "����"
]),
([
        "action" : "�����������죬һ����͵�������$N��ָӿ��������һ�С�����ů�ڡ�����������$n$l",
        "weapon" : "һ��ָ��",
        "force": 220,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "����ů��",
	"lvl": 40,
        "damage_type" : "����"
]),
([
        "action" : "$N̤ǰһ������ָ�������һ�㣬$nֻ����Ϣһ�����ѱ������ս������ĸ�����������$l",
        "weapon" : "��������",
        "force": 260,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "���ս���",
	"lvl": 50,
        "damage_type" : "����"
]),
([
        "action" : "$N������ڣ������������׻ӳ���ӿ��$n��$l���������������һ�С�������ů��",
        "skill_name" : "������ů",
        "force": 300,
        "dodge": random(20),
        "parry": random(10),
        "weapon" : "һ��ָ��",
	"lvl": 60,
        "damage_type" : "����"
]),
([
        "action" : "$N���΢Ц�������ʳָ����������$n�ؿڣ����С�ĺ��ӳ�ա�����������ȴ��˿���ƿ�֮��",
        "weapon" : "һ��ָ��",
        "force": 330,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "ĺ��ӳ��",
	"lvl": 70,
        "damage_type" : "����"
]),
([
        "action" : "ֻ��$Nʳָ΢����һָ������Ǭ�������������ɭ�ϣ�Ӻ�����£�������֮�в������߷�ȣ�",
        "weapon" : "��������",
        "force": 380,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "����Ǭ��",
	"lvl": 80,
        "damage_type" : "����"
]),
([     
        "action" : "$Nͷ�������뵣����۽�Ũ����������һ�㣬ʳָ�����һʽ��������̩������$n��",
        "weapon" : "��������",
        "force": 420,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "������̩",
	"lvl": 90,
        "damage_type" : "����"
])
});

mapping *action_sword = ({
([
        "action" : "$N�����Ц����$wƽ�أ���׼ʱ��һ���̳����������������Ѹ���ޱȵ�ֱ��$n$l",
        "damage_type" : "����",
]),
([ 
        "action" : "$N����������������󴫶�����һ��ָ�񹦻���$w֮�ϣ��������أ�ƽƽ�����ش���$n",
        "damage_type" : "����",
]),
([ 
        "action" : "ֻ��$N��Ϣ���񣬽Ų����ţ����ߵ��ƣ�һʽ����������$n$l����ʽ��������",
        "damage_type" : "����",
]),
([
        "action" : "$N���²���΢�䣬���潣�ߣ��������أ���Ʈ�ݵ�һ����$n�̳���������ȴҲ��ʧ��������",
        "damage_type" : "����",
]),
([
        "action" : "$Nƽ��һ�������е�$w���ƽ������أ�ʹ��ʱ�Ա���ǰ��ɬ����ʵ�Ǿ������أ�����֮��",
        "damage_type" : "����",
]),
});

int valid_enable(string usage) 
{  
       return usage=="finger" || usage=="parry" || usage=="sword"; 
}

int valid_learn(object me)
{     
       if ((string)me->query("gender") != "����") 
                return notify_fail("һ��ָ���Ǵ�������������ο�����ϰ��\n");
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��һ��ָ������֡�\n");
       if ((int)me->query_skill("qingyan-zhang", 1) < 70)
                return notify_fail("��������书��򲻹����޷�ѧһ��ָ��\n");      
       if (!me->query_skill("kurong-changong", 1))
                if((int)me->query_skill("qiantian-yiyang", 1) < 100)
                        return notify_fail("����ڹ���򲻹����޷�ѧһ��ָ��\n");
       if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷���һ��ָ��\n");
       return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action_finger)-1; i >= 0; i--)
                return action_finger[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level, n;
        mapping skill_name;
        string msg;

        level = me->query_skill("yiyang-zhi",1);
        me->delete_temp("hit_ob_hit");
        if( objectp(weapon) )
                return ([
                        "action": action_sword[random(sizeof(action_sword))]["action"],
                        "damage": me->query_str()+random(50), 
                        "damage_type": "����",
                        "dodge": random(20),
                        "force": level/2 + me->query_str()*2,
                ]);  
        
        if( intp(n = me->query_temp("yyz/yz3m")) && n > 0 ){
                switch(n){
			case 3: msg = "$N����ʳָ΢����ͻȻ�����ʹ�ľ�Ȼ���ǣ�һ��ָ��������$Nʳָ�϶��������仺��$n�ϰ��������Ѩ\n"+
                                "ȴ��ȫ��$Nһָ����֮�£�����֪Ҫ�������һ��Ѩ�����Ŵ���Ѩ�Դ�ָ֮��";break;
                        case 2: msg = "$N����δ�꣬��������������һָ��������ȴ��ָ��$nС������һָ�����ֵ�ҪѨ���㣬�Ǹ������ʮ����Ѩ�������š�\n"+
                                "ͨ�ȣ�������ע��������ֱ�ֺ�ǡ���������������һָ����֮��"; break;
			case 1: msg = "���ŵ���ָ�ֳ�����һָѸ�����磬ֱָ$nü�ģ�ָ���������ƺ�ͷ��̫�������У��ٻᣮ���ȸ���ҪѨ������һָ����";break;
                        default:msg = "$N����Ծ�����Ƹ��أ�����ʳָ�������ʽδ�ϣ��������أ��������磬����ָ֮�������޷ֺ�ƫ�������\n"+
                                "$n��ǿ�䡢�Ի����縮����׵���յ����������������̨�����ȶ�����ʮ��Ѩ"; break;
                }
                me->add_temp("yyz/yz3m", -1);
                return ([
                        "action":msg,
                        "damage_type":"����",
                        "dodge": 20,
                        "force": level + me->query("jiali"),
                        "skill_name" : "һָ������",
                        "weapon" : "һ��ָ��",
                ]);
        }

        //  ####����####   
        if ( stringp(msg = me->query("env/liumai")) 
        && me->query("jiali") > 50 
        && mapp(skill_name = me->query("liumai-shenjian")) 
        && me->query_skill("liumai-shenjian", 1) )
        {
                n = member_array(msg, keys(skill_name));
                if( n != -1 )
                        switch(msg){
                                case "shaoze": msg = shaoze[random(sizeof(shaoze))]; break;
                                case "guanchong": msg = guanchong[random(sizeof(guanchong))]; break;
                                case "shangyang": msg = shangyang[random(sizeof(shangyang))]; break;
                                case "shaochong": msg = shaochong[random(sizeof(shaochong))]; break;
                                case "zhongchong": msg = zhongchong[random(sizeof(zhongchong))]; break;
                                case "shaoshang": msg = shaoshang[random(sizeof(shaoshang))]; break;
                                default: msg = "";
                        }
                else msg = "";
                
        //hoho here is a bug,���jiali <50�Ļ������ʱ��msg����stringp,����set���Ǹ������ԼӸ��ж�:)
        	if( stringp(msg) && msg!=""){
                	me->set_temp("hit_ob_hit", 1);
                	me->set_temp("liumai_hit", me->query_str()*2);
                	return ([
                        	"action": msg,
                        	"damage": me->query_skill("liumai-shenjian", 1),
                        	"damage_type": "����",
                        	"dodge": random(me->query_dex()),
                        	"force": me->query_skill("force")/2 + me->query_str() * 5 + me->query("jiali") * 2,
                        	"parry": random(me->query_con()),
                        	"weapon" : "����",
                	]);
        	}
        }
        //  ####һ��ָ#### 
        for(i = sizeof(action_finger); i > 0; i--)
                if(level >= action_finger[i-1]["lvl"])
			return action_finger[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{        
        if (!me->query_skill("kurong-changong", 1))
                if((int)me->query_skill("qiantian-yiyang", 1) < 100)
                        return notify_fail("���Ǭ��һ������򲻹����޷���һ��ָ��\n");
        if ((int)me->query("jingli") < 70)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("�������������һ��ָ��\n");                         
        me->receive_damage("jingli", 40);
        me->receive_damage("neili", 10+random(10));
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yiyang-zhi/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        string name,msg;
        object weapon;
        lvl = me->query_skill("yiyang-zhi",1);

        if(me->query_temp("liumai_hit")){
                me->delete_temp("liumai_hit");
                return 0;
        }
        
        if( me->is_perform() 
        || !me->query("env/һ��ָ��Ѩ")
        || me->query("neili") < 1000
	|| me->query("max_neili") < 1500
        || me->query_skill("yiyang-zhi", 1) < 150 )
        	return 0;
        	     
        if( random(10) > 6
        && !me->query_temp("yyz/yz3m")
        && me->query_skill_prepared("finger") == "yiyang-zhi" 
        && me->query_skill_mapped("parry") == "yiyang-zhi"
	&& (me->query_skill_mapped("force") == "qiantian-yiyang"
	||me->query_skill_mapped("force") == "kurong-changong")
        && me->query("combat_exp") >= (victim->query("combat_exp")/3*2) )
        {                                    
        	name = xue_name[random(sizeof(xue_name))];
            	me->add("neili",- 70);
            	me->start_perform(2+random(2), "һ��ָ��Ѩ");
            	if( !objectp(weapon = me->query_temp("weapon"))  ){ 
            		switch(random(6)){
                        case 0 :
                                msg = "$Nһָ���,����$n�ġ�"+name+"����һ��ָ�ھ�ֱ͸��$n���ڸ���ҪѨ��\n";
//				victim->apply_condition("yyz_hurt", lvl/40+victim->query_condition("yyz_hurt"));
                                break;
                        case 1 :
                                msg = "$N����һָ,��һ�б仯Ī��,������$n�ġ�"+name+"����\n";
                                victim->receive_damage("jing", lvl);
                                victim->receive_wound("jing", lvl);
                                break;
                        case 2 :
                                msg = "������$Nʳָһ��һ��,һ��ָ���ƿն���,������$n�ġ�"+name+"����$n���������̻�ɢ��\n";
                                victim->add("neili", -lvl*2);
                                if( victim->query("neili") < 0) 
                                    victim->set("neili", 0);
                                break;
                        case 3 :
                                msg = "$N��ָ���,ɲ�Ǽ�����һ��ָ��ֱ��$n�ġ�"+name+"����$n����һ��,������ҪѨ��\n";
                                if( !victim->is_busy() )
                                        victim->start_busy(2 + random(2));
                                else    victim->add_temp("lost_attack", 2);
                                break;
                        case 4:
                                msg = "$Nָ���仯�޳�,һָ����,һ��ָ��ȴ��������$n�ġ�"+name+"����$n��֮�±����С�\n";
                                victim->add("jingli", -lvl);
                                break;
                        case 5:
                                msg ="$N��������,һ��ָ��ȫ������$n�ġ�"+name+"��,$n����Ϣ����ɢ�ҡ�\n";
                                victim->apply_condition("no_perform", 3);
                                victim->add_temp("lost_attack", 2);
                                break;
                }         
                message_vision(msg, me, victim);
        } 
        else {
                victim->receive_damage("neili", me->query_skill("yiyang-zhi",1)/4 );
                victim->receive_wound("qi", me->query_skill("yiyang-zhi",1)/2 + damage_bonus/4);
                return "ֻ��$N����"+weapon->query("name")+"ͻȻ����һ��ҫ�۵Ĺ�â,$n����������"+name+"���������ɵ�һ�ͣ�\n";
        }
}
}
