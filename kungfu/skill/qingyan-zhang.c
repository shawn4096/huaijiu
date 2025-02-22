// qingyan-zhang.c 五罗轻烟掌
//cool@SJ,9905027 

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N向后飘出尺许，转过身来，一招「五陵烟云」忽地左掌向后斜劈，飕的一声轻响切向$n的$l",
        "skill_name" : "五陵烟云",
        "damage_type": "瘀伤"
]),

([      "action": "$N起手一式「烟雾弥漫」，右掌向后斜劈，荡起一股微风抚向$n的$l，不带丝毫霸气",
        "skill_name" : "烟雾弥漫",
        "damage_type": "瘀伤"
]),

([      "action": "$N微微一笑，出掌按向$n的$l，如行云、如流水，潇洒之极，正是那招「烟雨朦胧」",
        "skill_name" : "烟雨朦胧",
        "damage_type": "瘀伤"
]),

([  "action": "$N抬起头来，目不转瞬的向$n凝视，接着轻飘飘一转身「烟飘云散」左右两掌往后拍出",
        "skill_name" : "烟飘云散",
        "damage_type": "瘀伤"
]),

([  "action": "$N身形随风飘动，一式「五罗轻烟」左右轻拍连出五掌，五丝轻风绕过$N的身子悄然向$n的$l袭去",
        "skill_name" : "五罗轻烟",
        "damage_type": "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }


string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i,a,b,level;
		string msg;
        level   = (int) me->query_skill("qingyan-zhang",1);
        if (level>100) a=100;
                  else a=level;
        b=level/30;
		if (b>5) b=5;
		    
			 if(me->query_temp("fenglei")){
          switch(me->query_temp("fenglei")){
             case 4: msg = HIW"$N左手向前斜劈，一道锐利的掌风划过空气，＂哗＂的一声在$n的身前散成"+chinese_number(b)+"道掌力，分袭各处要害．\n" NOR;break;
			 case 3: msg = HIW"$N凌空下击，回剑入鞘，右掌向左一削，左掌向右一砍，两道交叉的无形掌力，直逼$n身前要害．\n" NOR;break;
             case 2: msg = HIW"$N人在空中，掌法使的行云流水，＂叭＂的一声，一掌按出，又是"+chinese_number(b)+"道掌力分散开笼罩$n的全身．\n" NOR; break;
			 case 1: msg = HIW"$N袖子一摆，掌式轻柔，犹如风中落叶，连拍"+chinese_number(b)+"下，数道掌力交织成一道无形的气网，缓缓推向$n．\n"NOR;break;
             default: msg = HIW"$N袖子一摆，掌式轻柔，犹如风中落叶，连拍"+chinese_number(b)+"下，数道掌力交织成一道无形的气网，缓缓推向$n．\n" NOR; break;
          }
          me->add_temp("fenglei", -1);
              return ([
                "action":msg,
                "damage_type":"内伤",
                "dodge": random(20)+20, 
                "force": 150+a+random(50)+b*40,
                "parry": random(5)-random(20),
                "skill_name" : "潇湘烟雨",
              ]);
     
		}	
			
		for(i = sizeof(action); i > 0; i--) {
           if(level > action[i-1]["lvl"]) {
             return ([
                "action":action[NewRandom(i, 20, level/5)]["action"],
                "damage_type": action[NewRandom(i, 20, level/5)]["damage_type"],
                "dodge": 10+random(15),
                "force": 150+a+random(100),
                "parry": random(20)-random(20),
                "skill_name" : action[NewRandom(i, 20, level/5)]["skill_name"],
             ]);
           }
        }
     }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
            return notify_fail("空了手才能练习五罗轻烟掌。\n");
       
        if(!me->query_skill("kurong-changong", 1))
           if (!me->query_skill("qiantian-yiyang", 1)) 
                   return notify_fail("练五罗轻烟掌需要有乾天一阳功的支持。\n");
       
        if (!me->query_skill("kurong-changong", 1))
            if ((int)me->query_skill("qiantian-yiyang", 1) < 10 )
                   return notify_fail("你的乾天一阳功根基不够。\n");

        if ((int)me->query("max_neili") < 100)
            return notify_fail("你内力修行太差, 练不了五罗轻烟掌掌。\n");
        return 1;
}

int practice_skill(object me)
{
       if(!me->query_skill("kurong-changong", 1))
          if (!me->query_skill("qiantian-yiyang", 1))
               return notify_fail("练五罗轻烟掌需要有乾天一阳功的支持。\n");
       if ((int)me->query("jingli") < 30)
               return notify_fail("你的体力太低了。\n");
       if ((int)me->query("neili") < 40)
               return notify_fail("你的内力不够练五罗轻烟掌掌。\n");
       me->receive_damage("jingli", 20);
       me->add("neili", -5);
       return 1;
}
