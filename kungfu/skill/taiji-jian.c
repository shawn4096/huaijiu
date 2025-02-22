// created by snowman@SJ
// Modified by snowman@SJ 02/10/2000
// Modified again for tjj level > 450,  by snowman@SJ 23/02/2001
// Modified by snowman@SJ 23/04/2001. Npc cannot use 剑指

#include <ansi.h>
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>

string  *msg = ({
"$N右脚向前一步，左膝提起，$w向前，从上方划出一招「宿鸟投林」，刺向$n的$l",
"只见$N一反身，手中$w跟着向前划了一个大弧，使出一招「流星赶月」，回劈$n的$l",
"$N一式「大魁星」点出漫天圈影，一时竟如千万把$w同时画圈般，分不清孰真孰幻",
"$N一招「天马行空」，双脚轻点，向前两步跃落，右手$w由上向前劈下，飘逸地点向$n的$l",
"$N提起左腿，转身垫步，接着右脚跟进，一招「黄峰入洞」，$w中宫直进，刺向$n的$l",
"$N一招「射雁式」，左脚跃步落地，将$w回抽，剑势不缓不急，反手勾向$n的$l",
"$N跟进一招「燕子抄水」，手中$w自上而下划出一个大弧，平平地向$n的$l挥去",
"$n身形加快，手中兵刃几向$N背后，$N反手圈转化解，身随剑转，正是一招「狮子摇头」",
"$N摆一个左虚步，手中$w顺势划出一个整圆，点出一式「小魁星」，撩向$n的$l",
"$N运使太极剑意画出无数剑圈，忽听“叮”地一声清鸣，一点「小魁星」似电剑星急射$n面门",
"$N右脚独立，右手$w向后撤，再向前平平托起，这是一招「挑帘式」，刺向$n的$l",
"$N使一招「风扫梅花」，身体不停地旋转，右手$w随身转动，风雷电掣般向$n的$l扫去",
"$N左脚前进一步，右手$w一招「顺水推舟」，剑势绵绵不断，向前刺向$n的$l",
"$N一个弓步挂劈，再一个虚步抡劈，左右「车轮剑」，绵绵不绝劈向$n的$l",
"$N反执长剑，青芒闪烁间足踏偏门一式“顺水推舟”带出一片柔和的流光划过$n身侧",
"$N微一凝神，一招「探海式」，右脚独立，左膝提起，钢剑向前抡劈$n的$l",
"$N右脚后撤一步，一转身，右手$w向后反击，一招「大鹏展翅」，抹向$n的$l",
"$N双脚并步，身体立起，双手持$w，一招「白猿献果」，向前平平刺出，点向$n的$l",
"$N向前连跳两步，一招「野马跳涧」，手中$w向前平刺两剑，齐齐点向$n的$l",
"$N右脚向前垫步，一招「海底捞月」，$w由上向后划一个大弧，向前撩向$n的$l",
"只见$N身形似逐月之飞花，右手轻捻剑决，左手$w轻盈点出「挑帘式」",
"$N神色凝重，左脚独立，右膝提起，双手捧剑，一招「虎抱头」，缓缓刺向$n的$l",
"$N左脚踏实，右脚虚点，一招「仙人指路」，右手$w带着一团剑花，逼向$n的$l",
"$N顺手一招「右拦扫」，一招「左拦扫」，剑锋平指，一气呵成横扫$n的$l",
"$N$w圈转淡然化解$n凌厉攻势，青锋顺势一式“迎风掸尘”有如清风徐送，却是杀机暗藏",
"$N一招「乌龙摆尾」，右脚变虚步，右手回收，顺势带动$w向下截劈$n的$l",
"$N心神不乱，顺手拔出腰间$w，一招太极剑法「圆转如意」，斜斜划了个圈子，刺向$n的$l",
"$N左脚向前进一步，$w由后划一整圆向前托起，一招「迎风掸尘」，刺向$n的$l",
"$N使一招「青龙出水」，右脚向后回撤，$w随身体右后撤，突然向左前方刺向$n的$l",
"$N虚步提腰，一招「蜻蜓点水」，手中$w轻轻颤动，一剑剑点向$n的全身大穴",
"$N向前跨上一步，左手剑诀，右手$w使出一式「指南针」，剑尖直刺$n的$l",
"$N一招「燕子掠波」，$w自上而下划出一个大弧，平平地向$n的$l挥去",
"$n势如疯魔，绕着$N展开狂风般的攻击，$N剑守「指南针」从容化解,倏然清斥一声“着”",
"$N一招「却步抽剑」，左脚跃步落地，引$p进前，接着$w回抽，反手勾向$n的$l",
"$N右腿半屈般蹲，一招「如封似闭」，捏了个剑诀，剑尖虚指，转身撩向$n的$l",
"$N回身拧腰，右手虚抱，一招「拨云瞻日」，$w中宫直进，中正平和地刺向$n的$l"
});

