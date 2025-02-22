//cool@SJ,19990628
// Modified by snowman@SJ 20/08/2000
// Modified by Cool@SJ 09/10/2000,change autopfm and yyz_hurt as qishang-quan.

#include <ansi.h>
#include <skill.h>

inherit SKILL;

#include "yiyang-zhi/liumai_skill_msg.h"

string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
"涌泉穴","大锥穴","风府穴",
}); 

mapping *action_finger = ({
([
        "action" : "忽听嗤嗤轻响，一股柔和的气流自$N手指涌出，正是一招「阳春暖融」，缓缓点向$n$l",
        "weapon" : "一阳指力",
        "force": 200,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "阳春暖融",
	"lvl": 0,
        "damage_type" : "刺伤"
]),
([
        "action" : "$N右手食指微点，出招「晓天初阳」，一股雄浑的一阳指力射向$n，出手沉稳，招数正大",
        "weapon" : "一阳指力",
        "force": 150,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "晓天初阳",
	"lvl": 20,
        "damage_type" : "刺伤"
]),
([
        "action" : "$N一指「日出霞光」，激出的一股罡气涌向$n，看似是温淳平和，但沛然浑厚，无可与抗",
        "weapon" : "一阳指力",
        "force": 180,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "日出霞光",
	"lvl": 30,
        "damage_type" : "内伤"
]),
([
        "action" : "忽听嗤嗤轻响，一股柔和的气流自$N手指涌出，正是一招「阳春暖融」，缓缓点向$n$l",
        "weapon" : "一阳指力",
        "force": 220,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "阳春暖融",
	"lvl": 40,
        "damage_type" : "刺伤"
]),
([
        "action" : "$N踏前一步，伸指凌空轻轻一点，$n只觉气息一紧，已被「赤日焦阳」的刚阳气劲触到$l",
        "weapon" : "纯阳真气",
        "force": 260,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "赤日焦阳",
	"lvl": 50,
        "damage_type" : "刺伤"
]),
([
        "action" : "$N衣袖轻摆，罡阳柔气从袖底挥出，涌向$n的$l，正是玄功若神的一招「晓阳云暖」",
        "skill_name" : "晓阳云暖",
        "force": 300,
        "dodge": random(20),
        "parry": random(10),
        "weapon" : "一阳指力",
	"lvl": 60,
        "damage_type" : "内伤"
]),
([
        "action" : "$N面带微笑，伸出右食指，缓缓点向$n胸口，这招「暮云映日」劲气弥漫，却无丝毫破空之声",
        "weapon" : "一阳指力",
        "force": 330,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "暮云映日",
	"lvl": 70,
        "damage_type" : "刺伤"
]),
([
        "action" : "只见$N食指微屈，一指「九天乾阳」点出，气象森严，雍容肃穆，于威猛之中不脱王者风度！",
        "weapon" : "纯阳真气",
        "force": 380,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "九天乾阳",
	"lvl": 80,
        "damage_type" : "内伤"
]),
([     
        "action" : "$N头顶白气氤氲，渐聚渐浓，便似蒸笼一般，食指伸出，一式「三阳开泰」按向$n！",
        "weapon" : "纯阳真气",
        "force": 420,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "三阳开泰",
	"lvl": 90,
        "damage_type" : "震伤"
])
});

mapping *action_sword = ({
([
        "action" : "$N嘴角轻笑，提$w平胸，看准时机一剑刺出，激起呼呼风声，迅猛无比地直插$n$l",
        "damage_type" : "刺伤",
]),
([ 
        "action" : "$N左手捏个剑诀，右腕传动，将一阳指神功化于$w之上，出剑凝重，平平正正地刺向$n",
        "damage_type" : "刺伤",
]),
([ 
        "action" : "只见$N屏息凝神，脚步沉着，剑走刀势，一式横劈，砍向$n$l，招式威猛正大",
        "damage_type" : "割伤",
]),
([
        "action" : "$N脚下步法微变，身随剑走，端凝自重，极飘逸的一剑向$n刺出，轻灵中却也不失王者气象",
        "damage_type" : "刺伤",
]),
([
        "action" : "$N平推一剑，手中的$w看似渐渐沉重，使动时略比先前滞涩，但实是举轻若重，威猛之极",
        "damage_type" : "刺伤",
]),
});

int valid_enable(string usage) 
{  
       return usage=="finger" || usage=="parry" || usage=="sword"; 
}

