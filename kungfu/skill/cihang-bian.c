//慈航鞭,
//取自普明禅师<牧牛图颂>
//cool@SJ,990420

#include <ansi.h>

inherit SKILL;

string *body_name = ({ 
"左手腕","左胳膊","脖子","头部","腰部","左腿","小腿","左脚脚腕","右手腕","右胳膊","右腿","右脚脚腕",}); 

mapping *action = ({
([ "action": "$N双手合什，内力灌注, 一式「未牧」，腰间$w似有灵性，忽地一转，卷向$n的$l",
   "skill_name" : "未牧",
   "damage_type":  "拉伤",
]),
([ "action": "$N沉肩滑步，手中$w一抖，一式「初调」，迅捷无比地分打左右两侧，$n顿时左右支绌，慌了手脚",
   "skill_name" : "初调",
   "damage_type":  "拉伤"
]),
([ "action": "$N将内力注入$w，蓦地使出一式「受制」，$w矫夭飞舞，直如神龙破空一般抽向$n",
   "skill_name" : "受制",
   "damage_type":  "拉伤"
]),

([ "action": "$N一声清啸，手中$w一招「回首」，划出漫天鞭影铺天盖地地向$n卷来，势道猛烈之极",
   "skill_name" : "回首",
   "damage_type":  "拉伤"
]),
([ "action": "$N急速旋绕手中$w，一式「驯服」，挥出无数旋转气流向$n逼去 ",
   "skill_name" : "驯服",
   "damage_type":  "拉伤"
]),
([ "action": "$N身体凌空飞起，右手大力挥出$w，一式「无碍」，一股排山倒海的鞭风直击向$n",
   "skill_name" : "无碍",
   "damage_type":  "拉伤"
]),
([ "action": "$N面露微笑跨前一步，右手$w轻扬，使出一式「任运」，鞭势平和中正，不带丝毫霸气",
   "skill_name" : "任运",
   "damage_type":  "拉伤"
]),
([ "action": "$N向前急进，双手握住$w，缓缓使出一式「相望」，鞭势沉稳, 一股劲风破空而起",
   "skill_name" : "相望",
   "damage_type":  "拉伤"
]),
([ "action": "$N狂舞手中$w，一式「独照」，鞭若蛟龙, 盘旋飞舞",
    "skill_name" : "独照",
   "damage_type":  "拉伤"
]),
([ "action": "$N身体螺旋飞舞，手中$w突然挥出，使出一式「双泯」，鞭势犹如雨中闪电,气势惊人",
   "skill_name" : "双泯",
   "damage_type":  "拉伤"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_neili") < 800 )
               return notify_fail("你的内力不足，没有办法练习鞭法, 多练些内力再来吧。\n");

       if ((int)me->query_skill("kurong-changong", 1) < 20)
               return notify_fail("你的枯荣禅功修为不够。\n");

       if ( !objectp(weapon = me->query_temp("weapon"))
        ||( string)weapon->query("skill_type") != "whip" )
               return notify_fail("你必须先找一条鞭子才能练鞭法。\n");
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
             		case 3: msg = MAG"但见$N身形朝前一冲， 手中"+ weapon->name()+MAG"抽向你的小腹" NOR; break;
             		case 2: msg =HIY"紧跟着$N把内力运在"+ weapon->name()+ "，"+ weapon->name()+HIY"如判官笔般点向$n的前心" NOR;break;
             		case 1: msg = HIW"最后$N向上高高一跃，发了疯般挥舞"+ weapon->name()+HIW "向着$n发起攻击" NOR; break;
             		default: msg = HIW"最后$N向上高高一跃，发了疯般挥舞"+ weapon->name()+HIW"向着$n发起攻击" NOR; break;
          	}
          	a = me->query_str() * 2 + random(me->query("jiali")/2);
          	me->add_temp("chb", -1);
              	return ([
                	"action":	msg,
                	"damage":	a, 
                	"damage_type": 	"拉伤",
                	"dodge": me->query_dex(), 
                	"force": (a + me->query_skill("force", 1)) / 2,
              	]);
        }
        for(i = sizeof(action); i > 0; i--) {
        	a = NewRandom(i, 20, level/5);
              	return ([
                	"action":	action[a]["action"],
                	"damage": 	me->query_str(), 
                	"damage_type": 	"拉伤",
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
           	return notify_fail("你使用的武器不对。\n");
      	if ((int)me->query_skill("kurong-changong",1) < 100)
               	return notify_fail("慈航鞭法以枯荣禅功为根基,你不会枯荣禅功,无法修练慈航鞭。\n");
       	if ((int)me->query("jingli") < 50)
               	return notify_fail("你的体力不够练慈航鞭法。\n");
       	if ((int)me->query("neili") < 50)
               	return notify_fail("你的内力不够练慈航鞭法。\n");
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
               		message_vision(HIY "只见$N急速挥舞" + weap1->name() + "，转出无数个大小圈子，以阴柔之劲缠住对方的" + weap->name() +"！\n" NOR, me ); 
               		if (random(me->query_skill("parry", 1)) > victim->query_skill("parry", 1)/2 ){       
                 		message_vision(HIY "$N气运手臂用力一拽，" + weap->name()
                                	+ "却无法从"+weap1->name()+"的缠绕中脱开，情急之下只好放弃了手中的兵刃。\n" NOR, victim );
                 		weap->unequip();
                 		weap->move(environment(me));
                 		victim->reset_action();
               		}
               		else {
                 		message_vision(HIY "$N暗运巧劲，" + weap->name()
                                	+ "顺着方向快速旋转数下，解开了"+weap1->name()+"的缠绕。\n" NOR, victim );
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
            		message_vision(HIY "只见$N的鞭式灵动异常，"
				+ weap1->name() + "转出无数个大小圈子，以阴柔之劲缠住了对方的"
				+ body_name[random(sizeof(body_name))] +"！\n" NOR, me);
               		message_vision(HIR "$N身形一缓,似乎受了点伤。\n" NOR, victim );    
           	}             
        }
        return;
}

string perform_action_file(string action)
{
               return __DIR__"cihang-bian/" + action;
}