string *parry_msg = ({
"$p左手剑诀斜引，$w横过，画了个半圈，平搭在$P$W之上，劲力传出，$W登时一沉。\n",
"$p手中$w斜指，太极圆圈在$W上一搭，结果$P的力道被卸在一旁！",
"$p剑交左手，在身前划了两个圆圈，剑劲连绵护住全身，竟无半分空隙，欲将$P之来势化解与无形。\n",
"$p将$w交左手，在身前划了两个圆圈，$P见$p剑劲连绵，护住全身，竟无半分空隙。\n",
"只见$p使出四两拨千斤之巧劲，$w斜引，将$P的$W引在一旁！\n",
"$p以数十招剑法混成守势，似有千百柄长剑护住全身，圆转如意，竟无半分破绽。\n",
"$p剑招陡然圈转，划出几个白色光圈，大圈小圈，正圈斜圈、一个未消，另一个再生，全身隐入光圈之中。\n",
"$n身形绕向$P背后，$N身随剑转，反手圈转轻易地化解！\n",
"$p剑招未曾使老，已然圈转。突然之间，$P眼前出现了几个白色光圈，大圈小圈，正圈斜圈，闪烁不已。$P眼睛一花，只好回招。\n",
"$p当下凝神专志，将一套太极剑法使得圆转如意，严密异常的守住门户，使$P招数落空。\n",
"$p以太极剑中「云麾三舞」三式解开。$P见$p化解时举重若轻，深得内家剑术三昧，不待$p回手，跳开一步。\n"
});

