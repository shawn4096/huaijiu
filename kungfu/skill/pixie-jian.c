// pixie-jian.c 辟邪剑法
// by snowman 22/11/98
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
"突然之间，白影急幌，$n向后滑出丈余，立时又回到了原地，躲过了$N这一招。\n",
"$n手臂回转，在$N手肘下一推，顺势闪到一旁。\n",
"$n右手伸出，在$N手腕上迅速无比的一按，顺势跳到一旁。\n",
"$n身形飘忽，有如鬼魅，转了几转，移步到$N的身后，躲过了$N这一招。\n",
"$N只觉眼前一花，似乎见到$n身形一幌，但随即又见$n回到原地，却似从未离开。\n",
"$N眼睛一花，$n已没了踪影。突然$n从身后拍了一下$N的头，轻轻跃开。\n",
"$n嫣然一笑，诡异之极，$N竟不知如何是好，停住了攻击。\n",
"$n左一拨，右一拨，上一拨，下一拨，将$N的招数尽数拨开。这四下拨挡，周身竟无半分破绽。\n",
"$n右手大拇指和食指捏住一根绣花针，向上一举，挡住来势，$N的招式便使不下去。\n",
"$n不挡不闪，左手食指颤动，向$N的左目急刺，竟是两败俱伤的打法！\n",
"$n左拨右挡，兀自好整以暇的啧啧对$N连赞：“好功夫，好功夫！”\n",
});


string  *msg = ({
"$N身形一变，如闪电般欺到$n身前，相距不过一尺，手中$w已经刺到$n的$l",
"但见红影闪处，$N手中的$w向$n的$l直戳而来，势如奔雷，避不可避",
"$N欺身而上，左手在$n的肩上一拍再横飞出去，而手中的$w却指向$n的$l",
"$N突然跃起丈余，$n一抬头，发现空中并无$N的身影，而一股寒气却从身后袭来",
"$N左一拨，右一拨，上一拨，下一拨，将$n的招数尽数拨开，右手一转，刺向$n",
"蓦地里$N空手猱身而上，双手擒拿点拍，攻势凌厉之极，乘$n惊骇之际弹出$w刺向$n",
"$N身形飘忽，有如鬼魅，转了几转，移步向西，一剑刺向$n。出手之奇之快，直是匪夷所思",
"$N脚下一顿，站立片刻，忽向$n的左后方滑出丈余，跟着快速无伦的回到原处",
"$N潜运内力，忽进忽退，绕着$n身子乱转，手中$w所使剑招也如狂风骤雨一般，越来越快",
"突然$N手中$w向上一撩，就在$n微一分神之际直取$n的$l，势道劲急无伦",
"就在$n一呆之际，$N向右跃开两尺，右足刚著地，身子跟著弹起，刷刷两剑，向$n攻去",
"$N忽然化身为二，幻出左右两个身影高速滑向$n，手中$w幻化不定，招招紧逼$n的$l",
"$n只觉眼前一花，似乎见到$N身形一幌，但随即又见$N回到原地，却似从未离开",
"$N一声尖叫，飞身纵起，在半空中一转，快绝无比的飞落下来，手中$w破空直刺$n$l",
"$N的身形如鬼如魅，飘忽来去，直似轻烟，手中的$w却总是对着$n身子",
"$N一声冷笑，蓦地里疾冲上前，当真是动如脱兔，一瞬之间，与$n相距已不到一尺，两人的鼻子几乎要碰在一起",
"$N右手伸出，在$n手腕上迅速无比的一按，跟着手臂回转，又在$n手肘下一推",
"$N一剑挺刺，极尽都雅，神态之中，竟大有华山派女弟子所学‘玉女剑十九式’的风姿，只是带着三分阴森森的邪气",
"$N左手一圈，倒转$w，蓦地刺出，刷刷刷急攻三式，招招尽是指向$n的要害"
});


