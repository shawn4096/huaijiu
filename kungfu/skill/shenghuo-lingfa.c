// shenghuo-lingfa 圣火令法
// 1997-5-14
inherit SKILL;
#include <ansi.h>
string  *msgl = ({
"$N一式「以意相求」忽地放手，$w的尾端向上弹起，以意想不到方位呼的向$n拍去",
"$N平平一令击出，一式「风回路转」，$w在半空古古怪怪的转了个弯，打向$n的$l",
"$N突然一声清啸，双令一招「三虚七实」虚虚实实，是是而非的击向$n的$l",
"$N忽然低头，一式「头头是道」，一个头锤向$n撞去，手中$w却暗中的向$n的$l击去",
"$N突然纵身而起，一式「翻江倒海」连翻三个空心筋斗，白光忽闪，$w向$n的$l砸去",
"$N坐地锤胸，一式「瞒天过海」呼天抢地的哭号，突然间脚踢飞沙，抽出$w向$n疾刺",
"$N默念口诀，$w一招「应左则后」，明指前胸，突地一转弯，向$n的背心大穴砸去",
"$N使出的是圣火令中的一招「须右仍前」，凌空虚点$n右臂，$w却向对方胸前大穴刺去",
"$N一招「无中生有」，不知如何，手中已经多出$w，手腕一摆，快速无比的刺向$n的$l",
"$N手中的$w划出一个个的圈子，这招「天方地园」一出，顿时裹得$n眼花缭乱，不知所措"
});
string  *msgc = ({
"$N反守为攻，一招「乱中求胜」，身体斜飞，连环的向$n踢出四脚",
"$N一式「坐地求全」，忽地在地上一坐，左手抱向$n的$l，右手击向“中都”穴",
"$N突然间一式「以进为退」，接着向前一个空心筋斗，凌空落下，双足向$n$l踢去",
"$N呼的一声，一式「庶天蔽日」，纵身半空翻了几个空心筋斗，伸臂向$n的$l抓去",
"$N一个筋斗，一式「万流归宗」，身在半空，落下时右脚的膝盖在$n关顶一脆",
"$N向前一坐，一式「投怀送抱」，撞入$n的怀中，双肘向$n$l的穴道撞去",
"$N坐地锤胸，一式「飞沙走石」，呼天抢地的哭号，突然间脚踢飞沙，单手向$n疾点"
});

string  *msg2 = ({
HIW"$N直抢而前，脚下一踬，忽然一个筋斗摔了过去，双手$w"HIW"却已向$n胸口拍了过去"NOR,
HIR"$N平平一令击出，$w"HIR"在半途古古怪怪的转了个弯，拍的一响，拍向$n的$l"NOR,
MAG"$N将$w"MAG"插入怀中，右手一探，已抓住$n左脚，硬生生将$n在半空中拉了回来"NOR,
HIY"$N双手$w"HIY"急挥横扫，$n身形一转，向左避开，不意拍的一响，$l已被$w"HIY"击中"NOR,
YEL"$n左手倏地抓住了$N左手的$w"YEL"。岂知那$w"YEL"尾端向上弹起，拍的一响，正好打中$n手腕"NOR,
GRN"$N坐倒在地，双拳猛捶自己胸膛，待$n靠近突然间脚踢飞沙，抽出$w"GRN"向$n的$l疾刺"NOR,
HIG"$N上身微斜，右臂弯过，$w"HIG"从莫名其妙的方位转了过来，拍的一声，向$n的$l重重打去"NOR
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
            		case 4: msg = CYN"$N直抢而前，脚下一踬，忽然一个筋斗摔了过去，双手已向$n胸口拍了过去"NOR; break;
            		case 3: msg = CYN"$N坐倒在地，双拳猛捶自己胸膛，待$n靠近突然间脚踢飞沙，抽出$w"CYN"向$n的$l疾刺"NOR;break;
            		case 2: msg = CYN"$n在霎时之间，但觉飞雪扑面，双眼不能见物，茫然不知所措，$N趁势用"YEL"肩部"CYN"从背后向$n撞去"NOR; break;
            		case 1: msg = CYN"$N随着$n的去式，巧运"HIR"乾坤大挪移神功"CYN"，钻到$n的身前，将手中$w"CYN"向$n的$l插去"NOR;break;
            		default: msg = CYN"$N直抢而前，脚下一踬，忽然一个筋斗摔了过去，双手已向$n胸口拍了过去"NOR; break;
           	}  
           	me->add_temp("tisha", -1);
           	return ([
                        "action":msg, 
                        "force" :level * 2,
                        "dodge": random(30)-random(10),
                        "damage": level,
                        "parry": 20+random(20),
                        "damage_type" : me->query_temp("type")? "内伤":"割伤",
           	]);
        }
        if (!weapon)
       	 	return ([
                	"action":msgc[random(sizeof(msgc))],
                	"damage_type":"瘀伤",
                	"dodge":random(20)-random(8),
                	"force":random(250)+ 200,
        	]);
        if( me->query_temp("ling") && random(10)> 4)
          	return ([
                  	"action" :msg2[random(sizeof(msg2))],
                  	"force" : random(300)+level,
                  	"dodge": random(35)-random(10)+10,
                  	"damage": ((random(3)+1)* 80) +level,
                  	"damage_type":random(2)?"内伤":"割伤",
          ]);
        return ([
                "action":msgl[random(sizeof(msgl))],
                "damage":(random(3)+1)* 100,
                "damage_type":random(2)?"刺伤":"割伤",
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
               	return notify_fail("你没有使用的武器。\n");
       	if(weapon->query("id") == "shenghuo ling")
            	i = 35;
       	else if(weapon->query("id") == "tieyan ling")
            	i = 40;
       	else if(weapon->query("id") == "tie ling")
            	i = 50;
       	else i = 55;
       	
       	if ((int)me->query("jingli") < 60)
               	return notify_fail("你的体力不够练圣火令法。\n");         
       	if ((int)me->query("neili") < 60)
               	return notify_fail("你的内力不够练圣火令法。\n");
       	me->receive_damage("jingli", i);
       	me->receive_damage("neili", 15);
       	return 1;
}

int valid_learn(object me)
{
       int skill = me->query_skill("shenghuo-lingfa", 1);
       if ((int)me->query("max_neili") < 1000)
               return notify_fail("你的内力不够。\n");
       if ((int)me->query_skill("shenghuo-shengong", 1) < (skill-10)
           && me->query_skill("shenghuo-shengong", 1) < 200)
               return notify_fail("你的圣火神功火候太浅。\n");      
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shenghuo-lingfa/" + action;
}