string *taiji_msg = ({
"$N神情萧索，一式「手挥五弦」左手虚抚，右手长剑扬手挥洒，点点剑花飞向$n，虚实不定",
"$N目送远方翩鸿孤飞，清叹一声，内力到处$w发出嗡嗡轻鸣，剑意似绝非断，挥洒出漫天剑影",
"但见$N剑法吞吐开合、阴阳动静，实已到了太极剑法的绝诣",
"$N手中$w虽使得极快，却丝毫听不到金刃劈风之声，足见剑劲之柔韧已达于化境",
"$N将剑法中最精要之处都发挥了出来，愈战愈强，$w发出的内劲不断增强",
"太极剑法乃张三丰晚年继太极拳所创，实是近世登峰造极的剑术，$N功劲一加运开，绵绵不绝，绝无破绽",
"$N不疾不徐的漫步扬长而步，遇到$n招数，$P$w一颤，便是一缕剑光闪出",
"$N凝望$n招式，出剑以蜿蜒之势、身处庄稳之形，宛如旭日东升，剑光如金蛇万道，闪烁不定",
"$N出剑迟缓，可是剑法中破绽之少，实所罕见",
"$N左手$w缓缓向前划出，成一弧形，一股森森寒气，直逼向$n，突然之间，$N剑交右手，寒光一闪向$n的$l划去",
"$N剑法突变，剑招凌厉狠辣，以极浑厚内力，使极锋锐利剑，出极精妙招数，青光荡漾，剑气弥漫",
"$N出剑迅捷，可是剑法中破绽之少，实所罕见",
"$N$w随手一招打出，以己之钝，挡敌之无锋，正是张三丰传授的太极剑「剑意」的精奥神髓",
"$N猛然攻出招，招招都未曾使老，已然圈转，剑势犹如浪潮一般，缓缓涌向$n",
"$N姿式固是飘渺之极，但剑招古朴浑厚，剑上的威力似乎只发挥得一二成，其余的却是蓄势以待，深藏不露",
"但见青光闪动，$N手中$w刺了出去，但见剑刃平刺，锋口向着左右",
"$N双眼注视$n，手握$w剑柄，脚走八卦，拔剑一招中宫挺进，看似缓慢无力，实则包含了上乘太极之劲，力能辟金断银",
"$N出剑没有招式，剑招中全是“神在剑先、绵绵不绝”之意，一丝丝缠向$n",
"$N画剑成圈，一点寒星刺向$n",
"但见$N将手中$w缓缓伸出，随手画了个半圆，落向$n",
"$N随手一挥，$w又左向右斜划而出，可一阵尖锐的破空声出，证明此招已达反朴归真的境界",
"$N$w在空中划成大圈，右手剑诀戳出，竟似也发出嗤嗤微声",
"$N左足踏上，剑交左手，一招“三环套月”，一剑虚虚实实，以左手剑攻敌，剑尖上光芒闪烁，嗤嗤嗤的发出轻微响声",
"$N身子缓缓右转，左手持剑缓缓向上提起，剑身横于胸前，左右掌心相对，双臂成环，手中$w点出，已然蓄势无穷",
"$N一剑刺到，青光闪闪，发出嗤嗤声响，内力极强",
"$N右手捏着剑诀，左手$w不住的抖动，罩向$n上盘七大要穴，剑尖急颤，看不出攻向何处",
"$N左手剑诀斜引，$w横过，画个半圆，劲力传出，直刺$n$l",
"$N功劲一加运开，手中$w剑势绵绵不绝，绝无破绽",
"$N手里$w使得心应手，熟极而流，剑招精奇，轻翔灵动，变幻不测，突然抖腕翻剑，直向$n的$l刺到",
"$N$w递出，顺着$n来路削下，以己之钝，挡敌之无锋，实已得了太极剑法的精奥",
"$N以意驭剑，千变万化，无穷无尽，每一招都看似平淡，实则蓄势以待，深藏不露",
"$N以$w画着一个个圆圈，每一招均是以弧形刺出，以弧形收回",
"$N以意驭剑，神在剑先，绵绵不绝，剑招看似慢吞吞，软绵绵，实则千变万化，无穷无尽",
"$N朗声长啸，剑法纵横变化，奇幻无方，$w在其内力运使之下青光闪闪，威不可挡",
"$N心中竟无半点渣滓，以意运剑，$w每发一招，便似放出一条细丝，要去缠住$n",
"$N出剑递招，可说来来去去只有一招，然而这一招却永是应付不穷",
"$N剑法吞吐开合、阴阳动静，将太极剑法中最精要之处都发挥了出来，功劲一加运开，绵绵不绝",
"$N左手$w缓缓向前划出，成一弧形。$n只觉一股森森寒气，直逼过来",
"$N右手捏著剑诀，左手$w不住抖动，突然平刺，剑尖急颤，看不出攻向何处。$P这一招中笼罩了$n上盘七大要穴",
"$N剑招未曾使老，已然圈转。突然之间，$n眼前出现了几个白色光圈，大圈小圈，正圈斜圈，闪烁不已",
});