mapping *action = ({
([      "action":"突然之间，白影急幌，$N向后滑出丈余，立时又回到了原地",
        "force" : 90,
        "dodge" : 50,
        "damage": 70,
        "lvl" : 0,
        "skill_name" : "白影急幌",
        "damage_type":  "刺伤"
]),
([      "action":"$N右手伸出，在$n手腕上迅速无比的一按，$n险些击中自己小腹",
        "force" : 100,
        "dodge" : 50,
        "damage": 60,
        "lvl" : 10,
        "skill_name" : "自己小腹",
        "damage_type":  "刺伤"
]),
([      "action":"蓦地里$N猱身而上，蹿到$n的身后刺出一剑，又在瞬间跃回原地",
       "force" : 120,
        "dodge" : 45,
        "damage": 70,
        "lvl" : 20,
        "skill_name" : "猱身而上",
        "damage_type":  "刺伤"
]),
([      "action":"$n只觉眼前一花，似乎见到$N身形一幌，但随即又见$N回到原地，却似从未离开",
        "force" : 145,
        "dodge" : 45,
        "damage": 75,
        "lvl" : 30,
        "skill_name" : "眼前一花",
        "damage_type":  "刺伤"
]),
([      "action":"$N突然间招法一变，一招「江上弄笛」，$w忽伸忽缩，招式诡奇绝伦。$n惊骇之中方寸大乱",
        "force" : 150,
        "dodge" : 43,
        "damage": 90,
        "lvl" : 40,
        "skill_name" : "招法一变",
        "damage_type":  "刺伤"
]),
([      "action":"$N向后疾退，$n紧追两步，突然间$N闪到$n面前，一招「花开见佛」，手中$w直指$n的$l",
        "force" : 140,
        "dodge" : 50,
        "damage": 100,
        "lvl" : 50,
        "skill_name" : "向后疾退",
        "damage_type":  "刺伤"
]),
([      "action":"$N身形飘忽，有如鬼魅，转了几转，一招「紫气东来」，移步到$n的左侧",
        "force" : 170,
        "dodge" : 45,
        "damage": 95,
        "lvl" : 60,
        "skill_name" : "有如鬼魅",
        "damage_type":  "刺伤"
]),
([      "action":"$N一声冷笑，一招「流星赶月」，蓦地里疾冲上前，一瞬之间，与$n相距已不到一尺，$w随即递出",
        "force" : 140,
        "dodge" : 35,
        "damage": 110,
        "lvl" : 70,
        "skill_name" : "疾冲上前",
        "damage_type":  "刺伤"
]),
([      "action":"$N喝道：“好！”，便即拔出$w，一招「飞燕穿柳」，反手刺出，跟着转身离去",
        "force" : 205,
        "dodge" : 35,
        "damage": 120,
        "lvl" : 80,
        "skill_name" : "反手刺出",
        "damage_type":  "刺伤"
]),
([      "action":"$N蓦地冲到$n面前，一招「锺馗抉目」，手中$w直刺$n右眼！$n慌忙招架，不想$N的$w突然转向",
        "force" : 240,
        "dodge" : 50,
        "damage": 145,
        "lvl" : 90,
        "skill_name" : "直刺右眼",
        "damage_type":  "刺伤"
]),
([      "action":"$N飞身跃起，$n抬眼一望，但见得$N一招「流星飞堕」，从天直落而下，手中$w刺向$n的$l",
        "force" : 270,
        "dodge" : 60,
        "damage": 170,
        "lvl" : 100,
        "skill_name" : "飞身跃起",
        "damage_type":  "刺伤"
]),
([      "action":"$N一招「群邪辟易」，腰枝猛摆，$n眼前仿佛突然出现了七八个$N，七八只$w一起刺向$n",
        "force" : 300,
        "dodge" : 75,
        "damage": 200,
        "lvl" : 110,
        "skill_name" : "群邪辟易",
        "damage_type":  "刺伤"
]),
});


int valid_enable(string usage) 
{ 
    return usage == "sword" || usage == "dodge" || usage == "parry"; 
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
        int i, level, neili, force;
        level   = (int) me->query_skill("pixie-jian",1);
        force = me->query_skill("force");
        neili = me->query("neili");

        if (level > 120 && force > 180 && neili > 300 
            && me->query("max_neili") > 1200
            && random(me->query_dex()) > 25){
            return([      
                   "action": msg[random(sizeof(msg))],                   
                   "force" : force+random(force),
                   "dodge" : 20+random(60),
                   "parry" : 20+random(60),
                   "damage": me->query_temp("cimu")?force/2+random(force):force,
                   "damage_type" : "刺伤",
                   ]);
            }
           for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

string query_parry_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
       if (me->query_skill("pixie-jian",1) >= 180) return 1;
        return notify_fail("辟邪剑法只能通过研习《葵花宝典》来学习。\n");
}

string perform_action_file(string action)
{
        return __DIR__"pixie-jian/" + action;
}


int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("你的精力不够。\n");
       if (me->query_skill("pixie-jian",1) < 180) return 0;
        me->receive_damage("jingli", 30);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
   	object weapon = me->query_temp("weapon");

    	if (!weapon) return;
   	if(((string)weapon->query("id")=="xiuhua zhen" || (string)weapon->query("id")=="qijue zhen")  
      	&& random(me->query_str()) > victim->query_str()/2){
		victim->receive_wound("qi", me->query_str()+random(80));
		if (random(5) > 3) return HIR "只听「嗤」一声，一缕血丝从"+victim->name()+"被刺的针孔处喷出！\n" NOR;
	}
}

int double_attack(object me)
{	
   	if ( me->query_skill("pixie-jian", 1) >= 60
     	&& me->query_skill_mapped("sword") == "pixie-jian"
     	&& me->query("gender") == "无性")
             	return 1;
}
	