int valid_learn(object me)
{     
       if ((string)me->query("gender") != "男性") 
                return notify_fail("一阳指乃是纯阳玄功，你如何可以修习？\n");
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练一阳指必须空手。\n");
       if ((int)me->query_skill("qingyan-zhang", 1) < 70)
                return notify_fail("你的其它武功火候不够，无法学一阳指。\n");      
       if (!me->query_skill("kurong-changong", 1))
                if((int)me->query_skill("qiantian-yiyang", 1) < 100)
                        return notify_fail("你的内功火候不够，无法学一阳指。\n");
       if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力太弱，无法练一阳指。\n");
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
                        "damage_type": "刺伤",
                        "dodge": random(20),
                        "force": level/2 + me->query_str()*2,
                ]);  
        
        if( intp(n = me->query_temp("yyz/yz3m")) && n > 0 ){
                switch(n){
			case 3: msg = "$N右手食指微曲，突然点出，使的竟然便是＂一阳指＂。但见$N食指幌动，来势虽缓，$n上半身正面大穴\n"+
                                "却已全在$N一指笼罩之下，竟不知要点的是那一处穴道，九处大穴皆大指之虞";break;
                        case 2: msg = "$N招数未完，抢上数步，又是一指点出，这次却是指向$n小腹，这一指所盖罩的要穴更广，肚腹间冲脉十二大穴，自幽门、\n"+
                                "通谷，下至中注、四满，直抵横骨、会阴，尽处于这一指威力之下"; break;
			case 1: msg = "跟着第三指又出，这一指迅如闪电，直指$n眉心，指尖闪动，似乎头部太阳，人中，百会．．等各大要穴尽在这一指笼罩";break;
                        default:msg = "$N忽地跃起，左掌抚胸，右手食指点出，招式未老，立即缩回，快似闪电，但着指之处，竟无分毫偏差，连点向\n"+
                                "$n的强间、脑户、风府、大椎、陶道、身柱、神道、灵台．．等督脉三十大穴"; break;
                }
                me->add_temp("yyz/yz3m", -1);
                return ([
                        "action":msg,
                        "damage_type":"内伤",
                        "dodge": 20,
                        "force": level + me->query("jiali"),
                        "skill_name" : "一指点三脉",
                        "weapon" : "一阳指力",
                ]);
        }

        //  ####六脉####   
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
                
        //hoho here is a bug,如果jiali <50的话，这个时候msg还是stringp,就是set的那个，所以加个判断:)
        	if( stringp(msg) && msg!=""){
                	me->set_temp("hit_ob_hit", 1);
                	me->set_temp("liumai_hit", me->query_str()*2);
                	return ([
                        	"action": msg,
                        	"damage": me->query_skill("liumai-shenjian", 1),
                        	"damage_type": "刺伤",
                        	"dodge": random(me->query_dex()),
                        	"force": me->query_skill("force")/2 + me->query_str() * 5 + me->query("jiali") * 2,
                        	"parry": random(me->query_con()),
                        	"weapon" : "剑气",
                	]);
        	}
        }
        //  ####一阳指#### 
        for(i = sizeof(action_finger); i > 0; i--)
                if(level >= action_finger[i-1]["lvl"])
			return action_finger[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{        
        if (!me->query_skill("kurong-changong", 1))
                if((int)me->query_skill("qiantian-yiyang", 1) < 100)
                        return notify_fail("你的乾天一阳功火候不够，无法练一阳指。\n");
        if ((int)me->query("jingli") < 70)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("你的内力不够练一阳指。\n");                         
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
        || !me->query("env/一阳指点穴")
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
            	me->start_perform(2+random(2), "一阳指点穴");
            	if( !objectp(weapon = me->query_temp("weapon"))  ){ 
            		switch(random(6)){
                        case 0 :
                                msg = "$N一指点出,正中$n的「"+name+"」，一阳指内劲直透入$n体内各大要穴。\n";
//				victim->apply_condition("yyz_hurt", lvl/40+victim->query_condition("yyz_hurt"));
                                break;
                        case 1 :
                                msg = "$N反手一指,这一招变化莫测,正点中$n的「"+name+"」。\n";
                                victim->receive_damage("jing", lvl);
                                victim->receive_wound("jing", lvl);
                                break;
                        case 2 :
                                msg = "紧接着$N食指一曲一弹,一道指力破空而出,正点中$n的「"+name+"」，$n的真气立刻涣散。\n";
                                victim->add("neili", -lvl*2);
                                if( victim->query("neili") < 0) 
                                    victim->set("neili", 0);
                                break;
                        case 3 :
                                msg = "$N出指如电,刹那间数道一阳指力直逼$n的「"+name+"」，$n身子一滞,被击中要穴。\n";
                                if( !victim->is_busy() )
                                        victim->start_busy(2 + random(2));
                                else    victim->add_temp("lost_attack", 2);
                                break;
                        case 4:
                                msg = "$N指法变化无常,一指向天,一阳指力却弯曲绕向$n的「"+name+"」，$n大骇之下被击中。\n";
                                victim->add("jingli", -lvl);
                                break;
                        case 5:
                                msg ="$N连环三下,一阳指力全部击中$n的「"+name+"」,$n的内息立刻散乱。\n";
                                victim->apply_condition("no_perform", 3);
                                victim->add_temp("lost_attack", 2);
                                break;
                }         
                message_vision(msg, me, victim);
        } 
        else {
                victim->receive_damage("neili", me->query_skill("yiyang-zhi",1)/4 );
                victim->receive_wound("qi", me->query_skill("yiyang-zhi",1)/2 + damage_bonus/4);
                return "只见$N手中"+weapon->query("name")+"突然发出一股耀眼的光芒,$n被剑气刺中"+name+"，真气不由得一滞！\n";
        }
}
}