int super_hit(object me, object victim, object weapon, int damage);

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
      	int i, j, level, damage;
      	string str;
      	
      	level = me->query_skill("taiji-jian", 1);
      	i = random(me->query_skill("force"))+50;
      	if( i<100 ) i = 100;
      	j = random(40)-5;
      	damage = (random(6)+1)*35;
      	if( damage < 50 ) damage =50;

      	if(me->query_temp("tjj/sanhuan")){
          	switch(me->query_temp("tjj/sanhuan")){
                	case 3: str = HIG"$N使出「三环套月」，招式一变，左手抚剑把，右手托剑，剑尖青光闪动，以一个圆弧将$w"HIG"向$n轻轻挑出"NOR; break;
                	case 2: str = HIG"然后$N移进一步，右手左招，左手右招，同样一剑接着挥出，上下连续，不着一点停顿的痕迹"NOR; break;
                	case 1: str = HIG"剑光紧接，$N手中的$w"HIG"又一次挥出急点$n$l，这三剑剑势相联，剑气相叠，剑意相同，正合道家三清之属"NOR; break;
                	default: str = HIG"$N使出「三环套月」，招式一变，左手抚剑把，右手托剑，剑尖青光闪动，以一个圆弧将$w"HIG"向$n轻轻挑出"NOR; break;
                }
          	me->add_temp("tjj/sanhuan", -1);      
          	return ([
                	"action":str, 
                	"damage":damage*2,
                	"damage_type": "刺伤",
                	"dodge": j+40,
                	"force": i*2+random(i),
                ]);
        }
        
        else if( me->query_temp("tj/太极") || level > 350 ){   
        	if( weapon ){
        		switch(weapon->query("material")){
    				case "wood":
    				case "bamboo": 
    				case "paper":
        				weapon->set_temp("no_weapon_cut", 1); break;
        			default: break;
        		}
        	}
        	if( level > 450 )
        		return ([
                		"action": WHT + taiji_msg[random(sizeof(taiji_msg))] + NOR,
                		"damage": level/3 + damage,
                		"damage_type": "刺伤",
                		"dodge":  j+30,
                		"parry":  25 + random(25),
                		"force":  me->query_skill("force") + damage,
                		"post_action": (: super_hit :),
                	]);
        	if( level > 350 )
        		return ([
                		"action": taiji_msg[random(sizeof(taiji_msg))],
                		"damage": level/3+damage/2,
                		"damage_type": "刺伤",
                		"dodge":  j+20,
                		"parry":  25,
                		"force":  me->query_skill("force") + damage,
                		"post_action": (: super_hit :),
                	]);
          	else 	return ([
                		"action": msg[random(sizeof(msg))],
                		"damage": level/4+damage/3,
                		"damage_type": "刺伤",
                		"dodge":  j+10,
                		"force":  i,
                	]);
        }
        
      	else if( me->query_temp("tjj/powerup") >= 1 ){
          	me->add_temp("tjj/powerup", -1);
          	str = HIW+msg[random(sizeof(msg))]+NOR;
          	if(objectp(weapon))
          		str = replace_string(str, "$w", weapon->name()+HIW);       
          	return ([
                	"action":str,
                	"damage":damage*2,
                	"damage_type": "刺伤",
                	"dodge": j+random(20),
                	"force": i*2,
                ]);
        }
      	if(random(50) >= 45) me->add_temp("tjj/powerup", 1);
      	
        return ([
             	"action":msg[random(sizeof(msg))],
             	"damage":damage,
             	"damage_type": "刺伤",
             	"dodge": j,
             	"force": i,
        ]);
             	
}

int super_hit(object me, object victim, object weapon, int damage)
{
     	int ap, dp, lvl;
     	
     	if( random(10) != 5 ){
     		if( !wizardp(me) ) return 0;
     		if( me->query("env/combat") != "verbose")
			return 0;
	}
	
	if( !userp(me) && !me->query("taiji_quest") ) return 0;
	
	lvl = me->query_skill("taiji-jian", 1);
		
     	if(!victim 
     	|| !weapon 
     	|| me->query("neili") < 7000
     	|| lvl < 400
     	|| !present(victim, environment(me)) 
     	|| !victim->is_character() 
     	|| !me->is_fighting(victim) 
     	|| victim->query("env/invisibility")
     	|| !living(victim)
     	|| me->query_skill_mapped("force") != "yinyun-ziqi"
     	|| me->query_skill_mapped("cuff") != "taiji-quan"
     	|| me->query_skill_prepared("cuff") != "taiji-quan"
        || me->query_skill_mapped("parry") != "taiji-jian")
        	return 0;
		   	
     	ap = COMBAT_D->skill_power(me, "cuff", 1)/100;
     	if( lvl >= 450 )
     		ap *= 2;
     	dp = COMBAT_D->skill_power(victim, "parry", 2)/100;
     	
     	if( random( ap + dp ) > dp 
     	&& ((damage == RESULT_DODGE && !victim->query_temp("weapon"))
     	|| (damage == RESULT_PARRY && victim->query_temp("weapon"))) ){
     		me->set_temp("tjj/super_hit", 1);
     		me->set_temp("hit_ob_hit", 1);
     		me->add_temp("apply/damage", lvl/3);
     		victim->set_temp("must_be_hit", 1);
                weapon->unequip();
                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));
                weapon->wield();
                me->delete_temp("tjj/super_hit");
                me->delete_temp("hit_ob_hit");
                me->add_temp("apply/damage", -lvl/3);
                victim->delete_temp("must_be_hit");
	}        
	return 1;
}

int practice_skill(object me)
{
	int i;
    	object weapon = me->query_temp("weapon");
   	i = me->query_skill("taiji-jian", 1);
   	
    	if(!weapon || weapon->query("skill_type") != "sword")
        	return notify_fail("你使用的武器不对。\n");
    	if ((int)me->query("jingli") < 30 + i / 10)
        	return notify_fail("你的体力不够练太极剑法。\n");
        if( i > 450 )
        	i += i/2;
    	me->receive_damage("jingli", 20 + i/10);
    	return 1;
}

int valid_learn(object me)
{
    	mapping fam  = me->query("family");
 
    	if (!mapp(fam) || fam["family_name"] != "武当派" || fam["generation"] != 2)
         	return notify_fail("太极剑只能从武当张三丰处学到。\n");
    	if ((int)me->query("max_neili") < 800)
        	return notify_fail("你的内力不够。\n");
    	if (me->query_skill("taiji-jian", 1) > me->query_skill("yinyun-ziqi", 1)+30)
        	return notify_fail("你的氤氲紫气火候太浅。\n");
    	if (me->query_skill("taiji-jian", 1) > me->query_skill("taiji-quan", 1)+30)
        	return notify_fail("你的太极拳火候太浅。\n");
    	return 1;
}
string perform_action_file(string action)
{
        return __DIR__"taiji-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
    	object weapon, weapon1; 
    	int i;    
    	weapon = me->query_temp("weapon");
    	weapon1= victim->query_temp("weapon");

	if( !objectp(weapon) ) return;
	i = me->query_skill("taiji-jian", 1);
	
    	if(weapon1 && i> 150 && me->query("jiali")
       	&& me->query("max_neili") > 1200 && me->query("neili") > 1000 && random(10) >= 7
       	&& random(me->query_int()) > 30 && !me->query_temp("tjj/powerup")
       	&& me->query_skill_mapped("parry") == "taiji-jian"
       	&& random(me->query("combat_exp")) > victim->query("combat_exp")/3){
      		message_vision(HIM"$N左手剑诀斜引，"+weapon->name()+HIM"画个半圆，平搭在$n"+weapon1->name()+HIM"背脊上，劲力传出，"+weapon1->name()+HIM"登时一沉！\n"NOR, me,victim);
      		if(random(me->query("str")) > victim->query("str")/3){           
           		me->add("neili", -50);
           		message_vision(HIR"$N招式渐见涩滞，只觉得手中"+weapon1->name()+HIR"倒似不断的在增加重量，一个把持不定，脱手飞出！\n"NOR, victim);
           		weapon1->unequip();
           		weapon1->move(environment(victim));
           	}
      		else {
           		message_vision(HIY"$N一招使出，真力运得不足，被"+weapon->name()+HIY"带着连转几个圈子，手中"+weapon1->name()+HIY"一震，险些脱手！\n"NOR, victim);
           		victim->add_busy(3);
           	}
    	}
    	
    	else if( me->query_temp("tj/太极") || i > 350 ){
    		if( i < 350 ) return i/5;
    		switch(weapon->query("material")){
    			case "wood":
    			case "bamboo": 
    			case "paper":
    					if( random(i) > 250 
    					&& !victim->query_temp("lost_attack") 
    					&& !victim->is_busy() 
    					&& random(me->query_int()+me->query_dex()) > random(victim->query_int()*2) ){
    						victim->add_temp("lost_attack", 1+random(3));
    						message_vision(HIC"$P越斗越害怕，被$p带得招式渐见涩滞！\n"NOR, victim, me);
    						i *= 2;
    					}
    					if( i > 450 ) i *= 2;
    				 	i += me->query_skill("force") * 2 + (me->query("jiali") * (10+random(10)));
    					break;
    			default: 	
    					if( i > 450 ) {
    						if( random(i) > 250 
    						&& !victim->query_temp("lost_attack") 
    						&& !victim->is_busy() 
    						&& random(me->query_int()+me->query_dex()) > random(victim->query_int()*2) ){
    							victim->add_temp("lost_attack", 1+random(3));
    							message_vision(HIC"$P越斗越害怕，被$p带得招式渐见涩滞！\n"NOR, victim, me);
    							i += random(i);
    						}
    						i *= 2;
    				 		i += me->query_skill("force") * 2 + (me->query("jiali") * (10+random(10)));
    						break;
    					}
    					else { 
    						i = me->query_str(); 
    						i += random(i);
    						break;
    					}
    		}
    		
    		if( wizardp(me) && (string)me->query("env/combat")=="verbose" ) 
        		tell_object(me, GRN"TJJ i = "+i+" \n"NOR);
    		return i;
    	}
}

int ob_hit(object ob, object me, int damage)
{
        object weapon, wp;
        string msg, wpname,*limbs;
        int ap, dp, j = 0, skill;
        
        if( ob->query("env/invisibility") ) return 0;
        
        if (me->query_skill("yinyun-ziqi", 1) < 80
        || me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill_mapped("parry") != "taiji-jian"
        || me->query("combat_exp") < ob->query("combat_exp")/2) return 0;

        if ( skill = me->query_skill("taiji-jian", 1) < 80) return 0;
        
        if ( me->query("neili") < ob->query("neili")/4 ) return 0;
        
        if ( !objectp(wp = me->query_temp("weapon")) 
        || wp->query("skill_type") != "sword") return 0;
        
        if( skill > 350 || me->query_temp("tj/太极") ){
        	switch(wp->query("material")){
    			case "wood":
    			case "bamboo": 
    			case "paper":
        			wp->add_temp("no_weapon_cut", 1); break;
        		default: break;
        	}
        }
        
      	if( me->query_temp("fanzhen")){
         	me->delete_temp("fanzhen");
         	return 1;
        }
        
        if ( objectp(weapon = ob->query_temp("weapon")) ) 
        	msg = weapon->query("skill_type");
        else {
                mapping prepare = ob->query_skill_prepare();
                if (!sizeof(prepare)) msg = "unarmed";
                else msg = keys(prepare)[0];
        }
        
        ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 100;
        if ( !weapon ) ap *= 2;
        if ( ob->query("neili") > me->query("neili") * 2 ) ap *= 2;
        
        dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 100;
        if ( me->query_temp("tj/太极") ) dp *= 2;
        if ( random(10) < 3 ) me->set_temp("fanzhen", 1);   

	ap = ABS(ap);
        dp = ABS(dp);
        if ( skill > 350 ) dp += random(dp);
        if ( skill > 450 ) dp *= (2 + random(2));
        
	wpname = wp->name();
	        
        if ( random( dp ) > ap ) { 
        	limbs = ob->query("limbs");
        	if( weapon ) {
        		msg = parry_msg[random(sizeof(parry_msg))];
        		msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
        		msg = replace_string(msg, "$W", weapon->name());
        		msg = replace_string(msg, "$w", wpname);
         		message_vision(msg, ob, me);
         	}
        	
         	else {
         		msg = "$N不紧不满将"+wpname+"一立，锋刃正挡在$n的招式前方，";
         		if( random(me->query_skill("taiji-jian", 1)) > ob->query_skill("parry") ){
         			msg += "$n大吃一惊，来不及收招，自己打在了锋刃之上！\n";
         			ob->receive_damage("qi", damage/3 , me);
              			ob->receive_wound("qi", damage/3 , me);
              			j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              			msg += damage_msg(damage, "割伤") + "( $n"+eff_status_msg(j)+" )\n";
              			msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                   		msg = replace_string(msg, "$w", "锋刃");
                   	}
                   	else msg += "$n大吃一惊，连忙收招站开！\n";
                   	message_vision(msg, me, ob);
         	}	
              	return -50000;
        }
        
        else if( random(ap + dp) > ap ) {
        	if( weapon ) msg = "$N情急之下将"+wpname+"一拉，平贴在"+weapon->name()+"之上，用四两拨千斤之巧劲卸掉了$p一部分劲力！\n";
         	else msg = "$N连忙将"+wpname+"一横，挡住了$n一部分力量！\n";  
              	j = -damage/2;               
        }
        
        else if( random(ap + dp + dp) > ap ) {
        	if( weapon ) msg = "$N集中生智，用"+wpname+"将"+weapon->name()+"一拨，用卸力之法卸掉了一些劲力！\n";
         	else msg = "$N慌忙中用"+wpname+"拍出，刚好拍开了$n一部分的劲力！\n";  
         	j = -damage/4; 
        } 
        
        else return 0;
        
        message_vision(msg, me, ob);
        return j;
       	          
}


